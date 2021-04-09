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

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "email/context.hpp"
#include "email/email/polling_manager.hpp"
#include "email/log.hpp"
#include "email/safe_queue.hpp"
#include "email/subscription_handler.hpp"
#include "email/types.hpp"

namespace email
{

SubscriptionHandler::SubscriptionHandler()
: logger_(log::create("SubscriptionHandler")),
  subscribers_mutex_(),
  subscribers_()
{
  // Register handler with the polling manager
  get_global_context()->get_polling_manager()->register_handler(
    std::bind(
      &SubscriptionHandler::handle,
      this,
      std::placeholders::_1));
  logger_->debug("initialized");
}

SubscriptionHandler::~SubscriptionHandler() {}

void
SubscriptionHandler::register_subscriber(
  const std::string & topic_name,
  std::shared_ptr<SafeQueue<std::string>> message_queue)
{
  std::scoped_lock<std::mutex> lock(subscribers_mutex_);
  subscribers_.insert({topic_name, message_queue});
}

void
SubscriptionHandler::handle(const struct EmailData & data)
{
  logger_->debug("handle() called");
  const std::string & topic = data.content.subject;
  // Push it to the right queue
  {
    std::scoped_lock<std::mutex> lock(subscribers_mutex_);
    auto range = subscribers_.equal_range(topic);
    for (auto it = range.first; it != range.second; ++it) {
      // Push message content to the queue
      logger_->debug("pushing body to queue");
      it->second->push(data.content.body);
    }
  }
}

}  // namespace email
