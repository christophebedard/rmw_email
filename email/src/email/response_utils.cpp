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

static const std::regex REGEX_BCC(R"(Bcc: (.*)\r?\n)");
static const std::regex REGEX_BODY(R"((?:\r?\n){2}((?:.*\n*)*)(?:\r?\n)?)");
static const std::regex REGEX_CC(R"(Cc: (.*)\r?\n)");
static const std::regex REGEX_FROM(R"(From: (.*)\r?\n)");
static const std::regex REGEX_IN_REPLY_TO(R"(In-Reply-To: (.*)\r?\n)");
static const std::regex REGEX_MESSAGE_ID(R"(Message-ID: (.*)\r?\n)");
static const std::regex REGEX_NEXTUID(
  R"(.*OK \[UIDNEXT (.*)\] Predicted next UID.*)",
  std::regex::extended);
static const std::regex REGEX_SUBJECT(R"(Subject: (.*)\r?\n)");
static const std::regex REGEX_TO(R"(To: (.*)\r?\n)");

std::optional<int>
get_nextuid_from_response(const std::string & response)
{
  auto match_group = get_first_match_group(response, REGEX_NEXTUID);
  if (!match_group) {
    return std::nullopt;
  }
  return std::stoi(match_group.value());
}

std::optional<struct EmailContent>
get_email_content_from_response(const std::string & curl_result)
{
  auto match_subject = get_first_match_group(curl_result, REGEX_SUBJECT);
  auto match_body = get_first_match_group(curl_result, REGEX_BODY);
  if (!match_subject || !match_body) {
    return std::nullopt;
  }
  struct EmailContent content(
    match_subject.value(),
    match_body.value());
  return content;
}

std::optional<struct EmailData>
get_email_data_from_response(const std::string & curl_result)
{
  auto match_from = get_first_match_group(curl_result, REGEX_FROM);
  auto match_in_reply_to = get_first_match_group(curl_result, REGEX_IN_REPLY_TO);
  auto match_message_id = get_first_match_group(curl_result, REGEX_MESSAGE_ID);
  auto content_opt = get_email_content_from_response(curl_result);
  if (!match_from || !match_in_reply_to || !match_message_id || !content_opt) {
    return std::nullopt;
  }
  auto match_to = get_first_match_group(curl_result, REGEX_TO);
  auto match_cc = get_first_match_group(curl_result, REGEX_CC);
  auto match_bcc = get_first_match_group(curl_result, REGEX_BCC);
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
    content_opt.value());
  return email_data;
}

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

}  // namespace response
}  // namespace utils
}  // namespace email
