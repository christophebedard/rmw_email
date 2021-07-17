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

#include <chrono>
#include <memory>
#include <string>

#include "email/subscriber.hpp"
#include "email/wait_set.hpp"

namespace email
{

std::string
wait_for_message(
  std::shared_ptr<Subscriber> subscription,
  const std::chrono::milliseconds timeout)
{
  email::WaitSet waitset({subscription});
  const bool timedout = waitset.wait(timeout);
  assert(!timedout);

  return subscription->get_message().value();
}

}  // namespace email
