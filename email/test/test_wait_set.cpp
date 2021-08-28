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
#include <thread>

#include "email/guard_condition.hpp"
#include "email/log.hpp"
#include "email/wait_set.hpp"

class TestWaitSet : public ::testing::Test
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

TEST_F(TestWaitSet, empty) {
  email::WaitSet waitset;
  // Expect true: it should timeout since there is nothing that can satisfy the wait
  EXPECT_TRUE(waitset.wait(std::chrono::milliseconds(0)));
  EXPECT_TRUE(waitset.wait(std::chrono::milliseconds(10)));

  EXPECT_EQ(0UL, waitset.get_subscriptions().size());
  EXPECT_EQ(0UL, waitset.get_clients().size());
  EXPECT_EQ(0UL, waitset.get_servers().size());
  EXPECT_EQ(0UL, waitset.get_guard_conditions().size());
}

TEST_F(TestWaitSet, guard_condition_in_use) {
  email::GuardCondition cond;
  email::WaitSet waitset1;
  waitset1.add_guard_condition(&cond);
  EXPECT_EQ(1u, waitset1.get_guard_conditions().size());
  email::WaitSet waitset2;
  EXPECT_THROW(waitset2.add_guard_condition(&cond), email::GuardConditionAlreadyInUseError);
  EXPECT_EQ(0u, waitset2.get_guard_conditions().size());

  cond.trigger();
  EXPECT_FALSE(waitset1.wait());
  waitset1.clear();
  waitset1.add_guard_condition(&cond);
  EXPECT_TRUE(waitset1.wait(std::chrono::milliseconds(0)));
}

TEST_F(TestWaitSet, guard_condition) {
  {
    // Should time out, and guard cond should be set to nullptr since it wasn't triggered
    email::GuardCondition cond;
    email::WaitSet waitset;
    waitset.add_guard_condition(&cond);
    bool timedout = waitset.wait(std::chrono::milliseconds(1));
    EXPECT_TRUE(timedout);
    ASSERT_EQ(1u, waitset.get_guard_conditions().size());
    EXPECT_EQ(nullptr, waitset.get_guard_conditions()[0]);
  }
  {
    email::GuardCondition cond;
    email::WaitSet waitset;
    waitset.add_guard_condition(&cond);

    // Trigger guard cond after a small delay
    // Not a great test, but it should work
    auto delay = std::chrono::milliseconds(100);
    auto start = std::chrono::steady_clock::now();
    auto trigger_thread = std::thread(
      [&]() {
        std::this_thread::sleep_for(delay);
        cond.trigger();
      });
    bool timedout = waitset.wait();
    auto end = std::chrono::steady_clock::now();
    EXPECT_FALSE(timedout);
    // Check delay to make sure it's close to the expected delay
    auto actual_delay = end - start;
    auto diff = std::chrono::abs(actual_delay - delay);
    EXPECT_TRUE(diff < std::chrono::milliseconds(15)) <<
      "diff=" << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ms";
    trigger_thread.join();
    ASSERT_EQ(1u, waitset.get_guard_conditions().size());
    EXPECT_NE(nullptr, waitset.get_guard_conditions()[0]);
  }
}

TEST_F(TestWaitSet, multiple_waits) {
  email::WaitSet waitset;
  email::GuardCondition cond;
  bool timedout = false;

  waitset.add_guard_condition(&cond);
  cond.trigger();
  timedout = waitset.wait(std::chrono::milliseconds(-1));
  EXPECT_FALSE(timedout);
  ASSERT_EQ(1u, waitset.get_guard_conditions().size());
  EXPECT_NE(nullptr, waitset.get_guard_conditions()[0]);
  waitset.clear();

  waitset.add_guard_condition(&cond);
  timedout = waitset.wait(std::chrono::milliseconds(1));
  EXPECT_TRUE(timedout);
  ASSERT_EQ(1u, waitset.get_guard_conditions().size());
  EXPECT_EQ(nullptr, waitset.get_guard_conditions()[0]);
  waitset.clear();

  cond.trigger();
  waitset.add_guard_condition(&cond);
  timedout = waitset.wait(std::chrono::milliseconds(-1));
  EXPECT_FALSE(timedout);
  ASSERT_EQ(1u, waitset.get_guard_conditions().size());
  EXPECT_NE(nullptr, waitset.get_guard_conditions()[0]);
  waitset.clear();
}
