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
#include "email/email/info.hpp"
#include "email/email/polling_manager.hpp"
#include "email/email/response_utils.hpp"
#include "email/gid.hpp"
#include "email/log.hpp"
#include "email/safe_map.hpp"
#include "email/safe_queue.hpp"
#include "email/service_handler.hpp"
#include "email/service_info.hpp"
#include "email/utils.hpp"

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

ServiceHandler::~ServiceHandler()
{
  logger_->debug("destroying");
}

void
ServiceHandler::register_service_client(
  const Gid & gid,
  ServiceResponseMap::SharedPtr response_map)
{
  {
    std::scoped_lock<std::mutex> lock(mutex_clients_);
    clients_.insert({gid.value(), response_map});
  }
  logger_->debug("service client registered with GID: {}", gid);
}

void
ServiceHandler::register_service_server(
  const std::string & service_name,
  RequestQueue::SharedPtr request_queue)
{
  // TODO(christophebedard) throw/return flag if a service server already exists with the name?
  {
    std::scoped_lock<std::mutex> lock(mutex_servers_);
    servers_.insert({service_name, request_queue});
  }
  logger_->debug("service server registered with service name: {}", service_name);
}

void
ServiceHandler::handle(const struct EmailData & data) const
{
  logger_->debug("handling new email");
  const std::string & topic = data.content.subject;
  auto service_info_opt = ServiceInfo::from_headers(data.additional_headers);
  if (!service_info_opt) {
    logger_->debug("not a service message");
    return;
  }
  const ServiceInfo & service_info = service_info_opt.value();

  // Only a service response if it's a reply email, i.e. if In-Reply-To
  // header is not empty, and if it has a sequence number header
  if (!data.in_reply_to.empty()) {
    // If it has a sequence number header
    auto sequence_number = extract_sequence_number(data);
    if (sequence_number) {
      // Find service clients with matching client GID
      std::scoped_lock<std::mutex> lock(mutex_clients_);
      auto range = clients_.equal_range(service_info.client_gid().value());
      for (auto it = range.first; it != range.second; ++it) {
        logger_->debug(
          "adding response with seq number {} to client queue for service: {}",
          sequence_number.value(),
          topic);
        // Add data to the map
        it->second->insert({sequence_number.value(), {data, service_info}});
      }
    }
  }

  // Only a service request if it's not a reply email
  if (data.in_reply_to.empty()) {
    // Find service servers with matching topic
    std::scoped_lock<std::mutex> lock(mutex_servers_);
    auto range = servers_.equal_range(topic);
    for (auto it = range.first; it != range.second; ++it) {
      // Push message content to the queue
      logger_->debug("adding request to service queue for service: {}", topic);
      it->second->push({data, service_info});
    }
  }
}

std::optional<uint32_t>
ServiceHandler::extract_sequence_number(const struct EmailData & data)
{
  auto sequence_number = utils::response::get_header_value(
    HEADER_SEQUENCE_NUMBER, data.additional_headers);
  if (!sequence_number) {
    return std::nullopt;
  }
  return utils::optional_stoul(sequence_number.value());
}

}  // namespace email
