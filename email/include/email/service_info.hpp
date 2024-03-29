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

#ifndef EMAIL__SERVICE_INFO_HPP_
#define EMAIL__SERVICE_INFO_HPP_

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/communication_info.hpp"
#include "email/email/info.hpp"
#include "email/gid.hpp"
#include "email/timestamp.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Sequence number type.
typedef int64_t SequenceNumber;

/// Service info container.
/**
 * Contains metadata about a received service request or response.
 */
class ServiceInfo
{
public:
  /// Constructor.
  EMAIL_PUBLIC
  ServiceInfo(
    const Timestamp & source_timestamp,
    const Timestamp & received_timestamp,
    const Gid & client_gid,
    const SequenceNumber sequence_number);

  EMAIL_PUBLIC
  ServiceInfo(const ServiceInfo &) = default;

  EMAIL_PUBLIC
  ~ServiceInfo();

  /// Get the request or response source timestamp.
  EMAIL_PUBLIC
  const Timestamp &
  source_timestamp() const;

  /// Get the request or response reception timestamp.
  EMAIL_PUBLIC
  const Timestamp &
  received_timestamp() const;

  /// Get the service client GID.
  EMAIL_PUBLIC
  const Gid &
  client_gid() const;

  /// Get the request sequence number.
  EMAIL_PUBLIC
  SequenceNumber
  sequence_number() const;

  /// Get a ServiceInfo object from email headers.
  /**
   * The received timestamp will be created using Timestamp::now().
   *
   * \param headers the email headers
   * \return the service info object, or `std::nullopt` if the email headers
   *    don't contain the expected info
   */
  static
  std::optional<ServiceInfo>
  from_headers(const EmailHeaders & headers);

  /// Custom header name for service client GID.
  static constexpr auto HEADER_CLIENT_GID = "Client-GID";

private:
  const CommunicationInfo base_info_;
  const SequenceNumber sequence_number_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_INFO_HPP_
