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

#include "email/init.hpp"
#include "email/subscription.hpp"

int main()
{
  email::init();
  email::Subscription sub1("/my_topic");
  email::Subscription sub2("/my_other_topic");
  std::cout << "getting messages..." << std::endl;
  while (!(sub1.has_message() && sub2.has_message())) {}  // empty
  auto message1 = sub1.get_message();
  auto message2 = sub2.get_message();
  std::cout << "got message1: " << message1.value() << std::endl;
  std::cout << "got message2: " << message2.value() << std::endl;
  email::shutdown();
  return 0;
}
