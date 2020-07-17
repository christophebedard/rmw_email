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
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>

#include "email/context.hpp"
#include "email/email/receiver.hpp"
#include "email/email/sender.hpp"
#include "email/safe_queue.hpp"
#include "email/service.hpp"
#include "email/service_server.hpp"
#include "email/types.hpp"

namespace email
{

ServiceServer::ServiceServer(const std::string & service_name)
: ServiceObject(service_name),
  requests_(std::make_shared<SafeQueue<struct EmailData>>()),
  sender_(get_global_context()->get_sender())
{
  // Register with manager
  get_global_context()->get_subscriber_manager()->register_service_server(
    get_service_name(), requests_);
}

ServiceServer::~ServiceServer() {}

bool
ServiceServer::has_request()
{
  return !requests_->empty();
}

std::optional<std::string>
ServiceServer::get_request()
{
  if (!has_request()) {
    return std::nullopt;
  }
  return requests_->front().content.body;
}

std::string
ServiceServer::get_request_and_wait()
{
  while (requests_->empty()) {
    std::this_thread::sleep_for(WAIT_TIME);
  }
  return requests_->front().content.body;
}

void
ServiceServer::send_response(const std::string & response)
{
  // TODO(christophebedard) make this better
  if (!has_request()) {
    std::cerr << "no request to reply to" << std::endl;
    return;
  }
  auto request = requests_->dequeue();
  struct EmailContent response_content {get_service_name(), response};
  if (!sender_->reply(response_content, request)) {
    std::cerr << "send_response() failed" << std::endl;
  }
}

}  // namespace email
