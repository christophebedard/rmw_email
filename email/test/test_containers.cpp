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

#include "email/safe_map.hpp"
#include "email/safe_queue.hpp"

TEST(TestContainers, safe_map) {
  email::SafeMap<int, int> map;
  EXPECT_TRUE(map.empty());
  EXPECT_FALSE(map.contains(1));
  map.insert({1, 2});
  EXPECT_FALSE(map.empty());
  EXPECT_TRUE(map.contains(1));
  auto it = map.find(1);
  ASSERT_NE(it, map.cend());
  ASSERT_NE(it, map.end());
  ASSERT_EQ(it, map.cbegin());
  ASSERT_EQ(it, map.begin());
  map.erase(it);
  map.insert({1, 2});
  EXPECT_FALSE(map.empty());
  auto it_begin = map.begin();
  map.erase(it_begin);
  EXPECT_TRUE(map.empty());
}

TEST(TestContainers, safe_queue) {
  email::SafeQueue<int> queue;
  EXPECT_TRUE(queue.empty());
  queue.push(1);
  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(1, queue.front());
  EXPECT_EQ(1, queue.dequeue());
  EXPECT_TRUE(queue.empty());
  queue.push(1);
  EXPECT_FALSE(queue.empty());
  queue.pop();
  EXPECT_TRUE(queue.empty());
}
