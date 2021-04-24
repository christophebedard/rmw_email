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

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "email/email/payload_utils.hpp"

TEST(TestPayloadUtils, join_list) {
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

TEST(TestPayloadUtils, build_payload) {
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

TEST(TestPayloadUtils, cut_string_if_newline) {
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
