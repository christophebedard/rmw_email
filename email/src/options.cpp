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
  std::shared_ptr<struct EmailRecipients> recipients,
  bool debug)
: user_info_(user_info),
  recipients_(recipients),
  debug_(debug)
{}

Options::~Options() {}

std::shared_ptr<struct UserInfo>
Options::get_user_info() const
{
  return user_info_;
}

std::shared_ptr<struct EmailRecipients>
Options::get_recipients() const
{
  return recipients_;
}

bool
Options::debug() const
{
  return debug_;
}

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_args(int argc, char const * const argv[])
{
  // TODO(christophebedard) remove completely or refactor/extract parsing logic
  if (6 == argc || 7 == argc) {
    std::cerr << Options::USAGE_CLI_ARGS << std::endl;
    return std::nullopt;
  }
  std::shared_ptr<struct UserInfo> user_info = std::make_shared<struct UserInfo>();
  user_info->host_smtp = std::string(argv[1]);
  user_info->host_imap = std::string(argv[2]);
  user_info->username = std::string(argv[3]);
  user_info->password = std::string(argv[4]);
  std::shared_ptr<struct EmailRecipients> recipients = std::make_shared<struct EmailRecipients>();
  recipients->to = {std::string(argv[5])};
  bool debug = false;
  if (7 == argc) {
    const std::string argv6 = std::string(argv[6]);
    if ("-d" == argv6 || "--debug" == argv6) {
      debug = true;
    }
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
