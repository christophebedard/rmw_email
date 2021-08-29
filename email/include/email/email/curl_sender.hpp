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

#ifndef EMAIL__EMAIL__CURL_SENDER_HPP_
#define EMAIL__EMAIL__CURL_SENDER_HPP_

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/curl/executor.hpp"
#include "email/email/info.hpp"
#include "email/email/sender.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email sending wrapper for curl.
/**
 * Sets the options and executes commands to send emails with curl.
 */
class CurlEmailSender : public EmailSender, public CurlExecutor
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for sending emails
   * \param recipients the email recipients
   * \param curl_verbose the curl verbose status
   */
  EMAIL_PUBLIC
  explicit CurlEmailSender(
    UserInfo::SharedPtrConst user_info,
    EmailRecipients::SharedPtrConst recipients,
    const bool curl_verbose);

  EMAIL_PUBLIC
  virtual ~CurlEmailSender();

protected:
  virtual
  bool
  init_options();

  virtual
  bool
  send_payload(const std::string & payload);

private:
  EMAIL_DISABLE_COPY(CurlEmailSender)

  /// Read callback for curl upload.
  static
  size_t
  read_payload_callback(void * ptr, size_t size, size_t nmemb, void * userp);

  /// Utility struct for uploading data with curl.
  struct UploadData
  {
    const char * payload;
    size_t lines_read;
  };

  EmailRecipients::SharedPtrConst recipients_;
  struct curl_slist * recipients_list_;
  struct UploadData upload_ctx_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__CURL_SENDER_HPP_
