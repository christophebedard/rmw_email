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

#include <optional> // NOLINT cpplint mistakes <optional> for a C system header
#include <string>
#include <vector>

#include "email/payload_utils.hpp"
// #include "email/utils.hpp"

TEST(TestUtils, join_list) {
  const std::vector<std::string> vect_empty = {};
  EXPECT_EQ("", email::utils::PayloadUtils::join_list(vect_empty));

  const std::vector<std::string> vect_single = {"myelement"};
  EXPECT_EQ("myelement", email::utils::PayloadUtils::join_list(vect_single));

  const std::vector<std::string> vect_two = {"myelement", "asecondelement@email.com"};
  EXPECT_EQ(
    "myelement, asecondelement@email.com",
    email::utils::PayloadUtils::join_list(vect_two));

  const std::vector<std::string> vect_three = {
    "myelement", "asecondelement@email.com", "athird@one.com"};
  EXPECT_EQ(
    "myelement, asecondelement@email.com, athird@one.com",
    email::utils::PayloadUtils::join_list(vect_three));
}

TEST(TestUtils, build_payload) {
  // Check handling of multiple recipients
  std::string payload_one_recipient = \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  const struct email::EmailRecipients recipients_one = {{"my@email.com"}, {}, {}};
  const struct email::EmailContent content_one_line = {
    {"this is my awesome subject"}, {"this is the email's body"}};
  EXPECT_EQ(
    payload_one_recipient,
    email::utils::PayloadUtils::build_payload(recipients_one, content_one_line));

  std::string payload_multiple_recipients = \
    "To: my@email.com, another@email.com\r\n" \
    "Cc: onecc@email.ca\r\n" \
    "Bcc: first@email.ca, second@email.net, third@email.de\r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body\r\n";
  const struct email::EmailRecipients recipients_multiple = {
    {"my@email.com", "another@email.com"},
    {"onecc@email.ca"},
    {"first@email.ca", "second@email.net", "third@email.de"}};
  EXPECT_EQ(
    payload_multiple_recipients,
    email::utils::PayloadUtils::build_payload(recipients_multiple, content_one_line));

  // Check that a subject with a newline gets cut
  const struct email::EmailContent content_multiple_lines = {
    {"this is my awesome subject that stops here\nor not!"},
    {"this is the email's body\non multiple lines!"}};
  std::string payload_multiple_recipients_newlines = \
    "To: my@email.com, another@email.com\r\n" \
    "Cc: onecc@email.ca\r\n" \
    "Bcc: first@email.ca, second@email.net, third@email.de\r\n" \
    "Subject: this is my awesome subject that stops here\r\n\r\n" \
    "this is the email's body\non multiple lines!\r\n";
  EXPECT_EQ(
    payload_multiple_recipients_newlines,
    email::utils::PayloadUtils::build_payload(recipients_multiple, content_multiple_lines));
}

TEST(TestUtils, cut_string_if_newline) {
  std::string no_newline = "this is a string without any newline";
  EXPECT_EQ(no_newline, email::utils::PayloadUtils::cut_string_if_newline(no_newline));

  EXPECT_STREQ(
    "this is the first line",
    email::utils::PayloadUtils::cut_string_if_newline(
      "this is the first line\nthis is the second one").c_str());
  EXPECT_STREQ(
    "this is the first line...",
    email::utils::PayloadUtils::cut_string_if_newline(
      "this is the first line...\r\nthis is the second one\nthis is a third one!").c_str());
  EXPECT_STREQ(
    "this is the first line!?!?!?!?!",
    email::utils::PayloadUtils::cut_string_if_newline(
      "this is the first line!?!?!?!?!\r<--not sure this would happen, but\n\rwhy not").c_str());
}
