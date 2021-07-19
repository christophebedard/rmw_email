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

#ifndef RMW_EMAIL_CPP__CONVERSION_HPP_
#define RMW_EMAIL_CPP__CONVERSION_HPP_

#include <string>

#include "rcutils/allocator.h"

#include "rmw_email_cpp/types.hpp"

std::string msg_to_yaml(const rmw_email_pub_t * publisher, const void * msg);

bool yaml_to_msg(
  const rmw_email_sub_t * subscription,
  const std::string & yaml,
  void * ros_message,
  rcutils_allocator_t * allocator);

#endif  // RMW_EMAIL_CPP__CONVERSION_HPP_
