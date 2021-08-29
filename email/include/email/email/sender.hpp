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

#ifndef EMAIL__EMAIL__SENDER_HPP_
#define EMAIL__EMAIL__SENDER_HPP_

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/email/info.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Abstract email sender.
/**
 * Sends emails.
 * The recipients are always the same.
 * Only the email subject & body can change from one sent email to another.
 */
class EmailSender
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for sending emails
   * \param recipients the email recipients
   */
  EMAIL_PUBLIC
  explicit EmailSender(
    UserInfo::SharedPtrConst user_info,
    EmailRecipients::SharedPtrConst recipients);

  EMAIL_PUBLIC
  virtual ~EmailSender();

  /// Send an email.
  /**
   * \param content the content
   * \param additional_headers the optional additional headers to include in the email
   * \return true if successful, false otherwise
   */
  EMAIL_PUBLIC
  virtual
  bool
  send(
    const struct EmailContent & content,
    std::optional<EmailHeaders> additional_headers = std::nullopt);

  /// Reply to an email.
  /**
   * \param content the content
   * \param email the email to reply to
   * \param additional_headers the optional additional headers to include in the email
   * \return true if successful, false otherwise
   */
  EMAIL_PUBLIC
  virtual
  bool
  reply(
    const struct EmailContent & content,
    const struct EmailData & email,
    std::optional<EmailHeaders> additional_headers = std::nullopt);

protected:
  /// Send payload.
  /**
   * \param payload the payload
   * \return true if successful, false otherwise
   */
  virtual
  bool
  send_payload(const std::string & payload) = 0;

  /// Get logger.
  static
  std::shared_ptr<Logger>
  logger();

private:
  EMAIL_DISABLE_COPY(EmailSender)

  UserInfo::SharedPtrConst user_info_;
  EmailRecipients::SharedPtrConst recipients_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__SENDER_HPP_
