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

#include "email/publisher.hpp"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"

#include "rmw_email_cpp/conversion.hpp"
#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_ret_t rmw_publish(
  const rmw_publisher_t * publisher,
  const void * ros_message,
  rmw_publisher_allocation_t * allocation)
{
  static_cast<void>(allocation);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    publisher, "publisher handle is null",
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    publisher, publisher->implementation_identifier, rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    ros_message, "ros message handle is null",
    return RMW_RET_INVALID_ARGUMENT);

  auto rmw_email_pub = static_cast<rmw_email_pub_t *>(publisher->data);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    rmw_email_pub, "rmw_email_pub is null",
    return RMW_RET_ERROR);
  assert(rmw_email_pub);
  email::Publisher * email_pub = rmw_email_pub->email_pub;
  RMW_CHECK_FOR_NULL_WITH_MSG(
    email_pub, "email_pub is null",
    return RMW_RET_ERROR);

  // Convert to YAML string and publish
  const std::string msg_yaml = rmw_email_cpp::msg_to_yaml(rmw_email_pub, ros_message);
  assert(!msg_yaml.empty());
  email_pub->publish(msg_yaml);
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_publish_serialized_message(
  const rmw_publisher_t * publisher,
  const rmw_serialized_message_t * serialized_message,
  rmw_publisher_allocation_t * allocation)
{
  static_cast<void>(allocation);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    publisher, "publisher handle is null",
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    publisher, publisher->implementation_identifier, rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    serialized_message, "serialized message handle is null",
    return RMW_RET_INVALID_ARGUMENT);

  auto pub = static_cast<email::Publisher *>(publisher->data);
  assert(pub);

  RMW_SET_ERROR_MSG("rmw_publish_serialized_message not implemented for rmw_email_cpp");
  return RMW_RET_UNSUPPORTED;
}

extern "C" rmw_ret_t rmw_publish_loaned_message(
  const rmw_publisher_t * publisher,
  void * ros_message,
  rmw_publisher_allocation_t * allocation)
{
  static_cast<void>(allocation);
  static_cast<void>(publisher);
  static_cast<void>(ros_message);
  RMW_SET_ERROR_MSG("rmw_publish_loaned_message not implemented for rmw_email_cpp");
  return RMW_RET_UNSUPPORTED;
}
