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

// TODO(christophebedard) replace cout/endl with proper logging
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>

#include "dynmsg/message_reading.hpp"
#include "dynmsg/msg_parser.hpp"
#include "rcutils/allocator.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rmw/error_handling.h"

#include "rmw_email_cpp/conversion.hpp"
#include "rmw_email_cpp/log.hpp"

std::string _yaml_to_string(const YAML::Node & yaml)
{
  YAML::Emitter emitter;
  // Make the YAML a one-line
  emitter << YAML::DoubleQuoted << YAML::Flow << yaml;
  // TODO(christophebedard) make this string conversion better
  return emitter.c_str();
}

const rosidl_message_type_support_t * _get_type_support(
  const rosidl_message_type_support_t * type_supports)
{
  const rosidl_message_type_support_t * ts_c = get_message_typesupport_handle(
    type_supports,
    rosidl_typesupport_introspection_c__identifier);
  if (ts_c) {
    RMW_EMAIL_LOG_DEBUG("typesupport: C");
    return ts_c;
  }
  // TODO(christophebedard) support C++ typesupport
  // const rosidl_message_type_support_t * ts_cpp = get_message_typesupport_handle(
  //   type_supports,
  //   rosidl_typesupport_introspection_cpp::typesupport_identifier);
  // if (ts_cpp) {
  //   RMW_EMAIL_LOG_DEBUG("typesupport: C++");
  //   return ts_cpp;
  // }
  return nullptr;
}

std::string msg_to_yaml(
  const rmw_email_pub_t * publisher,
  const void * msg)
{
  // Get introspection information
  const rosidl_message_type_support_t * ts = _get_type_support(&publisher->type_supports);
  if (!ts) {
    RMW_SET_ERROR_MSG("msg_to_yaml: type support trouble");
    // TODO(christophebedard) handle this error better
    return "";
  }
  // rosidl_typesupport_introspection_cpp::MessageMembers *
  auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(ts->data);

  // Convert to YAML
  RosMessage ros_msg;
  ros_msg.type_info = members;
  // ros_msg.data = reinterpret_cast<const uint8_t *>(msg);
  ros_msg.data = const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(msg));
  YAML::Node yaml = message_to_yaml(ros_msg);
  const auto & str = _yaml_to_string(yaml);
  std::cout << "MESSAGE: " << str << std::endl;
  return str;
}

bool yaml_to_msg(
  const rmw_email_sub_t * subscription,
  const std::string & yaml,
  void * ros_message,
  rcutils_allocator_t * allocator)
{
  // Get introspection information
  const rosidl_message_type_support_t * ts = _get_type_support(&subscription->type_supports);
  if (!ts) {
    RMW_SET_ERROR_MSG("yaml_to_msg: type support trouble");
    // TODO(christophebedard) handle this error better
    return false;
  }
  auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(ts->data);
  // rosidl_typesupport_introspection_cpp::MessageMembers *

  // Convert to message
  RosMessage ros_msg = yaml_to_rosmsg_(members, yaml, allocator);
  if (!ros_msg.data && !ros_msg.type_info) {
    return false;
  }
  memcpy(ros_message, ros_msg.data, members->size_of_);
  // TODO(christophebedard) figure out how/when to deallocate
  // when message gets returned by the executor after executing the callback?
  // ros_message_destroy_(&ros_msg, allocator);
  return true;
}
