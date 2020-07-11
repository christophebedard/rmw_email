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

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/context.hpp"
#include "email/email/receiver.hpp"
#include "email/pub_sub.hpp"
#include "email/subscriber.hpp"
#include "email/types.hpp"

namespace email
{

Subscriber::Subscriber(const std::string & topic)
: PubSubObject(topic),
  receiver_(get_global_context()->get_receiver())
{}

Subscriber::~Subscriber() {}

std::string
Subscriber::get_message()
{
  std::optional<struct EmailData> email_data = std::nullopt;
  std::string subject = "";
  while (subject != get_topic()) {
    while (!email_data) {
      email_data = receiver_->get_email();
    }
    subject = email_data.value().content.subject;
  }
  return email_data.value().content.body;
}

}  // namespace email
