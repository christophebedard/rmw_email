#!/usr/bin/env python3
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

"""Helper script to plot and compare performance_test experiments."""

from typing import Dict
from typing import List
from typing import Tuple

from apex_performance_plotter.load_logfiles import load_logfile
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

cyclonedds = 'rmw_cyclonedds_cpp'
email = 'rmw_email_cpp'
email_intra = 'rmw_email_cpp (intraprocess)'

# RMW implementation --> experiment results file name
experiment_files = {
    cyclonedds: 'perf_rmw_cyclonedds_cpp_sub',
    email: 'perf_rmw_email_cpp_sub',
    email_intra: 'perf_rmw_email_cpp_intra',
}
# RMW implementation --> experiment results colour
colours = {
    cyclonedds: 'green',
    email: 'blue',
    email_intra: 'lightblue',
}

include_plot_title = True
save_plots = True


def filter_invalid_values(time, received, latency_means) -> Tuple[np.array, np.array, np.array]:
    assert len(time) == len(latency_means)
    new_time = []
    new_received = []
    new_latency_means = []
    for i in range(len(time)):
        value_time = time[i]
        value_received = received[i]
        value_latency_mean = latency_means[i]
        # Only keep data for this iteration if there were messages
        # (inf/-inf values (from csv files) are converted to 0 when imported by pandas)
        if value_latency_mean > 0:
            new_time.append(value_time)
            # Adding 1 to work around: https://gitlab.com/ApexAI/performance_test/-/issues/126
            new_received.append(1 + value_received)
            new_latency_means.append(value_latency_mean)
    return np.array(new_time), np.array(new_received), np.array(new_latency_means)


def get_data(run_dataframe: pd.DataFrame) -> Tuple[np.array, np.array, np.array]:
    return filter_invalid_values(
        run_dataframe['T_experiment'],
        run_dataframe['received'],
        run_dataframe['latency_mean (ms)'],
    )


def compute_latency_mean(received: np.array, latency_means: np.array) -> float:
    # Weighted mean using number of received messages
    return (received * latency_means).sum() / received.sum()


def format_latex(string: str) -> str:
    return string.replace('_', r'\_')


def format_filename(string: str) -> str:
    string = string.replace('(', '')
    string = string.replace(')', '')
    string = string.replace(' ', '_')
    return string


def get_sub_dict(keys: List[str], d: Dict[str, str]) -> Dict[str, str]:
    return {key: d[key] for key in d.keys() if key in keys}


def plot_single_rmw_implementation(rmw_implementation_name: str) -> None:
    """
    Plot the results of a single experiment.

    :param rmw_implementation_name: the RMW implementation name
    """
    fig, ax = plt.subplots(1, 1)

    run_file = experiment_files[rmw_implementation_name]
    _, dataframe = load_logfile(run_file)
    time, received, latency_means = get_data(dataframe)
    ax.plot(time, latency_means, 'o-', color=colours[rmw_implementation_name])

    title = f'Latency result for {format_latex(rmw_implementation_name)}'
    if include_plot_title:
        ax.set(title=title)
    ax.set(xlabel='time (s)')
    ax.set(ylabel='mean latency (ms)')
    ax.grid()

    if save_plots:
        filename = f'figure_1-{rmw_implementation_name}'
        filename = format_filename(filename)
        fig.savefig(f'{filename}.png', bbox_inches='tight')
        fig.savefig(f'{filename}.svg', bbox_inches='tight')


def plot_comparison(
    selected_experiment_files: Dict[str, str],
    bbox_to_anchor: Tuple[float, float],
    legend_loc: str = 'center',
) -> None:
    """
    Create a plot to compare RMW implementations.

    :param selected_experiment_files: a { implementation name: experiment results file name } dict
        of RMW implementations to compare
    :param bbox_to_anchor: (x, y) coordinates for the legend wrt x, y axes
        (0,0) is lower left, (1,1) is top right
        some manual adjustments might be required
    :param legend_loc: the 'loc' param value for the legend
    """
    fig, ax = plt.subplots(1, 1)

    legends = []
    for rmw_implementation_name, run_file in selected_experiment_files.items():
        _, dataframe = load_logfile(run_file)
        time, received, latency_means = get_data(dataframe)
        ax.plot(time, latency_means, 'o-', color=colours[rmw_implementation_name])
        mean_latency = compute_latency_mean(received, latency_means)
        legends.append(
            fr'{format_latex(rmw_implementation_name)} ($\approx$ {mean_latency:.2f} ms)')

    title = 'RMW implementations latency comparison'
    if include_plot_title:
        ax.set(title=title)
    ax.set(xlabel='time (s)')
    ax.set(ylabel='mean latency (ms)')
    ax.legend(legends, loc=legend_loc, bbox_to_anchor=bbox_to_anchor)
    ax.grid()

    if save_plots:
        filename = 'figure_2-comparison_' + '-'.join(selected_experiment_files.keys())
        filename = format_filename(filename)
        fig.savefig(f'{filename}.png', bbox_inches='tight')
        fig.savefig(f'{filename}.svg', bbox_inches='tight')


def main():
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', size=14)
    plt.rc('axes', titlesize=20)
    plt.rc('legend', fontsize=14)

    plot_single_rmw_implementation('rmw_cyclonedds_cpp')
    plot_single_rmw_implementation('rmw_email_cpp')
    plot_single_rmw_implementation('rmw_email_cpp (intraprocess)')

    plot_comparison(
        get_sub_dict(['rmw_cyclonedds_cpp', 'rmw_email_cpp'], experiment_files),
        (0.6, 0.2),
    )
    plot_comparison(
        get_sub_dict(['rmw_cyclonedds_cpp', 'rmw_email_cpp (intraprocess)'], experiment_files),
        (0.5, 0.4),
    )

    plt.show()


if __name__ == '__main__':
    main()
