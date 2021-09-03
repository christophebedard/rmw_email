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

#include <optional> // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/email/payload_utils.hpp"
#include "email/email/response_utils.hpp"

TEST(TestResponseUtils, get_nextuid_from_response) {
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

TEST(TestResponseUtils, get_email_data_from_response) {
  std::optional<email::EmailData> data_opt;
  data_opt = email::utils::response::get_email_data_from_response("");
  EXPECT_FALSE(data_opt.has_value());

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
    "this is the email's body";
  data_opt = email::utils::response::get_email_data_from_response(response);
  ASSERT_TRUE(data_opt.has_value());
  email::EmailData data = data_opt.value();
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

  // Missing subject/body
  const std::string response_missing_subject = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject!?!?: this is my awesome subject\r\n\r\n" \
    "this is the email's body";
  data_opt = email::utils::response::get_email_data_from_response(response_missing_subject);
  EXPECT_FALSE(data_opt.has_value());
  const std::string response_missing_body = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n";
  data_opt = email::utils::response::get_email_data_from_response(response_missing_body);
  EXPECT_FALSE(data_opt.has_value());

  // Missing recipients
  const std::string response_missing_to = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body";
  data_opt = email::utils::response::get_email_data_from_response(response_missing_to);
  EXPECT_FALSE(data_opt.has_value());
  const std::string response_missing_cc = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body";
  data_opt = email::utils::response::get_email_data_from_response(response_missing_cc);
  EXPECT_FALSE(data_opt.has_value());
  const std::string response_missing_bcc = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body";
  data_opt = email::utils::response::get_email_data_from_response(response_missing_bcc);
  EXPECT_FALSE(data_opt.has_value());
  const std::string response_missing_all_recipients = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the email's body";
  data_opt = email::utils::response::get_email_data_from_response(response_missing_all_recipients);
  EXPECT_FALSE(data_opt.has_value());

  // Multi-line body
  const std::string response_multiline_body = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the\r\n" \
    " email's \r\n" \
    "body";
  data_opt = email::utils::response::get_email_data_from_response(response_multiline_body);
  ASSERT_TRUE(data_opt.has_value());
  data = data_opt.value();
  EXPECT_EQ(data.content.subject, "this is my awesome subject");
  EXPECT_EQ(data.content.body, "this is the\r\n email's \r\nbody");

  // Multi-line body without CR
  // (although RFC 5322 says that CR & LF should always go together as CRLF)
  const std::string response_multiline_body_nocr = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the\n" \
    " email's \n" \
    "body";
  data_opt = email::utils::response::get_email_data_from_response(response_multiline_body_nocr);
  ASSERT_TRUE(data_opt.has_value());
  data = data_opt.value();
  EXPECT_EQ(data.content.subject, "this is my awesome subject");
  EXPECT_EQ(data.content.body, "this is the\n email's \nbody");

  // Multi-line body with trailing newline
  const std::string response_multiline_body_trailing_crlf = \
    "Message-ID: <some.id@mx.google.com>\r\n" \
    "Date: Sat, 17 Oct 2020 11:06:37 -0700 (PDT)\r\n" \
    "From: some@email.com\r\n" \
    "Sequence-ID: 123\r\n" \
    "In-Reply-To: \r\nReferences: \r\n" \
    "To: my@email.com\r\n" \
    "Cc: \r\n" \
    "Bcc: \r\n" \
    "Subject: this is my awesome subject\r\n\r\n" \
    "this is the\r\n" \
    " email's \r\n" \
    "body\r\n";
  data_opt = email::utils::response::get_email_data_from_response(
    response_multiline_body_trailing_crlf);
  ASSERT_TRUE(data_opt.has_value());
  data = data_opt.value();
  EXPECT_EQ(data.content.subject, "this is my awesome subject");
  EXPECT_EQ(data.content.body, "this is the\r\n email's \r\nbody\r\n");
}

TEST(TestResponseUtils, payload_to_response) {
  std::string payload;
  std::optional<struct email::EmailContent> content;
  email::EmailHeaders headers;
  email::EmailHeaders::iterator header_find;

  // The email payload string isn't exactly the same as the received response string, but it
  // should be close enough to simulate some kind of end-to-end test (payload building and then
  // response parsing) for some elements of the response.

  // Typical use-case
  payload = email::utils::payload::build_payload(
    {"my@email.com"},
    {},
    {},
    {{"this is my awesome subject"}, {"the \nawesome\nemail \nbody"}});
  headers = email::utils::response::get_email_headers_from_response(payload);
  content = email::utils::response::get_email_content_from_response(payload, headers);
  ASSERT_TRUE(content.has_value());
  EXPECT_EQ(content.value().subject, "this is my awesome subject");
  EXPECT_EQ(content.value().body, "the \nawesome\nemail \nbody");
  header_find = headers.find("To");
  ASSERT_NE(header_find, headers.end());
  EXPECT_EQ(header_find->first, "To");
  EXPECT_EQ(header_find->second, "my@email.com");

  // Single line
  payload = email::utils::payload::build_payload(
    {"my@email.com"},
    {},
    {},
    {{"this is my awesome subject"}, {"the body"}});
  headers = email::utils::response::get_email_headers_from_response(payload);
  content = email::utils::response::get_email_content_from_response(payload, headers);
  ASSERT_TRUE(content.has_value());
  EXPECT_EQ(content.value().subject, "this is my awesome subject");
  EXPECT_EQ(content.value().body, "the body");

  // Trailing newlines
  payload = email::utils::payload::build_payload(
    {"my@email.com"},
    {},
    {},
    {{"this is my awesome subject"}, {"the body\n\n"}});
  headers = email::utils::response::get_email_headers_from_response(payload);
  content = email::utils::response::get_email_content_from_response(payload, headers);
  ASSERT_TRUE(content.has_value());
  EXPECT_EQ(content.value().subject, "this is my awesome subject");
  EXPECT_EQ(content.value().body, "the body\n\n");
}

TEST(TestResponseUtils, get_header_value) {
  auto value_opt_fail = email::utils::response::get_header_value("doesntexist", {});
  EXPECT_FALSE(value_opt_fail.has_value());

  auto value_opt = email::utils::response::get_header_value(
    "headername",
    {{"someotherheader", "somevalue"}, {"headername", "headervalue"}});
  ASSERT_TRUE(value_opt.has_value());
  EXPECT_STREQ("headervalue", value_opt.value().c_str());
}
