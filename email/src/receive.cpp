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

// #include <cstdio>

#include <iostream>
#include <string>
#include <optional>

#include <email/email_receiver.hpp>

int main(void)
{
  struct UserConnectionInfo info;
  info.url = "imap.gmail.com";
  info.username = "";
  info.password = "";
  EmailReceiver receiver(info);

  std::optional<std::string> response = receiver.get_email();
  if (!response) {
    return 1;
  }
  printf("response!\n%s", response.value().c_str());
  return 0;
}
