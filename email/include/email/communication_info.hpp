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

#ifndef EMAIL__COMMUNICATION_INFO_HPP_
#define EMAIL__COMMUNICATION_INFO_HPP_

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/email/info.hpp"
#include "email/gid.hpp"
#include "email/timestamp.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Communication info container.
/**
 * Contains metadata about a specific communication instance.
 * This container is too abstract to be used by itself.
 */
class CommunicationInfo
{
public:
  /// Constructor.
  EMAIL_PUBLIC
  CommunicationInfo(
    const Timestamp & source_timestamp,
    const Timestamp & received_timestamp,
    const Gid & source_gid);

  EMAIL_PUBLIC
  CommunicationInfo(const CommunicationInfo &) = default;

  EMAIL_PUBLIC
  ~CommunicationInfo();

  /// Get the source timestamp.
  EMAIL_PUBLIC
  const Timestamp &
  source_timestamp() const;

  /// Get the reception timestamp.
  EMAIL_PUBLIC
  const Timestamp &
  received_timestamp() const;

  /// Get the source GID.
  EMAIL_PUBLIC
  const Gid &
  source_gid() const;

  /// Get a CommunicationInfo object from email headers.
  /**
   * The received timestamp will be created using Timestamp::now().
   *
   * \param headers the email headers
   * \param source_gid_header the name of the header for the source GID
   * \return the communication info object, or `std::nullopt` if the email headers
   *    don't contain the expected info
   */
  static
  std::optional<CommunicationInfo>
  from_headers(const EmailHeaders & headers, const std::string & source_gid_header);

  /// Custom header name for source timestamp.
  static constexpr auto HEADER_SOURCE_TIMESTAMP = "Source-Timestamp";

private:
  const Timestamp source_timestamp_;
  const Timestamp received_timestamp_;
  const Gid source_gid_;
};

}  // namespace email

#endif  // EMAIL__COMMUNICATION_INFO_HPP_
