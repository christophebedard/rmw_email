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

#include <memory>
#include <string>

#include "email/log.hpp"
#include "rcpputils/filesystem_helper.hpp"
#include "rcutils/env.h"

TEST(TestLog, init)
{
  EXPECT_NO_THROW(email::log::shutdown());

  email::log::init(email::log::Level::debug);
  EXPECT_NO_THROW(email::log::init(email::log::Level::warn));
  EXPECT_NO_THROW(email::log::create("some logger"));
  EXPECT_NO_THROW(email::log::shutdown());
  EXPECT_NO_THROW(email::log::get_or_create("some logger"));
  auto logger = email::log::get_or_create("some logger");
  EXPECT_NO_THROW(email::log::remove(logger));
  email::log::shutdown();
}

TEST(TestLog, init_log_levels)
{
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", "debug"));
  email::log::init_from_env();
  email::log::shutdown();
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", "info"));
  email::log::init_from_env();
  email::log::shutdown();
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", "warn"));
  email::log::init_from_env();
  email::log::shutdown();
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", "error"));
  email::log::init_from_env();
  email::log::shutdown();
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", "fatal"));
  email::log::init_from_env();
  email::log::shutdown();
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", "off"));
  email::log::init_from_env();
  email::log::shutdown();
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_LEVEL", nullptr));
  email::log::init_from_env();
  email::log::shutdown();
}

TEST(TestLog, get)
{
  EXPECT_THROW(
    email::log::remove(std::shared_ptr<email::Logger>(nullptr)),
    email::log::LoggingNotInitializedError);
  EXPECT_NO_THROW(email::log::create("some logger"));
  EXPECT_NO_THROW(email::log::get_or_create("some logger"));
  EXPECT_NO_THROW(email::log::shutdown());

  auto logger = email::log::create("mylogger");
  EXPECT_NE(nullptr, logger.get());
  auto logger2 = email::log::get_or_create("mylogger");
  EXPECT_EQ(logger.get(), logger2.get());
  email::log::shutdown();
}

TEST(TestLog, file)
{
  auto logfile_path = rcpputils::fs::create_temp_directory("TestLog_file") / "log";
  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_FILE", logfile_path.string().c_str()));
  email::log::init_from_env();

  EXPECT_TRUE(rcutils_set_env("EMAIL_LOG_FILE", nullptr));
  email::log::shutdown();
}
