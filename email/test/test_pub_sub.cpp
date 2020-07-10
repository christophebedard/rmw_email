// Copyright 2020 Christophe Bedard
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

#include "email/pub_sub.hpp"

class PubSubObjectStub : public email::PubSubObject
{
public:
  explicit PubSubObjectStub(const std::string & topic)
  : PubSubObject(topic)
  {}
};

TEST(TestPubSub, validate_topic) {
  EXPECT_THROW(PubSubObjectStub(""), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\n"), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("\nbbb"), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\nbbb"), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("\n"), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\r\n"), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("\r\nccc"), email::TopicInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\r\nccc"), email::TopicInvalidError);
}
