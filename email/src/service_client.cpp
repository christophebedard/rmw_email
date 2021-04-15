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

#include "email/context.hpp"
#include "email/log.hpp"
#include "email/publisher.hpp"
#include "email/safe_map.hpp"
#include "email/service_client.hpp"

namespace email
{

ServiceClient::ServiceClient(const std::string & service_name)
: ServiceObject(service_name),
  logger_(log::create("ServiceClient::" + service_name)),
  responses_(std::make_shared<SafeMap<uint32_t, struct EmailData>>()),
  pub_(get_service_name())
{
  // Register with handler
  get_global_context()->get_service_handler()->register_service_client(
    service_name, responses_);
}


ServiceClient::~ServiceClient() {}

void
ServiceClient::send_request(const std::string & request, const uint32_t request_id)
{
  const EmailHeaders request_id_header = {
    {std::string(ServiceHandler::HEADER_REQUEST_ID), std::to_string(request_id)}};
  pub_.publish(request, request_id_header);
}

uint32_t
ServiceClient::send_request(const std::string & request)
{
  static std::atomic_uint32_t request_id_counter = 0u;
  const uint32_t request_id = request_id_counter++;
  logger_->debug("creating request with ID: " + std::to_string(request_id));
  send_request(request, request_id);
  return request_id;
}

bool
ServiceClient::has_response(const uint32_t request_id)
{
  return responses_->find(request_id) != responses_->cend();
}

std::optional<std::string>
ServiceClient::get_response(const uint32_t request_id)
{
  // TODO(christophebedard) remove double check
  if (!has_response(request_id)) {
    return std::nullopt;
  }
  auto it = responses_->find(request_id);
  if (it == responses_->cend()) {
    return std::nullopt;
  }
  const std::string response = it->second.content.body;
  responses_->erase(it);
  return response;
}

std::optional<std::string>
ServiceClient::send_request_and_wait(const std::string & request)
{
  const auto request_id = send_request(request);
  while (!has_response(request_id)) {
    std::this_thread::sleep_for(WAIT_TIME);
  }
  return get_response(request_id);
}

}  // namespace email
