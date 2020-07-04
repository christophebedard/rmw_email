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

#ifndef EMAIL__RESPONSE_UTILS_HPP_
#define EMAIL__RESPONSE_UTILS_HPP_

#include <optional>
#include <regex>
#include <string>

#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{
namespace utils
{

/**
 * Utilities for extracting information from an email formatted according to RFC 5322.
 *
 * See: https://tools.ietf.org/html/rfc5322
 */
class ResponseUtils
{
public:
  ResponseUtils() = delete;
  ~ResponseUtils() = delete;

  static std::optional<int> get_nextuid_from_response(const std::string & response);

  static std::optional<struct EmailContent> get_email_content_from_response(
    const std::string & curl_result);

private:
  static std::optional<std::string> get_first_match_group(
    const std::string & string,
    const std::regex & regex);

  static const std::regex regex_nextuid;
  static const std::regex regex_subject;
  static const std::regex regex_body;
};

}  // namespace utils
}  // namespace email

#endif  // EMAIL__RESPONSE_UTILS_HPP_
