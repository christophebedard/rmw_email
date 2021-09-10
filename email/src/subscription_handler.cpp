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

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include "email/context.hpp"
#include "email/email/handler.hpp"
#include "email/email/info.hpp"
#include "email/email/polling_manager.hpp"
#include "email/log.hpp"
#include "email/lttng.hpp"
#include "email/message_info.hpp"
#include "email/safe_queue.hpp"
#include "email/subscription_handler.hpp"

namespace email
{

SubscriptionHandler::SubscriptionHandler()
: EmailHandler(),
  logger_(log::create("SubscriptionHandler")),
  subscriptions_mutex_(),
  subscriptions_()
{
  logger_->debug("initialized");
}

SubscriptionHandler::~SubscriptionHandler()
{
  logger_->debug("destroying");
}

void
SubscriptionHandler::register_handler()
{
  // Register handler with the polling manager
  get_global_context()->get_polling_manager()->register_handler(
    [handler = std::weak_ptr<SubscriptionHandler>(this->shared_from_this())](
      const struct EmailData & data) {
      if (auto handler_ptr = handler.lock()) {
        handler_ptr->handle(data);
      }
      // Do nothing if the pointer could not be locked
    });
  logger_->debug("registered");
}

void
SubscriptionHandler::register_subscription(
  const std::string & topic_name,
  MessageQueue::SharedPtr message_queue)
{
  {
    std::scoped_lock<std::mutex> lock(subscriptions_mutex_);
    subscriptions_.insert({topic_name, message_queue});
  }
  logger_->debug("subscription registered with topic name: {}", topic_name);
}

void
SubscriptionHandler::handle(const struct EmailData & data)
{
  logger_->debug("handling new email");
  const std::string & topic = data.content.subject;
  const std::string & msg = data.content.body;
  auto msg_info_opt = MessageInfo::from_headers(data.additional_headers);
  if (!msg_info_opt) {
    logger_->debug("not a subscription message");
    return;
  }
  const MessageInfo & msg_info = msg_info_opt.value();

  // Push it to the right queue
  {
    std::scoped_lock<std::mutex> lock(subscriptions_mutex_);
    auto range = subscriptions_.equal_range(topic);
    for (auto it = range.first; it != range.second; ++it) {
      // Push message content to the queue
      logger_->debug("adding message to subscription queue with topic: {}", topic);
      EMAIL_TRACEPOINT(
        subscription_handle,
        static_cast<const void *>(it->second.get()),
        msg_info.source_timestamp().nanoseconds());
      it->second->push({msg, msg_info});
    }
  }
}

}  // namespace email
