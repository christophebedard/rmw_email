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
  } catch (const std::out_of_range &) {
  } catch (const std::exception &) {
  } catch (...) {
  }
  return std::nullopt;
}

std::optional<int>
optional_stoi(const std::string & str)
{
  try {
    return std::stoi(str);
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {
  } catch (const std::exception &) {
  } catch (...) {
  }
  return std::nullopt;
}

}  // namespace utils
}  // namespace email
