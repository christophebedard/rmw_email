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

#include <cassert>

#include "email/communication_info.hpp"
#include "email/email/response_utils.hpp"
#include "email/gid.hpp"
#include "email/service_handler.hpp"
#include "email/service_info.hpp"
#include "email/timestamp.hpp"
#include "email/utils.hpp"

namespace email
{

ServiceInfo::ServiceInfo(
  const Timestamp & source_timestamp,
  const Timestamp & received_timestamp,
  const Gid & client_gid,
  const uint32_t sequence_number)
: base_info_(source_timestamp, received_timestamp, client_gid),
  sequence_number_(sequence_number)
{}

ServiceInfo::~ServiceInfo() {}

const Timestamp &
ServiceInfo::source_timestamp() const
{
  return base_info_.source_timestamp();
}

const Timestamp &
ServiceInfo::received_timestamp() const
{
  return base_info_.received_timestamp();
}

const Gid &
ServiceInfo::client_gid() const
{
  return base_info_.source_gid();
}

uint32_t
ServiceInfo::sequence_number() const
{
  return sequence_number_;
}

ServiceInfo
ServiceInfo::from_headers(const EmailHeaders & headers)
{
  const CommunicationInfo base_info = CommunicationInfo::from_headers(
    headers,
    ServiceInfo::HEADER_CLIENT_GID);
  auto sequence_number_str_opt = utils::response::get_header_value(
    ServiceHandler::HEADER_SEQUENCE_NUMBER,
    headers);
  // TODO(christophebedard) handle missing header or bad conversion
  assert(sequence_number_str_opt.has_value());
  auto sequence_number_opt = utils::optional_stoul(sequence_number_str_opt.value());
  assert(sequence_number_opt.has_value());
  const uint32_t sequence_number = sequence_number_opt.value();
  return ServiceInfo(
    base_info.source_timestamp(),
    base_info.received_timestamp(),
    base_info.source_gid(),
    sequence_number);
}

}  // namespace email
