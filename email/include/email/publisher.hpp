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

#ifndef EMAIL__PUBLISHER_HPP_
#define EMAIL__PUBLISHER_HPP_

#include <memory>
#include <string>

#include "email/email/sender.hpp"
#include "email/pub_sub.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Message publisher.
/**
 * Uses emails, with the topic as the email subject and the data as the email body.
 */
class Publisher : public PubSubObject
{
public:
  /// Constructor.
  /**
   * \param topic_name the topic name to publish on
   */
  explicit Publisher(const std::string & topic_name);
  Publisher(const Publisher &) = delete;
  Publisher & operator=(const Publisher &) = delete;
  virtual ~Publisher();

  /// Publish message.
  /**
   * \param message the message
   */
  void
  publish(const std::string & message);

private:
  std::shared_ptr<EmailSender> sender_;
};

}  // namespace email

#endif  // EMAIL__PUBLISHER_HPP_
