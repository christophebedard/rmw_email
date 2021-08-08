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

#include "email/subscription.hpp"
#include "rcpputils/scope_exit.hpp"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"
#include "rmw/validate_full_topic_name.h"
#include "tracetools/tracetools.h"

#include "rmw_email_cpp/gid.hpp"
#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/macros.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_ret_t rmw_init_subscription_allocation(
  const rosidl_message_type_support_t * type_support,
  const rosidl_runtime_c__Sequence__bound * message_bounds,
  rmw_subscription_allocation_t * allocation)
{
  static_cast<void>(type_support);
  static_cast<void>(message_bounds);
  static_cast<void>(allocation);
  RMW_SET_ERROR_MSG("rmw_init_subscription_allocation: unimplemented");
  return RMW_RET_UNSUPPORTED;
}

extern "C" rmw_ret_t rmw_fini_subscription_allocation(rmw_subscription_allocation_t * allocation)
{
  static_cast<void>(allocation);
  RMW_SET_ERROR_MSG("rmw_fini_subscription_allocation: unimplemented");
  return RMW_RET_UNSUPPORTED;
}

static rmw_subscription_t * _create_subscription(
  const char * topic_name,
  const rmw_subscription_options_t * subscription_options,
  const rosidl_message_type_support_t * type_supports)
{
  rmw_email_sub_t * sub = new (std::nothrow) rmw_email_sub_t();
  RET_ALLOC_X(sub, return nullptr);
  sub->type_supports = *type_supports;

  // Create email subscription
  auto email_sub = new (std::nothrow) email::Subscription(topic_name);
  RET_ALLOC_X(email_sub, return nullptr);
  sub->email_sub = email_sub;

  // Get GID from email subscription
  sub->gid = rmw_email_cpp::convert_gid(email_sub->get_gid());

  // Put everything together
  rmw_subscription_t * rmw_subscription = rmw_subscription_allocate();
  RET_ALLOC_X(rmw_subscription, return nullptr);
  auto cleanup_rmw_subscription = rcpputils::make_scope_exit(
    [rmw_subscription]() {
      rmw_free(const_cast<char *>(rmw_subscription->topic_name));
      rmw_subscription_free(rmw_subscription);
    });

  rmw_subscription->implementation_identifier = rmw_email_cpp::identifier;
  rmw_subscription->data = sub;
  rmw_subscription->topic_name = reinterpret_cast<char *>(rmw_allocate(strlen(topic_name) + 1));
  RET_ALLOC_X(rmw_subscription->topic_name, return nullptr);
  memcpy(const_cast<char *>(rmw_subscription->topic_name), topic_name, strlen(topic_name) + 1);
  rmw_subscription->options = *subscription_options;
  rmw_subscription->can_loan_messages = false;

  cleanup_rmw_subscription.cancel();
  TRACEPOINT(rmw_subscription_init, static_cast<const void *>(rmw_subscription), sub->gid.data);
  return rmw_subscription;
}

extern "C" rmw_subscription_t * rmw_create_subscription(
  const rmw_node_t * node,
  const rosidl_message_type_support_t * type_supports,
  const char * topic_name,
  const rmw_qos_profile_t * qos_policies,
  const rmw_subscription_options_t * subscription_options)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(type_supports, nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, nullptr);
  if (0 == strlen(topic_name)) {
    RMW_SET_ERROR_MSG("topic_name argument is an empty string");
    return nullptr;
  }
  RMW_CHECK_ARGUMENT_FOR_NULL(qos_policies, nullptr);

  // Validate topic name
  // TODO(christophebedard) extract to function since rmw_create_publisher does the same thing
  int validation_result = RMW_TOPIC_VALID;
  rmw_ret_t ret = rmw_validate_full_topic_name(topic_name, &validation_result, nullptr);
  if (RMW_RET_OK != ret) {
    return nullptr;
  }
  if (RMW_TOPIC_VALID != validation_result) {
    const char * reason = rmw_full_topic_name_validation_result_string(validation_result);
    RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("invalid topic name: %s", reason);
    return nullptr;
  }

  return _create_subscription(topic_name, subscription_options, type_supports);
}

static rmw_ret_t _destroy_subscription(rmw_subscription_t * subscription)
{
  rmw_email_sub_t * sub = static_cast<rmw_email_sub_t *>(subscription->data);
  email::Subscription * email_sub = sub->email_sub;
  delete email_sub;
  delete sub;
  rmw_free(const_cast<char *>(subscription->topic_name));
  rmw_subscription_free(subscription);
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_destroy_subscription(rmw_node_t * node, rmw_subscription_t * subscription)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    subscription,
    subscription->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  return _destroy_subscription(subscription);
}

extern "C" rmw_ret_t rmw_subscription_count_matched_publishers(
  const rmw_subscription_t * subscription, size_t * publisher_count)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    subscription,
    subscription->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(publisher_count, RMW_RET_INVALID_ARGUMENT);

  // We're always listening
  *publisher_count = 1u;
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_subscription_get_actual_qos(
  const rmw_subscription_t * subscription,
  rmw_qos_profile_t * qos)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    subscription,
    subscription->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(qos, RMW_RET_INVALID_ARGUMENT);

  // TODO(christophebedard) figure out
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_count_subscribers(
  const rmw_node_t * node,
  const char * topic_name,
  size_t * count)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(topic_name, RMW_RET_INVALID_ARGUMENT);

  // Validate topic name
  int validation_result = RMW_TOPIC_VALID;
  rmw_ret_t ret = rmw_validate_full_topic_name(topic_name, &validation_result, nullptr);
  if (RMW_RET_OK != ret) {
    return ret;
  }
  if (RMW_TOPIC_VALID != validation_result) {
    const char * reason = rmw_full_topic_name_validation_result_string(validation_result);
    RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("topic_name argument is invalid: %s", reason);
    return RMW_RET_INVALID_ARGUMENT;
  }

  RMW_CHECK_ARGUMENT_FOR_NULL(count, RMW_RET_INVALID_ARGUMENT);
  // TODO(christophebedard) figure out
  *count = 1u;
  return RMW_RET_OK;
}
