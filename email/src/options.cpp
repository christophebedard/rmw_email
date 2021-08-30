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

#include <chrono>
#include <iostream>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>
#include <vector>

#include "rcpputils/filesystem_helper.hpp"
#include "rcutils/env.h"
#include "yaml-cpp/yaml.h"

#include "email/email/info.hpp"
#include "email/log.hpp"
#include "email/options.hpp"
#include "email/utils.hpp"

namespace email
{

Options::Options(
  UserInfo::SharedPtrConst user_info,
  EmailRecipients::SharedPtrConst recipients,
  const bool curl_verbose,
  const bool intraprocess,
  const std::optional<std::chrono::nanoseconds> polling_period)
: user_info_(user_info),
  recipients_(recipients),
  curl_verbose_(curl_verbose),
  intraprocess_(intraprocess),
  polling_period_(polling_period)
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

bool
Options::intraprocess() const
{
  return intraprocess_;
}

std::optional<std::chrono::nanoseconds>
Options::polling_period() const
{
  return polling_period_;
}

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_args(int argc, char const * const argv[])
{
  if (!(6 == argc || 7 == argc) || nullptr == argv) {
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
    curl_verbose,
    false,
    std::nullopt);
}

std::optional<std::shared_ptr<Options>>
Options::yaml_to_options_impl(YAML::Node node)
{
  logger()->debug("options:\n{}", node);
  // Validate content
  if (!node["email"]) {
    logger()->error("missing top-level 'email' key in options");
    return std::nullopt;
  }
  YAML::Node node_email = node["email"];
  if (!node_email["user"]) {
    logger()->error("missing key in options: email.user");
    return std::nullopt;
  }
  YAML::Node node_user = node_email["user"];
  // Need all values under email.user
  for (const auto & user_key : {"url-smtp", "url-imap", "username", "password"}) {
    if (!node_user[user_key]) {
      logger()->error("missing key in options: email.user.{}", user_key);
      return std::nullopt;
    }
  }
  if (!node_email["recipients"]) {
    logger()->error("missing key in options: email.recipients");
    return std::nullopt;
  }
  YAML::Node node_recipients = node_email["recipients"];
  // Only require 'to', the rest are optional
  if (!node_recipients["to"]) {
    logger()->error("missing key in options: email.recipients.to");
    return std::nullopt;
  }

  bool intraprocess = false;
  if (node_email["intraprocess"]) {
    intraprocess = "true" == node_email["intraprocess"].as<std::string>();
  }

  std::optional<std::chrono::nanoseconds> polling_period = std::nullopt;
  if (node_email["polling-period"]) {
    const auto polling_period_str = node_email["polling-period"].as<std::string>();
    const auto polling_period_ns = utils::optional_stoll(polling_period_str);
    if (!polling_period_ns) {
      logger()->error("invalid value in options: email.polling-period: {}", polling_period_str);
      return std::nullopt;
    }
    polling_period = std::chrono::nanoseconds(polling_period_ns.value());
  }

  UserInfo::SharedPtrConst user_info = std::make_shared<const struct UserInfo>(
    node_user["url-smtp"].as<std::string>(),
    node_user["url-imap"].as<std::string>(),
    node_user["username"].as<std::string>(),
    node_user["password"].as<std::string>());
  EmailRecipients::SharedPtrConst recipients =
    std::make_shared<const struct EmailRecipients>(
    utils::split_email_list(node_recipients["to"]),
    utils::split_email_list(node_recipients["cc"]),
    utils::split_email_list(node_recipients["bcc"]));
  const std::string curl_verbose_env_var = utils::get_env_var(Options::ENV_VAR_CURL_VERBOSE);
  return std::make_shared<Options>(
    user_info,
    recipients,
    !curl_verbose_env_var.empty(),
    intraprocess,
    polling_period);
}

std::optional<std::shared_ptr<Options>>
Options::yaml_to_options(YAML::Node node)
{
  try {
    return Options::yaml_to_options_impl(node);
  } catch (const YAML::Exception & e) {
    logger()->error("error when parsing YAML node: {}", e.what());
    return std::nullopt;
  }
}

std::optional<std::shared_ptr<Options>>
Options::parse_options_file(const rcpputils::fs::path & file_path)
{
  logger()->debug("parsing options file: {}", file_path);
  if (file_path.is_directory() || !file_path.exists()) {
    logger()->debug("options file path does not exist or is not a file: {}", file_path);
    return std::nullopt;
  }
  YAML::Node node;
  const std::string path = file_path.string();
  try {
    node = YAML::LoadFile(path);
  } catch (const YAML::Exception & e) {
    logger()->error("could not load options file '{}': {}", path, e.what());
    return std::nullopt;
  }
  return Options::yaml_to_options(node);
}

std::optional<std::shared_ptr<Options>>
Options::parse_options_from_file()
{
  // First try using path from environment variable or the default value
  const std::string config_file_path = utils::get_env_var_or_default(
    Options::ENV_VAR_CONFIG_FILE,
    (rcpputils::fs::current_path() / Options::CONFIG_FILE_DEFAULT_NAME).string());

  // Value can't be empty here because the default value is used if the env var is empty
  auto options = Options::parse_options_file(config_file_path);
  if (!options) {
    // Try reading backup config file
    // Use file path from environment variable if defined,
    // otherwise use the default name relative to the home directory
    const rcpputils::fs::path backup_file_path =
      utils::get_env_var_or_default(
      Options::ENV_VAR_CONFIG_FILE_DEFAULT_PATH,
      (rcpputils::fs::path(rcutils_get_home_dir()) / Options::CONFIG_FILE_DEFAULT_NAME).string());
    logger()->debug("trying backup config file path: {}", backup_file_path);
    options = Options::parse_options_file(backup_file_path);
    if (!options) {
      logger()->error(
        "could not read config file from path '{}' or from backup path '{}'",
        config_file_path,
        backup_file_path);
      return std::nullopt;
    }
  }
  return options;
}

std::shared_ptr<Logger>
Options::logger()
{
  static auto logger = log::create("Options");
  return logger;
}

}  // namespace email
