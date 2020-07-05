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

namespace email
{
namespace utils
{

std::optional<int> ResponseUtils::get_nextuid_from_response(const std::string & response)
{
  auto match_group = get_first_match_group(response, ResponseUtils::regex_nextuid);
  if (!match_group) {
    return std::nullopt;
  }
  return std::stoi(match_group.value());
}

std::optional<struct EmailContent> ResponseUtils::get_email_content_from_response(
  const std::string & curl_result)
{
  auto match_group_subject = get_first_match_group(curl_result, ResponseUtils::regex_subject);
  auto match_group_body = get_first_match_group(curl_result, ResponseUtils::regex_body);
  if (!match_group_subject || !match_group_body) {
    return std::nullopt;
  }
  struct EmailContent content;
  content.subject = match_group_subject.value();
  content.body = match_group_body.value();
  return content;
}

std::optional<std::string> ResponseUtils::get_first_match_group(
  const std::string & string,
  const std::regex & regex)
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

const std::regex ResponseUtils::regex_nextuid(
  R"(.*OK \[UIDNEXT (.*)\] Predicted next UID.*)",
  std::regex::extended);
const std::regex ResponseUtils::regex_subject(
  R"(Subject: (.*)\r?\n)");
const std::regex ResponseUtils::regex_body(
  R"((?:\r?\n){2}((?:.*\n*)*)(?:\r?\n)?)");

}  // namespace utils
}  // namespace email
