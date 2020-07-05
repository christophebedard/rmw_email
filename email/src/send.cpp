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

#include "email/email_sender.hpp"
#include "email/init.hpp"
#include "email/types.hpp"
#include "email/options.hpp"

int main(int argc, char ** argv)
{
  email::init(argc, argv);
  auto options = email::parse_options(argc, argv);
  if (!options || !options.value()->get_recipients().has_value()) {
    return 1;
  }
  const struct email::UserInfo info = *options.value()->get_user_info().get();
  const struct email::EmailRecipients recipients = *options.value()->get_recipients().value().get();
  email::EmailSender sender(info, recipients);
  if (!sender.init()) {
    return 1;
  }
  const std::string subject = "this is the subject\nwoopsies";
  const std::string body = "this is the body!\nthis is on another line";
  bool ret = sender.send({subject, body});
  return ret ? 0 : 1;
}
