// Copyright 2020 Christophe Bedard
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

#ifndef EMAIL__SUBSCRIBER_MANAGER_HPP_
#define EMAIL__SUBSCRIBER_MANAGER_HPP_

#include <atomic>
#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "email/email/receiver.hpp"
#include "email/safe_queue.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Manager for distributing messages to susbcribers.
/**
 * Does the polling for new emails and distributes them to the right subscriber(s).
 */
class SubscriberManager
{
public:
  /// Constructor.
  /**
   * \param receiver the email receiver to use for getting emails
   * \param debug the debug status
   */
  explicit SubscriberManager(std::shared_ptr<EmailReceiver> receiver, const bool debug);
  SubscriberManager(const SubscriberManager &) = delete;
  ~SubscriberManager();

  /// Register a subscriber with the manager.
  /**
   * TODO(christophebedard) support multiple subscribers for a topic (using a multimap)
   *
   * \param topic the topic
   * \param message_queue the message queue of the subscriber
   */
  void
  register_subscriber(
    const std::string & topic,
    std::shared_ptr<SafeQueue<std::string>> message_queue);

  /// Get status.
  /**
   * \return true if it has been started, false otherwise
   */
  bool
  has_started() const;

  /// Start manager.
  void
  start();

  /// Shut down manager and internal thread.
  void
  shutdown();

private:
  /// Thread function for polling for new emails.
  void
  poll_thread();

  std::shared_ptr<EmailReceiver> receiver_;
  bool debug_;
  bool has_started_;
  std::atomic_bool do_shutdown_;
  std::thread thread_;
  std::mutex map_mutex_;
  std::map<std::string, std::shared_ptr<SafeQueue<std::string>>> map_;

  static constexpr auto POLLING_PERIOD = std::chrono::milliseconds(1);
};

}  // namespace email

#endif  // EMAIL__SUBSCRIBER_MANAGER_HPP_
