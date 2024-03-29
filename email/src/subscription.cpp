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
#include "email/email/info.hpp"
#include "email/log.hpp"
#include "email/lttng.hpp"
#include "email/message_info.hpp"
#include "email/pub_sub.hpp"
#include "email/safe_queue.hpp"
#include "email/subscription.hpp"
#include "email/subscription_handler.hpp"

namespace email
{

Subscription::Subscription(const std::string & topic_name)
: PubSubObject(topic_name),
  logger_(log::get_or_create("Subscription::" + topic_name)),
  messages_(std::make_shared<SubscriptionHandler::MessageQueue>())
{
  logger_->debug("created with GID: {}", get_gid());
  // Register with handler
  get_global_context()->get_subscription_handler()->register_subscription(
    get_topic_name(),
    messages_);
  EMAIL_TRACEPOINT(
    create_subscription,
    static_cast<const void *>(this),
    get_topic_name().c_str(),
    get_gid().value(),
    static_cast<const void *>(messages_.get()));
}

Subscription::~Subscription()
{
  logger_->debug("destroying");
}

bool
Subscription::has_message() const
{
  return !messages_->empty();
}

std::optional<std::string>
Subscription::get_message()
{
  auto message_with_info_opt = get_message_with_info();
  if (!message_with_info_opt) {
    return std::nullopt;
  }
  return message_with_info_opt.value().first;
}

std::optional<std::pair<std::string, MessageInfo>>
Subscription::get_message_with_info()
{
  if (!has_message()) {
    return std::nullopt;
  }
  return messages_->dequeue();
}

}  // namespace email
