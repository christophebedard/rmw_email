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

#include <numeric>
#include <string>
#include <vector>

#include "email/types.hpp"
#include "email/payload_utils.hpp"
#include "email/utils.hpp"

namespace email
{
namespace utils
{

const std::string PayloadUtils::build_payload(
  const struct email::EmailRecipients & recipients,
  const struct email::EmailContent & content)
{
  // TODO(christophebedard) validate subject (one line, no newline)
  // TODO(christophebedard) validate/format body (replace all \n with \r\n)
  return email::utils::string_format(
    "To: %s\r\nCc: %s\r\nBcc: %s\r\nSubject: %s\r\n\r\n%s\r\n",
    join_list(recipients.to).c_str(),
    join_list(recipients.cc).c_str(),
    join_list(recipients.bcc).c_str(),
    content.subject.c_str(),
    content.body.c_str());
}

const std::string PayloadUtils::join_list(
  const std::vector<std::string> & list)
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

}  // namespace utils
}  // namespace email
