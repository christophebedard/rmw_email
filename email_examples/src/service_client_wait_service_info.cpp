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
#include "email/service_client.hpp"
#include "email/wait.hpp"

int main()
{
  email::init();
  email::ServiceClient client("/my_service");
  const std::string request_content = "this is the request!";
  std::cout << "making request for service '" << client.get_service_name() << "': " <<
    request_content << std::endl;
  auto sequence_number = client.send_request(request_content);
  std::cout << "waiting for response..." << std::endl;
  const auto [response, req_info] = email::wait_for_response_with_info(sequence_number, &client);
  std::cout << "response: " << response << std::endl;
  std::cout << "request info:" << std::endl <<
    "\tsource timestamp  : " << fmt::format("{}", req_info.source_timestamp()) << std::endl <<
    "\treceived timestamp: " << fmt::format("{}", req_info.received_timestamp()) << std::endl <<
    "\tclient GID        : " << req_info.client_gid().to_string() << std::endl;
  email::shutdown();
  return 0;
}
