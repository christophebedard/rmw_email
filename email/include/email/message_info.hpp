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

#ifndef EMAIL__MESSAGE_INFO_HPP_
#define EMAIL__MESSAGE_INFO_HPP_

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/communication_info.hpp"
#include "email/email/info.hpp"
#include "email/gid.hpp"
#include "email/timestamp.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Message info container.
/**
 * Contains metadata about a received message.
 */
class MessageInfo
{
public:
  /// Constructor.
  EMAIL_PUBLIC
  MessageInfo(
    const Timestamp & source_timestamp,
    const Timestamp & received_timestamp,
    const Gid & publisher_gid);

  EMAIL_PUBLIC
  MessageInfo(const MessageInfo &) = default;

  EMAIL_PUBLIC
  ~MessageInfo();

  /// Get the message source timestamp.
  EMAIL_PUBLIC
  const Timestamp &
  source_timestamp() const;

  /// Get the message reception timestamp.
  EMAIL_PUBLIC
  const Timestamp &
  received_timestamp() const;

  /// Get the publisher GID.
  EMAIL_PUBLIC
  const Gid &
  publisher_gid() const;

  /// Get a MessageInfo object from email headers.
  /**
   * The received timestamp will be created using Timestamp::now().
   *
   * \param headers the email headers
   * \return the message info object, or `std::nullopt` if the email headers
   *    don't contain the expected info
   */
  static
  std::optional<MessageInfo>
  from_headers(const EmailHeaders & headers);

  /// Custom header name for publisher GID.
  static constexpr auto HEADER_PUBLISHER_GID = "Publisher-GID";

private:
  const CommunicationInfo base_info_;
};

}  // namespace email

#endif  // EMAIL__MESSAGE_INFO_HPP_
