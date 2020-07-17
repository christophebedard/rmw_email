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

#include "email/init.hpp"
#include "email/service_client.hpp"

int main()
{
  email::init();
  email::ServiceClient client("/my_service");
  std::cout << "making request" << std::endl;
  auto response = client.send_request_and_wait("this is the request!");
  if (response) {
    std::cout << "response: " << response.value() << std::endl;
  } else {
    std::cout << "no response" << std::endl;
  }
  email::shutdown();
  return 0;
}
