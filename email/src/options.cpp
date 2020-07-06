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
#include <regex>
#include <string>
#include <vector>

#include "rcpputils/get_env.hpp"
#include "rcpputils/split.hpp"

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

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_args(int argc, char const * const argv[])
{
  // TODO(christophebedard) remove completely or refactor/extract parsing logic
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

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_file()
{
  std::string options_file_path = rcpputils::get_env_var(Options::env_var_options_file);
  if (options_file_path.empty()) {
    std::cerr << "'" << Options::env_var_options_file << "'" <<
      " env var not found or empty" << std::endl;
    return std::nullopt;
  }
  auto content = utils::read_file(options_file_path);
  if (!content) {
    std::cerr << "could not read options file from path: " << options_file_path << std::endl;
    return std::nullopt;
  }
  std::smatch matches;
  if (!std::regex_search(content.value(), matches, regex_params_file)) {
    std::cerr << "invalid options file" << std::endl;
    return std::nullopt;
  }
  // 6 groups besides the global match itself
  if (matches.size() != 7) {
    std::cerr << "invalid options file" << std::endl;
    return std::nullopt;
  }
  std::shared_ptr<struct UserInfo> user_info = std::make_shared<struct UserInfo>();
  user_info->url = matches[1].str();
  user_info->username = matches[2].str();
  user_info->password = matches[3].str();
  std::string list_to = matches[4].str();
  std::string list_cc = matches[5].str();
  std::string list_bcc = matches[6].str();
  std::vector<std::string> to = rcpputils::split(list_to, ',', true);
  std::vector<std::string> cc = rcpputils::split(list_cc, ',', true);
  std::vector<std::string> bcc = rcpputils::split(list_bcc, ',', true);
  std::shared_ptr<struct EmailRecipients> recipients = std::make_shared<struct EmailRecipients>();
  recipients->to = to;
  recipients->cc = cc;
  recipients->bcc = bcc;
  const std::string debug_env_var = rcpputils::get_env_var(Options::env_var_debug);
  return std::make_shared<Options>(
    user_info,
    recipients,
    !debug_env_var.empty());
}

// See: regexr.com/57stl
const std::regex Options::regex_params_file(
  R"(email:\n  user:\n    url: (.*)\n    username: (.*)\n    password: (.*)\n  recipients:\n    to:[ ]?(.*)\n    cc:[ ]?(.*)\n    bcc:[ ]?(.*)[\n]?)");  // NOLINT

}  // namespace email
