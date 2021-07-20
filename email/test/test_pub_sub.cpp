// Copyright 2020-2021 Christophe Bedard
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

#include "email/gid.hpp"
#include "email/pub_sub.hpp"

class PubSubObjectStub : public email::PubSubObject
{
public:
  explicit PubSubObjectStub(const std::string & topic_name)
  : PubSubObject(topic_name)
  {}
};

TEST(TestPubSub, validate_topic_name) {
  EXPECT_NO_THROW(PubSubObjectStub("/my_topic"));
  EXPECT_THROW(PubSubObjectStub(""), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\n"), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("\nbbb"), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\nbbb"), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("\n"), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\r\n"), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("\r\nccc"), email::TopicNameInvalidError);
  EXPECT_THROW(PubSubObjectStub("aaa\r\nccc"), email::TopicNameInvalidError);
}

TEST(TestPubSub, gid) {
  // Just check that they don't have the same GID
  PubSubObjectStub o1("/my_topic");
  PubSubObjectStub o2("/my_other_topic");
  EXPECT_NE(o1.get_gid().value(), o2.get_gid().value());
  EXPECT_STRNE(o1.get_gid().to_string().c_str(), o2.get_gid().to_string().c_str());
}
