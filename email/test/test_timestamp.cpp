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

TEST(TestTimestamp, init) {
  email::Timestamp ts1 = email::Timestamp::now();
  EXPECT_NE(0u, ts1.nanoseconds());

  email::Timestamp ts2 = email::Timestamp::now();
  EXPECT_NE(0u, ts2.nanoseconds());

  EXPECT_LT(ts1.nanoseconds(), ts2.nanoseconds());
}

TEST(TestTimestamp, string) {
  email::Timestamp ts = email::Timestamp::now();
  auto str = ts.to_string();
  email::Timestamp ts_str = email::Timestamp::from_string(str);

  EXPECT_EQ(ts.nanoseconds(), ts_str.nanoseconds());

  EXPECT_DEATH(email::Timestamp::from_string("abc"), "");
}

TEST(TestTimestamp, format) {
  printf("%s\n", fmt::format("timestamp: {}", email::Timestamp::now()).c_str());
}
