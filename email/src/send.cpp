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

#include <string>

#include <email/email_sender.hpp>
#include <email/utils.hpp>

int main(int argc, char ** argv)
{
  auto info_opt = email::utils::parse_user_connection_info(argc, argv);
  if (!info_opt) {
    return 1;
  }
  struct email::UserConnectionInfo info = info_opt.value();
  EmailSender sender(info);
  const std::string to = "bedard.christophe@gmail.com";
  const std::string subject = "this is the subject";
  const std::string body = "this is the body!";
  bool ret = sender.send(
    to,
    subject,
    body);
  return ret ? 0 : 1;
}
