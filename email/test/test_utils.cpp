// Copyright 2020 Christophe Bedard
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

#include <memory>
#include <optional> // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <vector>

#include "email/email/payload_utils.hpp"
#include "email/email/response_utils.hpp"
#include "email/utils.hpp"

TEST(TestUtils, join_list) {
  const std::vector<std::string> vect_empty = {};
  EXPECT_EQ("", email::utils::payload::join_list(vect_empty));

  const std::vector<std::string> vect_single = {"myelement"};
  EXPECT_EQ("myelement", email::utils::payload::join_list(vect_single));

  const std::vector<std::string> vect_two = {"myelement", "asecondelement@email.com"};
  EXPECT_EQ(
    "myelement, asecondelement@email.com",
    email::utils::payload::join_list(vect_two));

  const std::vector<std::string> vect_three = {
    "myelement", "asecondelement@email.com", "athird@one.com"};
  EXPECT_EQ(
    "myelement, asecondelement@email.com, athird@one.com",
    email::utils::payload::join_list(vect_three));
}

TEST(TestUtils, split_email_list) {
  EXPECT_TRUE(email::utils::split_email_list("").empty());

  const std::string list_single = "my@email.com";
  auto vector_single = email::utils::split_email_list(list_single);
  ASSERT_EQ(1UL, vector_single.size());
  EXPECT_EQ("my@email.com", vector_single[0]);

  auto vector_single_space = email::utils::split_email_list(list_single, true);
  ASSERT_EQ(1UL, vector_single_space.size());
  EXPECT_EQ("my@email.com", vector_single_space[0]);

  const std::string list_multiple_nospace = "my@email.com,another@email.ca,lastone@geemail.com";
  auto vector_multiple_nospace = email::utils::split_email_list(list_multiple_nospace);
  ASSERT_EQ(3UL, vector_multiple_nospace.size());
  EXPECT_EQ("my@email.com", vector_multiple_nospace[0]);
  EXPECT_EQ("another@email.ca", vector_multiple_nospace[1]);
  EXPECT_EQ("lastone@geemail.com", vector_multiple_nospace[2]);

  const std::string list_multiple_space = "my@email.com, another@email.ca, lastone@geemail.com";
  auto vector_multiple_space = email::utils::split_email_list(list_multiple_space, true);
  ASSERT_EQ(3UL, vector_multiple_space.size());
  EXPECT_EQ("my@email.com", vector_multiple_space[0]);
  EXPECT_EQ("another@email.ca", vector_multiple_space[1]);
  EXPECT_EQ("lastone@geemail.com", vector_multiple_space[2]);
}

TEST(TestUtils, optional_stox) {
  auto stoi_opt_fail = email::utils::optional_stoi("abc");
  EXPECT_FALSE(stoi_opt_fail.has_value());
  auto stoul_opt_fail = email::utils::optional_stoul("abc");
  EXPECT_FALSE(stoul_opt_fail.has_value());

  auto stoi_opt = email::utils::optional_stoi("42");
  ASSERT_TRUE(stoi_opt.has_value());
  EXPECT_EQ(42, stoi_opt);
  auto stoul_opt = email::utils::optional_stoul("42");
  ASSERT_TRUE(stoul_opt.has_value());
  EXPECT_EQ(42ul, stoul_opt);
}

TEST(TestUtils, build_payload) {
  // Check handling of multiple recipients
  const std::string payload_one_recipient = \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  email::EmailRecipients::SharedPtrConst recipients_one =
    std::make_shared<const struct email::EmailRecipients>("my@email.com");
  const struct email::EmailContent content_one_line = {
    {"this is my awesome subject"}, {"this is the email's body"}};
  EXPECT_EQ(
    payload_one_recipient,
    email::utils::payload::build_payload(recipients_one, content_one_line));

  const std::string payload_multiple_recipients = \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com, another@email.com\r\n" \
    "Cc: onecc@email.ca\r\n" \
    "Bcc: first@email.ca, second@email.net, third@email.de\r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  email::EmailRecipients::SharedPtrConst recipients_multiple =
    std::make_shared<const struct email::EmailRecipients>(
    std::vector<std::string>{"my@email.com", "another@email.com"},
    std::vector<std::string>{"onecc@email.ca"},
    std::vector<std::string>{"first@email.ca", "second@email.net", "third@email.de"});
  EXPECT_EQ(
    payload_multiple_recipients,
    email::utils::payload::build_payload(recipients_multiple, content_one_line));

  // Check that a subject with a newline gets cut
  const struct email::EmailContent content_multiple_lines = {
    {"this is my awesome subject that stops here\nor not!"},
    {"this is the email's body\non multiple lines!"}};
  const std::string payload_multiple_recipients_newlines = \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com, another@email.com\r\n" \
    "Cc: onecc@email.ca\r\n" \
    "Bcc: first@email.ca, second@email.net, third@email.de\r\n" \
    "Subject: this is my awesome subject that stops here\r\n\r\n" \
    "this is the email's body\non multiple lines!\r\n";
  EXPECT_EQ(
    payload_multiple_recipients_newlines,
    email::utils::payload::build_payload(recipients_multiple, content_multiple_lines));

  // Reply reference
  const std::string payload_reply_ref = \
    "In-Reply-To: thisisaref\r\nReferences: thisisaref\r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  const std::string reply_ref = "thisisaref";
  EXPECT_EQ(
    payload_reply_ref,
    email::utils::payload::build_payload(
      recipients_one,
      content_one_line,
      std::nullopt,
      reply_ref));

  // Additional headers
  const email::EmailHeaders additional_headers = {
    {"key", "value"}, {"anotherKey", "another@value.com"}};
  // Here we have to watch out for the order when testing
  const std::string payload_additional_headers = \
    "anotherKey: another@value.com\r\n" \
    "key: value\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  EXPECT_EQ(
    payload_additional_headers,
    email::utils::payload::build_payload(
      recipients_one,
      content_one_line,
      additional_headers,
      std::nullopt));
}

TEST(TestUtils, cut_string_if_newline) {
  std::string no_newline = "this is a string without any newline";
  EXPECT_EQ(no_newline, email::utils::payload::cut_string_if_newline(no_newline));

  EXPECT_STREQ(
    "this is the first line",
    email::utils::payload::cut_string_if_newline(
      "this is the first line\nthis is the second one").c_str());
  EXPECT_STREQ(
    "this is the first line...",
    email::utils::payload::cut_string_if_newline(
      "this is the first line...\r\nthis is the second one\nthis is a third one!").c_str());
  EXPECT_STREQ(
    "this is the first line!?!?!?!?!",
    email::utils::payload::cut_string_if_newline(
      "this is the first line!?!?!?!?!\r<--not sure this would happen, but\n\rwhy not").c_str());
}

TEST(TestUtils, get_nextuid_from_response) {
  auto nextuid_opt_fail = email::utils::response::get_nextuid_from_response("whatever 42");
  EXPECT_FALSE(nextuid_opt_fail.has_value());

  const std::string response = \
    "Some line\r\n" \
    "another line\r\n" \
    "* OK [UIDNEXT 42] Predicted next UID.\r\n" \
    "a last line";
  auto nextuid_opt = email::utils::response::get_nextuid_from_response(response);
  ASSERT_TRUE(nextuid_opt.has_value());
  auto nextuid = nextuid_opt.value();
  EXPECT_EQ(42, nextuid);
}

TEST(TestUtils, get_email_data_from_response) {
  // Typical use-case with an additional/non-standard header (Sequence-ID)
  const std::string response = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  auto data_opt = email::utils::response::get_email_data_from_response(response);
  ASSERT_TRUE(data_opt.has_value());
  auto data = data_opt.value();
  EXPECT_EQ(data.message_id, "<some.id@mx.google.com>");
  EXPECT_EQ(data.in_reply_to, "");
  EXPECT_EQ(data.from, "some@email.com");
  ASSERT_EQ(data.recipients.to.size(), 1UL);
  EXPECT_EQ(data.recipients.to[0], "my@email.com");
  EXPECT_EQ(data.recipients.cc.size(), 0UL);
  EXPECT_EQ(data.recipients.bcc.size(), 0UL);
  EXPECT_EQ(data.content.subject, "this is my awesome subject");
  EXPECT_EQ(data.content.body, "this is the email's body");
  auto custom_header_find = data.additional_headers.find("Sequence-ID");
  ASSERT_NE(custom_header_find, data.additional_headers.end());
  EXPECT_EQ(custom_header_find->first, "Sequence-ID");
  EXPECT_EQ(custom_header_find->second, "123");
}
