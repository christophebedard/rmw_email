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

#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>
#include <vector>

#include "spdlog/fmt/chrono.h"

#include "email/email/info.hpp"
#include "email/email/polling_manager.hpp"
#include "email/email/receiver.hpp"
#include "email/log.hpp"
#include "email/utils.hpp"

namespace email
{

PollingManager::PollingManager(
  std::shared_ptr<EmailReceiver> receiver,
  const std::optional<std::chrono::nanoseconds> polling_period)
: receiver_(receiver),
  polling_period_(polling_period),
  has_started_(false),
  do_shutdown_(false),
  thread_({}),
  handlers_mutex_(),
  handlers_(),
  logger_(log::create("PollingManager"))
{
  logger_->debug(
    "initialized: period={}",
    (polling_period_.has_value() ? fmt::to_string(polling_period_.value()) : "(default)"));
}

PollingManager::~PollingManager()
{
  logger_->debug("destroying");
  shutdown();
}

void
PollingManager::register_handler(const HandlerFunction & handler)
{
  {
    std::scoped_lock<std::mutex> lock(handlers_mutex_);
    handlers_.push_back(handler);
  }
  logger_->debug("handler registered");
}

bool
PollingManager::has_started() const
{
  return has_started_;
}

void
PollingManager::start()
{
  logger_->debug("starting");
  has_started_ = true;
  thread_ = std::thread(&PollingManager::poll_thread, this);
  logger_->debug("started");
}

void
PollingManager::shutdown()
{
  logger_->debug("shutting down");
  receiver_->shutdown();
  if (has_started()) {
    do_shutdown_.store(true);
    if (thread_.joinable()) {
      thread_.join();
    }
  }
  has_started_ = false;
  logger_->debug("shut down");
}

void
PollingManager::poll_thread()
{
  utils::thread_append_name("-poll");
  logger_->debug("poll_thread start");
  while (!do_shutdown_.load()) {
    // Get new email
    std::optional<struct EmailData> email_data = std::nullopt;
    // Use a 'while true' to avoid duplicating code
    while (true) {
      email_data = receiver_->get_email(polling_period_);
      // Sleep a bit if polling wasn't successful;
      // avoid sleeping for now reason,
      // either before polling or after polling when we're shutting down
      const bool keep_polling = !email_data && !do_shutdown_.load();
      if (!keep_polling) {
        break;
      }
    }
    // Break now if shutting down
    if (do_shutdown_.load()) {
      break;
    }
    const struct EmailData & data = email_data.value();
    // Call handlers
    {
      std::scoped_lock<std::mutex> lock(handlers_mutex_);
      for (auto it = handlers_.begin(); it != handlers_.end(); ++it) {
        logger_->debug("calling handler");
        it->operator()(data);
      }
    }
  }
  logger_->debug("poll_thread end");
}

}  // namespace email
