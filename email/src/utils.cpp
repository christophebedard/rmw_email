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
#include <string>
#include <vector>

#include "rcpputils/split.hpp"

#include "email/utils.hpp"

namespace email
{
namespace utils
{

std::optional<std::string> read_file(const std::string & path)
{
  // TODO(christophebedard) handle possible failure
  std::ifstream stream(path);
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return buffer.str();
}

std::vector<std::string> split_email_list(const std::string & list)
{
  return rcpputils::split(list, ',', true);
}

std::string full_url(
  const std::string & protocol,
  const std::string & host,
  const int port)
{
  return protocol + "://" + host + ":" + std::to_string(port) + "/";
}

}  // namespace utils
}  // namespace email
