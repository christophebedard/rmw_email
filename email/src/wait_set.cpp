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
#include <memory>
#include <utility>
#include <vector>

#include "email/log.hpp"
#include "email/guard_condition.hpp"
#include "email/service_client.hpp"
#include "email/service_server.hpp"
#include "email/subscription.hpp"
#include "email/wait_set.hpp"

using namespace std::chrono_literals;

namespace email
{

WaitSet::WaitSet()
: logger_(log::get_or_create("WaitSet")),
  subscriptions_(),
  clients_(),
  servers_(),
  guard_conditions_()
{
  logger_->debug("created");
}

WaitSet::~WaitSet()
{
  // Make sure to properly clear & release the waitables
  release_guard_conditions(guard_conditions_);
  clear();
  logger_->debug("destroyed");
}

void
WaitSet::check_guard_condition(GuardCondition * guard_condition)
{
  if (guard_condition->exchange_in_use(true)) {
    throw GuardConditionAlreadyInUseError();
  }
}

void
WaitSet::release_guard_conditions(std::vector<GuardCondition *> & guard_conditions)
{
  for (auto guard_condition : guard_conditions) {
    if (guard_condition) {
      guard_condition->reset();
      guard_condition->exchange_in_use(false);
    }
  }
}

void
WaitSet::add_subscription(Subscription * subscription)
{
  logger_->debug("adding subscription: {}", subscription->get_topic_name());
  subscriptions_.push_back(subscription);
}

void
WaitSet::add_client(ServiceClient * client)
{
  logger_->debug("adding client: {}", client->get_service_name());
  clients_.push_back(client);
}

void
WaitSet::add_server(ServiceServer * server)
{
  logger_->debug("adding server: {}", server->get_service_name());
  servers_.push_back(server);
}

void
WaitSet::add_guard_condition(GuardCondition * guard_condition)
{
  check_guard_condition(guard_condition);
  logger_->debug("adding guard condition");
  guard_conditions_.push_back(guard_condition);
}

const std::vector<Subscription *> &
WaitSet::get_subscriptions() const
{
  return subscriptions_;
}

const std::vector<ServiceClient *> &
WaitSet::get_clients() const
{
  return clients_;
}

const std::vector<ServiceServer *> &
WaitSet::get_servers() const
{
  return servers_;
}

const std::vector<GuardCondition *> &
WaitSet::get_guard_conditions() const
{
  return guard_conditions_;
}

void
WaitSet::clear()
{
  subscriptions_.clear();
  clients_.clear();
  servers_.clear();
  guard_conditions_.clear();
  logger_->debug("cleared");
}

bool
WaitSet::wait(const std::chrono::milliseconds timeout)
{
  if (0 ==
    (subscriptions_.size() + clients_.size() + servers_.size() + guard_conditions_.size()))
  {
    logger_->debug("waiting on empty waitset");
  }

  auto start = std::chrono::steady_clock::now();
  auto loop_predicate = get_loop_predicate(timeout, start);
  logger_->debug("wait start: timeout={} ms", timeout.count());

  // Success is defined as having at least one sub/client/server/guard condition ready
  bool success = false;

  std::vector<bool> subscriptions_ready(subscriptions_.size(), false);
  std::vector<bool> clients_ready(clients_.size(), false);
  std::vector<bool> servers_ready(servers_.size(), false);
  std::vector<bool> guard_conditions_ready(guard_conditions_.size(), false);
  do {
    // Subscriptions
    for (std::size_t i = 0u; i < subscriptions_.size(); i++) {
      if (!subscriptions_ready[i] && subscriptions_[i]->has_message()) {
        subscriptions_ready[i] = true;
        success = true;
        logger_->debug("ready subscription: {}", subscriptions_[i]->get_topic_name());
      }
    }
    // Clients
    for (std::size_t i = 0u; i < clients_.size(); i++) {
      if (!clients_ready[i] && clients_[i]->has_response()) {
        clients_ready[i] = true;
        success = true;
        logger_->debug("ready client: {}", clients_[i]->get_service_name());
      }
    }
    // Servers
    for (std::size_t i = 0u; i < servers_.size(); i++) {
      if (!servers_ready[i] && servers_[i]->has_request()) {
        servers_ready[i] = true;
        success = true;
        logger_->debug("ready server: {}", servers_[i]->get_service_name());
      }
    }
    // Guard conditions
    for (std::size_t i = 0u; i < guard_conditions_.size(); i++) {
      if (!guard_conditions_ready[i] && guard_conditions_[i]->triggered()) {
        guard_conditions_ready[i] = true;
        success = true;
        logger_->debug("ready guard condition");
      }
    }
    if (success) {
      break;
    }
  } while (loop_predicate());

  release_guard_conditions(guard_conditions_);

  // Apply statuses to vectors
  apply_status<>(subscriptions_, subscriptions_ready);
  apply_status<>(clients_, clients_ready);
  apply_status<>(servers_, servers_ready);
  apply_status<>(guard_conditions_, guard_conditions_ready);
  if (!success) {
    // Timed out
    logger_->debug("wait done: timed out");
    return true;
  }
  logger_->debug("wait done: successful");
  return false;
}

std::function<bool()>
WaitSet::get_loop_predicate(
  std::chrono::nanoseconds timeout_ns,
  std::chrono::steady_clock::time_point start)
{
  if (timeout_ns >= 0ns) {
    // Loop until the end
    auto end = start + timeout_ns;
    return [end]() -> bool {return std::chrono::steady_clock::now() < end;};
  }
  // Loop forever
  return []() -> bool {return true;};
}

}  // namespace email
