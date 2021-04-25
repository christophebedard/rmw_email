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
#include <vector>

#include "email/utils.hpp"

TEST(TestUtils, string_format) {
  EXPECT_STREQ("answer is: 42!", email::utils::string_format("answer is: %d!", 42).c_str());
}

TEST(TestUtils, get_env_var) {
  EXPECT_STREQ("", email::utils::get_env_var("SHOULDNT_EXIST").c_str());
  // See CMakeLists.txt for declaration of this env var
  EXPECT_STREQ("value42", email::utils::get_env_var("EMAIL_TEST_UTILS_TEST_ENV_VAR").c_str());
}

TEST(TestUtils, get_env_var_or_default) {
  EXPECT_STREQ(
    "defaultvalue",
    email::utils::get_env_var_or_default("SHOULDNT_EXIST", "defaultvalue").c_str());
  // See CMakeLists.txt for declaration of this env var
  EXPECT_STREQ(
    "value42",
    email::utils::get_env_var_or_default("EMAIL_TEST_UTILS_TEST_ENV_VAR", "defaultvalue").c_str());
}

TEST(TestUtils, read_file) {
  EXPECT_FALSE(email::utils::read_file("doesntexist.txt").has_value());

  auto filepath = email::utils::get_env_var("EMAIL_TEST_UTILS_FILE");
  ASSERT_FALSE(filepath.empty());
  auto file_content = email::utils::read_file(filepath);
  ASSERT_TRUE(file_content.has_value());
  EXPECT_FALSE(file_content.value().empty());
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

TEST(TestUtils, full_url) {
  EXPECT_STREQ("https://google.com:42/", email::utils::full_url("https", "google.com", 42).c_str());
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
