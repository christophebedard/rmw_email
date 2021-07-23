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

#include "email/communication_info.hpp"
#include "email/gid.hpp"
#include "email/timestamp.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

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
    const uint32_t request_id);

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

  /// Get the request ID.
  EMAIL_PUBLIC
  uint32_t
  request_id() const;

  /// Get a ServiceInfo object from email headers.
  /**
   * The received timestamp will be created using Timestamp::now().
   */
  static
  ServiceInfo
  from_headers(const EmailHeaders & headers);

  /// Custom header name for service client GID.
  static constexpr auto HEADER_CLIENT_GID = "Client-GID";

private:
  const CommunicationInfo base_info_;
  const uint32_t request_id_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_INFO_HPP_
