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

#ifndef EMAIL__OPTIONS_HPP_
#define EMAIL__OPTIONS_HPP_

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "rcpputils/filesystem_helper.hpp"
#include "yaml-cpp/yaml.h"

#include "email/email/info.hpp"
#include "email/log.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Options container and parsing methods.
/**
 * Owns the various data objects.
 */
class Options
{
public:
  /// Constructor.
  /**
   * Not to be called directly: use `parse_options_from_*()` instead.
   *
   * \param user_info the user info
   * \param recipients the recipients
   * \param curl_verbose the curl verbose status
   */
  EMAIL_PUBLIC
  Options(
    UserInfo::SharedPtrConst user_info,
    EmailRecipients::SharedPtrConst recipients,
    bool curl_verbose);
  EMAIL_PUBLIC
  ~Options();

  /// Get user information data.
  /**
   * \return the `UserInfo` object
   */
  EMAIL_PUBLIC
  UserInfo::SharedPtrConst
  get_user_info() const;

  /// Get email recipient data.
  /**
   * \return the `EmailRecipients` object
   */
  EMAIL_PUBLIC
  EmailRecipients::SharedPtrConst
  get_recipients() const;

  /// Get the curl verbose status.
  /**
   * \return true if verbose, false otherwise
   */
  EMAIL_PUBLIC
  bool
  curl_verbose() const;

  /// Parse options from CLI arguments.
  /**
   * \param argc the argument count
   * \param argv the argument vector
   * \return the resulting `Options` object, or `std::nullopt` if it failed
   */
  static
  std::optional<std::shared_ptr<Options>>
  parse_options_from_args(int argc, char const * const argv[]);

  /// Parse options from config file.
  /**
   * It first tries to read `$EMAIL_CONFIG_FILE`, or `$PWD/email.yml` if it is not set.
   * If that does not work, it then tries to read from a backup file path: `~/email.yml`.
   *
   * \return the resulting `Options` object, or `std::nullopt` if it failed
   */
  static
  std::optional<std::shared_ptr<Options>>
  parse_options_from_file();

  /// Get `Options` object from yaml node.
  /**
   * \return the resulting `Options` object, or `std::nullopt` if it failed
   */
  EMAIL_PUBLIC
  static
  std::optional<std::shared_ptr<Options>>
  yaml_to_options(YAML::Node);

  /// Parse options file.
  /**
   * \param file_path the path to the file to parse
   * \return the resulting `Options` object, or `std::nullopt` if it failed
   */
  static
  std::optional<std::shared_ptr<Options>>
  parse_options_file(const rcpputils::fs::path & file_path);

private:
  /// Get logger.
  static
  std::shared_ptr<Logger>
  logger();

  UserInfo::SharedPtrConst user_info_;
  EmailRecipients::SharedPtrConst recipients_;
  bool curl_verbose_;

  static constexpr const char * ENV_VAR_CURL_VERBOSE = "EMAIL_CURL_VERBOSE";
  static constexpr const char * ENV_VAR_CONFIG_FILE = "EMAIL_CONFIG_FILE";
  static constexpr const char * ENV_VAR_CONFIG_FILE_DEFAULT = "email.yml";
  static constexpr const char * USAGE_CLI_ARGS =
    "usage: HOST_SMTP HOST_IMAP EMAIL PASSWORD EMAIL_TO [-v|--curl-verbose]";
};

}  // namespace email

#endif  // EMAIL__OPTIONS_HPP_
