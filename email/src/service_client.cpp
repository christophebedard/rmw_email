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

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/publisher.hpp"
#include "email/service_client.hpp"
#include "email/subscriber.hpp"

namespace email
{

ServiceClient::ServiceClient(const std::string & service_name)
: ServiceObject(service_name),
  pub_(get_service_name()),
  sub_(get_service_name())
{}

ServiceClient::~ServiceClient() {}

void
ServiceClient::send_request(const std::string & request)
{
  pub_.publish(request);
}

std::optional<std::string>
ServiceClient::get_response()
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
