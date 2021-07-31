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

#include "email/communication_info.hpp"
#include "email/context.hpp"
#include "email/email/info.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/message_info.hpp"
#include "email/pub_sub.hpp"
#include "email/publisher.hpp"
#include "email/timestamp.hpp"

namespace email
{

Publisher::Publisher(const std::string & topic_name)
: PubSubObject(topic_name),
  logger_(log::get_or_create("Publisher::" + topic_name)),
  sender_(get_global_context()->get_sender())
{
  logger_->debug("created with GID: {}", get_gid());
}

Publisher::~Publisher()
{
  logger_->debug("destroying");
}

void
Publisher::publish(const std::string & message, std::optional<EmailHeaders> additional_headers)
{
  // Add GID and source timestamp to headers
  EmailHeaders headers = {
    {MessageInfo::HEADER_PUBLISHER_GID, get_gid().to_string()},
    {CommunicationInfo::HEADER_SOURCE_TIMESTAMP, Timestamp::now().to_string()}};
  // Insert given additional header and overwrite the above map if necessary
  if (additional_headers.has_value()) {
    for (auto const & [header_name, value] : additional_headers.value()) {
      headers[header_name] = value;
    }
  }

  struct EmailContent content {get_topic_name(), message};
  if (!sender_->send(content, headers)) {
    logger_->error("publish() failed");
  }
}

}  // namespace email
