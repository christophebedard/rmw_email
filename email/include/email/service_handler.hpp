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

#ifndef EMAIL__SERVICE_HANDLER_HPP_
#define EMAIL__SERVICE_HANDLER_HPP_

#include <map>
#include <memory>
#include <mutex>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/safe_map.hpp"
#include "email/safe_queue.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email handler for service servers.
/**
 * Distributes them to the right service server.
 */
class ServiceHandler
{
public:
  /// Constructor.
  ServiceHandler();

  ~ServiceHandler();

  /// Register a service client with the handler.
  /**
   * \param service_name the service name
   * \param response_map the service client's response map to add the new response to
   */
  void
  register_service_client(
    const std::string & service_name,
    std::shared_ptr<SafeMap<uint32_t, struct EmailData>> response_map);

  /// Register a service server with the handler.
  /**
   * \param service_name the service name
   * \param request_queue the service server's request queue to push the new request to
   */
  void
  register_service_server(
    const std::string & service_name,
    std::shared_ptr<SafeQueue<struct EmailData>> request_queue);

  /// Handle new email.
  /**
   * To be called by the `PollingManager`.
   *
   * \param data the new email data
   */
  void
  handle(const struct EmailData & data) const;

  /// Extract request ID from email data.
  /**
   * \param data the email data
   * \return the request ID, or `std::nullopt` if there is none
   */
  static
  std::optional<uint32_t>
  extract_request_id(const struct EmailData & data);

  static constexpr auto HEADER_REQUEST_ID = "Request-ID";

private:
  EMAIL_DISABLE_COPY(ServiceHandler)

  /// Try to call `std::stoul` and return `std::nullopt` if it fails.
  static
  std::optional<uint32_t>
  optional_stoul(const std::string & str);

  std::shared_ptr<Logger> logger_;
  mutable std::mutex mutex_clients_;
  std::multimap<std::string, std::shared_ptr<SafeMap<uint32_t, struct EmailData>>> clients_;
  mutable std::mutex mutex_servers_;
  std::multimap<std::string, std::shared_ptr<SafeQueue<struct EmailData>>> servers_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_HANDLER_HPP_
