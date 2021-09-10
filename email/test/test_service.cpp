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

#include "email/service.hpp"

class ServiceObjectStub : public email::ServiceObject
{
public:
  explicit ServiceObjectStub(const std::string & service_name)
  : ServiceObject(service_name)
  {}
};

TEST(TestService, validate_service_name)
{
  EXPECT_NO_THROW(ServiceObjectStub("/my_service"));
  EXPECT_THROW(ServiceObjectStub(""), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("aaa\n"), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("\nbbb"), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("aaa\nbbb"), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("\n"), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("aaa\r\n"), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("\r\nccc"), email::ServiceNameInvalidError);
  EXPECT_THROW(ServiceObjectStub("aaa\r\nccc"), email::ServiceNameInvalidError);
}
