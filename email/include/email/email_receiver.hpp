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

#ifndef EMAIL__EMAIL_RECEIVER_HPP_
#define EMAIL__EMAIL_RECEIVER_HPP_

#include <curl/curl.h>

#include <iostream>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "email/curl_executor.hpp"
#include "email/types.hpp"

namespace email
{

class EmailReceiver : public CurlExecutor
{
public:
  explicit EmailReceiver(
    const struct UserInfo & user_info,
    const bool debug = true);
  EmailReceiver(const EmailReceiver &) = delete;
  virtual ~EmailReceiver();

  std::optional<struct EmailContent> get_email();

protected:
  virtual bool init_options();

private:
  std::optional<std::string> execute(
    std::optional<std::string> url_options,
    std::optional<std::string> custom_request);

  std::optional<int> get_nextuid_from_response(const std::string & response);
  std::optional<int> get_nextuid();

  std::optional<struct EmailContent> get_email_from_uid(int uid);

  std::optional<struct EmailContent> result_to_email_content(const std::string & curl_result);

  std::optional<std::string> get_first_match_group(
    const std::string & string,
    const std::regex & regex);

  std::string read_buffer_;

  static const std::regex regex_nextuid;
  static const std::regex regex_subject;
  static const std::regex regex_body;
};

}  // namespace email

#endif  // EMAIL__EMAIL_RECEIVER_HPP_
