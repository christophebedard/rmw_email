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
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
// #include <utility>
#include <vector>

#include "email/email/polling_manager.hpp"
#include "email/email/receiver.hpp"
#include "email/types.hpp"

namespace email
{

PollingManager::PollingManager(std::shared_ptr<EmailReceiver> receiver, const bool debug)
: receiver_(receiver),
  debug_(debug),
  has_started_(false),
  do_shutdown_(false),
  thread_({}),
  handlers_mutex_(),
  handlers_()
{}

PollingManager::~PollingManager() {}

void
PollingManager::register_handler(const HandlerFunction & handler)
{
  std::lock_guard<std::mutex> lock(handlers_mutex_);
  handlers_.push_back(handler);
}

bool
PollingManager::has_started() const
{
  return has_started_;
}

void
PollingManager::start()
{
  has_started_ = true;
  thread_ = std::thread(&PollingManager::poll_thread, this);
}

void
PollingManager::shutdown()
{
  receiver_->shutdown();
  if (has_started()) {
    do_shutdown_ = true;
    thread_.join();
  }
}

void
PollingManager::poll_thread()
{
  while (!do_shutdown_.load()) {
    // Get new email
    std::optional<struct EmailData> email_data = std::nullopt;
    while (!email_data && !do_shutdown_.load()) {
      email_data = receiver_->get_email();
      std::this_thread::sleep_for(POLLING_PERIOD);
    }
    // Break now if shutting down
    if (do_shutdown_.load()) {
      break;
    }
    const struct EmailData & data = email_data.value();
    // Call handlers
    {
      std::lock_guard<std::mutex> lock(handlers_mutex_);
      for (auto it = handlers_.begin(); it != handlers_.end(); ++it) {
        if (debug_) {
          std::cout << "[PollingManager] calling handler" << std::endl;
        }
        it->operator()(data);
      }
    }
  }
}

}  // namespace email
