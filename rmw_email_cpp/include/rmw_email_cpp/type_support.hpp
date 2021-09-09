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

#ifndef RMW_EMAIL_CPP__TYPE_SUPPORT_HPP_
#define RMW_EMAIL_CPP__TYPE_SUPPORT_HPP_

#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_cpp/service_type_support_decl.hpp"

namespace rmw_email_cpp
{

const rosidl_message_type_support_t * validate_type_support_message(
  const rosidl_message_type_support_t * type_support);

const rosidl_service_type_support_t * validate_type_support_service(
  const rosidl_service_type_support_t * type_support);

}  // namespace rmw_email_cpp

#endif  // RMW_EMAIL_CPP__TYPE_SUPPORT_HPP_
