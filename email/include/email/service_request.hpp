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

#ifndef EMAIL__SERVICE_REQUEST_HPP_
#define EMAIL__SERVICE_REQUEST_HPP_

#include <string>

#include "email/gid.hpp"
#include "email/service_info.hpp"

namespace email
{

/// Service request ID, with a sequence number and a client GID.
struct ServiceRequestId
{
  /// Sequence number of the request.
  SequenceNumber sequence_number;
  /// GID of the service client that made the request.
  Gid client_gid;
  /// Constructor.
  ServiceRequestId(const SequenceNumber sequence_number_, const Gid & client_gid_)
  : sequence_number(sequence_number_),
    client_gid(client_gid_)
  {}
  /// Copy constructor.
  ServiceRequestId(const ServiceRequestId &) = default;
};

/// Service request, with a request ID and some content.
struct ServiceRequest
{
  /// Request ID.
  ServiceRequestId id;
  /// Content of the request.
  std::string content;
  /// Constructor.
  ServiceRequest(
    const SequenceNumber sequence_number_,
    const Gid & client_gid_,
    const std::string & content_)
  : id(sequence_number_, client_gid_),
    content(content_)
  {}
  /// Copy constructor.
  ServiceRequest(const ServiceRequest &) = default;
};

}  // namespace email

#endif  // EMAIL__SERVICE_REQUEST_HPP_
