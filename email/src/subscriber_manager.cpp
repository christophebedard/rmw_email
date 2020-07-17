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
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

#include "email/email/receiver.hpp"
#include "email/safe_queue.hpp"
#include "email/subscriber_manager.hpp"
#include "email/types.hpp"

namespace email
{

SubscriberManager::SubscriberManager(std::shared_ptr<EmailReceiver> receiver, const bool debug)
: receiver_(receiver),
  debug_(debug),
  has_started_(false),
  do_shutdown_(false),
  thread_({}),
  subscribers_mutex_(),
  subscribers_(),
  services_mutex_(),
  services_()
{}

SubscriberManager::~SubscriberManager() {}

void
SubscriberManager::register_subscriber(
  const std::string & topic,
  std::shared_ptr<SafeQueue<std::string>> message_queue)
{
  std::lock_guard<std::mutex> lock(subscribers_mutex_);
  subscribers_.insert({topic, message_queue});
}

void
SubscriberManager::register_service_server(
  const std::string & service,
  std::shared_ptr<SafeQueue<struct EmailData>> request_queue)
{
  std::lock_guard<std::mutex> lock(services_mutex_);
  services_.insert({service, request_queue});
}

bool
SubscriberManager::has_started() const
{
  return has_started_;
}

void
SubscriberManager::start()
{
  has_started_ = true;
  thread_ = std::thread(&SubscriberManager::poll_thread, this);
}

void
SubscriberManager::shutdown()
{
  receiver_->shutdown();
  do_shutdown_ = true;
  thread_.join();
}

void
SubscriberManager::poll_thread()
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
    const std::string & topic = data.content.subject;
    // Push it to the right queue
    // TODO(christophebedard) rename this class, or extract thread/polling to another class
    {
      std::lock_guard<std::mutex> lock(subscribers_mutex_);
      auto range = subscribers_.equal_range(topic);
      for (auto it = range.first; it != range.second; ++it) {
        // Push message content to the queue
        it->second->push(data.content.body);
      }
    }
    // Only a service request if it's not a reply email, i.e. if In-Reply-To header is empty
    if (data.in_reply_to.empty()) {
      // TODO(christophebedard) exclude emails coming from the sender's email?
      std::lock_guard<std::mutex> lock(services_mutex_);
      auto range = services_.equal_range(topic);
      for (auto it = range.first; it != range.second; ++it) {
        // Push message content to the queue
        it->second->push(data);
      }
    }
  }
}

}  // namespace email
