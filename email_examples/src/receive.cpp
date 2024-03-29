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
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/context.hpp"
#include "email/curl/info.hpp"
#include "email/email/curl_receiver.hpp"
#include "email/email/info.hpp"
#include "email/init.hpp"

int main(int argc, char ** argv)
{
  email::init(argc, argv);
  auto options = email::get_global_context()->get_options();
  if (options->intraprocess()) {
    return 1;
  }
  email::CurlEmailReceiver receiver(options->get_user_info().value(), options->curl_verbose());
  if (!receiver.init()) {
    return 1;
  }
  std::optional<struct email::EmailData> response = receiver.get_email();
  if (!response) {
    return 1;
  }
  std::cout << "response!" << std::endl <<
    response.value().content.subject << std::endl << std::endl <<
    response.value().content.body << std::endl;
  return 0;
}
