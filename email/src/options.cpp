// Copyright 2020-2021 Christophe Bedard
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

#include "rcpputils/filesystem_helper.hpp"
#include "rcutils/env.h"

#include "email/log.hpp"
#include "email/options.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{

Options::Options(
  UserInfo::SharedPtrConst user_info,
  EmailRecipients::SharedPtrConst recipients,
  bool curl_verbose)
: user_info_(user_info),
  recipients_(recipients),
  curl_verbose_(curl_verbose)
{}

Options::~Options() {}

UserInfo::SharedPtrConst
Options::get_user_info() const
{
  return user_info_;
}

EmailRecipients::SharedPtrConst
Options::get_recipients() const
{
  return recipients_;
}

bool
Options::curl_verbose() const
{
  return curl_verbose_;
}

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_args(int argc, char const * const argv[])
{
  if (!(6 == argc || 7 == argc)) {
    std::cerr << Options::USAGE_CLI_ARGS << std::endl;
    return std::nullopt;
  }
  UserInfo::SharedPtrConst user_info = std::make_shared<const struct UserInfo>(
    std::string(argv[1]),
    std::string(argv[2]),
    std::string(argv[3]),
    std::string(argv[4]));
  EmailRecipients::SharedPtrConst recipients =
    std::make_shared<const struct EmailRecipients>(std::string(argv[5]));
  bool curl_verbose = false;
  if (7 == argc) {
    const std::string argv6 = std::string(argv[6]);
    if ("-v" == argv6 || "--curl-verbose" == argv6) {
      curl_verbose = true;
    }
  }
  return std::make_shared<Options>(
    user_info,
    recipients,
    curl_verbose);
}

std::optional<std::string>
Options::get_options_file_content()
{
  const std::string config_file_path = utils::get_env_var_or_default(
    Options::ENV_VAR_CONFIG_FILE,
    Options::ENV_VAR_CONFIG_FILE_DEFAULT);
  if (config_file_path.empty()) {
    logger()->error("'%s' env var not found or empty", Options::ENV_VAR_CONFIG_FILE);
    return std::nullopt;
  }
  auto content = utils::read_file(config_file_path);
  if (!content) {
    // Try reading backup config file
    logger()->debug("could not read config file from path: {}", config_file_path);
    auto backup_file_path =
      (rcpputils::fs::path(rcutils_get_home_dir()) / Options::ENV_VAR_CONFIG_FILE_DEFAULT)
      .string();
    logger()->debug("trying backup config file path: {}", backup_file_path);
    content = utils::read_file(backup_file_path);
    if (!content) {
      logger()->error(
        "could not read config file from path '{}' or from backup path '{}'",
        config_file_path,
        backup_file_path);
      return std::nullopt;
    }
  }
  return content;
}

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_file()
{
  auto content = Options::get_options_file_content();
  if (!content) {
    return std::nullopt;
  }
  std::smatch matches;
  if (!std::regex_search(content.value(), matches, Options::REGEX_CONFIG_FILE)) {
    logger()->error("invalid config file");
    return std::nullopt;
  }
  // 7 groups besides the global match itself
  if (matches.size() != 8) {
    logger()->error("invalid config file");
    return std::nullopt;
  }
  UserInfo::SharedPtrConst user_info = std::make_shared<const struct UserInfo>(
    matches[1].str(),
    matches[2].str(),
    matches[3].str(),
    matches[4].str());
  EmailRecipients::SharedPtrConst recipients =
    std::make_shared<const struct EmailRecipients>(
    utils::split_email_list(matches[5].str()),
    utils::split_email_list(matches[6].str()),
    utils::split_email_list(matches[7].str()));
  const std::string curl_verbose_env_var = utils::get_env_var(Options::ENV_VAR_CURL_VERBOSE);
  return std::make_shared<Options>(
    user_info,
    recipients,
    !curl_verbose_env_var.empty());
}

std::shared_ptr<Logger>
Options::logger()
{
  static auto logger = log::create("Options");
  return logger;
}

// See: https://regexr.com/580va
const std::regex Options::REGEX_CONFIG_FILE(
  R"(email:\n  user:\n    url-smtp:[ ]?(.*)\n    url-imap:[ ]?(.*)\n    username: (.*)\n    password: (.*)\n  recipients:\n    to:[ ]?(.*)\n    cc:[ ]?(.*)\n    bcc:[ ]?(.*)[\n]?)");  // NOLINT

}  // namespace email
