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

#ifndef EMAIL__SUBSCRIBER_HPP_
#define EMAIL__SUBSCRIBER_HPP_

#include <chrono>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <utility>

#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/message_info.hpp"
#include "email/pub_sub.hpp"
#include "email/safe_queue.hpp"
#include "email/subscription_handler.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Message subscriber.
/**
 * Uses emails, with the topic name as the email subject and the data as the email body.
 * TODO(christophebedard) add take to get a vector of all available messages?
 */
class Subscriber : public PubSubObject
{
public:
  /// Constructor.
  /**
   * \param topic_name the topic name to subscribe to
   */
  EMAIL_PUBLIC
  explicit Subscriber(const std::string & topic_name);

  EMAIL_PUBLIC
  virtual ~Subscriber();

  /// Check if the subscriber has a message.
  /**
   * \return true if there is a message, false otherwise
   */
  EMAIL_PUBLIC
  bool
  has_message() const;

  /// Get a message if there is one.
  /**
   * This is the same as "taking" a message if there is one.
   *
   * \return the message, or `std::nullopt` if there is none
   */
  EMAIL_PUBLIC
  std::optional<std::string>
  get_message();

  /// Get a message with info if there is one.
  /**
   * This is the same as "taking" a message with its info if there is one.
   *
   * \return the message & message info pair, or `std::nullopt` if there is none
   */
  EMAIL_PUBLIC
  std::optional<std::pair<std::string, MessageInfo>>
  get_message_with_info();

private:
  EMAIL_DISABLE_COPY(Subscriber)

  std::shared_ptr<Logger> logger_;
  SubscriptionHandler::SubscriberQueue::SharedPtr messages_;
};

}  // namespace email

#endif  // EMAIL__SUBSCRIBER_HPP_
