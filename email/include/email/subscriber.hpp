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

#ifndef EMAIL__SUBSCRIBER_HPP_
#define EMAIL__SUBSCRIBER_HPP_

#include <memory>
#include <string>

#include "email/email_receiver.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

class Subscriber
{
public:
  Subscriber(
    const std::string & topic);
  Subscriber(const Subscriber &) = delete;
  ~Subscriber();

  std::string get_message();

private:
  const std::string topic_;
  std::shared_ptr<EmailReceiver> receiver_;
};

}  // namespace email

#endif  // EMAIL__SUBSCRIBER_HPP_
