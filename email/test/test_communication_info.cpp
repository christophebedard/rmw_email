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
#include "email/communication_info.hpp"
#include "email/message_info.hpp"
#include "email/service_info.hpp"
#include "email/service_handler.hpp"
#include "email/timestamp.hpp"

TEST(TestMessageInfo, init)
{
  auto ts_source = email::Timestamp::now();
  auto ts_received = email::Timestamp::now();
  auto pub_gid = email::Gid::new_gid();
  auto msg_info = email::MessageInfo(ts_source, ts_received, pub_gid);
  EXPECT_EQ(ts_source, msg_info.source_timestamp());
  EXPECT_EQ(ts_received, msg_info.received_timestamp());
  EXPECT_EQ(pub_gid, msg_info.publisher_gid());
}

TEST(TestMessageInfo, from_headers)
{
  auto info = email::MessageInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::MessageInfo::HEADER_PUBLISHER_GID, "456"}
  });
  ASSERT_TRUE(info.has_value());
  EXPECT_EQ(info.value().source_timestamp().nanoseconds(), 123);
  EXPECT_EQ(info.value().publisher_gid().value(), 456u);

  EXPECT_FALSE(email::MessageInfo::from_headers({}).has_value());
  EXPECT_FALSE(
    email::MessageInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "123"}
  }).has_value());
  EXPECT_FALSE(
    email::MessageInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "abc"},
    {email::MessageInfo::HEADER_PUBLISHER_GID, "123"}
  }).has_value());
  EXPECT_FALSE(
    email::MessageInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::MessageInfo::HEADER_PUBLISHER_GID, "abc"}
  }).has_value());
}

TEST(TestServiceInfo, init)
{
  auto ts_source = email::Timestamp::now();
  auto ts_received = email::Timestamp::now();
  auto client_gid = email::Gid::new_gid();
  auto sequence_number = 42u;
  auto srv_info = email::ServiceInfo(ts_source, ts_received, client_gid, sequence_number);
  EXPECT_EQ(ts_source, srv_info.source_timestamp());
  EXPECT_EQ(ts_received, srv_info.received_timestamp());
  EXPECT_EQ(client_gid, srv_info.client_gid());
  EXPECT_EQ(sequence_number, srv_info.sequence_number());
}

TEST(TestServiceInfo, from_headers)
{
  auto info = email::ServiceInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::ServiceInfo::HEADER_CLIENT_GID, "456"},
    {email::ServiceHandler::HEADER_SEQUENCE_NUMBER, "42"}
  });
  ASSERT_TRUE(info.has_value());
  EXPECT_EQ(info.value().source_timestamp().nanoseconds(), 123);
  EXPECT_EQ(info.value().client_gid().value(), 456u);
  EXPECT_EQ(info.value().sequence_number(), 42u);

  EXPECT_FALSE(email::ServiceInfo::from_headers({}).has_value());
  EXPECT_FALSE(
    email::ServiceInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::ServiceInfo::HEADER_CLIENT_GID, "456"}
  }).has_value());
  EXPECT_FALSE(
    email::ServiceInfo::from_headers(
  {
    {email::CommunicationInfo::HEADER_SOURCE_TIMESTAMP, "123"},
    {email::ServiceInfo::HEADER_CLIENT_GID, "456"},
    {email::ServiceHandler::HEADER_SEQUENCE_NUMBER, "abc"}
  }).has_value());
}
