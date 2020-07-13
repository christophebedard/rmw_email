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
#include "email/subscriber.hpp"

int main()
{
  email::init();
  email::Subscriber sub1("/my_topic");
  email::Subscriber sub2("/my_other_topic");
  std::cout << "getting message..." << std::endl;
  auto message1 = sub1.get_message_and_wait();
  std::cout << "got message1: " << message1 << std::endl;
  auto message2 = sub2.get_message_and_wait();
  std::cout << "got message2: " << message2 << std::endl;
  email::shutdown();
  return 0;
}
