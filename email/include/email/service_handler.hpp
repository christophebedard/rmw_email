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
#include <string>

#include "email/safe_queue.hpp"
#include "email/log.hpp"
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
  ServiceHandler(const ServiceHandler &) = delete;
  ServiceHandler & operator=(const ServiceHandler &) = delete;
  ~ServiceHandler();

  void
  register_service_client(
    const std::string & service_name,
    std::shared_ptr<SafeQueue<struct EmailData>> response_queue);

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
  handle(const struct EmailData & data);

private:
  std::shared_ptr<Logger> logger_;
  std::mutex services_mutex_;
  std::multimap<std::string, std::shared_ptr<SafeQueue<struct EmailData>>> services_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_HANDLER_HPP_
