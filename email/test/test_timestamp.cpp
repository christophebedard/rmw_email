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

#include <string>

#include "email/timestamp.hpp"

TEST(TestTimestamp, init)
{
  email::Timestamp ts1 = email::Timestamp::now();
  EXPECT_NE(ts1.nanoseconds(), 0);

  email::Timestamp ts2 = email::Timestamp::now();
  EXPECT_NE(ts2.nanoseconds(), 0);

  EXPECT_LT(ts1, ts2);
}

TEST(TestTimestamp, string)
{
  email::Timestamp ts = email::Timestamp::now();
  auto str = ts.to_string();
  auto ts_str_opt = email::Timestamp::from_string(str);
  ASSERT_TRUE(ts_str_opt.has_value());
  EXPECT_EQ(ts, ts_str_opt.value());

  EXPECT_FALSE(email::Timestamp::from_string("abc").has_value());
}

TEST(TestTimestamp, format)
{
  printf("%s\n", fmt::format("timestamp: {}", email::Timestamp::now()).c_str());
}
