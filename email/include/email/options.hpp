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

#include "email/types.hpp"

namespace email
{

class Options
{
public:
  Options(
    std::shared_ptr<struct UserInfo> user_info,
    std::optional<std::shared_ptr<struct EmailRecipients>> recipients,
    bool debug);
  ~Options();

  std::shared_ptr<struct UserInfo> get_user_info() const;
  std::optional<std::shared_ptr<struct EmailRecipients>> get_recipients() const;
  bool debug() const;

private:
  std::shared_ptr<struct UserInfo> user_info_;
  std::optional<std::shared_ptr<struct EmailRecipients>> recipients_;
  bool debug_;
};

std::optional<std::shared_ptr<Options>> parse_options(int argc, char const * const argv[]);

}  // namespace email

#endif  // EMAIL__OPTIONS_HPP_
