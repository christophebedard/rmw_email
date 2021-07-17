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
#include "email/service_client.hpp"
#include "email/service_server.hpp"
#include "email/subscriber.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Wait set.
/**
 * Waits on a set of subscriptions, clients, and servers.
 */
class WaitSet
{
public:
  /// Constructor.
  EMAIL_PUBLIC
  WaitSet(
    std::vector<std::shared_ptr<Subscriber>> subscriptions,
    std::vector<std::shared_ptr<ServiceClient>> clients = {},
    std::vector<std::shared_ptr<ServiceServer>> servers = {});

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
   * \param timeout the timeout
   * \return whether the wait call timed out
   */
  EMAIL_PUBLIC
  bool
  wait(const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

  /// Get the subscriptions.
  EMAIL_PUBLIC
  const std::vector<std::shared_ptr<Subscriber>> &
  get_subscriptions() const;

  /// Get the clients.
  EMAIL_PUBLIC
  const std::vector<std::shared_ptr<ServiceClient>> &
  get_clients() const;

  /// Get the servers.
  EMAIL_PUBLIC
  const std::vector<std::shared_ptr<ServiceServer>> &
  get_servers() const;

private:
  EMAIL_DISABLE_COPY(WaitSet)

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
      if (ready[i]) {
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
  std::vector<std::shared_ptr<Subscriber>> subscriptions_;
  std::vector<std::shared_ptr<ServiceClient>> clients_;
  std::vector<std::shared_ptr<ServiceServer>> servers_;
};

}  // namespace email

#endif  // EMAIL__WAIT_SET_HPP_