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

#include <map>
#include <memory>
#include <mutex>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/context.hpp"
#include "email/email/polling_manager.hpp"
#include "email/email/response_utils.hpp"
#include "email/log.hpp"
#include "email/safe_queue.hpp"
#include "email/service_handler.hpp"
#include "email/types.hpp"

namespace email
{

ServiceHandler::ServiceHandler()
: logger_(log::create("ServiceHandler")),
  mutex_clients_(),
  clients_(),
  mutex_servers_(),
  servers_()
{
  // Register handler with the polling manager
  get_global_context()->get_polling_manager()->register_handler(
    std::bind(
      &ServiceHandler::handle,
      this,
      std::placeholders::_1));
  logger_->debug("initialized");
}

ServiceHandler::~ServiceHandler() {}

void
ServiceHandler::register_service_client(
  const std::string & service_name,
  std::shared_ptr<std::map<uint32_t, struct EmailData>> response_map)
{
  // TODO(christophebedard) throw/return flag if a service client already exists with the name?
  std::lock_guard<std::mutex> lock(mutex_clients_);
  clients_.insert({service_name, response_map});
}

void
ServiceHandler::register_service_server(
  const std::string & service_name,
  std::shared_ptr<SafeQueue<struct EmailData>> request_queue)
{
  // TODO(christophebedard) throw/return flag if a service server already exists with the name?
  std::lock_guard<std::mutex> lock(mutex_servers_);
  servers_.insert({service_name, request_queue});
}

void
ServiceHandler::handle(const struct EmailData & data) const
{
  // TODO(christophebedard) exclude emails coming from the sender's email?
  const std::string & topic = data.content.subject;

  // Only a service response if it's a reply email, i.e. if In-Reply-To
  // header is not empty, and if it has a request ID header
  if (!data.in_reply_to.empty()) {
    // If it has a request ID header
    auto request_id = extract_request_id(data);
    if (request_id) {
      // Find service clients with matching topic
      std::lock_guard<std::mutex> lock(mutex_clients_);
      auto range = clients_.equal_range(topic);
      for (auto it = range.first; it != range.second; ++it) {
        // Add data to the map
        it->second->insert({request_id.value(), data});
      }
    }
  }

  // Only a service request if it's not a reply email
  if (data.in_reply_to.empty()) {
    // Find service servers with matching topic
    std::lock_guard<std::mutex> lock(mutex_servers_);
    auto range = servers_.equal_range(topic);
    for (auto it = range.first; it != range.second; ++it) {
      // Push message content to the queue
      it->second->push(data);
    }
  }
}

std::optional<uint32_t>
ServiceHandler::extract_request_id(const struct EmailData & data)
{
  auto request_id = utils::response::get_header_value(HEADER_REQUEST_ID, data.additional_headers);
  if (!request_id) {
    return std::nullopt;
  }
  return static_cast<uint32_t>(std::stoul(request_id.value()));
}

}  // namespace email
