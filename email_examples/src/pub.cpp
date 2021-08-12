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
#include "email/publisher.hpp"

int main()
{
  email::init();
  email::Publisher pub1("/my_topic");
  email::Publisher pub2("/my_other_topic");
  std::cout << "publishing messages on topics:" << std::endl;
  std::cout << "\t'" << pub1.get_topic_name() << "'" << std::endl;
  pub1.publish("my awesome message!");
  std::cout << "\t'" << pub2.get_topic_name() << "'" << std::endl;
  pub2.publish("my other awesome message!");
  email::shutdown();
  return 0;
}
