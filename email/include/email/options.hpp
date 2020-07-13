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

#ifndef EMAIL__OPTIONS_HPP_
#define EMAIL__OPTIONS_HPP_

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "email/types.hpp"

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
   * \param debug the debug status
   */
  Options(
    UserInfo::SharedPtrConst user_info,
    EmailRecipients::SharedPtrConst recipients,
    bool debug);
  ~Options();

  /// Get user information data.
  /**
   * \return the `UserInfo` object
   */
  UserInfo::SharedPtrConst
  get_user_info() const;

  /// Get email recipient data.
  /**
   * \return the `EmailRecipients` object
   */
  EmailRecipients::SharedPtrConst
  get_recipients() const;

  /// Get the debug status.
  /**
   * \return true if debug, false otherwise
   */
  bool
  debug() const;

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
   * \return the resulting `Options` object, or `std::nullopt` if it failed
   */
  static
  std::optional<std::shared_ptr<Options>>
  parse_options_from_file();

private:
  UserInfo::SharedPtrConst user_info_;
  EmailRecipients::SharedPtrConst recipients_;
  bool debug_;

  static const std::regex REGEX_CONFIG_FILE;
  static constexpr const char * ENV_VAR_DEBUG = "EMAIL_DEBUG";
  static constexpr const char * ENV_VAR_CONFIG_FILE = "EMAIL_CONFIG_FILE";
  static constexpr const char * ENV_VAR_CONFIG_FILE_DEFAULT = "email.yml";
  static constexpr const char * USAGE_CLI_ARGS =
    "usage: HOST_SMTP HOST_IMAP EMAIL PASSWORD EMAIL_TO [-d|--debug]";
};

}  // namespace email

#endif  // EMAIL__OPTIONS_HPP_
