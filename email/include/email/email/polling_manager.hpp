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

#ifndef EMAIL__EMAIL__POLLING_MANAGER_HPP_
#define EMAIL__EMAIL__POLLING_MANAGER_HPP_

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <thread>
#include <vector>

#include "email/email/handler.hpp"
#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Manager for polling for new emails.
/**
 * Does the polling for new emails and distributes them to handlers.
 */
class PollingManager
{
public:
  /// Constructor.
  /**
   * \param receiver the email receiver to use for getting emails
   * \param polling_period the polling period, or `std::optional` to use the default value
   */
  explicit PollingManager(
    std::shared_ptr<EmailReceiver> receiver,
    const std::optional<std::chrono::nanoseconds> polling_period);

  ~PollingManager();

  /// Register a handler with the manager.
  /**
   * The handler's handling function will be called when there is a new email.
   *
   * \param handler the handler to call with new emails
   */
  void
  register_handler(std::weak_ptr<EmailHandler> handler);

  /// Get status.
  /**
   * \return true if it has been started, false otherwise
   */
  bool
  has_started() const;

  /// Start manager.
  void
  start();

  /// Shut down manager and internal thread.
  void
  shutdown();

private:
  EMAIL_DISABLE_COPY(PollingManager)

  /// Thread function for polling for new emails.
  void
  poll_thread();

  std::shared_ptr<EmailReceiver> receiver_;
  const std::optional<std::chrono::nanoseconds> polling_period_;
  bool has_started_;
  std::atomic_bool do_shutdown_;
  std::thread thread_;
  std::mutex handlers_mutex_;
  std::vector<std::weak_ptr<EmailHandler>> handlers_;
  std::shared_ptr<Logger> logger_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__POLLING_MANAGER_HPP_
