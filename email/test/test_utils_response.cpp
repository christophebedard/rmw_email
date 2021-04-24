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
