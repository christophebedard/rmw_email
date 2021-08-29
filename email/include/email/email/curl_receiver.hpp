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

#ifndef EMAIL__EMAIL__CURL_RECEIVER_HPP_
#define EMAIL__EMAIL__CURL_RECEIVER_HPP_

#include <curl/curl.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "email/curl/executor.hpp"
#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email reception wrapper for curl.
/**
 * Sets the options and executes the commands to receive emails.
 */
class CurlEmailReceiver : public EmailReceiver, public CurlExecutor
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for receiving emails
   * \param curl_verbose the curl verbose status
   */
  EMAIL_PUBLIC
  explicit CurlEmailReceiver(
    UserInfo::SharedPtrConst user_info,
    const bool curl_verbose);

  EMAIL_PUBLIC
  virtual ~CurlEmailReceiver();

  EMAIL_PUBLIC
  virtual
  std::optional<struct EmailData>
  get_email(std::optional<std::chrono::nanoseconds> polling_period = std::nullopt);

protected:
  virtual
  bool
  init_options();

private:
  EMAIL_DISABLE_COPY(CurlEmailReceiver)

  /// Get the NEXTUID value.
  /**
   * This value represents the predicted UID value of the next email, if there ever is a new email.
   *
   * \return the NEXTUID, or `std::nullopt` if it failed
   */
  std::optional<int>
  get_nextuid();

  /// Get an email from its UID.
  /**
   * Will fail if there is no email with that UID.
   *
   * \param uid the UID
   * \return the email data, or `std::nullopt` if it failed
   */
  std::optional<struct EmailData>
  get_email_from_uid(int uid);

  /// Execute curl command.
  /**
   * \param url_options the options to append to the request URL, or `std::nullopt`
   * \param custom_request the custom IMAP request, or `std::nullopt`
   * \return the response, or `std::nullopt` if it failed
   */
  std::optional<std::string>
  execute(std::optional<std::string> url_options, std::optional<std::string> custom_request);

  /// Write callback for curl download/response reception.
  static
  size_t
  write_callback(void * contents, size_t size, size_t nmemb, void * userp);

  int current_uid_;
  int next_uid_;
  std::string read_buffer_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__CURL_RECEIVER_HPP_
