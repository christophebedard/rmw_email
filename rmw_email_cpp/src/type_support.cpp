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

#include "rcutils/error_handling.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_cpp/message_type_support_decl.hpp"
#include "rosidl_runtime_cpp/service_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rmw/error_handling.h"

#include "rmw_email_cpp/type_support.hpp"

namespace rmw_email_cpp
{

const rosidl_message_type_support_t * validate_type_support_message(
  const rosidl_message_type_support_t * type_support)
{
  const rosidl_message_type_support_t * ts = nullptr;
  ts = get_message_typesupport_handle(
    type_support,
    rosidl_typesupport_introspection_c__identifier);
  if (ts) {
    return ts;
  }
  rcutils_error_string_t error_c = rcutils_get_error_string();
  rcutils_reset_error();

  ts = get_message_typesupport_handle(
    type_support,
    rosidl_typesupport_introspection_cpp::typesupport_identifier);
  if (ts) {
    return ts;
  }
  rcutils_error_string_t error_cpp = rcutils_get_error_string();
  rcutils_reset_error();

  RMW_SET_ERROR_MSG_WITH_FORMAT_STRING(
    "Couldn't find typesupport:\n"
    "C: %s\n"
    "C++: %s",
    error_c.str,
    error_cpp.str);
  return nullptr;
}

const rosidl_service_type_support_t * validate_type_support_service(
  const rosidl_service_type_support_t * type_support)
{
  const rosidl_service_type_support_t * ts = nullptr;
  ts = get_service_typesupport_handle(
    type_support,
    rosidl_typesupport_introspection_c__identifier);
  if (ts) {
    return ts;
  }
  rcutils_error_string_t error_c = rcutils_get_error_string();
  rcutils_reset_error();

  ts = get_service_typesupport_handle(
    type_support,
    rosidl_typesupport_introspection_cpp::typesupport_identifier);
  if (ts) {
    return ts;
  }
  rcutils_error_string_t error_cpp = rcutils_get_error_string();
  rcutils_reset_error();

  RMW_SET_ERROR_MSG_WITH_FORMAT_STRING(
    "Couldn't find typesupport:\n"
    "C: %s\n"
    "C++: %s",
    error_c.str,
    error_cpp.str);
  return nullptr;
}

}  // namespace rmw_email_cpp
