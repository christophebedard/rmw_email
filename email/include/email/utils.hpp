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

#ifndef EMAIL__UTILS_HPP_
#define EMAIL__UTILS_HPP_

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <stdexcept>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

#include "email/visibility_control.hpp"

namespace email
{
namespace utils
{

/// Format a string.
/**
 * \param format the format string
 * \param args the arguments
 * \return the formatted string
 * \throw std::runtime_error if underlying `snprintf()` call fails
 */
template<typename ... Args>
std::string
string_format(const std::string & format, Args... args)
{
  size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
  if (size <= 0) {  // LCOV_EXCL_LINE
    throw std::runtime_error("Error during formatting.");  // LCOV_EXCL_LINE
  }
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args ...);
  return std::string(buf.get(), buf.get() + size - 1);
}

/// Get an environment variable value.
/**
 * \param env_var the environment variable name
 * \return the value, or an empty string if it does not exist
 * \throw std::runtime_error on error
 */
EMAIL_PUBLIC
std::string
get_env_var(const std::string & env_var);

/// Get an environment variable value or a default value.
/**
 * The default value is used if the value is not found or if it is the empty string.
 * TODO(christophebedard) use `rcutils_get_env()` directly to tell between unset and empty?
 *
 * \param env_var the environment variable name
 * \param default_value the default value to use if not found
 * \return the value or default value
 * \throw std::runtime_error on error
 */
EMAIL_PUBLIC
std::string
get_env_var_or_default(const std::string & env_var, const std::string & default_value);

/// Read and get file content.
/**
 * \param path the path to the file
 * \return the file content, or `std::nullopt` if it failed (e.g. file does not exist)
 */
EMAIL_PUBLIC
std::optional<std::string>
read_file(const std::string & path);

/// Split list of emails separated by a comma.
/**
 * \param list the list of emails
 * \param has_space_after_comma whether there is a space after the comma, before the next email
 * \return the individual emails as a vector
 */
EMAIL_PUBLIC
std::vector<std::string>
split_email_list(const std::string & list, const bool has_space_after_comma = false);

/// Split list of emails in a YAML node.
/**
 * \param node the yaml node
 * \return the individual emails as a vector
 */
EMAIL_PUBLIC
std::vector<std::string>
split_email_list(const YAML::Node & node);

/// Convert YAML node to string.
/**
 * \param node the YAML node
 * \return the string equivalent
 */
EMAIL_PUBLIC
std::string
yaml_to_string(const YAML::Node & node);

/// Build a full URL from the necessary information.
/**
 * i.e. protocol://host:port/
 *
 * \param protocol the protocol as a string
 * \param host the host name
 * \param port the port, corresponding to the protocol
 * \return the full URL
 */
EMAIL_PUBLIC
std::string
full_url(const std::string & protocol, const std::string & host, const int port);

/// Try to call `std::stoul`.
/**
 * \param str the string to convert to unsigned long
 * \return the number, or `std::nullopt` if it fails
 */
EMAIL_PUBLIC
std::optional<uint32_t>
optional_stoul(const std::string & str);

/// Try to call `std::stoi`.
/**
 * \param str the string to convert to int
 * \return the number, or `std::nullopt` if it fails
 */
EMAIL_PUBLIC
std::optional<int>
optional_stoi(const std::string & str);

/// Try to call `std::stoll`.
/**
 * \param str the string to convert to long int/long
 * \return the number, or `std::nullopt` if it fails
 */
EMAIL_PUBLIC
std::optional<int64_t>
optional_stoll(const std::string & str);

/// Get the name of the current thread if the platform supports it.
/**
 * The platform might have a minimum buffer length requirement (16 for Linux).
 *
 * \param name the buffer in which to write the name
 * \param len the length of the buffer
 */
EMAIL_PUBLIC
void
thread_get_name(char * name, size_t len);

/// Set the name of the current thread if the platform supports it.
/**
 * The name might be truncated if the platform has a name length limit.
 *
 * \param name the thread name
 */
EMAIL_PUBLIC
void
thread_set_name(const char * name);

/// Append a suffix to name of the current thread if the platform supports it.
/**
 * The current name will be truncated to fit the suffix if needed.
 *
 * \param suffix the suffix
 */
EMAIL_PUBLIC
void
thread_append_name(const char * suffix);

}  // namespace utils
}  // namespace email

#endif  // EMAIL__UTILS_HPP_
