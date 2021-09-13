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

  rcpputils::fs::path tmp{rcpputils::fs::temp_directory_path()};
};

TEST_F(TestOptions, yaml_to_options)
{
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
  std::shared_ptr<email::Options> options_val;

  // With required 'to' value
  node["email"]["recipients"]["to"] = "to@email.com";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();

  EXPECT_STREQ("some.url", options_val->get_user_info().value()->host_smtp.c_str());
  EXPECT_STREQ("some.other.url", options_val->get_user_info().value()->host_imap.c_str());
  EXPECT_STREQ("my@email.ca", options_val->get_user_info().value()->username.c_str());
  EXPECT_STREQ("tinkywinky", options_val->get_user_info().value()->password.c_str());
  ASSERT_EQ(1UL, options_val->get_recipients().value()->to.size());
  EXPECT_STREQ("to@email.com", options_val->get_recipients().value()->to[0].c_str());
  EXPECT_EQ(0UL, options_val->get_recipients().value()->cc.size());
  EXPECT_EQ(0UL, options_val->get_recipients().value()->bcc.size());
  EXPECT_EQ(false, options_val->curl_verbose());
  EXPECT_FALSE(options_val->polling_period().has_value());

  // Bad polling period value
  node["email"]["polling-period"] = "laalaa";
  options = email::Options::yaml_to_options(node);
  EXPECT_FALSE(options.has_value());

  // Optional values
  node["email"]["polling-period"] = "123";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  ASSERT_TRUE(options_val->polling_period().has_value());
  EXPECT_EQ(std::chrono::nanoseconds(123), options_val->polling_period().value());
  EXPECT_FALSE(options_val->intraprocess());

  node["email"]["recipients"]["cc"] = "cc@email.com";
  node["email"]["recipients"]["bcc"] = "bcc@email.com";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  ASSERT_EQ(1UL, options_val->get_recipients().value()->cc.size());
  ASSERT_EQ(1UL, options_val->get_recipients().value()->bcc.size());
  EXPECT_STREQ("cc@email.com", options_val->get_recipients().value()->cc[0].c_str());
  EXPECT_STREQ("bcc@email.com", options_val->get_recipients().value()->bcc[0].c_str());
  EXPECT_FALSE(options_val->intraprocess());

  node["email"]["intraprocess"] = "false";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_FALSE(options_val->intraprocess());

  node["email"]["intraprocess"] = "true";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_TRUE(options_val->intraprocess());
}


TEST_F(TestOptions, yaml_to_options_intraprocess)
{
  YAML::Node node;
  node["email"] = YAML::Node();

  std::optional<std::shared_ptr<email::Options>> options;
  std::shared_ptr<email::Options> options_val;

  // User info and recipients must be provided if intraprocess is not enabled
  node["email"]["intraprocess"] = "false";
  options = email::Options::yaml_to_options(node);
  EXPECT_FALSE(options.has_value());

  node["email"]["intraprocess"] = "true";
  options = email::Options::yaml_to_options(node);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_TRUE(options_val->intraprocess());
  EXPECT_FALSE(options_val->get_user_info().has_value());
  EXPECT_FALSE(options_val->get_recipients().has_value());
  EXPECT_FALSE(options_val->polling_period().has_value());
}

TEST_F(TestOptions, parse_options_file)
{
  rcpputils::fs::path file;

  // Exists, but directory
  file = rcpputils::fs::create_temp_directory("TestOptions-parse_options_file-dir-");
  EXPECT_FALSE(email::Options::parse_options_file(file).has_value());
  EXPECT_TRUE(rcpputils::fs::remove(file));

  // File, but doesn't exist
  file = tmp / "TestOptions-parse_options_file-not-created";
  EXPECT_FALSE(email::Options::parse_options_file(file).has_value());

  // Bad YAML file
  file = tmp / "TestOptions-parse_options_file-created";
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

TEST_F(TestOptions, parse_options_from_file)
{
  // Good file
  rcpputils::fs::path file = tmp / "TestOptions-parse_options_from_file.email.yml";
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
  std::shared_ptr<email::Options> options_val;

  options = email::Options::parse_options_from_file();
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_STREQ("some.url", options_val->get_user_info().value()->host_smtp.c_str());
  EXPECT_STREQ("some.other.url", options_val->get_user_info().value()->host_imap.c_str());
  EXPECT_STREQ("my@email.ca", options_val->get_user_info().value()->username.c_str());
  EXPECT_STREQ("tinkywinky", options_val->get_user_info().value()->password.c_str());
  ASSERT_EQ(1UL, options_val->get_recipients().value()->to.size());
  EXPECT_STREQ("to@email.com", options_val->get_recipients().value()->to[0].c_str());
  EXPECT_FALSE(options_val->intraprocess());

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

TEST_F(TestOptions, parse_options_from_file_intraprocess)
{
  // Good file
  rcpputils::fs::path file = tmp / "TestOptions-parse_options_from_file_intraprocess.email.yml";
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", file.string().c_str()));
  std::ofstream file_stream;
  file_stream = std::ofstream(file.string().c_str());
  file_stream <<
    R"(
email:
  intraprocess: true
)";
  file_stream.close();

  std::optional<std::shared_ptr<email::Options>> options;
  std::shared_ptr<email::Options> options_val;

  options = email::Options::parse_options_from_file();
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_TRUE(options_val->intraprocess());
  EXPECT_FALSE(options_val->get_user_info().has_value());
  EXPECT_FALSE(options_val->get_recipients().has_value());
  EXPECT_FALSE(options_val->polling_period().has_value());

  EXPECT_TRUE(rcpputils::fs::remove(file));
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", NULL));
}

TEST_F(TestOptions, parse_options_from_args)
{
  // Bad
  const char * const argv_bad[] = {"a", "b"};
  EXPECT_FALSE(email::Options::parse_options_from_args(0, nullptr).has_value());
  EXPECT_FALSE(email::Options::parse_options_from_args(2, argv_bad).has_value());
  EXPECT_FALSE(email::Options::parse_options_from_args(6, nullptr).has_value());
  EXPECT_FALSE(email::Options::parse_options_from_args(7, nullptr).has_value());

  std::optional<std::shared_ptr<email::Options>> options;
  std::shared_ptr<email::Options> options_val;

  // Good without curl verbose
  const char * const argv_good[] = {
    "exe", "some.url", "some.other.url", "my@email.ca", "tinkywinky", "to@email.com"};
  options = email::Options::parse_options_from_args(
    (sizeof(argv_good) / sizeof(char *)), argv_good);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_STREQ("some.url", options_val->get_user_info().value()->host_smtp.c_str());
  EXPECT_STREQ("some.other.url", options_val->get_user_info().value()->host_imap.c_str());
  EXPECT_STREQ("my@email.ca", options_val->get_user_info().value()->username.c_str());
  EXPECT_STREQ("tinkywinky", options_val->get_user_info().value()->password.c_str());
  ASSERT_EQ(1UL, options_val->get_recipients().value()->to.size());
  EXPECT_STREQ("to@email.com", options_val->get_recipients().value()->to[0].c_str());
  EXPECT_FALSE(options_val->curl_verbose());
  EXPECT_FALSE(options_val->intraprocess());

  // Good with curl verbose
  const char * const argv_good_v[] = {
    "exe", "some.url", "some.other.url", "my@email.ca", "tinkywinky", "to@email.com", "-v"};
  options = email::Options::parse_options_from_args(
    (sizeof(argv_good_v) / sizeof(char *)), argv_good_v);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_TRUE(options_val->curl_verbose());
  EXPECT_FALSE(options_val->intraprocess());

  const char * const argv_good_cv[] = {
    "exe", "some.url", "some.other.url", "my@email.ca",
    "tinkywinky", "to@email.com", "--curl-verbose"};
  options = email::Options::parse_options_from_args(
    (sizeof(argv_good_cv) / sizeof(char *)), argv_good_cv);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_TRUE(options_val->curl_verbose());
  EXPECT_FALSE(options_val->intraprocess());

  // Bad curl verbose flag
  const char * const argv_bad_cv[] = {
    "exe", "some.url", "some.other.url", "my@email.ca",
    "tinkywinky", "to@email.com", "--bad-option"};
  options = email::Options::parse_options_from_args(
    (sizeof(argv_bad_cv) / sizeof(char *)), argv_bad_cv);
  ASSERT_TRUE(options.has_value());
  options_val = options.value();
  EXPECT_FALSE(options_val->curl_verbose());
  EXPECT_FALSE(options_val->intraprocess());
}

TEST_F(TestOptions, intraprocess)
{
  // User info and recipients must be provided if intraprocess is not enabled
  EXPECT_DEATH(
    email::Options(std::nullopt, std::nullopt, false, false, std::nullopt), "Assertion .* failed");
}
