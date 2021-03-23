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

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/publisher.hpp"
#include "email/service_client.hpp"
#include "email/subscriber.hpp"

namespace email
{

static constexpr auto HEADER_REQUEST_ID = "Request-ID";

ServiceClient::ServiceClient(const std::string & service_name)
: ServiceObject(service_name),
  pub_(get_service_name()),
  sub_(get_service_name())
{}
// TODO register a service (client) handler, similar to how service server gets its requests
// remove use of subscriber

// have `ServiceHandler::register_service_client()`
// have its own queue/map with <request ID: message>
// create SafeMap

ServiceClient::~ServiceClient() {}

uint32_t
ServiceClient::send_request(const std::string & request)
{
  static uint32_t request_id = 0;
  const uint32_t next_id = request_id++;
  const EmailHeaders request_id_header = {{std::string(HEADER_REQUEST_ID), std::to_string(next_id)}};
  pub_.publish(request, request_id_header);
  return next_id;
}

std::optional<std::string>
ServiceClient::get_response(uint32_t request_id)
{
  return sub_.get_message();
}

std::optional<std::string>
ServiceClient::send_request_and_wait(const std::string & request)
{
  pub_.publish(request);
  return sub_.get_message_and_wait();
}

}  // namespace email
