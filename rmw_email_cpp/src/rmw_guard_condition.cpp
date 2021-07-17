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

#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"

#include "email/guard_condition.hpp"

#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/types.hpp"

static rmw_guard_condition_t * _create_guard_condition()
{
  auto email_guard_condition = new (std::nothrow) email::GuardCondition();
  if (nullptr == email_guard_condition) {
    RMW_SET_ERROR_MSG("failed to allocate guard condition impl");
    return nullptr;
  }

  auto rmw_email_guard_condition = new (std::nothrow) rmw_email_guard_condition_t;
  if (nullptr == email_guard_condition) {
    RMW_SET_ERROR_MSG("failed to allocate rmw guard condition");
    return nullptr;
  }
  rmw_email_guard_condition->email_guard_condition = email_guard_condition;

  rmw_guard_condition_t * guard_condition = new (std::nothrow) rmw_guard_condition_t;
  if (nullptr == guard_condition) {
    RMW_SET_ERROR_MSG("failed to allocate guard condition");
    return nullptr;
  }
  guard_condition->implementation_identifier = email_identifier;
  guard_condition->data = rmw_email_guard_condition;
  return guard_condition;
}

static rmw_ret_t _destroy_guard_condition(rmw_guard_condition_t * guard_condition)
{
  auto rmw_email_guard_condition = static_cast<rmw_email_guard_condition_t *>(
    guard_condition->data);
  auto email_guard_condition = rmw_email_guard_condition->email_guard_condition;
  delete email_guard_condition;
  delete rmw_email_guard_condition;
  delete guard_condition;
  return RMW_RET_OK;
}

extern "C" rmw_guard_condition_t * rmw_create_guard_condition(rmw_context_t * context)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(context, nullptr);
  return _create_guard_condition();
}

extern "C" rmw_ret_t rmw_destroy_guard_condition(rmw_guard_condition_t * guard_condition)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(guard_condition, RMW_RET_INVALID_ARGUMENT);
  return _destroy_guard_condition(guard_condition);
}

extern "C" rmw_ret_t rmw_trigger_guard_condition(const rmw_guard_condition_t * guard_condition)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(guard_condition, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    guard_condition,
    guard_condition->implementation_identifier,
    email_identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  auto rmw_email_guard_condition = static_cast<rmw_email_guard_condition_t *>(
    guard_condition->data);
  auto email_guard_condition = rmw_email_guard_condition->email_guard_condition;
  email_guard_condition->trigger();
  return RMW_RET_OK;
}
