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

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>
#include <utility>

#include "email/context.hpp"
#include "email/log.hpp"
#include "email/message_info.hpp"
#include "email/pub_sub.hpp"
#include "email/safe_queue.hpp"
#include "email/subscriber.hpp"
#include "email/subscription_handler.hpp"
#include "email/types.hpp"

namespace email
{

Subscriber::Subscriber(const std::string & topic_name)
: PubSubObject(topic_name),
  logger_(log::get_or_create("Subscriber::" + topic_name)),
  messages_(std::make_shared<SubscriptionHandler::SubscriberQueue>())
{
  logger_->debug("created with GID: {}", get_gid());
  // Register with handler
  get_global_context()->get_subscription_handler()->register_subscriber(
    get_topic_name(),
    messages_);
}

Subscriber::~Subscriber()
{
  logger_->debug("destroying");
}

bool
Subscriber::has_message() const
{
  return !messages_->empty();
}

std::optional<std::string>
Subscriber::get_message()
{
  if (!has_message()) {
    return std::nullopt;
  }
  return messages_->dequeue().first;
}

std::optional<std::pair<std::string, MessageInfo>>
Subscriber::get_message_with_info()
{
  if (!has_message()) {
    return std::nullopt;
  }
  return messages_->dequeue();
}

}  // namespace email
