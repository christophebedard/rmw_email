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

#include "email/email/response_utils.hpp"
#include "email/gid.hpp"
#include "email/message_info.hpp"
#include "email/timestamp.hpp"

namespace email
{

MessageInfo::MessageInfo(
  const Timestamp & source_timestamp,
  const Timestamp & received_timestamp,
  const Gid & publisher_gid)
: source_timestamp_(source_timestamp),
  received_timestamp_(received_timestamp),
  publisher_gid_(publisher_gid)
{}

MessageInfo::~MessageInfo() {}

const Timestamp &
MessageInfo::source_timestamp() const
{
  return source_timestamp_;
}

const Timestamp &
MessageInfo::received_timestamp() const
{
  return received_timestamp_;
}

const Gid &
MessageInfo::publisher_gid() const
{
  return publisher_gid_;
}

MessageInfo
MessageInfo::from_headers(const EmailHeaders & headers)
{
  auto source_ts_opt = utils::response::get_header_value(
    MessageInfo::HEADER_SOURCE_TIMESTAMP, headers);
  auto publisher_gid_opt = utils::response::get_header_value(
    MessageInfo::HEADER_PUBLISHER_GID, headers);
  // TODO(christophebedard) handle missing header
  assert(source_ts_opt.has_value());
  assert(publisher_gid_opt.has_value());
  const Timestamp source_timestamp = Timestamp::from_string(source_ts_opt.value());
  const Timestamp received_timestamp = Timestamp::now();
  const Gid publisher_gid = Gid::from_string(publisher_gid_opt.value());
  MessageInfo info(source_timestamp, received_timestamp, publisher_gid);
  return info;
}

}  // namespace email
