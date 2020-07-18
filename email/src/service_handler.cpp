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

#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "email/context.hpp"
#include "email/email/polling_manager.hpp"
#include "email/safe_queue.hpp"
#include "email/service_handler.hpp"
#include "email/types.hpp"

namespace email
{

ServiceHandler::ServiceHandler(const bool debug)
: debug_(debug),
  services_mutex_(),
  services_()
{
  // Register handler with the polling manager
  get_global_context()->get_polling_manager()->register_handler(
    std::bind(
      &ServiceHandler::handle,
      this,
      std::placeholders::_1));
}

ServiceHandler::~ServiceHandler() {}

void
ServiceHandler::register_service_server(
  const std::string & service,
  std::shared_ptr<SafeQueue<struct EmailData>> request_queue)
{
  // TODO(christophebedard) throw/return flag if a service server already exists with the name?
  std::lock_guard<std::mutex> lock(services_mutex_);
  services_.insert({service, request_queue});
}

void
ServiceHandler::handle(const struct EmailData & data)
{
  // TODO(christophebedard) exclude emails coming from the sender's email?
  // Only a service request if it's not a reply email, i.e. if In-Reply-To header is empty
  if (data.in_reply_to.empty()) {
    std::lock_guard<std::mutex> lock(services_mutex_);
    const std::string & topic = data.content.subject;
    auto range = services_.equal_range(topic);
    for (auto it = range.first; it != range.second; ++it) {
      // Push message content to the queue
      it->second->push(data);
    }
  }
}

}  // namespace email
