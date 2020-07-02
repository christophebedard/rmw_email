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
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/utils.hpp"

namespace email
{
namespace utils
{

std::optional<struct UserInfo> parse_user_connection_info(int argc, char ** argv)
{
  if (4 != argc) {
    std::cerr << "usage: email password url" << std::endl;
    return std::nullopt;
  }
  struct UserInfo info;
  info.username = std::string(argv[1]);
  info.password = std::string(argv[2]);
  info.url = std::string(argv[3]);
  return info;
}

}  // namespace utils
}  // namespace email
