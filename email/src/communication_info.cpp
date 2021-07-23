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
#include <string>

#include "email/communication_info.hpp"
#include "email/email/response_utils.hpp"
#include "email/gid.hpp"
#include "email/message_info.hpp"
#include "email/timestamp.hpp"

namespace email
{

CommunicationInfo::CommunicationInfo(
  const Timestamp & source_timestamp,
  const Timestamp & received_timestamp,
  const Gid & source_gid)
: source_timestamp_(source_timestamp),
  received_timestamp_(received_timestamp),
  source_gid_(source_gid)
{}

CommunicationInfo::~CommunicationInfo() {}

const Timestamp &
CommunicationInfo::source_timestamp() const
{
  return source_timestamp_;
}

const Timestamp &
CommunicationInfo::received_timestamp() const
{
  return received_timestamp_;
}

const Gid &
CommunicationInfo::source_gid() const
{
  return source_gid_;
}

CommunicationInfo
CommunicationInfo::from_headers(
  const EmailHeaders & headers,
  const std::string & source_gid_header)
{
  auto source_ts_opt = utils::response::get_header_value(
    CommunicationInfo::HEADER_SOURCE_TIMESTAMP, headers);
  auto source_gid_opt = utils::response::get_header_value(source_gid_header, headers);
  // TODO(christophebedard) handle missing header
  assert(source_ts_opt.has_value());
  assert(source_gid_opt.has_value());
  const Timestamp source_timestamp = Timestamp::from_string(source_ts_opt.value());
  const Timestamp received_timestamp = Timestamp::now();
  const Gid source_gid = Gid::from_string(source_gid_opt.value());
  return CommunicationInfo(source_timestamp, received_timestamp, source_gid);
}

}  // namespace email
