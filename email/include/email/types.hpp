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

#ifndef EMAIL__TYPES_HPP_
#define EMAIL__TYPES_HPP_

#include <string>

namespace email
{

struct UserInfo
{
  // URL without the port or '<protocol>://'
  std::string url;
  // Username (i.e. email)
  std::string username;
  // Password
  std::string password;
};

struct ProtocolInfo
{
  // Protocol, i.e. <protocol>://
  std::string protocol;
  // Port
  int port;
};

}  // namespace email

#endif  // EMAIL__TYPES_HPP_