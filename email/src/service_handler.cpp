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
#include "email/email/handler.hpp"
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
: EmailHandler(),
  logger_(log::create("ServiceHandler")),
  mutex_clients_(),
  clients_(),
  clients_last_seq_(),
  mutex_servers_(),
  servers_()
{
  // Register handler with the polling manager
  get_global_context()->get_polling_manager()->register_handler(
    [handler = std::weak_ptr<ServiceHandler>(this->shared_from_this())](
      const struct EmailData & data) {
      if (auto handler_ptr = handler.lock()) {
        handler_ptr->handle(data);
      }
      // Do nothing if the pointer could not be locked
    });
  logger_->debug("initialized");
}

ServiceHandler::~ServiceHandler()
{
  logger_->debug("destroying");
}

void
ServiceHandler::register_service_client(
  const Gid & gid,
  ResponseMap::SharedPtr response_map)
{
  {
    std::scoped_lock<std::mutex> lock(mutex_clients_);
    clients_.insert({gid.value(), response_map});
    // Set last received response sequence number to -1, i.e. none received;
    // of course note that this assumes that sequence numbers start at 0
    clients_last_seq_[gid.value()] = -1;
  }
  logger_->debug("service client registered with GID: {}", gid);
}

void
ServiceHandler::register_service_server(
  const std::string & service_name,
  RequestQueue::SharedPtr request_queue)
{
  {
    std::scoped_lock<std::mutex> lock(mutex_servers_);
    servers_.insert({service_name, request_queue});
  }
  logger_->debug("service server registered with service name: {}", service_name);
}

void
ServiceHandler::handle(const struct EmailData & data)
{
  logger_->debug("handling new email");
  const std::string & topic = data.content.subject;
  auto service_info_opt = ServiceInfo::from_headers(data.additional_headers);
  if (!service_info_opt) {
    logger_->debug("not a service message");
    return;
  }
  const ServiceInfo & service_info = service_info_opt.value();
  const Gid & client_gid = service_info.client_gid();

  // Only a service response if it's a reply email, i.e. if In-Reply-To
  // header is not empty, and if it has a sequence number header
  if (!data.in_reply_to.empty()) {
    std::scoped_lock<std::mutex> lock(mutex_clients_);
    const SequenceNumber sequence_number = service_info.sequence_number();
    // Find service client with the corresponding client GID
    auto client_it = clients_.find(client_gid.value());
    if (client_it == clients_.cend()) {
      logger_->debug(
        "client with gid {} not found for response with seq number {} for service: {}",
        client_gid,
        sequence_number,
        topic);
    } else {
      auto service_response_map = client_it->second;
      // If the client already received a response for this specific request, discard it
      const SequenceNumber last_response_sequence_number = clients_last_seq_[client_gid.value()];
      if (sequence_number <= last_response_sequence_number) {
        logger_->debug(
          "discarding response with seq number {} (<={}) for client with gid {} for service: {}",
          sequence_number,
          last_response_sequence_number,
          client_gid,
          topic);
      } else {
        logger_->debug(
          "adding response with seq number {} to client queue with gid {} for service: {}",
          sequence_number,
          client_gid,
          topic);
        // Set last received sequence number to this new one
        clients_last_seq_[client_gid.value()] = sequence_number;
        // Add data and service info to the map
        service_response_map->insert({sequence_number, {data, service_info}});
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

}  // namespace email
