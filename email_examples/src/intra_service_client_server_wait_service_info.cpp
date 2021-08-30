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
#include "email/service_info.hpp"
#include "email/service_server.hpp"
#include "email/wait.hpp"

int main()
{
  email::init();
  email::ServiceClient client("/my_service");
  email::ServiceServer server("/my_service");

  const std::string request_content = "this is the request!";
  std::cout << "making request for service '" << client.get_service_name() << "': " <<
    request_content << std::endl;
  auto sequence_number = client.send_request(request_content);

  std::cout << "waiting for request for service '" << server.get_service_name() << "'..." <<
    std::endl;
  auto request_with_info = email::wait_for_request_with_info(&server);
  auto request = request_with_info.first;
  auto request_info = request_with_info.second;
  std::cout << "got request!" << std::endl <<
    "\tsequence number: " << request.id.sequence_number << std::endl <<
    "\trequest        : " << request.content << std::endl;
  std::cout << "request info:" << std::endl <<
    "\tsource timestamp  : " << fmt::format("{}", request_info.source_timestamp()) <<
    std::endl <<
    "\treceived timestamp: " << fmt::format("{}", request_info.received_timestamp()) <<
    std::endl <<
    "\tclient GID        : " << request_info.client_gid().to_string() << std::endl;
  const std::string response_content = "responseeeee!";
  std::cout << "sending response: " << response_content << std::endl;
  server.send_response(request.id, response_content);

  std::cout << "waiting for response..." << std::endl;
  auto response_with_info = email::wait_for_response_with_info(sequence_number, &client);
  auto response = response_with_info.first;
  auto resp_info = response_with_info.second;
  std::cout << "response: " << response << std::endl;
  std::cout << "request info:" << std::endl <<
    "\tsource timestamp  : " << fmt::format("{}", resp_info.source_timestamp()) << std::endl <<
    "\treceived timestamp: " << fmt::format("{}", resp_info.received_timestamp()) << std::endl <<
    "\tclient GID        : " << resp_info.client_gid().to_string() << std::endl;
  email::shutdown();
  return 0;
}
