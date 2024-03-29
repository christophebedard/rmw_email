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

#ifndef EMAIL__SERVICE_SERVER_HPP_
#define EMAIL__SERVICE_SERVER_HPP_

#include <chrono>
#include <map>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <utility>

#include "email/email/info.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/safe_queue.hpp"
#include "email/service.hpp"
#include "email/service_handler.hpp"
#include "email/service_info.hpp"
#include "email/service_request.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Service server.
/**
 * Gets a request from a client and sends a response.
 */
class ServiceServer : public ServiceObject
{
public:
  /// Constructor.
  /**
   * \param service_name the service name
   */
  EMAIL_PUBLIC
  explicit ServiceServer(const std::string & service_name);

  EMAIL_PUBLIC
  ~ServiceServer();

  /// Check if the server has an available request.
  /**
   * \return true if there is an available request, false otherwise
   */
  EMAIL_PUBLIC
  bool
  has_request();

  /// Get a request if there is one.
  /**
   * \return the request, or `std::nullopt` if there is none
   */
  EMAIL_PUBLIC
  std::optional<struct ServiceRequest>
  get_request();

  /// Get a request with info if there is one.
  /**
   * \return the request with info, or `std::nullopt` if there is none
   */
  EMAIL_PUBLIC
  std::optional<std::pair<struct ServiceRequest, ServiceInfo>>
  get_request_with_info();

  /// Send response.
  /**
   * \param request_id the original request ID
   * \param response the response
   */
  EMAIL_PUBLIC
  void
  send_response(const struct ServiceRequestId & request_id, const std::string & response);

private:
  EMAIL_DISABLE_COPY(ServiceServer)

  std::shared_ptr<Logger> logger_;
  ServiceHandler::RequestQueue::SharedPtr requests_;
  std::shared_ptr<EmailSender> sender_;
  std::map<SequenceNumber, struct EmailData> requests_raw_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_SERVER_HPP_
