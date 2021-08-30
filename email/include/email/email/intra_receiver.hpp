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

#ifndef EMAIL__EMAIL__INTRA_RECEIVER_HPP_
#define EMAIL__EMAIL__INTRA_RECEIVER_HPP_

#include <chrono>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/macros.hpp"
#include "email/safe_queue.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Intraprocess email receiver.
/**
 * Receives email objects from the intraprocess email sender.
 * Uses a simple queue to act as a buffer in between.
 */
class IntraEmailReceiver : public EmailReceiver
{
public:
  /// Constructor.
  /**
   * \param user_info the user information for receiving emails
   */
  EMAIL_PUBLIC
  explicit IntraEmailReceiver(UserInfo::SharedPtrConst user_info);

  EMAIL_PUBLIC
  virtual ~IntraEmailReceiver();

  EMAIL_PUBLIC
  virtual
  std::optional<struct EmailData>
  get_email(std::optional<std::chrono::nanoseconds> polling_period = std::nullopt);

  /// Receive new email.
  /**
   * This function will take care of generating a unique message ID.
   *
   * \param data the new email data
   */
  EMAIL_PUBLIC
  void
  receive(const struct EmailData & data);

private:
  EMAIL_DISABLE_COPY(IntraEmailReceiver)

  SafeQueue<struct EmailData> emails_;
};

}  // namespace email

#endif  // EMAIL__EMAIL__INTRA_RECEIVER_HPP_
