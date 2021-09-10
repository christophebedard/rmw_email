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

#include "email/context.hpp"
#include "email/init.hpp"

TEST(TestCli, init)
{
  EXPECT_DEATH(email::init(0, nullptr), "");
  EXPECT_FALSE(email::shutdown());

  const char * const argv_good[] = {
    "exe", "some.url", "some.other.url", "my@email.ca", "tinkywinky", "to@email.com"};
  email::init((sizeof(argv_good) / sizeof(char *)), argv_good);
  EXPECT_THROW(
    email::init((sizeof(argv_good) / sizeof(char *)), argv_good),
    email::ContextAlreadyInitializedError);
  EXPECT_TRUE(email::shutdown());
}