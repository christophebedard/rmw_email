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

#ifndef RMW_EMAIL_CPP__TAKE_HPP_
#define RMW_EMAIL_CPP__TAKE_HPP_

#include "rmw/types.h"

namespace rmw_email_cpp
{

rmw_ret_t rmw_take(
  const rmw_subscription_t * subscription,
  void * ros_message,
  bool * taken,
  rmw_subscription_allocation_t * allocation,
  rmw_message_info_t * message_info);

}  // namespace rmw_email_cpp

#endif  // RMW_EMAIL_CPP__TAKE_HPP_
