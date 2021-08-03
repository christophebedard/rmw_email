// Copyright 2020-2021 Christophe Bedard
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
// #include "email/wait.hpp"

int main()
{
  email::init();
  email::ServiceClient client1("/my_service");
  email::ServiceClient client2("/my_service");
  const std::string request_content = "this is the request!";
  const std::string request1 = request_content + "1";
  const std::string request2 = request_content + "2";
  std::cout << "making requests:" << std::endl <<
    request1 << std::endl <<
    request2 << std::endl;
  auto id1 = client1.send_request(request1);
  auto id2 = client2.send_request(request2);
  while (!(client1.has_response(id1) && client2.has_response(id2))) {}  // empty
  auto response1 = client1.get_response(id1);
  auto response2 = client2.get_response(id2);
  if (response1) {
    std::cout << "response1: " << response1.value() << std::endl;
  } else {
    std::cout << "no response1" << std::endl;
  }
  if (response2) {
    std::cout << "response2: " << response2.value() << std::endl;
  } else {
    std::cout << "no response2" << std::endl;
  }
  email::shutdown();
  return 0;
}
