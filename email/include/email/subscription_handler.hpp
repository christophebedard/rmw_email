// Copyright 2020-2021 Christophe Bedard
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
#include <utility>

#include "email/safe_queue.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/message_info.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email handler for subscriptions.
/**
 * Distributes new messages to the right subscriber(s).
 */
class SubscriptionHandler
{
public:
  using SubscriberQueue = SafeQueue<std::pair<std::string, MessageInfo>>;

  /// Constructor.
  SubscriptionHandler();

  ~SubscriptionHandler();

  /// Register a subscriber with the handler.
  /**
   * New messages will be added to the subscriber's queue if the topic name matches.
   *
   * \param topic_name the topic name
   * \param message_queue the subscriber's message queue to push the new message to
   */
  void
  register_subscriber(
    const std::string & topic_name,
    SubscriberQueue::SharedPtr message_queue);

  /// Handle new email.
  /**
   * To be called by the `PollingManager`.
   *
   * Adds the message to the queues of subscribers with topic names that match the new message.
   *
   * \param data the new email data
   */
  void
  handle(const struct EmailData & data);

private:
  EMAIL_DISABLE_COPY(SubscriptionHandler)

  std::shared_ptr<Logger> logger_;
  std::mutex subscribers_mutex_;
  std::multimap<std::string, SubscriberQueue::SharedPtr> subscribers_;
};

}  // namespace email

#endif  // EMAIL__SUBSCRIPTION_HANDLER_HPP_
