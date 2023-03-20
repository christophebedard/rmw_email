#!/bin/bash
# Copyright 2021 Christophe Bedard
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# performance_test experiment and comparison for rmw_email_cpp
# This script runs performance_test for:
#   1. rmw_cyclonedds_cpp
#   2. rmw_email_cpp
#   3. rmw_email_cpp (intraprocess enabled)
# Notes:
#   * run with 'sudo' if using realtime mode (using '--use-rt-prio' or '--use-rt-cpus')
#      $ sudo chrt --fifo 99 ./perf_test.sh
#      * when running with sudo, you may need to manually pass *PATH environment variables for shared libraries to be found
#         $ sudo env PATH="$PATH" LD_LIBRARY_PATH="$LD_LIBRARY_PATH" ./perf_test.sh
#         * see https://unix.stackexchange.com/a/251374
#   * this script expects 3 email different config files:
#      1. send.email.yml: configured to send emails from A to B
#      2. receive.email.yml: configured to send emails from B to A
#      3. intra.email.yml: configured to enable intraprocess, no other values necessary
# Workspace setup:
#   $ mkdir -p ws/src
#   $ cd ws
#   $ vcs import src --input https://raw.githubusercontent.com/ros2/ros2/rolling/ros2.repos
#   $ vcs import src --input https://raw.githubusercontent.com/christophebedard/rmw_email/rolling/dependencies.repos
#   $ cd src
#   $ git clone https://github.com/christophebedard/rmw_email.git
#   $ git clone https://gitlab.com/ApexAI/performance_test.git
#   $ cd ..
#   $ colcon build --packages-up-to performance_test --mixin release
#   $ source install/setup.sh

message="Array1k"
max_runtime=65
ignore=5
rate=1
comm="rclcpp-single-threaded-executor"

is_realtime_ish=0
no_smt=1

as_root=0
if [ "$EUID" -eq 0 ]; then
  as_root=1
fi

rt_run_options_p=""
rt_run_options_s=""
if [ ${is_realtime_ish} -eq 1 ]; then
  # Make sure SMT/hyperthreading is disabled
  smt_active=$(cat /sys/devices/system/cpu/smt/active)
  if [ ${no_smt=1} -eq 1 ] && [ "$smt_active" -eq 1 ]; then
    echo "SMT is active!"
    echo "  Disable it by running:"
    echo "    sudo bash -c 'echo off > /sys/devices/system/cpu/smt/control'"
    echo "  Or by adding 'nosmt' to GRUB_CMDLINE_LINUX in /etc/default/grub, then running:"
    echo "    sudo update-grub && sudo reboot -h now"
    exit 1
  fi

  # Masks:
  #   CPUs 0-1: 3
  #   CPUs 2-3: 12
  # Priority:
  #   highest RT priority: 99
  #     https://stackoverflow.com/a/52501811
  #     also: sudo chrt --fifo 99 ./perf_test.sh
  rt_run_options_p="--use-rt-prio 99"
  rt_run_options_s="--use-rt-prio 99"
  # rt_run_options_p="--use-rt-prio 99 --use-rt-cpus 3"
  # rt_run_options_s="--use-rt-prio 99 --use-rt-cpus 12"

  if [ ${as_root} -ne 1 ]; then
    echo "Please run as root to use RT settings"
    echo "  sudo ./perf_test.sh"
    echo "You may also need to manually pass *PATH environment variables, see: https://unix.stackexchange.com/a/251374"
    echo "  sudo env PATH="$PATH" LD_LIBRARY_PATH="$LD_LIBRARY_PATH" ./perf_test.sh"
    exit 1
  fi
fi

# Print params and write to file so that they are kept alongside the results
timestamp=`date +%Y-%m-%dT%H:%M:%S`
policy=`chrt -p $$`
params="\
Params: ${timestamp}
message         = ${message}
max_runtime     = ${max_runtime}
ignore          = ${ignore}
rate            = ${rate}
comm            = ${comm}
is_realtime_ish = ${is_realtime_ish}
no_smt          = ${no_smt}
cmd             = $0 $*
as_root         = ${as_root}
policy          = ${policy}
"
echo -e "${params}"
echo -e "${params}" > perf_params

function run_experiment() {
  local rmw_impl=$1
  local config_file_p="send.email.yml"
  local config_file_s="receive.email.yml"
  local is_intraprocess=0
  if [ ! -z "$2" ]; then
    is_intraprocess=1
    config_file_p="intra.email.yml"
    config_file_s="intra.email.yml"
  fi
  logfile_base="perf_${rmw_impl}_"

  export RMW_IMPLEMENTATION="${rmw_impl}"
  echo "RMW_IMPLEMENTATION=${RMW_IMPLEMENTATION}"

  if [ ${is_intraprocess} -eq 0 ]; then
    # Interprocess
    echo "EMAIL_CONFIG_FILE={${config_file_p},${config_file_s}}"
    run_cmd_p="\
        ./install/performance_test/lib/performance_test/perf_test \
        -c ${comm} -p 1 -s 0 -r ${rate} -m ${message} --max-runtime ${max_runtime} --ignore ${ignore} -o csv --csv-logfile ${logfile_base}pub ${rt_run_options_p}"
    run_cmd_s="\
        ./install/performance_test/lib/performance_test/perf_test \
        -c ${comm} -p 0 -s 1 -r ${rate} -m ${message} --max-runtime ${max_runtime} --ignore ${ignore} -o csv --csv-logfile ${logfile_base}sub ${rt_run_options_s}"
    echo -e "running:\n  ${run_cmd_p} &\n  ${run_cmd_s}"

    export EMAIL_CONFIG_FILE=${config_file_p}
    ${run_cmd_p} &
    pid_p=$!

    export EMAIL_CONFIG_FILE=${config_file_s}
    ${run_cmd_s} &
    pid_s=$!

    wait ${pid_p}
    wait ${pid_s}
  else
    # Intraprocess
    echo "EMAIL_CONFIG_FILE=${config_file_p}"
    run_cmd_ps="\
        ./install/performance_test/lib/performance_test/perf_test \
        -c ${comm} -p 1 -s 1 -r ${rate} -m ${message} --max-runtime ${max_runtime} --ignore ${ignore} -o csv --csv-logfile ${logfile_base}intra ${rt_run_options_s}"
    echo -e "running:\n  ${run_cmd_ps}"

    export EMAIL_CONFIG_FILE=${config_file_p}
    ${run_cmd_ps}
  fi

  echo
}

run_experiment "rmw_cyclonedds_cpp"
run_experiment "rmw_email_cpp"
run_experiment "rmw_email_cpp" intraprocess
