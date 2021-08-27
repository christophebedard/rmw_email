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

#include <chrono>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "email/log.hpp"
#include "email/options.hpp"
#include "rcpputils/filesystem_helper.hpp"
#include "rcutils/env.h"
#include "yaml-cpp/yaml.h"

class TestOptions : public ::testing::Test
{
public:
  void SetUp()
  {
    email::log::init(email::log::Level::debug);
  }

  void TearDown()
  {
    email::log::shutdown();
  }
};

TEST_F(TestOptions, yaml_to_options) {
  // Empty node
  YAML::Node node;
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());

  // Empty email node
  node["email"] = YAML::Node();
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());

  // User node, but missing values
  node["email"]["user"] = YAML::Node();
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());
  node["email"]["user"]["url-smtp"] = "some.url";
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());
  node["email"]["user"]["url-imap"] = "some.other.url";
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());
  node["email"]["user"]["username"] = "my@email.ca";
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());

  // Missing recipients node
  node["email"]["user"]["password"] = "tinkywinky";
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());

  // Empty recipients node
  node["email"]["recipients"] = YAML::Node();
  EXPECT_FALSE(email::Options::yaml_to_options(node).has_value());

  std::optional<std::shared_ptr<email::Options>> options;

  // With required 'to' value
  node["email"]["recipients"]["to"] = "to@email.com";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());

  EXPECT_STREQ("some.url", options.value()->get_user_info()->host_smtp.c_str());
  EXPECT_STREQ("some.other.url", options.value()->get_user_info()->host_imap.c_str());
  EXPECT_STREQ("my@email.ca", options.value()->get_user_info()->username.c_str());
  EXPECT_STREQ("tinkywinky", options.value()->get_user_info()->password.c_str());
  ASSERT_EQ(1UL, options.value()->get_recipients()->to.size());
  EXPECT_STREQ("to@email.com", options.value()->get_recipients()->to[0].c_str());
  EXPECT_EQ(0UL, options.value()->get_recipients()->cc.size());
  EXPECT_EQ(0UL, options.value()->get_recipients()->bcc.size());
  EXPECT_EQ(false, options.value()->curl_verbose());
  EXPECT_FALSE(options.value()->polling_period().has_value());

  // Optional values
  node["email"]["recipients"]["cc"] = "cc@email.com";
  node["email"]["recipients"]["bcc"] = "bcc@email.com";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  ASSERT_EQ(1UL, options.value()->get_recipients()->cc.size());
  ASSERT_EQ(1UL, options.value()->get_recipients()->bcc.size());
  EXPECT_STREQ("cc@email.com", options.value()->get_recipients()->cc[0].c_str());
  EXPECT_STREQ("bcc@email.com", options.value()->get_recipients()->bcc[0].c_str());

  node["email"]["polling-period"] = "1000";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  ASSERT_TRUE(options.value()->polling_period().has_value());
  EXPECT_EQ(std::chrono::nanoseconds(1000), options.value()->polling_period().value());

  // Bad polling period value
  node["email"]["polling-period"] = "laalaa";
  options = email::Options::yaml_to_options(node);
  ASSERT_FALSE(options.has_value());
}

TEST_F(TestOptions, parse_options_file) {
  rcpputils::fs::path file;

  // Exists, but directory
  file = rcpputils::fs::create_temp_directory("TestOptions-parse_options_file-dir-");
  EXPECT_FALSE(email::Options::parse_options_file(file).has_value());
  EXPECT_TRUE(rcpputils::fs::remove(file));

  // File, but doesn't exist
  file = rcpputils::fs::temp_directory_path() / "TestOptions-parse_options_file-not-created";
  EXPECT_FALSE(email::Options::parse_options_file(file).has_value());

  // Bad YAML file
  file = rcpputils::fs::temp_directory_path() / "TestOptions-parse_options_file-created";
  std::ofstream file_stream;

  file_stream = std::ofstream(file.string().c_str());
  file_stream << "DIPSY" << std::endl;
  file_stream.close();
  EXPECT_FALSE(email::Options::parse_options_file(file).has_value());
  EXPECT_TRUE(rcpputils::fs::remove(file));

  file_stream = std::ofstream(file.string().c_str());
  file_stream << "{DIPSY" << std::endl;
  file_stream.close();
  EXPECT_FALSE(email::Options::parse_options_file(file).has_value());
  EXPECT_TRUE(rcpputils::fs::remove(file));
}

TEST_F(TestOptions, parse_options_from_file) {
  // Good file
  rcpputils::fs::path file =
    rcpputils::fs::temp_directory_path() / "TestOptions-parse_options_from_file.email.yml";
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", file.string().c_str()));
  std::ofstream file_stream;
  file_stream = std::ofstream(file.string().c_str());
  file_stream <<
    R"(
email:
  user:
    url-smtp: some.url
    url-imap: some.other.url
    username: my@email.ca
    password: tinkywinky
  recipients:
    to: to@email.com
)";
  file_stream.close();

  std::optional<std::shared_ptr<email::Options>> options;
  options = email::Options::parse_options_from_file();
  ASSERT_TRUE(options.has_value());
  EXPECT_STREQ("some.url", options.value()->get_user_info()->host_smtp.c_str());
  EXPECT_STREQ("some.other.url", options.value()->get_user_info()->host_imap.c_str());
  EXPECT_STREQ("my@email.ca", options.value()->get_user_info()->username.c_str());
  EXPECT_STREQ("tinkywinky", options.value()->get_user_info()->password.c_str());
  ASSERT_EQ(1UL, options.value()->get_recipients()->to.size());
  EXPECT_STREQ("to@email.com", options.value()->get_recipients()->to[0].c_str());

  EXPECT_TRUE(rcpputils::fs::remove(file));
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", NULL));

  // Bad default file
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE_DEFAULT_PATH", file.string().c_str()));

  file_stream = std::ofstream(file.string().c_str());
  file_stream << "{DIPSY" << std::endl;
  file_stream.close();
  options = email::Options::parse_options_from_file();
  EXPECT_FALSE(options.has_value());

  EXPECT_TRUE(rcpputils::fs::remove(file));
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE_DEFAULT_PATH", NULL));
}
