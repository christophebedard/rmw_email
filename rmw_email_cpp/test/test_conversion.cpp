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

// Some code taken from:
// https://github.com/osrf/dynamic_message_introspection/blob/main/dynmsg_demo/test/test_read_msg_buffer.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <iostream>
#include <limits>
#include <string>

#include "dynmsg/message_reading.hpp"
#include "dynmsg/msg_parser.hpp"
#include "dynmsg/typesupport.hpp"

#include "builtin_interfaces/msg/time.h"
#include "builtin_interfaces/msg/time.hpp"
#include "rcl_interfaces/msg/parameter.h"
#include "rcl_interfaces/msg/parameter.hpp"
#include "rcl_interfaces/msg/parameter_event.h"
#include "rcl_interfaces/msg/parameter_event.hpp"
#include "std_msgs/msg/string.h"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/header.h"
#include "std_msgs/msg/header.hpp"
#include "test_msgs/msg/arrays.h"
#include "test_msgs/msg/arrays.hpp"
#include "test_msgs/msg/basic_types.h"
#include "test_msgs/msg/basic_types.hpp"
#include "test_msgs/msg/nested.h"
#include "test_msgs/msg/nested.hpp"
#include "test_msgs/msg/unbounded_sequences.h"
#include "test_msgs/msg/unbounded_sequences.hpp"

#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/u16string_functions.h"

std::string yaml_to_string(
  const YAML::Node & yaml,
  const bool double_quoted = false,
  const bool flow_style = false)
{
  YAML::Emitter emitter;
  if (double_quoted) {
    emitter << YAML::DoubleQuoted;
  }
  if (flow_style) {
    emitter << YAML::Flow;
  }
  emitter << yaml;
  return emitter.c_str();
}

template<typename BasicTypes>
void populate_basic_types(BasicTypes * msg)
{
  msg->bool_value = true;
  msg->byte_value = 142;
  msg->char_value = 42;
  msg->float32_value = 42.42;
  msg->float64_value = 4242424242424242.42;
  msg->int8_value = -42;
  msg->uint8_value = 242;
  msg->int16_value = -4242;
  msg->uint16_value = 4242;
  msg->int32_value = -42424242;
  msg->uint32_value = 4242424242u;
  msg->int64_value = -424242424242;
  msg->uint64_value = 424242424242u;
}

template<typename Nested>
void populate_nested(Nested * msg)
{
  populate_basic_types(&msg->basic_types_value);
}

template<typename BasicTypes>
void compare_basic_types(BasicTypes * msg)
{
  EXPECT_EQ(msg->bool_value, true);
  EXPECT_EQ(msg->byte_value, 142);
  EXPECT_EQ(msg->char_value, 42);
  EXPECT_FLOAT_EQ(msg->float32_value, 42.42);
  EXPECT_FLOAT_EQ(msg->float64_value, 4242424242424242.42);
  EXPECT_EQ(msg->int8_value, -42);
  EXPECT_EQ(msg->uint8_value, 242);
  EXPECT_EQ(msg->int16_value, -4242);
  EXPECT_EQ(msg->uint16_value, 4242);
  EXPECT_EQ(msg->int32_value, -42424242);
  EXPECT_EQ(msg->uint32_value, 4242424242u);
  EXPECT_EQ(msg->int64_value, -424242424242);
  EXPECT_EQ(msg->uint64_value, 424242424242u);
}

template<typename Nested>
void compare_nested(Nested * msg)
{
  compare_basic_types(&msg->basic_types_value);
}

template<typename Arrays>
void populate_arrays(Arrays * msg)
{
  msg->bool_values[0] = true;
  msg->bool_values[1] = false;
  msg->bool_values[2] = true;
  msg->byte_values[0] = 0;
  msg->byte_values[1] = 127;
  msg->byte_values[2] = 255;
  msg->char_values[0] = 0;
  msg->char_values[1] = 127;
  msg->char_values[2] = 255;
  msg->float32_values[0] = 1e5;
  msg->float32_values[1] = 1e-5;
  msg->float32_values[2] = 1;
  msg->float64_values[0] = 1e10;
  msg->float64_values[1] = 1e-10;
  msg->float64_values[2] = 1;
  msg->int8_values[0] = -128;
  msg->int8_values[1] = 0;
  msg->int8_values[2] = 127;
  msg->uint8_values[0] = 0;
  msg->uint8_values[1] = 127;
  msg->uint8_values[2] = 255;
  msg->int16_values[0] = -32768;
  msg->int16_values[1] = 0;
  msg->int16_values[2] = 32767;
  msg->uint16_values[0] = 0;
  msg->uint16_values[1] = 32767;
  msg->uint16_values[2] = 65535;
  msg->int32_values[0] = -2147483648;
  msg->int32_values[1] = 0;
  msg->int32_values[2] = 2147483647;
  msg->uint32_values[0] = 0u;
  msg->uint32_values[1] = 2147483647u;
  msg->uint32_values[2] = 4294967295u;
  msg->int64_values[0] = -9223372036854775807l;
  msg->int64_values[1] = 0;
  msg->int64_values[2] = 9223372036854775807l;
  msg->uint64_values[0] = std::numeric_limits<uint64_t>::min();
  msg->uint64_values[1] = 9223372036854775807ul;
  msg->uint64_values[2] = 18446744073709551615ul;
  if constexpr (std::is_same<Arrays, test_msgs__msg__Arrays>::value) {
    rosidl_runtime_c__String__assign(&msg->string_values[0], "one");
    rosidl_runtime_c__String__assign(&msg->string_values[1], "two");
    rosidl_runtime_c__String__assign(&msg->string_values[2], "three");
  } else if constexpr (std::is_same<Arrays, test_msgs::msg::Arrays>::value) {  // NOLINT[readability/braces] not handled correctly
    msg->string_values[0] = "one";
    msg->string_values[1] = "two";
    msg->string_values[2] = "three";
  } else {
  }
  for (size_t ii = 0; ii < 3; ++ii) {
    populate_basic_types(&msg->basic_types_values[ii]);
  }
  msg->alignment_check = 42;
}

template<typename Arrays>
void compare_arrays(Arrays * msg)
{
  EXPECT_EQ(msg->bool_values[0], true);
  EXPECT_EQ(msg->bool_values[1], false);
  EXPECT_EQ(msg->bool_values[2], true);
  EXPECT_EQ(msg->byte_values[0], 0);
  EXPECT_EQ(msg->byte_values[1], 127);
  EXPECT_EQ(msg->byte_values[2], 255);
  EXPECT_EQ(msg->char_values[0], 0);
  EXPECT_EQ(msg->char_values[1], 127);
  EXPECT_EQ(msg->char_values[2], 255);
  EXPECT_FLOAT_EQ(msg->float32_values[0], 1e5);
  EXPECT_FLOAT_EQ(msg->float32_values[1], 1e-5);
  EXPECT_FLOAT_EQ(msg->float32_values[2], 1);
  EXPECT_FLOAT_EQ(msg->float64_values[0], 1e10);
  EXPECT_FLOAT_EQ(msg->float64_values[1], 1e-10);
  EXPECT_FLOAT_EQ(msg->float64_values[2], 1);
  EXPECT_EQ(msg->int8_values[0], -128);
  EXPECT_EQ(msg->int8_values[1], 0);
  EXPECT_EQ(msg->int8_values[2], 127);
  EXPECT_EQ(msg->uint8_values[0], 0);
  EXPECT_EQ(msg->uint8_values[1], 127);
  EXPECT_EQ(msg->uint8_values[2], 255);
  EXPECT_EQ(msg->int16_values[0], -32768);
  EXPECT_EQ(msg->int16_values[1], 0);
  EXPECT_EQ(msg->int16_values[2], 32767);
  EXPECT_EQ(msg->uint16_values[0], 0);
  EXPECT_EQ(msg->uint16_values[1], 32767);
  EXPECT_EQ(msg->uint16_values[2], 65535);
  EXPECT_EQ(msg->int32_values[0], -2147483648);
  EXPECT_EQ(msg->int32_values[1], 0);
  EXPECT_EQ(msg->int32_values[2], 2147483647);
  EXPECT_EQ(msg->uint32_values[0], 0u);
  EXPECT_EQ(msg->uint32_values[1], 2147483647u);
  EXPECT_EQ(msg->uint32_values[2], 4294967295u);
  EXPECT_EQ(msg->int64_values[0], -9223372036854775807l);
  EXPECT_EQ(msg->int64_values[1], 0);
  EXPECT_EQ(msg->int64_values[2], 9223372036854775807l);
  EXPECT_EQ(msg->uint64_values[0], std::numeric_limits<uint64_t>::min());
  EXPECT_EQ(msg->uint64_values[1], 9223372036854775807ul);
  EXPECT_EQ(msg->uint64_values[2], 18446744073709551615ul);
  if constexpr (std::is_same<Arrays, test_msgs__msg__Arrays>::value) {
    EXPECT_STREQ(msg->string_values[0].data, "one");
    EXPECT_STREQ(msg->string_values[1].data, "two");
    EXPECT_STREQ(msg->string_values[2].data, "three");
  } else if constexpr (std::is_same<Arrays, test_msgs::msg::Arrays>::value) {  // NOLINT[readability/braces] not handled correctly
    EXPECT_STREQ(msg->string_values[0].c_str(), "one");
    EXPECT_STREQ(msg->string_values[1].c_str(), "two");
    EXPECT_STREQ(msg->string_values[2].c_str(), "three");
  } else {
  }
  for (size_t i = 0u; i < 3u; i++) {
    compare_basic_types(&msg->basic_types_values[i]);
  }
  EXPECT_FLOAT_EQ(msg->float32_values_default[0], 1.125);
  EXPECT_FLOAT_EQ(msg->float32_values_default[1], 0.0);
  EXPECT_FLOAT_EQ(msg->float32_values_default[2], -1.125);
  EXPECT_FLOAT_EQ(msg->float64_values_default[0], 3.1415);
  EXPECT_FLOAT_EQ(msg->float64_values_default[1], 0.0);
  EXPECT_FLOAT_EQ(msg->float64_values_default[2], -3.1415);
  EXPECT_EQ(msg->alignment_check, 42);
}

void populate_unbounded_sequences(test_msgs__msg__UnboundedSequences * msg)
{
  rosidl_runtime_c__boolean__Sequence__init(&msg->bool_values, 4);
  msg->bool_values.data[0] = true;
  msg->bool_values.data[1] = false;
  msg->bool_values.data[2] = false;
  msg->bool_values.data[3] = true;
  rosidl_runtime_c__octet__Sequence__init(&msg->byte_values, 4);
  msg->byte_values.data[0] = 4;
  msg->byte_values.data[1] = 2;
  msg->byte_values.data[2] = 2;
  msg->byte_values.data[3] = 7;
  rosidl_runtime_c__uint8__Sequence__init(&msg->char_values, 4);
  msg->char_values.data[0] = 42;
  msg->char_values.data[1] = 27;
  msg->char_values.data[2] = 9;
  msg->char_values.data[3] = 242;
  rosidl_runtime_c__float__Sequence__init(&msg->float32_values, 4);
  msg->float32_values.data[0] = 42.42;
  msg->float32_values.data[1] = 24.24;
  msg->float32_values.data[2] = 24.42;
  msg->float32_values.data[3] = 42.24;
  rosidl_runtime_c__double__Sequence__init(&msg->float64_values, 4);
  msg->float64_values.data[0] = 42.42;
  msg->float64_values.data[1] = 24.24;
  msg->float64_values.data[2] = 24.42;
  msg->float64_values.data[3] = 42.24;
  rosidl_runtime_c__int8__Sequence__init(&msg->int8_values, 4);
  msg->int8_values.data[0] = -42;
  msg->int8_values.data[1] = -27;
  msg->int8_values.data[2] = 9;
  msg->int8_values.data[3] = 123;
  rosidl_runtime_c__uint8__Sequence__init(&msg->uint8_values, 4);
  msg->uint8_values.data[0] = 42;
  msg->uint8_values.data[1] = 27;
  msg->uint8_values.data[2] = 9;
  msg->uint8_values.data[3] = 242;
  rosidl_runtime_c__int16__Sequence__init(&msg->int16_values, 4);
  msg->int16_values.data[0] = -42;
  msg->int16_values.data[1] = -27;
  msg->int16_values.data[2] = 9;
  msg->int16_values.data[3] = 242;
  rosidl_runtime_c__uint16__Sequence__init(&msg->uint16_values, 4);
  msg->uint16_values.data[0] = 42;
  msg->uint16_values.data[1] = 27;
  msg->uint16_values.data[2] = 9;
  msg->uint16_values.data[3] = 242;
  rosidl_runtime_c__int32__Sequence__init(&msg->int32_values, 4);
  msg->int32_values.data[0] = -42;
  msg->int32_values.data[1] = -27;
  msg->int32_values.data[2] = 9;
  msg->int32_values.data[3] = 242;
  rosidl_runtime_c__uint32__Sequence__init(&msg->uint32_values, 4);
  msg->uint32_values.data[0] = 42u;
  msg->uint32_values.data[1] = 27u;
  msg->uint32_values.data[2] = 9u;
  msg->uint32_values.data[3] = 242u;
  rosidl_runtime_c__int64__Sequence__init(&msg->int64_values, 4);
  msg->int64_values.data[0] = -42;
  msg->int64_values.data[1] = -27;
  msg->int64_values.data[2] = 9;
  msg->int64_values.data[3] = 242;
  rosidl_runtime_c__uint64__Sequence__init(&msg->uint64_values, 4);
  msg->uint64_values.data[0] = 42u;
  msg->uint64_values.data[1] = 27u;
  msg->uint64_values.data[2] = 9u;
  msg->uint64_values.data[3] = 242u;
  // And the rest
}

void populate_unbounded_sequences(test_msgs::msg::UnboundedSequences * msg)
{
  msg->bool_values.push_back(true);
  msg->bool_values.push_back(false);
  msg->bool_values.push_back(false);
  msg->bool_values.push_back(true);
  msg->byte_values.push_back(4);
  msg->byte_values.push_back(2);
  msg->byte_values.push_back(2);
  msg->byte_values.push_back(7);
  msg->char_values.push_back(42);
  msg->char_values.push_back(27);
  msg->char_values.push_back(9);
  msg->char_values.push_back(242);
  msg->float32_values.push_back(42.42);
  msg->float32_values.push_back(24.24);
  msg->float32_values.push_back(24.42);
  msg->float32_values.push_back(42.24);
  msg->float64_values.push_back(42.42);
  msg->float64_values.push_back(24.24);
  msg->float64_values.push_back(24.42);
  msg->float64_values.push_back(42.24);
  msg->int8_values.push_back(-42);
  msg->int8_values.push_back(-27);
  msg->int8_values.push_back(9);
  msg->int8_values.push_back(123);
  msg->uint8_values.push_back(42);
  msg->uint8_values.push_back(27);
  msg->uint8_values.push_back(9);
  msg->uint8_values.push_back(242);
  msg->int16_values.push_back(-42);
  msg->int16_values.push_back(-27);
  msg->int16_values.push_back(9);
  msg->int16_values.push_back(242);
  msg->uint16_values.push_back(42);
  msg->uint16_values.push_back(27);
  msg->uint16_values.push_back(9);
  msg->uint16_values.push_back(242);
  msg->int32_values.push_back(-42);
  msg->int32_values.push_back(-27);
  msg->int32_values.push_back(9);
  msg->int32_values.push_back(242);
  msg->uint32_values.push_back(42u);
  msg->uint32_values.push_back(27u);
  msg->uint32_values.push_back(9u);
  msg->uint32_values.push_back(242u);
  msg->int64_values.push_back(-42);
  msg->int64_values.push_back(-27);
  msg->int64_values.push_back(9);
  msg->int64_values.push_back(242);
  msg->uint64_values.push_back(42u);
  msg->uint64_values.push_back(27u);
  msg->uint64_values.push_back(9u);
  msg->uint64_values.push_back(242u);
  // And the rest
}

void compare_unbounded_sequences(test_msgs__msg__UnboundedSequences * msg)
{
  EXPECT_EQ(msg->bool_values.data[0], true);
  EXPECT_EQ(msg->bool_values.data[1], false);
  EXPECT_EQ(msg->bool_values.data[2], false);
  EXPECT_EQ(msg->bool_values.data[3], true);
  EXPECT_EQ(msg->byte_values.data[0], 4);
  EXPECT_EQ(msg->byte_values.data[1], 2);
  EXPECT_EQ(msg->byte_values.data[2], 2);
  EXPECT_EQ(msg->byte_values.data[3], 7);
  EXPECT_EQ(msg->char_values.data[0], 42);
  EXPECT_EQ(msg->char_values.data[1], 27);
  EXPECT_EQ(msg->char_values.data[2], 9);
  EXPECT_EQ(msg->char_values.data[3], 242);
  EXPECT_FLOAT_EQ(msg->float32_values.data[0], 42.42);
  EXPECT_FLOAT_EQ(msg->float32_values.data[1], 24.24);
  EXPECT_FLOAT_EQ(msg->float32_values.data[2], 24.42);
  EXPECT_FLOAT_EQ(msg->float32_values.data[3], 42.24);
  EXPECT_FLOAT_EQ(msg->float64_values.data[0], 42.42);
  EXPECT_FLOAT_EQ(msg->float64_values.data[1], 24.24);
  EXPECT_FLOAT_EQ(msg->float64_values.data[2], 24.42);
  EXPECT_FLOAT_EQ(msg->float64_values.data[3], 42.24);
  EXPECT_EQ(msg->int8_values.data[0], -42);
  EXPECT_EQ(msg->int8_values.data[1], -27);
  EXPECT_EQ(msg->int8_values.data[2], 9);
  EXPECT_EQ(msg->int8_values.data[3], 123);
  EXPECT_EQ(msg->uint8_values.data[0], 42);
  EXPECT_EQ(msg->uint8_values.data[1], 27);
  EXPECT_EQ(msg->uint8_values.data[2], 9);
  EXPECT_EQ(msg->uint8_values.data[3], 242);
  EXPECT_EQ(msg->int16_values.data[0], -42);
  EXPECT_EQ(msg->int16_values.data[1], -27);
  EXPECT_EQ(msg->int16_values.data[2], 9);
  EXPECT_EQ(msg->int16_values.data[3], 242);
  EXPECT_EQ(msg->uint16_values.data[0], 42);
  EXPECT_EQ(msg->uint16_values.data[1], 27);
  EXPECT_EQ(msg->uint16_values.data[2], 9);
  EXPECT_EQ(msg->uint16_values.data[3], 242);
  EXPECT_EQ(msg->int32_values.data[0], -42);
  EXPECT_EQ(msg->int32_values.data[1], -27);
  EXPECT_EQ(msg->int32_values.data[2], 9);
  EXPECT_EQ(msg->int32_values.data[3], 242);
  EXPECT_EQ(msg->uint32_values.data[0], 42u);
  EXPECT_EQ(msg->uint32_values.data[1], 27u);
  EXPECT_EQ(msg->uint32_values.data[2], 9u);
  EXPECT_EQ(msg->uint32_values.data[3], 242u);
  EXPECT_EQ(msg->int64_values.data[0], -42);
  EXPECT_EQ(msg->int64_values.data[1], -27);
  EXPECT_EQ(msg->int64_values.data[2], 9);
  EXPECT_EQ(msg->int64_values.data[3], 242);
  EXPECT_EQ(msg->uint64_values.data[0], 42u);
  EXPECT_EQ(msg->uint64_values.data[1], 27u);
  EXPECT_EQ(msg->uint64_values.data[2], 9u);
  EXPECT_EQ(msg->uint64_values.data[3], 242u);
  // And the rest
}

void compare_unbounded_sequences(test_msgs::msg::UnboundedSequences * msg)
{
  EXPECT_EQ(msg->bool_values[0], true);
  EXPECT_EQ(msg->bool_values[1], false);
  EXPECT_EQ(msg->bool_values[2], false);
  EXPECT_EQ(msg->bool_values[3], true);
  EXPECT_EQ(msg->byte_values[0], 4);
  EXPECT_EQ(msg->byte_values[1], 2);
  EXPECT_EQ(msg->byte_values[2], 2);
  EXPECT_EQ(msg->byte_values[3], 7);
  EXPECT_EQ(msg->char_values[0], 42);
  EXPECT_EQ(msg->char_values[1], 27);
  EXPECT_EQ(msg->char_values[2], 9);
  EXPECT_EQ(msg->char_values[3], 242);
  EXPECT_FLOAT_EQ(msg->float32_values[0], 42.42);
  EXPECT_FLOAT_EQ(msg->float32_values[1], 24.24);
  EXPECT_FLOAT_EQ(msg->float32_values[2], 24.42);
  EXPECT_FLOAT_EQ(msg->float32_values[3], 42.24);
  EXPECT_FLOAT_EQ(msg->float64_values[0], 42.42);
  EXPECT_FLOAT_EQ(msg->float64_values[1], 24.24);
  EXPECT_FLOAT_EQ(msg->float64_values[2], 24.42);
  EXPECT_FLOAT_EQ(msg->float64_values[3], 42.24);
  EXPECT_EQ(msg->int8_values[0], -42);
  EXPECT_EQ(msg->int8_values[1], -27);
  EXPECT_EQ(msg->int8_values[2], 9);
  EXPECT_EQ(msg->int8_values[3], 123);
  EXPECT_EQ(msg->uint8_values[0], 42);
  EXPECT_EQ(msg->uint8_values[1], 27);
  EXPECT_EQ(msg->uint8_values[2], 9);
  EXPECT_EQ(msg->uint8_values[3], 242);
  EXPECT_EQ(msg->int16_values[0], -42);
  EXPECT_EQ(msg->int16_values[1], -27);
  EXPECT_EQ(msg->int16_values[2], 9);
  EXPECT_EQ(msg->int16_values[3], 242);
  EXPECT_EQ(msg->uint16_values[0], 42u);
  EXPECT_EQ(msg->uint16_values[1], 27u);
  EXPECT_EQ(msg->uint16_values[2], 9u);
  EXPECT_EQ(msg->uint16_values[3], 242u);
  EXPECT_EQ(msg->int32_values[0], -42);
  EXPECT_EQ(msg->int32_values[1], -27);
  EXPECT_EQ(msg->int32_values[2], 9);
  EXPECT_EQ(msg->int32_values[3], 242);
  EXPECT_EQ(msg->uint32_values[0], 42u);
  EXPECT_EQ(msg->uint32_values[1], 27u);
  EXPECT_EQ(msg->uint32_values[2], 9u);
  EXPECT_EQ(msg->uint32_values[3], 242u);
  EXPECT_EQ(msg->int64_values[0], -42);
  EXPECT_EQ(msg->int64_values[1], -27);
  EXPECT_EQ(msg->int64_values[2], 9);
  EXPECT_EQ(msg->int64_values[3], 242);
  EXPECT_EQ(msg->uint64_values[0], 42u);
  EXPECT_EQ(msg->uint64_values[1], 27u);
  EXPECT_EQ(msg->uint64_values[2], 9u);
  EXPECT_EQ(msg->uint64_values[3], 242u);
  // And the rest
}

TEST(TestConversion, test_msgs__BasicTypes_c)
{
  // Start with a ROS message, like a test_msgs/BasicTypes
  test_msgs__msg__BasicTypes * msg = test_msgs__msg__BasicTypes__create();
  populate_basic_types(msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "BasicTypes"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<test_msgs__msg__BasicTypes *>(ros_msg_from_yaml.data);

  compare_basic_types(msg_from_yaml);

  test_msgs__msg__BasicTypes__fini(msg);
}

TEST(TestConversion, test_msgs__BasicTypes_cpp)
{
  test_msgs::msg::BasicTypes msg;
  populate_basic_types(&msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "BasicTypes"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  test_msgs::msg::BasicTypes msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  compare_basic_types(&msg_from_yaml);
}

TEST(TestConversion, test_msgs__UnboundedSequences_c)
{
  // Start with a ROS message, like a test_msgs/UnboundedSequences
  test_msgs__msg__UnboundedSequences * msg = test_msgs__msg__UnboundedSequences__create();
  populate_unbounded_sequences(msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "UnboundedSequences"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml =
    reinterpret_cast<test_msgs__msg__UnboundedSequences *>(ros_msg_from_yaml.data);

  compare_unbounded_sequences(msg_from_yaml);

  test_msgs__msg__UnboundedSequences__fini(msg);
}

TEST(TestConversion, test_msgs__UnboundedSequences_cpp)
{
  // Start with a ROS message, like a test_msgs/UnboundedSequences
  test_msgs::msg::UnboundedSequences msg;
  populate_unbounded_sequences(&msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "UnboundedSequences"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  test_msgs::msg::UnboundedSequences msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  compare_unbounded_sequences(&msg_from_yaml);
}

TEST(TestConversion, test_msgs__Nested_c)
{
  // Start with a ROS message, like a test_msgs/BasicTypes
  test_msgs__msg__Nested * msg = test_msgs__msg__Nested__create();
  populate_nested(msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "Nested"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<test_msgs__msg__Nested *>(ros_msg_from_yaml.data);

  compare_nested(msg_from_yaml);

  test_msgs__msg__Nested__fini(msg);
}

TEST(TestConversion, test_msgs__Nested_cpp)
{
  test_msgs::msg::Nested msg;
  populate_nested(&msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "Nested"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  test_msgs::msg::Nested msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  compare_nested(&msg_from_yaml);
}

TEST(TestConversion, test_msgs__Arrays_c)
{
  // Start with a ROS message, like a test_msgs/Arrays
  test_msgs__msg__Arrays * msg = test_msgs__msg__Arrays__create();
  populate_arrays(msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "Arrays"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<test_msgs__msg__Arrays *>(ros_msg_from_yaml.data);

  compare_arrays(msg_from_yaml);

  test_msgs__msg__Arrays__fini(msg);
}

TEST(TestConversion, test_msgs__Arrays_cpp)
{
  // Start with a ROS message, like a test_msgs/Arrays
  test_msgs::msg::Arrays msg;
  populate_arrays(&msg);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"test_msgs", "Arrays"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  test_msgs::msg::Arrays msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  compare_arrays(&msg_from_yaml);
}

TEST(TestConversion, std_msgs__String_c)
{
  // Start with a ROS message, like a std_msgs/String
  std_msgs__msg__String * msg = std_msgs__msg__String__create();
  rosidl_runtime_c__String__assign(&msg->data, "hello world");

  // Convert it to a YAML representation
  InterfaceTypeName interface{"std_msgs", "String"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;
  EXPECT_STREQ(yaml_string.c_str(), "data: hello world");

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<std_msgs__msg__String *>(ros_msg_from_yaml.data);

  EXPECT_STREQ(msg_from_yaml->data.data, "hello world");

  std_msgs__msg__String__fini(msg);
}

TEST(TestConversion, std_msgs__String_cpp)
{
  // Start with a ROS message, like a std_msgs/String
  std_msgs::msg::String msg;
  msg.data = "hello world";

  // Convert it to a YAML representation
  InterfaceTypeName interface{"std_msgs", "String"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;
  EXPECT_STREQ(
    yaml_string.c_str(), "data: hello world");

  // Convert YAML string back to a ROS message
  std_msgs::msg::String msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  EXPECT_STREQ(msg_from_yaml.data.c_str(), "hello world");
}

TEST(TestConversion, std_msgs__Header_c)
{
  // Start with a ROS message, like a std_msgs/Header
  std_msgs__msg__Header * msg = std_msgs__msg__Header__create();
  msg->stamp.sec = 4;
  msg->stamp.nanosec = 20u;
  rosidl_runtime_c__String__assign(&msg->frame_id, "my_frame");

  // Convert it to a YAML representation
  InterfaceTypeName interface{"std_msgs", "Header"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;
  EXPECT_STREQ(
    yaml_string.c_str(), 1 + R"(
stamp:
  sec: 4
  nanosec: 20
frame_id: my_frame)");

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<std_msgs__msg__Header *>(ros_msg_from_yaml.data);

  EXPECT_EQ(msg_from_yaml->stamp.sec, 4);
  EXPECT_EQ(msg_from_yaml->stamp.nanosec, 20u);
  EXPECT_STREQ(msg_from_yaml->frame_id.data, "my_frame");

  std_msgs__msg__Header__fini(msg);
}

TEST(TestConversion, std_msgs__Header_cpp)
{
  // Start with a ROS message, like a std_msgs/Header
  std_msgs::msg::Header msg;
  msg.frame_id = "my_frame";
  builtin_interfaces::msg::Time stamp;
  stamp.sec = 4;
  stamp.nanosec = 20u;
  msg.stamp = stamp;

  // Convert it to a YAML representation
  InterfaceTypeName interface{"std_msgs", "Header"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;
  EXPECT_STREQ(
    yaml_string.c_str(), 1 + R"(
stamp:
  sec: 4
  nanosec: 20
frame_id: my_frame)");

  // Convert YAML string back to a ROS message
  std_msgs::msg::Header msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  EXPECT_EQ(msg_from_yaml.stamp.sec, 4);
  EXPECT_EQ(msg_from_yaml.stamp.nanosec, 20u);
  EXPECT_STREQ(msg_from_yaml.frame_id.c_str(), "my_frame");
}

TEST(TestConversion, rcl_interfaces__ParameterEvent_c)
{
  // Start with a ROS message, like a rcl_interfaces/ParameterEvent
  rcl_interfaces__msg__ParameterEvent * msg = rcl_interfaces__msg__ParameterEvent__create();

  builtin_interfaces__msg__Time * stamp = builtin_interfaces__msg__Time__create();
  stamp->sec = 4;
  stamp->nanosec = 20u;
  msg->stamp = *stamp;

  rosidl_runtime_c__String__assign(&msg->node, "/my/node");

  rcl_interfaces__msg__Parameter__Sequence__init(&msg->new_parameters, 2);
  rosidl_runtime_c__String__assign(&(msg->new_parameters.data[0].name), "the_param_name");
  msg->new_parameters.data[0].value.type = 1u;
  msg->new_parameters.data[0].value.bool_value = true;
  rosidl_runtime_c__String__assign(&(msg->new_parameters.data[1].name), "some_other_param");
  msg->new_parameters.data[1].value.type = 5u;
  rosidl_runtime_c__octet__Sequence__init(
    &(msg->new_parameters.data[1].value.byte_array_value), 2);
  msg->new_parameters.data[1].value.byte_array_value.data[0] = 27;
  msg->new_parameters.data[1].value.byte_array_value.data[1] = 42;

  // Convert it to a YAML representation
  InterfaceTypeName interface{"rcl_interfaces", "ParameterEvent"};
  RosMessage ros_msg;
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  RosMessage ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml =
    reinterpret_cast<rcl_interfaces__msg__ParameterEvent *>(ros_msg_from_yaml.data);

  EXPECT_EQ(4, msg_from_yaml->stamp.sec);
  EXPECT_EQ(20u, msg_from_yaml->stamp.nanosec);
  EXPECT_STREQ("/my/node", msg_from_yaml->node.data);
  EXPECT_EQ(2u, msg_from_yaml->new_parameters.size);
  EXPECT_EQ(2u, msg_from_yaml->new_parameters.capacity);
  EXPECT_STREQ("the_param_name", msg_from_yaml->new_parameters.data[0].name.data);
  EXPECT_EQ(1u, msg_from_yaml->new_parameters.data[0].value.type);
  EXPECT_EQ(true, msg_from_yaml->new_parameters.data[0].value.bool_value);
  EXPECT_STREQ("some_other_param", msg_from_yaml->new_parameters.data[1].name.data);
  EXPECT_EQ(5u, msg_from_yaml->new_parameters.data[1].value.type);
  EXPECT_EQ(27, (char)msg_from_yaml->new_parameters.data[1].value.byte_array_value.data[0]);
  EXPECT_EQ(42, (char)msg_from_yaml->new_parameters.data[1].value.byte_array_value.data[1]);

  rcl_interfaces__msg__ParameterEvent__fini(msg);
}

TEST(TestConversion, rcl_interfaces__ParameterEvent_cpp)
{
  // Start with a ROS message, like a rcl_interfaces/ParameterEvent
  rcl_interfaces::msg::ParameterEvent msg;

  builtin_interfaces::msg::Time stamp;
  stamp.sec = 4;
  stamp.nanosec = 20u;

  rcl_interfaces::msg::ParameterValue param_value;
  param_value.type = 1u;
  // TODO(christophebedard) try with an array, like string[]
  param_value.bool_value = true;

  rcl_interfaces::msg::Parameter param;
  param.name = "the_param_name";
  param.value = param_value;

  msg.stamp = stamp;
  msg.node = "/my/node";
  msg.new_parameters.push_back(param);

  // Convert it to a YAML representation
  InterfaceTypeName interface{"rcl_interfaces", "ParameterEvent"};
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = dynmsg::cpp::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(&msg);
  YAML::Node yaml_msg = dynmsg::cpp::message_to_yaml(ros_msg);
  std::cout << "message to YAML:" << std::endl;
  std::cout << yaml_msg << std::endl << std::endl;

  // Convert the YAML representation to a string
  const std::string yaml_string = yaml_to_string(yaml_msg);
  std::cout << "YAML:" << std::endl;
  std::cout << yaml_string << std::endl << std::endl;

  // Convert YAML string back to a ROS message
  rcl_interfaces::msg::ParameterEvent msg_from_yaml;
  void * ros_message = reinterpret_cast<void *>(&msg_from_yaml);
  dynmsg::cpp::yaml_to_rosmsg_typeinfo(ros_msg.type_info, yaml_string, ros_message);

  EXPECT_STREQ(msg_from_yaml.node.c_str(), "/my/node");
  EXPECT_EQ(msg_from_yaml.stamp.sec, 4);
  EXPECT_EQ(msg_from_yaml.stamp.nanosec, 20u);
  ASSERT_EQ(msg_from_yaml.new_parameters.size(), 1ul);
  EXPECT_STREQ(msg_from_yaml.new_parameters[0].name.c_str(), "the_param_name");
  EXPECT_EQ(msg_from_yaml.new_parameters[0].value.type, 1u);
  EXPECT_EQ(msg_from_yaml.new_parameters[0].value.bool_value, true);
}
