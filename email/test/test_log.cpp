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

#include "email/log.hpp"

TEST(TestLog, init) {
  EXPECT_THROW(email::log::create("some logger"), email::log::LoggingNotInitializedError);
  EXPECT_THROW(
    email::log::get_or_create("some logger"), email::log::LoggingNotInitializedError);
  EXPECT_THROW(
    email::log::remove(std::shared_ptr<email::Logger>(nullptr)),
    email::log::LoggingNotInitializedError);
  EXPECT_NO_THROW(email::log::shutdown());

  email::log::init(email::log::Level::debug);
  EXPECT_THROW(
    email::log::init(email::log::Level::debug), email::log::LoggingAlreadyInitializedError);
  EXPECT_NO_THROW(email::log::create("some logger"));
  EXPECT_NO_THROW(email::log::get_or_create("some logger"));
  auto logger = email::log::get_or_create("some logger");
  EXPECT_NO_THROW(email::log::remove(logger));
  email::log::shutdown();
}
