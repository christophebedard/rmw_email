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

#include "email/gid.hpp"

TEST(TestGid, gid) {
  email::Gid gid1 = email::Gid::new_gid();
  email::Gid gid2 = email::Gid::new_gid();
  email::Gid gid3 = email::Gid::new_gid();

  // May be overkill
  EXPECT_NE(0u, gid1.value());
  EXPECT_NE(0u, gid2.value());
  EXPECT_NE(0u, gid3.value());
  EXPECT_NE(gid1.value(), gid2.value());
  EXPECT_NE(gid1.value(), gid3.value());
  EXPECT_NE(gid2.value(), gid3.value());
  EXPECT_FALSE(gid1.to_string().empty());
  EXPECT_FALSE(gid2.to_string().empty());
  EXPECT_FALSE(gid3.to_string().empty());
  EXPECT_STRNE(gid1.to_string().c_str(), gid2.to_string().c_str());
  EXPECT_STRNE(gid1.to_string().c_str(), gid3.to_string().c_str());
  EXPECT_STRNE(gid2.to_string().c_str(), gid3.to_string().c_str());

  // Check sequentiality (wow that's a real word)
  EXPECT_EQ(1u, gid2.value() - gid1.value());
  EXPECT_EQ(1u, gid3.value() - gid2.value());
}

TEST(TestGid, string) {
  email::Gid gid = email::Gid::new_gid();
  auto str = gid.to_string();
  auto gid_str_opt = email::Gid::from_string(str);

  ASSERT_TRUE(gid_str_opt.has_value());
  EXPECT_EQ(gid.value(), gid_str_opt.value().value());

  EXPECT_FALSE(email::Gid::from_string("abc").has_value());
}

class GidObjectStub : public email::GidObject
{
public:
  GidObjectStub()
  : GidObject()
  {}
};

TEST(TestGidObject, init) {
  auto gid_object = GidObjectStub();
  EXPECT_NE(0u, gid_object.get_gid().value());
}
