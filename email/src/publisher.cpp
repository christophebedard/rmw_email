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
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/context.hpp"
#include "email/email_sender.hpp"
#include "email/publisher.hpp"
#include "email/types.hpp"

namespace email
{

Publisher::Publisher(
  const std::string & topic)
: topic_(topic),
  sender_(get_global_context()->get_sender())
{
  // TODO(christophebedard) validate topic name (no newline)
}

Publisher::~Publisher() {}

void Publisher::publish(const std::string & message)
{
  struct EmailContent content;
  content.subject = topic_;
  content.body = message;
  if (!sender_->send(content)) {
    std::cerr << "publish() failed" << std::endl;
  }
}

}  // namespace email