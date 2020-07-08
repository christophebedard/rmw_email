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

std::shared_ptr<Context>
get_global_context()
{
  static std::shared_ptr<Context> global_context = std::make_shared<Context>();
  return global_context;
}

Context::Context()
: options_(nullptr),
  is_valid_(false)
{}

Context::~Context()
{
  if (!is_valid_) {
    (void)shutdown();
  }
}

void
Context::init()
{
  if (is_valid_) {
    throw std::runtime_error("Context already initialized");
  }
  auto options = Options::parse_options_from_file();
  if (!options) {
    throw std::runtime_error("Context::init() failed");
  }
  options_ = options.value();
  is_valid_ = true;
}

void
Context::init(int argc, char const * const argv[])
{
  if (is_valid_) {
    throw std::runtime_error("Context already initialized");
  }
  auto options = Options::parse_options_from_args(argc, argv);
  if (!options) {
    throw std::runtime_error("Context::init() failed");
  }
  options_ = options.value();
  is_valid_ = true;
}

bool
Context::shutdown()
{
  if (!is_valid_) {
    return false;
  }
  // TODO(christophebedard) actually do something
  return true;
}

bool
Context::is_valid() const
{
  return is_valid_;
}

std::shared_ptr<Options>
Context::get_options() const
{
  if (!is_valid_) {
    throw std::runtime_error("Context not initialized");
  }
  return options_;
}

std::shared_ptr<EmailReceiver>
Context::get_receiver() const
{
  if (!is_valid_) {
    throw std::runtime_error("Context not initialized");
  }
  // TODO(christophebedard) have classes use the UserInfo shared_ptr
  static std::shared_ptr<EmailReceiver> receiver = std::make_shared<EmailReceiver>(
    *options_->get_user_info().get());
  if (!receiver->is_valid()) {
    receiver->init();
  }
  return receiver;
}

std::shared_ptr<EmailSender>
Context::get_sender() const
{
  if (!is_valid_) {
    throw std::runtime_error("Context not initialized");
  }
  if (!options_->get_recipients().has_value()) {
    throw std::runtime_error("no recipients");
  }
  // TODO(christophebedard) have classes use the shared_ptrs
  static std::shared_ptr<EmailSender> sender = std::make_shared<EmailSender>(
    *options_->get_user_info().get(),
    *options_->get_recipients().value().get());
  if (!sender->is_valid()) {
    sender->init();
  }
  return sender;
}

}  // namespace email
