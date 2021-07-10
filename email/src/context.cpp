// Copyright 2020-2021 Christophe Bedard
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

#include <cstdlib>
#include <memory>
#include <string>

#include "email/context.hpp"
#include "email/log.hpp"
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
: logger_(nullptr),
  options_(nullptr),
  is_valid_(false),
  is_receiver_init_(false),
  is_polling_manager_init_(false)
{}

Context::~Context()
{
  if (!is_valid()) {
    (void)shutdown();
  }
}

void
Context::init()
{
  if (is_valid()) {
    throw ContextAlreadyInitializedError();
  }
  init_common();
  auto options = Options::parse_options_from_file();
  if (!options) {
    throw ContextInitFailedError("parsing options from file");
  }
  options_ = options.value();

  is_valid_ = true;
}

void
Context::init(int argc, char const * const argv[])
{
  if (is_valid()) {
    throw ContextAlreadyInitializedError();
  }
  init_common();
  auto options = Options::parse_options_from_args(argc, argv);
  if (!options) {
    // Exit with non-zero instead of throwing an exception, since this is CLI args-related
    exit(1);
  }
  options_ = options.value();

  is_valid_ = true;
}

void
Context::init_common()
{
  log::init_from_env();
  spdlog::get("root")->debug("logging initialized");
  logger_ = log::create("Context");
}

bool
Context::shutdown()
{
  if (!is_valid()) {
    return false;
  }
  logger_->debug("shutting down");
  // Only call shutdown() if they have been init, otherwise they will get initialized
  if (is_receiver_init_) {
    get_receiver()->shutdown();
  }
  if (is_polling_manager_init_) {
    get_polling_manager()->shutdown();
  }
  logger_->debug("shut down");
  log::shutdown();
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
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  return options_;
}

std::shared_ptr<EmailReceiver>
Context::get_receiver() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  static std::shared_ptr<EmailReceiver> receiver = std::make_shared<EmailReceiver>(
    options_->get_user_info(),
    options_->curl_verbose());
  if (!receiver->is_valid()) {
    receiver->init();
    is_receiver_init_ = true;
  }
  return receiver;
}

std::shared_ptr<EmailSender>
Context::get_sender() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  static std::shared_ptr<EmailSender> sender = std::make_shared<EmailSender>(
    options_->get_user_info(),
    options_->get_recipients(),
    options_->curl_verbose());
  if (!sender->is_valid()) {
    sender->init();
  }
  return sender;
}

std::shared_ptr<PollingManager>
Context::get_polling_manager() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  static std::shared_ptr<PollingManager> manager =
    std::make_shared<PollingManager>(get_receiver());
  if (!manager->has_started()) {
    manager->start();
    is_polling_manager_init_ = true;
  }
  return manager;
}

std::shared_ptr<SubscriptionHandler>
Context::get_subscription_handler() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  static std::shared_ptr<SubscriptionHandler> handler = std::make_shared<SubscriptionHandler>();
  return handler;
}

std::shared_ptr<ServiceHandler>
Context::get_service_handler() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  static std::shared_ptr<ServiceHandler> handler = std::make_shared<ServiceHandler>();
  return handler;
}

}  // namespace email
