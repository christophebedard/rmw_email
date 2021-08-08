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

#include <pthread.h>

#include <cassert>
#include <fstream>
#include <sstream>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>
#include <vector>

#include "rcpputils/get_env.hpp"
#include "rcpputils/split.hpp"

#include "email/utils.hpp"

namespace email
{
namespace utils
{

std::string
get_env_var(const std::string & env_var)
{
  return rcpputils::get_env_var(env_var.c_str());
}

std::string
get_env_var_or_default(const std::string & env_var, const std::string & default_value)
{
  const std::string value = rcpputils::get_env_var(env_var.c_str());
  return !value.empty() ? value : default_value;
}

std::optional<std::string>
read_file(const std::string & path)
{
  std::ifstream stream(path);
  if (!stream.is_open()) {
    return std::nullopt;
  }
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return buffer.str();
}

std::vector<std::string>
split_email_list(const std::string & list, const bool has_space_after_comma)
{
  if (has_space_after_comma) {
    static std::regex comma_space_regex(", ");
    return rcpputils::split(std::regex_replace(list, comma_space_regex, ","), ',', true);
  }
  return rcpputils::split(list, ',', true);
}

std::vector<std::string>
split_email_list(const YAML::Node & node)
{
  if (!node.IsDefined() || node.IsNull()) {
    return {};
  }
  if (node.IsSequence()) {
    return node.as<std::vector<std::string>>();
  }
  return {node.as<std::string>()};
}

std::string
yaml_to_string(const YAML::Node & node)
{
  YAML::Emitter emitter;
  emitter << YAML::DoubleQuoted << YAML::Flow << node;
  return emitter.c_str();
}

std::string
full_url(const std::string & protocol, const std::string & host, const int port)
{
  return protocol + "://" + host + ":" + std::to_string(port) + "/";
}

std::optional<uint32_t>
optional_stoul(const std::string & str)
{
  try {
    return static_cast<uint32_t>(std::stoul(str));
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {  // LCOV_EXCL_LINE
  } catch (const std::exception &) {  // LCOV_EXCL_LINE
  } catch (...) {  // LCOV_EXCL_LINE
  }
  return std::nullopt;
}

std::optional<int>
optional_stoi(const std::string & str)
{
  try {
    return std::stoi(str);
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {  // LCOV_EXCL_LINE
  } catch (const std::exception &) {  // LCOV_EXCL_LINE
  } catch (...) {  // LCOV_EXCL_LINE
  }
  return std::nullopt;
}

std::optional<int64_t>
optional_stoll(const std::string & str)
{
  try {
    return static_cast<int64_t>(std::stoll(str));
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {  // LCOV_EXCL_LINE
  } catch (const std::exception &) {  // LCOV_EXCL_LINE
  } catch (...) {  // LCOV_EXCL_LINE
  }
  return std::nullopt;
}

void
thread_set_name(const char * name)
{
  assert(NULL != name);
#if defined(__linux) || defined(__linux__)
  // Truncate to 15 characters + the null character
  const size_t name_max_len = 16UL;
  char name_buffer[name_max_len] = "";
  // Copy only up to, but excluding, the mandatory null character,
  // otherwise the destination string isn't null-terminated
  (void)strncpy(name_buffer, name, sizeof(name_buffer) - 1);
  (void)pthread_setname_np(pthread_self(), name_buffer);
#elif defined(__APPLE__)
  (void)pthread_setname_np(name);
#else
#warning "thread_set_name not supported for this platform"
#endif
}

}  // namespace utils
}  // namespace email
