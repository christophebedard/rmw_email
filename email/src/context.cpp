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

#include <memory>
#include <string>

#include "email/context.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{

std::shared_ptr<Context> get_global_context()
{
  static std::shared_ptr<Context> global_context = std::make_shared<Context>();
  return global_context;
}

void init(int argc, char const * const argv[])
{
  get_global_context()->init(argc, argv);
}

bool shutdown()
{
  return true;
}

Context::Context()
: user_info_(nullptr)
{}

Context::~Context()
{}

void Context::init(int argc, char const * const argv[])
{
  // TODO(christophebedard) change this to generic "options"
  auto info_opt = utils::parse_user_connection_info(argc, argv);
  if (!info_opt) {
    throw std::runtime_error("Context::init() failed");
  }
  user_info_ = std::make_shared<struct UserInfo>(info_opt.value());
}

std::shared_ptr<EmailReceiver> Context::get_receiver()
{
  // TODO(christophebedard) have classes use the UserInfo shared_ptr
  static std::shared_ptr<EmailReceiver> receiver = std::make_shared<EmailReceiver>(
    *user_info_.get());
  if (!receiver->is_valid()) {
    receiver->init();
  }
  return receiver;
}

std::shared_ptr<EmailSender> Context::get_sender()
{
  // TODO(christophebedard) build/extract recipients in init()
  static const struct EmailRecipients recipients = {{"bedard.christophe@gmail.com"}, {}, {}};
  // TODO(christophebedard) have classes use the UserInfo shared_ptr
  static std::shared_ptr<EmailSender> sender = std::make_shared<EmailSender>(
    *user_info_.get(), recipients);
  if (!sender->is_valid()) {
    sender->init();
  }
  return sender;
}


}  // namespace email
