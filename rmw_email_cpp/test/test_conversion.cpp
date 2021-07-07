// Copyright 2021 Christophe Bedard
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <iostream>
#include <string>

#include "builtin_interfaces/msg/time.h"
#include "dynmsg/message_reading.hpp"
#include "dynmsg/msg_parser.hpp"
#include "dynmsg/typesupport.hpp"
#include "std_msgs/msg/string.h"
#include "std_msgs/msg/header.h"

TEST(TestConversion, std_msgs__string)
{
  // Start with a ROS message, like a std_msgs/String
  char data[] = "hello world";
  std_msgs__msg__String msg{
    // rosidl_runtime_c__String
    {
      data,
      11,
      12
    },
  };

  // Convert it to a YAML representation
  InterfaceTypeName interface{"std_msgs", "String"};
  RosMessage ros_msg;
  ros_msg.type_info = get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  YAML::Emitter emitter;
  emitter << YAML::DoubleQuoted << YAML::Flow << yaml_msg;
  const std::string yaml_string(emitter.c_str());
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;
  ASSERT_STREQ(yaml_string.c_str(), "{\"data\": \"hello world\"}");

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<std_msgs__msg__String *>(ros_msg_from_yaml.data);
  rosidl_runtime_c__String msg_from_yaml_str = msg_from_yaml->data;
  std::cout << msg_from_yaml_str.data << std::endl;
  ASSERT_STREQ(msg_from_yaml_str.data, "hello world");
}

TEST(TestConversion, std_msgs__header)
{
  // Start with a ROS message, like a std_msgs/Header
  char data[] = "my_frame";
  std_msgs__msg__Header msg{
    // builtin_interfaces__msg__Time
    {
      4,
      20
    },
    // rosidl_runtime_c__String
    {
      data,
      8,
      9
    },
  };

  // Convert it to a YAML representation
  InterfaceTypeName interface{"std_msgs", "Header"};
  RosMessage ros_msg;
  ros_msg.type_info = get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  YAML::Emitter emitter;
  emitter << YAML::DoubleQuoted << YAML::Flow << yaml_msg;
  const std::string yaml_string(emitter.c_str());
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;
  ASSERT_STREQ(
    yaml_string.c_str(),
    "{\"stamp\": {\"sec\": \"4\", \"nanosec\": \"20\"}, \"frame_id\": \"my_frame\"}");

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = yaml_to_rosmsg(interface, emitter.c_str());
  auto msg_from_yaml = reinterpret_cast<std_msgs__msg__Header *>(ros_msg_from_yaml.data);
  builtin_interfaces__msg__Time msg_from_yaml_time = msg_from_yaml->stamp;
  rosidl_runtime_c__String msg_from_yaml_str = msg_from_yaml->frame_id;
  std::cout << "time: sec=" << msg_from_yaml_time.sec <<
    ", nanosec=" << msg_from_yaml_time.nanosec << std::endl;
  std::cout << "frame_id=" << msg_from_yaml_str.data << std::endl;
  ASSERT_EQ(msg_from_yaml->stamp.sec, 4);
  ASSERT_EQ(msg_from_yaml->stamp.nanosec, 20u);
  ASSERT_STREQ(msg_from_yaml->frame_id.data, "my_frame");
}
