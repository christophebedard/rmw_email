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

#include <iostream>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/options.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{

Options::Options(
  std::shared_ptr<struct UserInfo> user_info,
  std::optional<std::shared_ptr<struct EmailRecipients>> recipients,
  bool debug)
: user_info_(user_info),
  recipients_(recipients),
  debug_(debug)
{}

Options::~Options()
{}

std::shared_ptr<struct UserInfo> Options::get_user_info() const
{
  return user_info_;
}

std::optional<std::shared_ptr<struct EmailRecipients>> Options::get_recipients() const
{
  return recipients_;
}

bool Options::debug() const
{
  return debug_;
}

std::optional<std::shared_ptr<Options>> parse_options(int argc, char const * const argv[])
{
  if (argc <= 1) {
    std::cerr << "usage: --user email password url [--recipient TO] [-d|--debug]" << std::endl;
    return std::nullopt;
  }
  std::optional<struct UserInfo> user_info_opt = std::nullopt;
  std::optional<struct EmailRecipients> recipients_opt = std::nullopt;
  bool debug = false;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if ("--user" == arg && (argc - i) >= (3 + 1)) {
      struct UserInfo info;
      i++;
      info.username = std::string(argv[i]);
      i++;
      info.password = std::string(argv[i]);
      i++;
      info.url = std::string(argv[i]);
      user_info_opt = info;
    } else if ("--recipient" == arg && (argc - i) >= (1 + 1)) {
      i++;
      recipients_opt = {{std::string(argv[i])}, {}, {}};
    } else if ("-d" == arg || "--debug" == arg) {
      debug = true;
    }
  }
  if (!user_info_opt) {
    return std::nullopt;
  }
  std::shared_ptr<struct UserInfo> user_info = std::make_shared<struct UserInfo>();
  user_info->username = user_info_opt.value().username;
  user_info->password = user_info_opt.value().password;
  user_info->url = user_info_opt.value().url;
  std::optional<std::shared_ptr<struct EmailRecipients>> recipients = std::nullopt;
  if (recipients_opt) {
    recipients = std::make_shared<struct EmailRecipients>();
    recipients.value()->to = recipients_opt.value().to;
    recipients.value()->cc = recipients_opt.value().cc;
    recipients.value()->bcc = recipients_opt.value().bcc;
  }
  return std::make_shared<Options>(
    user_info,
    recipients,
    debug);
}

}  // namespace email
