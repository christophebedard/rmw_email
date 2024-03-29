// Copyright 2021 Christophe Bedard
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
#include <string>

#include "email/init.hpp"
#include "email/service_server.hpp"
#include "email/wait.hpp"

int main()
{
  email::init();
  email::ServiceServer server("/my_service");
  std::cout << "waiting for request for service '" << server.get_service_name() << "'..." <<
    std::endl;
  auto request = email::wait_for_request(&server);
  std::cout << "got request!" << std::endl;
  std::cout << "\tsequence number: " << request.id.sequence_number << std::endl;
  std::cout << "\trequest        : " << request.content << std::endl;
  const std::string response_content = "responseeeee!";
  std::cout << "sending response: " << response_content << std::endl;
  server.send_response(request.id, response_content);
  email::shutdown();
  return 0;
}
