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
#include <memory>
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

TEST_F(TestWaitSet, guard_condition_in_use) {
  auto cond = std::make_shared<email::GuardCondition>();
  email::WaitSet waitset1({}, {}, {}, {cond});
  EXPECT_THROW(email::WaitSet waitset2({}, {}, {}, {cond}), email::GuardConditionAlreadyInUseError);
}

TEST_F(TestWaitSet, guard_condition) {
  auto cond = std::make_shared<email::GuardCondition>();
  email::WaitSet waitset({}, {}, {}, {cond});

  auto delay = std::chrono::milliseconds(100);
  auto start = std::chrono::steady_clock::now();
  auto trigger_thread = std::thread(
    [&]() {
      std::this_thread::sleep_for(delay);
      cond->trigger();
    });
  bool timedout = waitset.wait();
  auto end = std::chrono::steady_clock::now();
  EXPECT_FALSE(timedout);
  auto actual_delay = end - start;
  auto diff = std::chrono::abs(actual_delay - delay);
  // Not a great test, but it should work
  EXPECT_TRUE(diff < std::chrono::milliseconds(10)) <<
    "diff=" << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ms";
  trigger_thread.join();
}
