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

#include <gtest/gtest.h>

#include <string>

#include "email/gid.hpp"
#include "email/message_info.hpp"
#include "email/timestamp.hpp"

TEST(TestMessageInfo, init) {
  auto ts_source = email::Timestamp::now();
  auto ts_received = email::Timestamp::now();
  auto pub_gid = email::Gid::new_gid();
  auto msg_info = email::MessageInfo(ts_source, ts_received, pub_gid);
  EXPECT_EQ(ts_source.nanoseconds(), msg_info.source_timestamp().nanoseconds());
  EXPECT_EQ(ts_received.nanoseconds(), msg_info.received_timestamp().nanoseconds());
  EXPECT_EQ(pub_gid.value(), msg_info.publisher_gid().value());
}

TEST(TestMessageInfo, string) {
  EXPECT_NO_THROW(
    email::MessageInfo::from_headers(
  {
    {email::MessageInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::MessageInfo::HEADER_PUBLISHER_GID, "456"}
  }));

  EXPECT_DEATH(email::MessageInfo::from_headers({}), "");
  EXPECT_DEATH(
    email::MessageInfo::from_headers({{email::MessageInfo::HEADER_SOURCE_TIMESTAMP, "123"}}), "");
  EXPECT_DEATH(
    email::MessageInfo::from_headers(
  {
    {email::MessageInfo::HEADER_SOURCE_TIMESTAMP, "abc"},
    {email::MessageInfo::HEADER_PUBLISHER_GID, "123"}
  }),
    "");
  EXPECT_DEATH(
    email::MessageInfo::from_headers(
  {
    {email::MessageInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::MessageInfo::HEADER_PUBLISHER_GID, "abc"}
  }),
    "");
}
