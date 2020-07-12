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
  EXPECT_EQ(1UL, vector_single.size());
  EXPECT_EQ("my@email.com", vector_single[0]);

  auto vector_single_space = email::utils::split_email_list(list_single, true);
  EXPECT_EQ(1UL, vector_single_space.size());
  EXPECT_EQ("my@email.com", vector_single_space[0]);

  const std::string list_multiple_nospace = "my@email.com,another@email.ca,lastone@geemail.com";
  auto vector_multiple_nospace = email::utils::split_email_list(list_multiple_nospace);
  EXPECT_EQ(3UL, vector_multiple_nospace.size());
  EXPECT_EQ("my@email.com", vector_multiple_nospace[0]);
  EXPECT_EQ("another@email.ca", vector_multiple_nospace[1]);
  EXPECT_EQ("lastone@geemail.com", vector_multiple_nospace[2]);

  const std::string list_multiple_space = "my@email.com, another@email.ca, lastone@geemail.com";
  auto vector_multiple_space = email::utils::split_email_list(list_multiple_space, true);
  EXPECT_EQ(3UL, vector_multiple_space.size());
  EXPECT_EQ("my@email.com", vector_multiple_space[0]);
  EXPECT_EQ("another@email.ca", vector_multiple_space[1]);
  EXPECT_EQ("lastone@geemail.com", vector_multiple_space[2]);
}

TEST(TestUtils, build_payload) {
  // Check handling of multiple recipients
  std::string payload_one_recipient = \
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

  std::string payload_multiple_recipients = \
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
  std::string payload_multiple_recipients_newlines = \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com, another@email.com\r\n" \
    "Cc: onecc@email.ca\r\n" \
    "Bcc: first@email.ca, second@email.net, third@email.de\r\n" \
    "Subject: this is my awesome subject that stops here\r\n\r\n" \
    "this is the email's body\non multiple lines!\r\n";
  EXPECT_EQ(
    payload_multiple_recipients_newlines,
    email::utils::payload::build_payload(recipients_multiple, content_multiple_lines));
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
