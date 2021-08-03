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

#ifndef EMAIL__WAIT_SET_HPP_
#define EMAIL__WAIT_SET_HPP_

#include <chrono>
#include <memory>
#include <vector>

#include "email/log.hpp"
#include "email/guard_condition.hpp"
#include "email/service_client.hpp"
#include "email/service_server.hpp"
#include "email/subscription.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Wait set.
/**
 * Waits on a set of subscriptions, clients, and servers.
 * TODO(christophebedard) allow waiting for ALL conditions
 */
class WaitSet
{
public:
  /// Constructor.
  EMAIL_PUBLIC
  WaitSet(
    std::vector<Subscription *> subscriptions = {},
    std::vector<ServiceClient *> clients = {},
    std::vector<ServiceServer *> servers = {},
    std::vector<GuardCondition *> guard_conditions = {});

  /// Constructor.
  EMAIL_PUBLIC
  explicit WaitSet(Subscription * subscription);

  EMAIL_PUBLIC
  ~WaitSet();

  /// Wait.
  /**
   * Wait on the wait set.
   *
   * A negative timeout value means to wait indefinitely.
   * A timeout value equal to 0 means to do a non-blocking check and not wait.
   * A positive timeout value will be used as a timeout.
   *
   * This will wait until at least one object (subscription, client, or server)
   * is ready, or until the timeout has been reached.
   * The objects that are ready will have their respective pointers be non-`nullptr`
   * in their respective vectors; the rest will have their pointers set to `nullptr`.
   *
   * Waiting on an empty waitset with a timeout>=0 is similar to a sleep() call.
   *
   * \param timeout the timeout
   * \return whether the wait call timed out
   */
  EMAIL_PUBLIC
  bool
  wait(const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

  /// Add a subscription.
  EMAIL_PUBLIC
  void
  add_subscription(Subscription * subscription);

  /// Add a client.
  EMAIL_PUBLIC
  void
  add_client(ServiceClient * client);

  /// Add a server.
  EMAIL_PUBLIC
  void
  add_server(ServiceServer * server);

  /// Add a guard condition.
  EMAIL_PUBLIC
  void
  add_guard_condition(GuardCondition * guard_condition);

  /// Get the subscriptions.
  EMAIL_PUBLIC
  const std::vector<Subscription *> &
  get_subscriptions() const;

  /// Get the clients.
  EMAIL_PUBLIC
  const std::vector<ServiceClient *> &
  get_clients() const;

  /// Get the servers.
  EMAIL_PUBLIC
  const std::vector<ServiceServer *> &
  get_servers() const;

  /// Get the guard conditions.
  EMAIL_PUBLIC
  const std::vector<GuardCondition *> &
  get_guard_conditions() const;

  /// Clear the wait set content.
  /**
   * This must be called after calling wait() and checking the result.
   */
  EMAIL_PUBLIC
  void
  clear();

private:
  EMAIL_DISABLE_COPY(WaitSet)

  /// Make sure guard condition is not already in use.
  /**
   * If the guard condition is in use, it throws.
   * If not, it flags the guard condition as being in use.
   *
   * \param guard_condition the guard condition
   * \throw `GuardConditionAlreadyInUseError` if guard condition is already used by a wait set
   */
  static
  void
  check_guard_condition(GuardCondition * guard_condition);

  /// Release guard conditions from this wait set.
  /**
   * By resetting the right flags.
   *
   * \param guard_conditions the guard conditions (must not have any `nullptr`s)
   */
  static
  void
  release_guard_conditions(std::vector<GuardCondition *> & guard_condition);

  /// Apply ready status to vector of objects.
  /**
   * If the Nth ready flag is `false`, the pointer to Nth
   * object in the vector will be set to `nullptr`.
   *
   * ­\param objects the vector of objects
   * \param ready the vector of ready statuses
   * \tparam T the object type
   */
  template<class T>
  void
  apply_status(std::vector<T> & objects, const std::vector<bool> & ready)
  {
    for (std::size_t i = 0u; i < objects.size(); i++) {
      if (!ready[i]) {
        objects[i] = nullptr;
      }
    }
  }

  /// Get predicate that can be used to check if we should loop again.
  std::function<bool()>
  get_loop_predicate(
    std::chrono::nanoseconds timeout_ns,
    std::chrono::steady_clock::time_point start);

  std::shared_ptr<Logger> logger_;
  std::vector<Subscription *> subscriptions_;
  std::vector<ServiceClient *> clients_;
  std::vector<ServiceServer *> servers_;
  std::vector<GuardCondition *> guard_conditions_;
};

}  // namespace email

#endif  // EMAIL__WAIT_SET_HPP_
