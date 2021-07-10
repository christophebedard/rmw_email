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

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/context.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/pub_sub.hpp"
#include "email/publisher.hpp"
#include "email/types.hpp"

namespace email
{

Publisher::Publisher(const std::string & topic_name)
: PubSubObject(topic_name),
  logger_(log::create("Publisher::" + topic_name)),
  sender_(get_global_context()->get_sender())
{}

Publisher::~Publisher()
{
  log::remove(logger_);
}

void
Publisher::publish(const std::string & message, std::optional<EmailHeaders> additional_headers)
{
  struct EmailContent content {get_topic_name(), message};
  if (!sender_->send(content, additional_headers)) {
    logger_->error("publish() failed");
  }
}

}  // namespace email
