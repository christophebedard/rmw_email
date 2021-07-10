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

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>
#include <utility>

#include "email/context.hpp"
#include "email/log.hpp"
#include "email/pub_sub.hpp"
#include "email/safe_queue.hpp"
#include "email/subscriber.hpp"
#include "email/subscription_handler.hpp"
#include "email/types.hpp"

namespace email
{

Subscriber::Subscriber(const std::string & topic_name)
: PubSubObject(topic_name),
  logger_(log::create("Subscriber::" + topic_name)),
  messages_(std::make_shared<SafeQueue<std::string>>())
{
  // Register with handler
  get_global_context()->get_subscription_handler()->register_subscriber(
    get_topic_name(),
    messages_);
}

Subscriber::~Subscriber()
{
  log::remove(logger_);
}

bool
Subscriber::has_message()
{
  return !messages_->empty();
}

std::optional<std::string>
Subscriber::get_message()
{
  if (!has_message()) {
    return std::nullopt;
  }
  return messages_->dequeue();
}

std::string
Subscriber::get_message_and_wait()
{
  while (messages_->empty()) {
    std::this_thread::sleep_for(WAIT_TIME);
  }
  return messages_->dequeue();
}

}  // namespace email
