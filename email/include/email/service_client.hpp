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

#ifndef EMAIL__SERVICE_CLIENT_HPP_
#define EMAIL__SERVICE_CLIENT_HPP_

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/publisher.hpp"
#include "email/service.hpp"
#include "email/subscriber.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Service client.
/**
 * Sends a request to a service server and gets a response.
 */
class ServiceClient : public ServiceObject
{
public:
  /// Constructor.
  /**
   * \param service_name the service name
   */
  explicit ServiceClient(const std::string & service_name);
  ServiceClient(const ServiceClient &) = delete;
  ServiceClient & operator=(const ServiceClient &) = delete;
  ~ServiceClient();

  /// Send request.
  /**
   * For asynchronous sending of a request.
   *
   * \param request the request
   */
  void
  send_request(const std::string & request);

  /// Get a response if there is one.
  /**
   * \return the response, or `std::nullopt` if there is none
   */
  std::optional<std::string>
  get_response();

  /// Send request and get response, waiting for it.
  /**
   * TODO(christophebedard) add timeout for response?
   *
   * \param request the request to send
   * \return the response, or `std::nullopt` if it failed
   */
  std::optional<std::string>
  send_request_and_wait(const std::string & request);

private:
  Publisher pub_;
  Subscriber sub_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_CLIENT_HPP_