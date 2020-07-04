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

#ifndef EMAIL__PAYLOAD_UTILS_HPP_
#define EMAIL__PAYLOAD_UTILS_HPP_

#include <regex>
#include <string>
#include <vector>

#include "email/types.hpp"
#include "email/utils.hpp"
#include "email/visibility_control.hpp"

namespace email
{
namespace utils
{

/**
 * Utilities for building email payloads according to RFC 5322.
 *
 * See: https://tools.ietf.org/html/rfc5322
 */
class PayloadUtils
{
public:
  PayloadUtils() = delete;
  ~PayloadUtils() = delete;

  static const std::string build_payload(
    const struct EmailRecipients & recipients,
    const struct EmailContent & content);

  static const std::string join_list(
    const std::vector<std::string> & list);

  static std::string cut_string_if_newline(const std::string & string);

private:
  static const std::regex regex_newline;
};

}  // namespace utils
}  // namespace email

#endif  // EMAIL__PAYLOAD_UTILS_HPP_
