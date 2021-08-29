// Copyright 2021 Christophe Bedard
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

#include "email/email/info.hpp"
#include "email/email/payload_utils.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/utils.hpp"

namespace email
{

EmailSender::EmailSender(
  UserInfo::SharedPtrConst user_info,
  EmailRecipients::SharedPtrConst recipients)
: user_info_(user_info),
  recipients_(recipients)
{}

EmailSender::~EmailSender()
{
  logger()->debug("destroying");
}

bool
EmailSender::send(
  const struct EmailContent & content,
  std::optional<EmailHeaders> additional_headers)
{
  logger()->debug("send");
  return send_payload(
    utils::payload::build_payload(recipients_, content, additional_headers, std::nullopt));
}

bool
EmailSender::reply(
  const struct EmailContent & content,
  const struct EmailData & email,
  std::optional<EmailHeaders> additional_headers)
{
  return send_payload(
    utils::payload::build_payload(
      {email.from},
      {},
      {},
      content,
      additional_headers,
      email.message_id));
}

std::shared_ptr<Logger>
EmailSender::logger()
{
  static auto logger = log::create("EmailSender");
  return logger;
}

}  // namespace email
