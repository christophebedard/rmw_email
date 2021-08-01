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

#include <atomic>
#include <map>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>
#include <utility>

#include "email/context.hpp"
#include "email/log.hpp"
#include "email/publisher.hpp"
#include "email/safe_map.hpp"
#include "email/service_client.hpp"
#include "email/service_info.hpp"
#include "email/service_handler.hpp"

namespace email
{

ServiceClient::ServiceClient(const std::string & service_name)
: ServiceObject(service_name),
  logger_(log::get_or_create("ServiceClient::" + service_name)),
  responses_(std::make_shared<ServiceHandler::ServiceResponseMap>()),
  pub_(get_service_name())
{
  logger_->debug("created with GID: {}", get_gid());
  // Register with handler
  get_global_context()->get_service_handler()->register_service_client(
    get_gid(), responses_);
}

ServiceClient::~ServiceClient()
{
  logger_->debug("destroying");
}

void
ServiceClient::send_request(const std::string & request, const SequenceNumber sequence_number)
{
  // Publisher will add source timestamp
  const EmailHeaders headers = {
    {std::string(ServiceHandler::HEADER_SEQUENCE_NUMBER), std::to_string(sequence_number)},
    {ServiceInfo::HEADER_CLIENT_GID, get_gid().to_string()}};
  pub_.publish(request, headers);
}

SequenceNumber
ServiceClient::send_request(const std::string & request)
{
  static std::atomic_int64_t sequence_number_counter = 0l;
  const SequenceNumber sequence_number = sequence_number_counter++;
  logger_->debug("creating request with sequence number: {}", sequence_number);
  send_request(request, sequence_number);
  return sequence_number;
}

bool
ServiceClient::has_response(const SequenceNumber sequence_number)
{
  return responses_->contains(sequence_number);
}

bool
ServiceClient::has_response()
{
  return !responses_->empty();
}

std::optional<std::string>
ServiceClient::get_response(const SequenceNumber sequence_number)
{
  auto response_with_info_opt = get_response_with_info(sequence_number);
  if (!response_with_info_opt) {
    return std::nullopt;
  }
  return response_with_info_opt.value().first;
}

std::optional<std::pair<std::string, ServiceInfo>>
ServiceClient::get_response_with_info(const SequenceNumber sequence_number)
{
  auto it = responses_->find(sequence_number);
  if (it == responses_->cend()) {
    return std::nullopt;
  }
  const auto email_data = it->second.first;
  const auto info = it->second.second;
  const std::string response = email_data.content.body;
  responses_->erase(it);
  return {{response, info}};
}

}  // namespace email
