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

#ifndef EMAIL__SERVICE_SERVER_HPP_
#define EMAIL__SERVICE_SERVER_HPP_

#include <chrono>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/email/receiver.hpp"
#include "email/email/sender.hpp"
#include "email/safe_queue.hpp"
#include "email/service.hpp"
#include "email/subscriber.hpp"
#include "email/types.hpp"
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
  explicit ServiceServer(const std::string & service_name);
  ServiceServer(const ServiceServer &) = delete;
  ServiceServer & operator=(const ServiceServer &) = delete;
  ~ServiceServer();

  /// Check if the server has a request.
  /**
   * \return true if there is a request, false otherwise
   */
  bool
  has_request();

  /// Get a request if there is one.
  /**
   * \return the request, or `std::nullopt` if there is none
   */
  std::optional<std::string>
  get_request();

  /// Get a request, waiting until one is available.
  /**
   * TODO(christophebedard) use a timeout?
   *
   * \return the request
   */
  std::string
  get_request_and_wait();

  /// Send response.
  /**
   * TODO(christophebedard) keep link betwen request & response
   *
   * \param response the response
   */
  void
  send_response(const std::string & response);

private:
  std::shared_ptr<SafeQueue<struct EmailData>> requests_;
  std::shared_ptr<EmailSender> sender_;

  static constexpr auto WAIT_TIME = std::chrono::milliseconds(1);
};

}  // namespace email

#endif  // EMAIL__SERVICE_SERVER_HPP_
