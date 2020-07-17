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
#include <string>

#include "email/init.hpp"
#include "email/service_server.hpp"

int main()
{
  email::init();
  email::ServiceServer server("/my_service");
  std::cout << "getting request" << std::endl;
  auto request = server.get_request_and_wait();
  std::cout << "request: " << request << std::endl;
  std::cout << "sending response" << std::endl;
  server.send_response("responseeeee!");
  email::shutdown();
  return 0;
}
