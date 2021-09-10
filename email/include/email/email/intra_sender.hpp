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

#ifndef EMAIL__EMAIL__INTRA_SENDER_HPP_
#define EMAIL__EMAIL__INTRA_SENDER_HPP_

#include <memory>
#include <string>

#include "email/email/info.hpp"
#include "email/email/intra_receiver.hpp"
#include "email/email/sender.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Intraprocess email sender.
/**
 * Simply builds an email object and sends it to the intraprocess email receiver.
 */
class IntraEmailSender : public EmailSender
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for sending emails
   * \param recipients the email recipients
   */
  EMAIL_PUBLIC
  explicit IntraEmailSender(
    UserInfo::SharedPtrConst user_info,
    EmailRecipients::SharedPtrConst recipients,
    std::shared_ptr<IntraEmailReceiver> receiver);

  EMAIL_PUBLIC
  virtual ~IntraEmailSender();

  EMAIL_PUBLIC
  virtual
  bool
  send(
    const struct EmailContent & content,
    std::optional<EmailHeaders> additional_headers = std::nullopt);

  EMAIL_PUBLIC
  virtual
  bool
  reply(
    const struct EmailContent & content,
    const struct EmailData & email,
    std::optional<EmailHeaders> additional_headers = std::nullopt);

private:
  EMAIL_DISABLE_COPY(IntraEmailSender)

  /// Send email data to receiver.
  bool
  send_email_data(const struct EmailData & data);

  std::shared_ptr<IntraEmailReceiver> receiver_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__INTRA_SENDER_HPP_
