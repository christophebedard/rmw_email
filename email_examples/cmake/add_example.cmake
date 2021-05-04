# Copyright 2020-2021 Christophe Bedard
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

#
# Add executable, target project lib and install an example.
#
# :param name: the name of the example
#   (name of the .cpp file under the src/ directory;
#   will be used as the executable name)
# :type name: string
#
macro(add_example name)
  add_executable(${name}
    src/${name}.cpp
  )
  ament_target_dependencies(${name}
    email
  )
  install(TARGETS
    ${name}
    DESTINATION lib/${PROJECT_NAME}
  )
endmacro()
