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

#include <string>

#include "email/message_info.hpp"
#include "email/subscription.hpp"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"
#include "tracetools/tracetools.h"

#include "rmw_email_cpp/conversion.hpp"
#include "rmw_email_cpp/gid.hpp"
#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/timestamp.hpp"
#include "rmw_email_cpp/types.hpp"

namespace rmw_email_cpp
{

rmw_ret_t rmw_take(
  const rmw_subscription_t * subscription,
  void * ros_message,
  bool * taken,
  rmw_subscription_allocation_t * allocation,
  rmw_message_info_t * message_info)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    subscription handle,
    subscription->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(ros_message, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);
  static_cast<void>(allocation);

  auto rmw_email_sub = static_cast<rmw_email_sub_t *>(subscription->data);
  email::Subscription * email_sub = rmw_email_sub->email_sub;

  // Take message with info
  rmw_ret_t ret = RMW_RET_OK;
  auto msg_with_info_opt = email_sub->get_message_with_info();
  if (!msg_with_info_opt.has_value()) {
    *taken = false;
  } else {
    *taken = true;
    auto msg_with_info = msg_with_info_opt.value();
    const std::string & msg_yaml = msg_with_info.first;
    const email::MessageInfo msg_info = msg_with_info.second;

    // Convert YAML string back to message
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    if (!rmw_email_cpp::yaml_to_msg(rmw_email_sub, msg_yaml, ros_message, &allocator)) {
      ret = RMW_RET_ERROR;
    }

    // Copy info if needed
    if (message_info) {
      message_info->publisher_gid = rmw_email_cpp::convert_gid(msg_info.publisher_gid());
      message_info->source_timestamp =
        rmw_email_cpp::convert_timestamp(msg_info.source_timestamp());
      message_info->received_timestamp =
        rmw_email_cpp::convert_timestamp(msg_info.received_timestamp());
      message_info->from_intra_process = false;
    }
  }

  TRACEPOINT(
    rmw_take,
    static_cast<const void *>(subscription),
    ros_message,
    (msg_with_info_opt.has_value() ?
    msg_with_info_opt.value().second.source_timestamp().nanoseconds() : 0LL),
    *taken);
  return ret;
}

}  // namespace rmw_email_cpp
