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
    std::cerr <<
      "usage: --user HOST_SMTP HOST_IMAP EMAIL PASSWORD [--recipient TO] [-d|--debug]" <<
      std::endl;
    return std::nullopt;
  }
  std::optional<struct UserInfo> user_info_opt = std::nullopt;
  std::optional<struct EmailRecipients> recipients_opt = std::nullopt;
  bool debug = false;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if ("--user" == arg && (argc - i) >= (4 + 1)) {
      struct UserInfo info;
      i++;
      info.host_smtp = std::string(argv[i]);
      i++;
      info.host_imap = std::string(argv[i]);
      i++;
      info.username = std::string(argv[i]);
      i++;
      info.password = std::string(argv[i]);
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
  user_info->host_smtp = user_info_opt.value().host_smtp;
  user_info->host_imap = user_info_opt.value().host_imap;
  user_info->username = user_info_opt.value().username;
  user_info->password = user_info_opt.value().password;
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
  const std::string config_file_path = utils::get_env_var_or_default(
    Options::ENV_VAR_CONFIG_FILE,
    Options::ENV_VAR_CONFIG_FILE_DEFAULT);
  if (config_file_path.empty()) {
    std::cerr << "'" << Options::ENV_VAR_CONFIG_FILE << "'" <<
      " env var not found or empty" << std::endl;
    return std::nullopt;
  }
  auto content = utils::read_file(config_file_path);
  if (!content) {
    std::cerr << "could not read config file from path: " << config_file_path << std::endl;
    return std::nullopt;
  }
  std::smatch matches;
  if (!std::regex_search(content.value(), matches, Options::REGEX_CONFIG_FILE)) {
    std::cerr << "invalid config file" << std::endl;
    return std::nullopt;
  }
  // 7 groups besides the global match itself
  if (matches.size() != 8) {
    std::cerr << "invalid config file" << std::endl;
    return std::nullopt;
  }
  std::shared_ptr<struct UserInfo> user_info = std::make_shared<struct UserInfo>();
  user_info->host_smtp = matches[1].str();
  user_info->host_imap = matches[2].str();
  user_info->username = matches[3].str();
  user_info->password = matches[4].str();
  std::shared_ptr<struct EmailRecipients> recipients = std::make_shared<struct EmailRecipients>();
  recipients->to = utils::split_email_list(matches[5].str());
  recipients->cc = utils::split_email_list(matches[6].str());
  recipients->bcc = utils::split_email_list(matches[7].str());
  const std::string debug_env_var = utils::get_env_var(Options::ENV_VAR_DEBUG);
  return std::make_shared<Options>(
    user_info,
    recipients,
    !debug_env_var.empty());
}

// See: https://regexr.com/580va
const std::regex Options::REGEX_CONFIG_FILE(
  R"(email:\n  user:\n    url-smtp:[ ]?(.*)\n    url-imap:[ ]?(.*)\n    username: (.*)\n    password: (.*)\n  recipients:\n    to:[ ]?(.*)\n    cc:[ ]?(.*)\n    bcc:[ ]?(.*)[\n]?)");  // NOLINT

}  // namespace email
