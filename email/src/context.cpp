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
#include "email/email/curl_receiver.hpp"
#include "email/email/curl_sender.hpp"
#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/utils.hpp"

namespace email
{

std::shared_ptr<Context> g_global_context = nullptr;

std::shared_ptr<Context>
get_global_context()
{
  if (!g_global_context) {
    g_global_context = std::make_shared<Context>();
  }
  return g_global_context;
}

Context::Context()
: is_valid_(false),
  options_(nullptr),
  logger_(nullptr),
  sender_(nullptr),
  receiver_(nullptr),
  polling_manager_(nullptr),
  subscription_handler_(nullptr),
  service_handler_(nullptr)
{}

Context::~Context()
{
  logger_->debug("destroying");
  if (is_valid()) {
    (void)shutdown();
  }
}

void
Context::init()
{
  if (is_valid()) {
    throw ContextAlreadyInitializedError();
  }
  is_valid_ = true;

  auto options = Options::parse_options_from_file();
  if (!options) {
    throw ContextInitFailedError("parsing options from file");
  }
  options_ = options.value();

  init_common();
}

void
Context::init(int argc, char const * const argv[])
{
  if (is_valid()) {
    throw ContextAlreadyInitializedError();
  }
  is_valid_ = true;

  auto options = Options::parse_options_from_args(argc, argv);
  if (!options) {
    // Exit with non-zero instead of throwing an exception, since this is CLI args-related
    exit(1);
  }
  options_ = options.value();

  init_common();
}

void
Context::init_common()
{
  log::init_from_env();
  spdlog::get("root")->debug("logging initialized");
  logger_ = log::create("Context");

  // Initialize in the right order: some objects might fetch
  // other objects from the context on creation or initialization
  assert(!sender_);
  sender_ = std::make_shared<CurlEmailSender>(
    options_->get_user_info(),
    options_->get_recipients(),
    options_->curl_verbose());
  std::dynamic_pointer_cast<CurlEmailSender>(sender_)->init();

  assert(!receiver_);
  receiver_ = std::make_shared<CurlEmailReceiver>(
    options_->get_user_info(),
    options_->curl_verbose());
  std::dynamic_pointer_cast<CurlEmailReceiver>(receiver_)->init();

  assert(!polling_manager_);
  polling_manager_ = std::make_shared<PollingManager>(receiver_, options_->polling_period());
  polling_manager_->start();

  assert(!subscription_handler_);
  subscription_handler_ = std::make_shared<SubscriptionHandler>();

  assert(!service_handler_);
  service_handler_ = std::make_shared<ServiceHandler>();

  logger_->debug("initialized");
}

bool
Context::shutdown()
{
  if (!is_valid()) {
    return false;
  }
  is_valid_ = false;
  logger_->debug("shutting down");

  // Finalize in the reverse order
  assert(service_handler_);
  service_handler_ = nullptr;

  assert(subscription_handler_);
  subscription_handler_ = nullptr;

  assert(polling_manager_);
  polling_manager_->shutdown();
  polling_manager_ = nullptr;

  assert(receiver_);
  receiver_->shutdown();
  receiver_ = nullptr;

  assert(sender_);
  sender_ = nullptr;

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
  return receiver_;
}

std::shared_ptr<EmailSender>
Context::get_sender() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  return sender_;
}

std::shared_ptr<PollingManager>
Context::get_polling_manager() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  return polling_manager_;
}

std::shared_ptr<SubscriptionHandler>
Context::get_subscription_handler() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  return subscription_handler_;
}

std::shared_ptr<ServiceHandler>
Context::get_service_handler() const
{
  if (!is_valid()) {
    throw ContextNotInitializedError();
  }
  return service_handler_;
}

}  // namespace email
