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
#include <string>

#include "rcutils/testing/fault_injection.h"

#include "email/email/info.hpp"
#include "email/email/intra_receiver.hpp"
#include "email/email/intra_sender.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"

namespace email
{

IntraEmailSender::IntraEmailSender(
  UserInfo::SharedPtrConst user_info,
  EmailRecipients::SharedPtrConst recipients,
  std::shared_ptr<IntraEmailReceiver> receiver)
: EmailSender(user_info, recipients),
  receiver_(receiver)
{}

IntraEmailSender::~IntraEmailSender()
{
  logger()->debug("destroying");
}

bool
IntraEmailSender::send(
  const struct EmailContent & content,
  std::optional<EmailHeaders> additional_headers)
{
  logger()->debug("sending");
  struct EmailData data(
    "",
    "",
    user_info_->username,
    *recipients_,
    content,
    additional_headers);
  return send_email_data(data);
}

bool
IntraEmailSender::reply(
  const struct EmailContent & content,
  const struct EmailData & email,
  std::optional<EmailHeaders> additional_headers)
{
  logger()->debug("replying");
  const struct EmailRecipients recipients(email.from);
  struct EmailData data(
    "",
    email.message_id,
    user_info_->username,
    recipients,
    content,
    additional_headers);
  return send_email_data(data);
}

bool
IntraEmailSender::send_email_data(const struct EmailData & data)
{
  RCUTILS_FAULT_INJECTION_MAYBE_RETURN_ERROR(false);
  logger()->debug("data:\n{}", data);
  receiver_->receive(data);
  return true;
}

}  // namespace email
