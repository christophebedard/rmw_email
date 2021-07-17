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
#include <memory>

#include "email/init.hpp"
#include "email/subscriber.hpp"
#include "email/wait_set.hpp"

using namespace std::chrono_literals;

int main()
{
  email::init();
  auto sub = std::make_shared<email::Subscriber>("/my_topic");

  std::cout << "waiting for message..." << std::endl;
  email::WaitSet waitset({sub});
  const bool timedout = waitset.wait(10s);

  if (!timedout) {
    auto message = sub->get_message();
    std::cout << "got message: " << message.value() << std::endl;
  } else {
    std::cout << "...wait timed out" << std::endl;
  }
  email::shutdown();
  return timedout ? 1 : 0;
}
