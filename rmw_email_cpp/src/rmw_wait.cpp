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

#include <chrono>

#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"

#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_wait_set_t * rmw_create_wait_set(rmw_context_t * context, size_t max_conditions)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(context, nullptr);
  static_cast<void>(max_conditions);

  auto email_waitset = new (std::nothrow) email::WaitSet({}, {}, {}, {});
  if (nullptr == email_waitset) {
    RMW_SET_ERROR_MSG("failed to allocate waitset impl");
    return nullptr;
  }

  auto rmw_email_waitset = new (std::nothrow) rmw_email_wait_set_t;
  if (nullptr == rmw_email_waitset) {
    RMW_SET_ERROR_MSG("failed to allocate rmw waitset");
    return nullptr;
  }
  rmw_email_waitset->email_waitset = email_waitset;

  rmw_wait_set_t * wait_set = rmw_wait_set_allocate();
  if (nullptr == wait_set) {
    RMW_SET_ERROR_MSG("failed to allocate waitset");
    return nullptr;
  }
  wait_set->implementation_identifier = email_identifier;
  wait_set->data = rmw_email_waitset;
  return wait_set;
}

extern "C" rmw_ret_t rmw_destroy_wait_set(rmw_wait_set_t * wait_set)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(wait_set, RMW_RET_ERROR);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    wait_set,
    wait_set->implementation_identifier,
    email_identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  auto rmw_email_waitset = static_cast<rmw_email_wait_set_t *>(wait_set->data);
  auto email_waitset = rmw_email_waitset->email_waitset;
  delete email_waitset;
  delete rmw_email_waitset;
  rmw_wait_set_free(wait_set);
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_wait(
  rmw_subscriptions_t * subscriptions,
  rmw_guard_conditions_t * guard_conditions,
  rmw_services_t * services,
  rmw_clients_t * clients,
  rmw_events_t * events,
  rmw_wait_set_t * wait_set,
  const rmw_time_t * wait_timeout)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(wait_set, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    wait_set,
    wait_set->implementation_identifier,
    email_identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  auto rmw_email_waitset = static_cast<rmw_email_wait_set_t *>(wait_set->data);
  auto email_waitset = rmw_email_waitset->email_waitset;

  // Add objects to wait set
  if (subscriptions) {
    for (size_t i = 0u; i < subscriptions->subscriber_count; i++) {
      void * data = subscriptions->subscribers[i];
      auto rmw_email_sub = static_cast<rmw_email_sub_t *>(data);
      email_waitset->add_subscription(rmw_email_sub->email_sub);
    }
  }
  if (guard_conditions) {
    for (size_t i = 0u; i < guard_conditions->guard_condition_count; i++) {
      void * data = guard_conditions->guard_conditions[i];
      auto rmw_email_guard_condition = static_cast<rmw_email_guard_condition_t *>(data);
      email_waitset->add_guard_condition(rmw_email_guard_condition->email_guard_condition);
    }
  }
  if (clients) {
    for (size_t i = 0u; i < clients->client_count; i++) {
      void * data = clients->clients[i];
      auto rmw_email_client = static_cast<rmw_email_client_t *>(data);
      email_waitset->add_client(rmw_email_client->email_client);
    }
  }
  if (services) {
    for (size_t i = 0u; i < services->service_count; i++) {
      void * data = services->services[i];
      auto rmw_email_server = static_cast<rmw_email_server_t *>(data);
      email_waitset->add_server(rmw_email_server->email_server);
    }
  }
  // Do nothing with events

  /// Wait
  // If a timeout isn't provided, we wait forever until ready
  std::chrono::milliseconds wait_timeout_chrono_ms = std::chrono::milliseconds(-1);
  if (wait_timeout) {
    auto wait_timeout_chrono =
      std::chrono::seconds(wait_timeout->sec) + std::chrono::nanoseconds(wait_timeout->nsec);
    auto wait_timeout_chrono_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(wait_timeout_chrono);
  }
  const bool timedout = email_waitset->wait(wait_timeout_chrono_ms);

  /// Set elements that were not triggered/that are not ready to nullptr in the arrays
  if (subscriptions) {
    const auto & waitset_subscriptions = email_waitset->get_subscriptions();
    assert(subscriptions->subscriber_count == waitset_subscriptions.size());
    for (size_t i = 0u; i < subscriptions->subscriber_count; i++) {
      if (nullptr == waitset_subscriptions[i]) {
        subscriptions->subscribers[i] = nullptr;
      }
    }
  }
  if (guard_conditions) {
    const auto & waitset_guard_conditions = email_waitset->get_guard_conditions();
    assert(guard_conditions->guard_condition_count == waitset_guard_conditions.size());
    for (size_t i = 0u; i < guard_conditions->guard_condition_count; i++) {
      if (nullptr == waitset_guard_conditions[i]) {
        guard_conditions->guard_conditions[i] = nullptr;
      }
    }
  }
  if (clients) {
    const auto & waitset_clients = email_waitset->get_clients();
    assert(clients->client_count == waitset_clients.size());
    for (size_t i = 0u; i < clients->client_count; i++) {
      if (nullptr == waitset_clients[i]) {
        clients->clients[i] = nullptr;
      }
    }
  }
  if (services) {
    const auto & waitset_servers = email_waitset->get_servers();
    assert(services->service_count == waitset_servers.size());
    for (size_t i = 0u; i < services->service_count; i++) {
      if (nullptr == waitset_servers[i]) {
        services->services[i] = nullptr;
      }
    }
  }
  if (events) {
    // Just set everything to nullptr since we didn't actually wait on these, so none are ready
    for (size_t i = 0u; i < events->event_count; i++) {
      events->events[i] = nullptr;
    }
  }

  return timedout ? RMW_RET_TIMEOUT : RMW_RET_OK;
}
