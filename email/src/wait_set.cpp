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
#include "email/service_client.hpp"
#include "email/service_server.hpp"
#include "email/subscriber.hpp"
#include "email/wait_set.hpp"

using namespace std::chrono_literals;

namespace email
{

// TODO(christophebedard) use static logger or create unique waitset name
WaitSet::WaitSet(
  std::vector<std::shared_ptr<Subscriber>> subscriptions,
  std::vector<std::shared_ptr<ServiceClient>> clients,
  std::vector<std::shared_ptr<ServiceServer>> servers)
: logger_(log::get_or_create("WaitSet")),
  subscriptions_(std::move(subscriptions)),
  clients_(std::move(clients)),
  servers_(std::move(servers))
{}

WaitSet::~WaitSet() {}

const std::vector<std::shared_ptr<Subscriber>> &
WaitSet::get_subscriptions() const
{
  return subscriptions_;
}

const std::vector<std::shared_ptr<ServiceClient>> &
WaitSet::get_clients() const
{
  return clients_;
}

const std::vector<std::shared_ptr<ServiceServer>> &
WaitSet::get_servers() const
{
  return servers_;
}

bool
WaitSet::wait(const std::chrono::milliseconds timeout)
{
  auto start = std::chrono::steady_clock::now();
  auto loop_predicate = get_loop_predicate(timeout, start);
  logger_->debug("wait start: timeout={} ms", timeout.count());

  // Success is defined as having at least one sub/client/server ready
  bool success = false;

  std::vector<bool> subscriptions_ready(subscriptions_.size(), false);
  std::vector<bool> clients_ready(clients_.size(), false);
  std::vector<bool> servers_ready(servers_.size(), false);
  do {
    // Subscriptions
    for (std::size_t i = 0u; i < subscriptions_.size(); i++) {
      if (!subscriptions_ready[i] && subscriptions_[i]->has_message()) {
        subscriptions_ready[i] = true;
        success = true;
      }
    }
    // Clients
    for (std::size_t i = 0u; i < clients_.size(); i++) {
      if (!clients_ready[i] && clients_[i]->has_response()) {
        clients_ready[i] = true;
        success = true;
      }
    }
    // Servers
    for (std::size_t i = 0u; i < servers_.size(); i++) {
      if (!servers_ready[i] && servers_[i]->has_request()) {
        servers_ready[i] = true;
        success = true;
      }
    }
    if (success) {
      break;
    }
  } while (loop_predicate());

  if (!success) {
    // Timed out
    logger_->debug("wait done: timed out");
    return true;
  }
  // Apply statuses to vectors
  apply_status<>(subscriptions_, subscriptions_ready);
  apply_status<>(clients_, clients_ready);
  apply_status<>(servers_, servers_ready);
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
