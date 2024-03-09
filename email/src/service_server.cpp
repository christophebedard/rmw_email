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

#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>
#include <utility>

#include "email/communication_info.hpp"
#include "email/context.hpp"
#include "email/email/info.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/safe_queue.hpp"
#include "email/service.hpp"
#include "email/service_handler.hpp"
#include "email/service_info.hpp"
#include "email/service_request.hpp"
#include "email/service_server.hpp"

namespace email
{

ServiceServer::ServiceServer(const std::string & service_name)
: ServiceObject(service_name),
  logger_(log::get_or_create("ServiceServer::" + service_name)),
  requests_(std::make_shared<ServiceHandler::RequestQueue>()),
  sender_(get_global_context()->get_sender()),
  requests_raw_()
{
  logger_->debug("created with GID: {}", get_gid());
  // Register with handler
  get_global_context()->get_service_handler()->register_service_server(
    get_service_name(), requests_);
}

ServiceServer::~ServiceServer()
{
  logger_->debug("destroying");
}

bool
ServiceServer::has_request()
{
  return !requests_->empty();
}

std::optional<struct ServiceRequest>
ServiceServer::get_request()
{
  auto request_with_info_opt = get_request_with_info();
  if (!request_with_info_opt) {
    return std::nullopt;
  }
  return request_with_info_opt.value().first;
}

std::optional<std::pair<struct ServiceRequest, ServiceInfo>>
ServiceServer::get_request_with_info()
{
  if (!has_request()) {
    return std::nullopt;
  }
  const auto [email_data, info] = requests_->dequeue();
  // Put raw request data in a map so that we can
  // fetch & use it when sending our response
  requests_raw_.insert({info.sequence_number(), email_data});
  return {{
    ServiceRequest(info.sequence_number(), info.client_gid(), email_data.content.body), info}};
}

void
ServiceServer::send_response(
  const struct ServiceRequestId & request_id,
  const std::string & response)
{
  // Get & remove raw request data from internal map
  auto request_data = requests_raw_.find(request_id.sequence_number);
  if (request_data == requests_raw_.end()) {
    logger_->error("could not find raw request data");
    return;
  }
  const struct EmailData data = request_data->second;
  requests_raw_.erase(request_data);
  // Reply and include sequence number and client GID
  struct EmailContent response_content {get_service_name(), response};
  const EmailHeaders headers = {
    {std::string(ServiceHandler::HEADER_SEQUENCE_NUMBER),
      std::to_string(request_id.sequence_number)},
    {ServiceInfo::HEADER_CLIENT_GID, request_id.client_gid.to_string()},
    {CommunicationInfo::HEADER_SOURCE_TIMESTAMP, Timestamp::now().to_string()}};
  if (!sender_->reply(response_content, data, headers)) {
    logger_->error("send_response() failed");
  }
}

}  // namespace email
