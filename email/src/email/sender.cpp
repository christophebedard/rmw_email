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

#include <memory>

#include "email/email/sender.hpp"
#include "email/log.hpp"

namespace email
{

EmailSender::EmailSender() {}

EmailSender::~EmailSender()
{
  logger()->debug("destroying");
}

std::shared_ptr<Logger>
EmailSender::logger()
{
  static auto logger = log::create("EmailSender");
  return logger;
}

}  // namespace email
