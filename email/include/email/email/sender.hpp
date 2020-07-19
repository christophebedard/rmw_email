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

#ifndef EMAIL__EMAIL__SENDER_HPP_
#define EMAIL__EMAIL__SENDER_HPP_

#include <memory>
#include <string>
#include <vector>

#include "email/curl/executor.hpp"
#include "email/log.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email sending wrapper for curl.
/**
 * Sets the options and executes commands to send emails with curl.
 * The recipients are always the same.
 * Only the email subject & body can change from one sent email to another.
 */
class EmailSender : public CurlExecutor
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for sending emails
   * \param recipients the email recipients
   * \param curl_verbose the curl verbose status
   */
  explicit EmailSender(
    UserInfo::SharedPtrConst user_info,
    EmailRecipients::SharedPtrConst recipients,
    const bool curl_verbose);
  EmailSender(const EmailSender &) = delete;
  EmailSender & operator=(const EmailSender &) = delete;
  virtual ~EmailSender();

  /// Send an email.
  /**
   * \param content the content
   * \return true if successful, false otherwise
   */
  bool
  send(const struct EmailContent & content);

  /// Reply to an email.
  /**
   * \param content the content
   * \param email the email to reply to
   * \return true if successful, false otherwise
   */
  bool
  reply(const struct EmailContent & content, const struct EmailData & email);

protected:
  virtual
  bool
  init_options();

private:
  /// Send payload.
  /**
   * \param payload the payload
   * \return true if successful, false otherwise
   */
  bool
  send_payload(const std::string & payload);

  /// Read callback for curl upload.
  static
  size_t
  read_payload_callback(void * ptr, size_t size, size_t nmemb, void * userp);

  /// Utility struct for uploading data with curl.
  struct UploadData
  {
    const char * payload;
    int lines_read;
  };

  std::shared_ptr<Logger> logger_;
  EmailRecipients::SharedPtrConst recipients_;
  struct curl_slist * recipients_list_;
  struct UploadData upload_ctx_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__SENDER_HPP_
