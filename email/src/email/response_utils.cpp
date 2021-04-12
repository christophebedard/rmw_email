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

#include <optional>
#include <regex>
#include <sstream>
#include <string>

#include "email/email/response_utils.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{
namespace utils
{
namespace response
{

static constexpr auto HEADER_BCC = "Bcc";
static constexpr auto HEADER_CC = "Cc";
static constexpr auto HEADER_FROM = "From";
static constexpr auto HEADER_IN_REPLY_TO = "In-Reply-To";
static constexpr auto HEADER_MESSAGE_ID = "Message-ID";
static constexpr auto HEADER_REFERENCES = "References";
static constexpr auto HEADER_SUBJECT = "Subject";
static constexpr auto HEADER_TO = "To";
static const std::regex REGEX_BODY(R"((?:\r?\n){2}((?:.*\n*)*)(?:\r?\n)?)");
static const std::regex REGEX_HEADER(R"(([a-zA-Z\-]+): (.*)\r)");
static const std::regex REGEX_NEXTUID(
  R"(.*OK \[UIDNEXT (.*)\] Predicted next UID.*)",
  std::regex::extended);

namespace
{

/// Get first match group for a string given a regex.
std::optional<std::string>
get_first_match_group(const std::string & string, const std::regex & regex)
{
  std::smatch matches;
  if (!std::regex_search(string, matches, regex)) {
    return std::nullopt;
  }
  // Only expecting one group besides the first global match itself
  if (matches.size() != 2) {
    return std::nullopt;
  }
  return matches[1].str();
}

/// Utility function for taking header value from container.
std::optional<std::string>
take_value_from_headers(const std::string & header_key, EmailHeaders & headers)
{
  auto it = headers.find(header_key);
  if (headers.end() == it) {
    return std::nullopt;
  }
  auto value = it->second;
  // Remove the item from the map ("take")
  headers.erase(it);
  return value;
}

}  // namespace

std::optional<int>
get_nextuid_from_response(const std::string & response)
{
  auto match_group = get_first_match_group(response, REGEX_NEXTUID);
  if (!match_group) {
    return std::nullopt;
  }
  return std::stoi(match_group.value());
}

std::optional<EmailHeaders>
get_email_headers_from_response(const std::string & response)
{
  EmailHeaders headers;
  std::istringstream lines(response);
  std::string line;
  while (getline(lines, line)) {
    std::smatch matches;
    if (!std::regex_search(line, matches, REGEX_HEADER)) {
      continue;
    }
    // A header match should have a size of 2 (key + value) + 1 (the first global match itself)
    if (matches.size() != 3) {
      continue;
    }
    headers.insert({matches[1].str(), matches[2].str()});
  }
  return headers;
}

std::optional<struct EmailContent>
get_email_content_from_response(const std::string & response, EmailHeaders & headers)
{
  auto match_subject = take_value_from_headers(HEADER_SUBJECT, headers);
  auto match_body = get_first_match_group(response, REGEX_BODY);
  if (!match_subject || !match_body) {
    return std::nullopt;
  }
  struct EmailContent content(
    match_subject.value(),
    match_body.value());
  return content;
}

std::optional<struct EmailData>
get_email_data_from_response(const std::string & response)
{
  auto match_headers = get_email_headers_from_response(response);
  if (!match_headers) {
    return std::nullopt;
  }
  auto headers = match_headers.value();

  auto match_from = take_value_from_headers(HEADER_FROM, headers);
  auto match_in_reply_to = take_value_from_headers(HEADER_IN_REPLY_TO, headers);
  auto match_message_id = take_value_from_headers(HEADER_MESSAGE_ID, headers);
  if (!match_from || !match_in_reply_to || !match_message_id) {
    return std::nullopt;
  }
  auto content_opt = get_email_content_from_response(response, headers);
  if (!content_opt) {
    return std::nullopt;
  }
  auto match_to = take_value_from_headers(HEADER_TO, headers);
  auto match_cc = take_value_from_headers(HEADER_CC, headers);
  auto match_bcc = take_value_from_headers(HEADER_BCC, headers);
  if (!match_to || !match_cc || !match_bcc) {
    return std::nullopt;
  }

  struct EmailRecipients recipients(
    split_email_list(match_to.value(), true),
    split_email_list(match_cc.value(), true),
    split_email_list(match_bcc.value(), true));
  struct EmailData email_data(
    match_message_id.value(),
    match_in_reply_to.value(),
    match_from.value(),
    recipients,
    content_opt.value(),
    headers);
  return email_data;
}

std::optional<std::string>
get_header_value(const std::string & header_name, const EmailHeaders & headers)
{
  auto it = headers.find(header_name);
  if (headers.end() == it) {
    return std::nullopt;
  }
  return it->second;
}

}  // namespace response
}  // namespace utils
}  // namespace email
