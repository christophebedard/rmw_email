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

#ifndef EMAIL__SERVICE_CLIENT_HPP_
#define EMAIL__SERVICE_CLIENT_HPP_

#include <chrono>
#include <map>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/publisher.hpp"
#include "email/safe_map.hpp"
#include "email/service.hpp"
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
  EMAIL_PUBLIC
  explicit ServiceClient(const std::string & service_name);

  EMAIL_PUBLIC
  ~ServiceClient();

  /// Send request with specific ID.
  /**
   * For asynchronous sending of a request.
   *
   * \param request the request
   * \param request_id the request ID; to use for getting the corresponding response
   */
  EMAIL_PUBLIC
  void
  send_request(const std::string & request, const uint32_t request_id);

  /// Send request.
  /**
   * For asynchronous sending of a request.
   *
   * \param request the request
   * \return the request ID to use for getting the corresponding response
   */
  EMAIL_PUBLIC
  uint32_t
  send_request(const std::string & request);

  /// Check if the client has an available response to a request.
  /**
   * \param request_id the request ID
   * \return true if there is an available response, false otherwise
   */
  EMAIL_PUBLIC
  bool
  has_response(const uint32_t request_id);

  /// Check if the client has an available response to any request.
  /**
   * Note: `has_response(uint32_t)` should be used instead.
   *
   * \return true if there is an available response, false otherwise
   */
  EMAIL_PUBLIC
  bool
  has_response();

  /// Get a response if there is one.
  /**
   * \param request_id the request ID
   * \return the response, or `std::nullopt` if there is none
   */
  EMAIL_PUBLIC
  std::optional<std::string>
  get_response(const uint32_t request_id);

private:
  EMAIL_DISABLE_COPY(ServiceClient)

  std::shared_ptr<Logger> logger_;
  SafeMap<uint32_t, struct EmailData>::SharedPtr responses_;
  Publisher pub_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_CLIENT_HPP_
