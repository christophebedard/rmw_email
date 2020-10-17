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

#include <memory>
#include <numeric>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "email/email/payload_utils.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{
namespace utils
{
namespace payload
{

const std::string
build_payload(
  const std::vector<std::string> & to,
  const std::vector<std::string> & cc,
  const std::vector<std::string> & bcc,
  const struct EmailContent & content,
  std::optional<EmailHeaders> additional_headers,
  std::optional<std::string> reply_ref)
{
  std::stringstream additional_headers_stream;
  if (additional_headers.has_value()) {
    for (auto & header : additional_headers.value()) {
      additional_headers_stream << std::get<0>(header) << ": " << std::get<1>(header) << "\r\n";
    }
  }
  // Subjects containing newlines will have the second+ line(s) be moved to the body,
  // but for the sake of simplicity, we will cut it out. As for the body, curl
  // seems to handle it correctly even if it contains "\n" instead of "\r\n"
  return utils::string_format(
    "%s"
    "In-Reply-To: %s\r\nReferences: %s\r\n"
    "To: %s\r\nCc: %s\r\nBcc: %s\r\nSubject: %s\r\n\r\n%s\r\n",
    additional_headers_stream.str().c_str(),
    (reply_ref.has_value() ? reply_ref.value().c_str() : ""),
    (reply_ref.has_value() ? reply_ref.value().c_str() : ""),
    join_list(to).c_str(),
    join_list(cc).c_str(),
    join_list(bcc).c_str(),
    cut_string_if_newline(content.subject).c_str(),
    content.body.c_str());
}

const std::string
build_payload(
  EmailRecipients::SharedPtrConst recipients,
  const struct EmailContent & content,
  std::optional<EmailHeaders> additional_headers,
  std::optional<std::string> reply_ref)
{
  return build_payload(
    recipients->to, recipients->cc, recipients->bcc, content, additional_headers, reply_ref);
}

const std::string
join_list(const std::vector<std::string> & list)
{
  // From: https://stackoverflow.com/a/12155571/6476709
  return std::accumulate(
    list.begin(),
    list.end(),
    std::string(),
    [](const std::string & a, const std::string & b) -> std::string {
      return a + (a.length() > 0 ? ", " : "") + b;
    });
}

std::string
cut_string_if_newline(const std::string & string)
{
  static const std::regex REGEX_NEWLINE_TO_END("[\r\n].*", std::regex::extended);
  return std::regex_replace(string, REGEX_NEWLINE_TO_END, "");
}

}  // namespace payload
}  // namespace utils
}  // namespace email
