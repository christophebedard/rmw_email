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
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/email/intra_receiver.hpp"
#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/gid.hpp"
#include "email/log.hpp"
#include "email/safe_queue.hpp"

namespace email
{

IntraEmailReceiver::IntraEmailReceiver()
: EmailReceiver(),
  emails_()
{}

IntraEmailReceiver::~IntraEmailReceiver()
{
  logger_->debug("destroying");
}

std::optional<struct EmailData>
IntraEmailReceiver::get_email(std::optional<std::chrono::nanoseconds> polling_period)
{
  static_cast<void>(polling_period);
  if (emails_.empty()) {
    return std::nullopt;
  }
  return emails_.dequeue();
}

void
IntraEmailReceiver::receive(const struct EmailData & data)
{
  // TODO(christophebedard) replace GID
  // add something to randomly generate message IDs like this here
  // Looks like: "<612c17e3.1c69fb81.6fd11.361f@mx.google.com>"
  struct EmailData data_with_message_id = data;
  data_with_message_id.message_id = Gid::new_gid().to_string();
  logger_->debug("receiving:\n{}", data_with_message_id);
  emails_.push(data_with_message_id);
}

}  // namespace email
