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
#include <unordered_map>
#include <utility>

#include "email/email/handler.hpp"
#include "email/email/info.hpp"
#include "email/email/polling_manager.hpp"
#include "email/gid.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/safe_map.hpp"
#include "email/safe_queue.hpp"
#include "email/service_info.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Email handler for service servers.
/**
 * Distributes them to the right service server.
 *
 * There can be more than one service server for the same service name.
 * All service servers may get the request and respond, but only the first response will be used
 * by the original service client; the rest will be discarded.
 */
class ServiceHandler : public EmailHandler, public std::enable_shared_from_this<ServiceHandler>
{
public:
  using ResponseMap = SafeMap<SequenceNumber, std::pair<struct EmailData, ServiceInfo>>;
  using RequestQueue = SafeQueue<std::pair<struct EmailData, ServiceInfo>>;

  /// Constructor.
  ServiceHandler();

  virtual ~ServiceHandler();

  /// Register a service client with the handler.
  /**
   * \param gid the service client GID
   * \param response_map the service client's response map to add the new response to
   */
  void
  register_service_client(
    const Gid & gid,
    ResponseMap::WeakPtr response_map);

  /// Register a service server with the handler.
  /**
   * \param service_name the service name
   * \param request_queue the service server's request queue to push the new request to
   */
  void
  register_service_server(
    const std::string & service_name,
    RequestQueue::WeakPtr request_queue);

  virtual
  void
  register_handler(std::shared_ptr<PollingManager> polling_manager);

  /// Handle new email.
  /**
   * Adds the response or request to the maps or queues of matching clients and servers.
   */
  virtual
  void
  handle(const struct EmailData & data);

  /// Custom header name for service request sequence number.
  /**
   * Note that there is no "X-" prefix.
   * See RFC 6648: https://tools.ietf.org/html/rfc6648
   */
  static constexpr auto HEADER_SEQUENCE_NUMBER = "Request-Sequence-Number";

private:
  EMAIL_DISABLE_COPY(ServiceHandler)

  std::shared_ptr<Logger> logger_;
  mutable std::mutex mutex_clients_;
  std::unordered_map<GidValue, ResponseMap::WeakPtr> clients_;
  std::unordered_map<GidValue, SequenceNumber> clients_last_seq_;
  mutable std::mutex mutex_servers_;
  std::unordered_multimap<std::string, RequestQueue::WeakPtr> servers_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_HANDLER_HPP_
