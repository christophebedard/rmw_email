// Copyright 2021 Christophe Bedard
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

#ifndef EMAIL__EMAIL__RECEIVER_HPP_
#define EMAIL__EMAIL__RECEIVER_HPP_

#include <atomic>
#include <chrono>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/email/info.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Abstract email receiver.
/**
 * Receives, or fetches, emails.
 */
class EmailReceiver
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for receiving emails
   */
  EMAIL_PUBLIC
  explicit EmailReceiver(UserInfo::SharedPtrConst user_info);

  EMAIL_PUBLIC
  virtual ~EmailReceiver();

  /// Shut down.
  /**
   * Stops any currently-running internal polling loop.
   */
  EMAIL_PUBLIC
  void
  shutdown();

  /// Get a new email.
  /**
   * This function fetches a new email through polling.
   *
   * The caller can specify a polling period, which will be used as a target polling rate.
   * This means that, if the internal polling call takes more time than the polling period,
   * the next call will be executed right away.
   *
   * If the polling period value is equal to 0, the sleep call will be skipped,
   * and polling will be done as fast as possible.
   * This is the default value.
   *
   * \param polling_period the polling period
   * \return the new email, or `std::nullopt` if it failed
   */
  EMAIL_PUBLIC
  virtual
  std::optional<struct EmailData>
  get_email(std::optional<std::chrono::nanoseconds> polling_period = std::nullopt) = 0;

protected:
  std::shared_ptr<Logger> logger_;
  UserInfo::SharedPtrConst user_info_;
  std::atomic_bool do_shutdown_;

private:
  EMAIL_DISABLE_COPY(EmailReceiver)
};

}  // namespace email

#endif  // EMAIL__EMAIL__RECEIVER_HPP_
