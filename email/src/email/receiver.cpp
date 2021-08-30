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

#include <atomic>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/log.hpp"

namespace email
{

EmailReceiver::EmailReceiver(UserInfo::SharedPtrConst user_info)
: logger_(log::create("EmailReceiver")),
  user_info_(user_info),
  do_shutdown_(false)
{}

EmailReceiver::~EmailReceiver()
{
  // logger_->debug("destroying");
}

void
EmailReceiver::shutdown()
{
  do_shutdown_.store(true);
}

}  // namespace email
