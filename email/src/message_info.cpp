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

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header

#include "email/communication_info.hpp"
#include "email/gid.hpp"
#include "email/message_info.hpp"
#include "email/timestamp.hpp"

namespace email
{

MessageInfo::MessageInfo(
  const Timestamp & source_timestamp,
  const Timestamp & received_timestamp,
  const Gid & publisher_gid)
: base_info_(source_timestamp, received_timestamp, publisher_gid)
{}

MessageInfo::~MessageInfo() {}

const Timestamp &
MessageInfo::source_timestamp() const
{
  return base_info_.source_timestamp();
}

const Timestamp &
MessageInfo::received_timestamp() const
{
  return base_info_.received_timestamp();
}

const Gid &
MessageInfo::publisher_gid() const
{
  return base_info_.source_gid();
}

std::optional<MessageInfo>
MessageInfo::from_headers(const EmailHeaders & headers)
{
  auto base_info_opt = CommunicationInfo::from_headers(
    headers,
    MessageInfo::HEADER_PUBLISHER_GID);
  // The headers could be missing if the type of communication isn't the one we expected,
  // especially the publisher GID header
  if (!base_info_opt) {
    return std::nullopt;
  }
  return MessageInfo(
    base_info_opt.value().source_timestamp(),
    base_info_opt.value().received_timestamp(),
    base_info_opt.value().source_gid());
}

}  // namespace email
