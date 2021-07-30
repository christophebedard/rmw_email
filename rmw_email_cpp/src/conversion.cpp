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

// TODO(christophebedard) make this string conversion better
std::string _yaml_to_string(const YAML::Node & yaml)
{
  YAML::Emitter emitter;
  // Make the YAML a one-line
  emitter << YAML::DoubleQuoted << YAML::Flow << yaml;
  return emitter.c_str();
}

namespace details
{
namespace c
{

std::string msg_to_yaml(
  const rosidl_typesupport_introspection_c__MessageMembers * members,
  const void * msg)
{
  // Convert to YAML
  RosMessage ros_msg;
  ros_msg.type_info = members;
  // ros_msg.data = reinterpret_cast<const uint8_t *>(msg);
  ros_msg.data = const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(msg));
  YAML::Node yaml = dynmsg::c::message_to_yaml(ros_msg);
  const auto & str = _yaml_to_string(yaml);
  RMW_EMAIL_LOG_DEBUG("message C: %s", str.c_str());
  return str;
}

bool yaml_to_msg(
  const rosidl_typesupport_introspection_c__MessageMembers * members,
  const std::string & yaml,
  void * ros_message,
  rcutils_allocator_t * allocator)
{
  // Convert to message
  RosMessage ros_msg = dynmsg::c::yaml_to_rosmsg_typeinfo(members, yaml, allocator);
  if (!ros_msg.data && !ros_msg.type_info) {
    return false;
  }
  memcpy(ros_message, ros_msg.data, members->size_of_);
  // TODO(christophebedard) figure out how/when to deallocate
  // when message gets returned by the executor after executing the callback?
  // ros_message_destroy_(&ros_msg, allocator);
  // TODO(christophebedard) provide ros_message pointer directly so that yaml_to_rosmsg_()
  // directly into it?
  return true;
}

}  // namespace c

namespace cpp
{

std::string msg_to_yaml(
  const rosidl_typesupport_introspection_cpp::MessageMembers * members,
  const void * msg)
{
  // Convert to YAML
  RosMessage_Cpp ros_msg;
  ros_msg.type_info = members;
  // ros_msg.data = reinterpret_cast<const uint8_t *>(msg);
  ros_msg.data = const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(msg));
  YAML::Node yaml = dynmsg::cpp::message_to_yaml(ros_msg);
  const auto & str = _yaml_to_string(yaml);
  RMW_EMAIL_LOG_DEBUG("message C++: %s", str.c_str());
  return str;
}

bool yaml_to_msg(
  const rosidl_typesupport_introspection_cpp::MessageMembers * members,
  const std::string & yaml,
  void * ros_message,
  rcutils_allocator_t * allocator)
{
  // Convert to message
  RosMessage_Cpp ros_msg = dynmsg::cpp::yaml_to_rosmsg_typeinfo(members, yaml, allocator);
  if (!ros_msg.data && !ros_msg.type_info) {
    return false;
  }
  memcpy(ros_message, ros_msg.data, members->size_of_);
  // TODO(christophebedard) figure out how/when to deallocate
  // when message gets returned by the executor after executing the callback?
  // ros_message_destroy_(&ros_msg, allocator);
  return true;
}

}  // namespace cpp
}  // namespace details

std::string msg_to_yaml(
  const rmw_email_pub_t * publisher,
  const void * msg)
{
  const rosidl_message_type_support_t * ts = nullptr;
  ts = get_message_typesupport_handle(
    &publisher->type_supports,
    rosidl_typesupport_introspection_c__identifier);
  if (ts) {
    RMW_EMAIL_LOG_DEBUG("msg_to_yaml typesupport: C");
    auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
      ts->data);
    return details::c::msg_to_yaml(members, msg);
  }
  rcutils_error_string_t error_c = rcutils_get_error_string();
  rcutils_reset_error();

  ts = get_message_typesupport_handle(
    &publisher->type_supports,
    rosidl_typesupport_introspection_cpp::typesupport_identifier);
  if (ts) {
    RMW_EMAIL_LOG_DEBUG("msg_to_yaml typesupport: C++");
    auto members = static_cast<const rosidl_typesupport_introspection_cpp::MessageMembers *>(
      ts->data);
    return details::cpp::msg_to_yaml(members, msg);
  }
  rcutils_error_string_t error_cpp = rcutils_get_error_string();
  rcutils_reset_error();

  throw std::runtime_error(
          "msg_to_yaml couldn't find typesupport:\n"
          "C:" + std::string(error_c.str) + "\n"
          "C++:" + std::string(error_cpp.str));
}

bool yaml_to_msg(
  const rmw_email_sub_t * subscription,
  const std::string & yaml,
  void * ros_message,
  rcutils_allocator_t * allocator)
{
  const rosidl_message_type_support_t * ts = nullptr;
  ts = get_message_typesupport_handle(
    &subscription->type_supports,
    rosidl_typesupport_introspection_c__identifier);
  if (ts) {
    RMW_EMAIL_LOG_DEBUG("yaml_to_msg typesupport: C");
    auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
      ts->data);
    return details::c::yaml_to_msg(members, yaml, ros_message, allocator);
  }
  rcutils_error_string_t error_c = rcutils_get_error_string();
  rcutils_reset_error();

  ts = get_message_typesupport_handle(
    &subscription->type_supports,
    rosidl_typesupport_introspection_cpp::typesupport_identifier);
  if (ts) {
    RMW_EMAIL_LOG_DEBUG("yaml_to_msg typesupport: C++");
    auto members = static_cast<const rosidl_typesupport_introspection_cpp::MessageMembers *>(
      ts->data);
    return details::cpp::yaml_to_msg(members, yaml, ros_message, allocator);
  }
  rcutils_error_string_t error_cpp = rcutils_get_error_string();
  rcutils_reset_error();

  throw std::runtime_error(
          "yaml_to_msg couldn't find typesupport:\n"
          "C:" + std::string(error_c.str) + "\n"
          "C++:" + std::string(error_cpp.str));
}
