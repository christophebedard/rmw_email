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

#ifndef EMAIL__SUBSCRIPTION_HANDLER_HPP_
#define EMAIL__SUBSCRIPTION_HANDLER_HPP_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "email/safe_queue.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email handler for subscriptions.
/**
 * Distributes them to the right subscriber(s).
 */
class SubscriptionHandler
{
public:
  /// Constructor.
  /**
   * \param debug the debug status
   */
  explicit SubscriptionHandler(const bool debug);
  SubscriptionHandler(const SubscriptionHandler &) = delete;
  SubscriptionHandler & operator=(const SubscriptionHandler &) = delete;
  ~SubscriptionHandler();

  /// Handle new email.
  /**
   * To be called by the `PollingManager`.
   *
   * \param data the new email data
   */
  void
  handle(const struct EmailData & data);

  /// Register a subscriber with the handler.
  /**
   * \param topic the topic
   * \param message_queue the message queue of the subscriber
   */
  void
  register_subscriber(
    const std::string & topic,
    std::shared_ptr<SafeQueue<std::string>> message_queue);

private:
  bool debug_;
  std::mutex subscribers_mutex_;
  std::multimap<std::string, std::shared_ptr<SafeQueue<std::string>>> subscribers_;
};

}  // namespace email

#endif  // EMAIL__SUBSCRIPTION_HANDLER_HPP_
