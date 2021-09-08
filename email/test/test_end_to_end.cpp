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

#include <fstream>
#include <memory>
#include <set>
#include <string>

#include "email/context.hpp"
#include "email/email.hpp"
#include "rcpputils/filesystem_helper.hpp"
#include "rcutils/env.h"

class TestEndToEnd : public ::testing::Test
{
public:
  void SetUp()
  {
    config_file =
      rcpputils::fs::temp_directory_path() / "TestEndToEnd.email.yml";
    ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", config_file.string().c_str()));
    std::ofstream config_file_stream;
    config_file_stream = std::ofstream(config_file.string().c_str());
    config_file_stream <<
      R"(
email:
  user:
    url-smtp: some.url
    url-imap: some.other.url
    username: my@email.ca
    password: tinkywinky
  recipients:
    to: to@email.com
  polling-period:
  intraprocess: true
)";
    config_file_stream.close();

    email::init();
  }

  void TearDown()
  {
    EXPECT_TRUE(email::shutdown());

    EXPECT_TRUE(rcpputils::fs::remove(config_file));
    ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", NULL));
  }

  rcpputils::fs::path config_file;
};

TEST_F(TestEndToEnd, intraprocess_init) {
  EXPECT_THROW(email::init(), email::ContextAlreadyInitializedError);

  EXPECT_TRUE(email::get_global_context()->get_options());
  EXPECT_TRUE(email::get_global_context()->get_receiver());
  EXPECT_TRUE(email::get_global_context()->get_sender());
  EXPECT_TRUE(email::get_global_context()->get_polling_manager());
  EXPECT_TRUE(email::get_global_context()->get_subscription_handler());
  EXPECT_TRUE(email::get_global_context()->get_service_handler());
}

TEST_F(TestEndToEnd, intraprocess_pub_sub) {
  email::Publisher pub1("/my_topic");
  email::Publisher pub2("/other_topic");
  email::Subscription sub1("/my_topic");
  email::Subscription sub2("/other_topic");

  EXPECT_STREQ(pub1.get_topic_name().c_str(), "/my_topic");
  EXPECT_STREQ(pub2.get_topic_name().c_str(), "/other_topic");
  EXPECT_STREQ(sub1.get_topic_name().c_str(), "/my_topic");
  EXPECT_STREQ(sub2.get_topic_name().c_str(), "/other_topic");

  std::set<email::GidValue> gids;
  gids.insert(pub1.get_gid().value());
  gids.insert(pub2.get_gid().value());
  gids.insert(sub1.get_gid().value());
  gids.insert(sub2.get_gid().value());
  EXPECT_EQ(4UL, gids.size());

  EXPECT_FALSE(sub1.has_message());
  EXPECT_FALSE(sub2.has_message());
  EXPECT_FALSE(sub1.get_message_with_info().has_value());
  EXPECT_FALSE(sub2.get_message_with_info().has_value());
  EXPECT_FALSE(sub1.get_message().has_value());
  EXPECT_FALSE(sub2.get_message().has_value());

  pub1.publish("some message");
  pub2.publish("some other message");

  email::WaitSet waitset;
  waitset.add_subscription(&sub1);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();
  waitset.add_subscription(&sub2);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();

  ASSERT_TRUE(sub1.has_message());
  ASSERT_TRUE(sub2.has_message());
  auto msg_with_info_1_opt = sub1.get_message_with_info();
  auto msg_with_info_2_opt = sub2.get_message_with_info();
  ASSERT_TRUE(msg_with_info_1_opt.has_value());
  ASSERT_TRUE(msg_with_info_2_opt.has_value());
  auto msg_with_info_1 = msg_with_info_1_opt.value();
  auto msg_with_info_2 = msg_with_info_2_opt.value();
  auto msg_1 = msg_with_info_1.first;
  auto msg_2 = msg_with_info_2.first;
  auto info_1 = msg_with_info_1.second;
  auto info_2 = msg_with_info_2.second;

  EXPECT_STREQ(msg_1.c_str(), "some message");
  EXPECT_STREQ(msg_2.c_str(), "some other message");
  EXPECT_EQ(pub1.get_gid().value(), info_1.publisher_gid().value());
  EXPECT_EQ(pub2.get_gid().value(), info_2.publisher_gid().value());
  EXPECT_LT(info_1.source_timestamp().nanoseconds(), info_2.source_timestamp().nanoseconds());
  EXPECT_LT(info_1.source_timestamp().nanoseconds(), info_1.received_timestamp().nanoseconds());
  EXPECT_LT(info_2.source_timestamp().nanoseconds(), info_2.received_timestamp().nanoseconds());

  pub1.publish("eh-oh!");
  waitset.add_subscription(&sub1);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();
  ASSERT_TRUE(sub1.has_message());
  auto msg_3_opt = sub1.get_message();
  ASSERT_TRUE(msg_3_opt.has_value());
  auto msg_3 = msg_3_opt.value();
  ASSERT_STREQ(msg_3.c_str(), "eh-oh!");
}

TEST_F(TestEndToEnd, intraprocess_service) {
  email::ServiceClient client1("/my_service");
  email::ServiceClient client2("/other_service");
  email::ServiceServer server1("/my_service");
  email::ServiceServer server2("/other_service");

  EXPECT_STREQ(client1.get_service_name().c_str(), "/my_service");
  EXPECT_STREQ(client2.get_service_name().c_str(), "/other_service");
  EXPECT_STREQ(server1.get_service_name().c_str(), "/my_service");
  EXPECT_STREQ(server2.get_service_name().c_str(), "/other_service");

  std::set<email::GidValue> gids;
  gids.insert(client1.get_gid().value());
  gids.insert(client2.get_gid().value());
  gids.insert(server1.get_gid().value());
  gids.insert(server2.get_gid().value());
  EXPECT_EQ(4UL, gids.size());

  EXPECT_FALSE(client1.has_response());
  EXPECT_FALSE(client2.has_response());
  EXPECT_FALSE(client1.get_response_with_info().has_value());
  EXPECT_FALSE(client2.get_response_with_info().has_value());
  EXPECT_FALSE(server1.has_request());
  EXPECT_FALSE(server2.has_request());
  EXPECT_FALSE(server1.get_request_with_info().has_value());
  EXPECT_FALSE(server2.get_request_with_info().has_value());
  EXPECT_FALSE(server1.get_request().has_value());
  EXPECT_FALSE(server2.get_request().has_value());

  email::SequenceNumber seq1 = client1.send_request("a super request");
  email::SequenceNumber seq2 = client2.send_request("an awesome request");
  EXPECT_NE(seq1, seq2);

  EXPECT_FALSE(client1.get_response(seq1).has_value());
  EXPECT_FALSE(client2.get_response(seq2).has_value());

  email::WaitSet waitset;
  waitset.add_server(&server1);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();
  waitset.add_server(&server2);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();

  ASSERT_TRUE(server1.has_request());
  ASSERT_TRUE(server2.has_request());
  auto req_with_info_1_opt = server1.get_request_with_info();
  auto req_with_info_2_opt = server2.get_request_with_info();
  ASSERT_TRUE(req_with_info_1_opt.has_value());
  ASSERT_TRUE(req_with_info_2_opt.has_value());
  auto req_with_info_1 = req_with_info_1_opt.value();
  auto req_with_info_2 = req_with_info_2_opt.value();
  auto req_1 = req_with_info_1.first;
  auto req_2 = req_with_info_2.first;
  auto req_info_1 = req_with_info_1.second;
  auto req_info_2 = req_with_info_2.second;

  EXPECT_STREQ(req_1.content.c_str(), "a super request");
  EXPECT_STREQ(req_2.content.c_str(), "an awesome request");
  EXPECT_EQ(seq1, req_1.id.sequence_number);
  EXPECT_EQ(seq1, req_info_1.sequence_number());
  EXPECT_EQ(seq2, req_2.id.sequence_number);
  EXPECT_EQ(seq2, req_info_2.sequence_number());
  EXPECT_EQ(client1.get_gid().value(), req_info_1.client_gid().value());
  EXPECT_EQ(client1.get_gid().value(), req_1.id.client_gid.value());
  EXPECT_EQ(client2.get_gid().value(), req_info_2.client_gid().value());
  EXPECT_EQ(client2.get_gid().value(), req_2.id.client_gid.value());
  EXPECT_LT(
    req_info_1.source_timestamp().nanoseconds(),
    req_info_2.source_timestamp().nanoseconds());
  EXPECT_LT(
    req_info_1.source_timestamp().nanoseconds(),
    req_info_1.received_timestamp().nanoseconds());
  EXPECT_LT(
    req_info_2.source_timestamp().nanoseconds(),
    req_info_2.received_timestamp().nanoseconds());

  server1.send_response(req_1.id, "a super response");
  server2.send_response(req_2.id, "an awesome response");

  waitset.add_client(&client1);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();
  waitset.add_client(&client2);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();

  ASSERT_TRUE(client1.has_response());
  ASSERT_TRUE(client2.has_response());
  auto res_with_info_1_opt = client1.get_response_with_info();
  auto res_with_info_2_opt = client2.get_response_with_info();
  ASSERT_TRUE(res_with_info_1_opt.has_value());
  ASSERT_TRUE(res_with_info_2_opt.has_value());
  auto res_with_info_1 = res_with_info_1_opt.value();
  auto res_with_info_2 = res_with_info_2_opt.value();
  auto res_1 = res_with_info_1.first;
  auto res_2 = res_with_info_2.first;
  auto res_info_1 = res_with_info_1.second;
  auto res_info_2 = res_with_info_2.second;

  EXPECT_STREQ(res_1.c_str(), "a super response");
  EXPECT_STREQ(res_2.c_str(), "an awesome response");
  EXPECT_EQ(seq1, res_info_1.sequence_number());
  EXPECT_EQ(seq2, res_info_2.sequence_number());
  EXPECT_EQ(client1.get_gid().value(), res_info_1.client_gid().value());
  EXPECT_EQ(client2.get_gid().value(), res_info_2.client_gid().value());
  EXPECT_LT(
    res_info_1.source_timestamp().nanoseconds(),
    res_info_2.source_timestamp().nanoseconds());
  EXPECT_LT(
    res_info_1.source_timestamp().nanoseconds(),
    res_info_1.received_timestamp().nanoseconds());
  EXPECT_LT(
    res_info_2.source_timestamp().nanoseconds(),
    res_info_2.received_timestamp().nanoseconds());

  email::SequenceNumber seq3 = client1.send_request("tubbytoast, please");
  EXPECT_NE(seq1, seq3);
  waitset.add_server(&server1);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();
  ASSERT_TRUE(server1.has_request());
  auto req_3_opt = server1.get_request();
  ASSERT_TRUE(req_3_opt.has_value());
  auto req_3 = req_3_opt.value();
  EXPECT_STREQ(req_3.content.c_str(), "tubbytoast, please");
  EXPECT_EQ(seq3, req_3.id.sequence_number);
  EXPECT_EQ(client1.get_gid().value(), req_3.id.client_gid.value());
  server1.send_response(req_3.id, "your tubbytoast");
  waitset.add_client(&client1);
  EXPECT_FALSE(waitset.wait());
  waitset.clear();
  ASSERT_TRUE(client1.has_response());
  EXPECT_FALSE(client1.get_response(seq1).has_value());
  EXPECT_FALSE(client1.get_response(seq2).has_value());
  auto res_3_opt = client1.get_response(seq3);
  ASSERT_TRUE(res_3_opt.has_value());
  auto res_3 = res_3_opt.value();
  EXPECT_STREQ(res_3.c_str(), "your tubbytoast");
}

TEST_F(TestEndToEnd, intraprocess_wait) {
  auto pub = std::make_shared<email::Publisher>("/my_topic");
  auto sub = std::make_shared<email::Subscription>("/my_topic");
  auto client = std::make_shared<email::ServiceClient>("/my_service");
  auto server = std::make_shared<email::ServiceServer>("/my_service");

  pub->publish("eh-oh!");
  pub->publish("oh no!");
  auto seq1 = client->send_request("tubbycustard, please");
  auto seq2 = client->send_request("more tubbycustard, please");

  auto msg = email::wait_for_message(sub);
  auto msg_with_info = email::wait_for_message_with_info(sub);
  auto req = email::wait_for_request(server);
  auto req_with_info = email::wait_for_request_with_info(server);

  EXPECT_STREQ(msg.c_str(), "eh-oh!");
  EXPECT_STREQ(msg_with_info.first.c_str(), "oh no!");
  EXPECT_EQ(req.id.sequence_number, seq1);
  EXPECT_STREQ(req.content.c_str(), "tubbycustard, please");
  EXPECT_EQ(req_with_info.first.id.sequence_number, seq2);
  EXPECT_STREQ(req_with_info.first.content.c_str(), "more tubbycustard, please");

  server->send_response(req.id, "your tubbytoast");
  server->send_response(req_with_info.first.id, "your tubbycustard");

  auto res = email::wait_for_response(seq1, client);
  auto res_with_info = email::wait_for_response_with_info(seq2, client);

  EXPECT_STREQ(res.c_str(), "your tubbytoast");
  EXPECT_STREQ(res_with_info.first.c_str(), "your tubbycustard");
}
