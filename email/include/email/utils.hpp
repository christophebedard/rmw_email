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

#ifndef EMAIL__UTILS_HPP_
#define EMAIL__UTILS_HPP_

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <stdexcept>
#include <string>

#include "email/types.hpp"

namespace email
{
namespace utils
{

template<typename ... Args>
std::string string_format(const std::string & format, Args... args)
{
  size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
  if (size <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args ...);
  return std::string(buf.get(), buf.get() + size - 1);
}

std::optional<struct UserInfo> parse_user_connection_info(int argc, char ** argv);

}  // namespace utils
}  // namespace email

#endif  // EMAIL__UTILS_HPP_
