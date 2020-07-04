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
#include <vector>

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

struct EmailRecipients
{
  std::vector<std::string> to;
  std::vector<std::string> cc;
  std::vector<std::string> bcc;
};

struct EmailContent
{
  // Subject, which should be one line without any newlines
  std::string subject;
  // Body/content, which may have multiple lines
  std::string body;
};

// struct Email
// {
//   // Recipients of the email
//   struct EmailRecipients recipients;
//   // Content of the email
//   struct EmailContent content;
// };

}  // namespace email

#endif  // EMAIL__TYPES_HPP_
