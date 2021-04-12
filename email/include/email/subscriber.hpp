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

#ifndef EMAIL__SUBSCRIBER_HPP_
#define EMAIL__SUBSCRIBER_HPP_

#include <chrono>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/pub_sub.hpp"
#include "email/safe_queue.hpp"
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

  Subscriber(const Subscriber &) = delete;
  Subscriber & operator=(const Subscriber &) = delete;
  EMAIL_PUBLIC
  virtual ~Subscriber();

  /// Check if the subscriber has a message.
  /**
   * \return true if there is a message, false otherwise
   */
  EMAIL_PUBLIC
  bool
  has_message();

  /// Get a message if there is one.
  /**
   * \return the message, or `std::nullopt` if there is none
   */
  EMAIL_PUBLIC
  std::optional<std::string>
  get_message();

  /// Get a message, waiting until one is available.
  /**
   * TODO(christophebedard) use a timeout?
   *
   * \return the message
   */
  EMAIL_PUBLIC
  std::string
  get_message_and_wait();

private:
  std::shared_ptr<SafeQueue<std::string>> messages_;

  static constexpr auto WAIT_TIME = std::chrono::milliseconds(1);
};

}  // namespace email

#endif  // EMAIL__SUBSCRIBER_HPP_
