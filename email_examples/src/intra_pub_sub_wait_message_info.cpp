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

#include "email/init.hpp"
#include "email/publisher.hpp"
#include "email/subscription.hpp"
#include "email/wait.hpp"

int main()
{
  email::init();
  email::Publisher pub("/my_topic");
  email::Subscription sub("/my_topic");

  std::cout << "publishing message on topic: '" << pub.get_topic_name() << "'" << std::endl;
  pub.publish("my awesome message!");

  std::cout << "waiting for message on topic '" << sub.get_topic_name() << "'..." << std::endl;
  auto message_with_info = email::wait_for_message_with_info(&sub);
  auto message = message_with_info.first;
  auto msg_info = message_with_info.second;
  std::cout << "got message: " << message << std::endl;
  std::cout << "message info:" << std::endl <<
    "\tsource timestamp  : " << fmt::format("{}", msg_info.source_timestamp()) << std::endl <<
    "\treceived timestamp: " << fmt::format("{}", msg_info.received_timestamp()) << std::endl <<
    "\tpublisher GID     : " << msg_info.publisher_gid().to_string() << std::endl;
  email::shutdown();
  return 0;
}
