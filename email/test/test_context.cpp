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

#include <fstream>
#include <string>

#include "email/context.hpp"
#include "rcpputils/filesystem_helper.hpp"
#include "rcutils/env.h"

TEST(TestContext, init) {
  rcpputils::fs::path file =
    rcpputils::fs::temp_directory_path() / "TestContext-init.email.yml";
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", file.string().c_str()));
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE_DEFAULT_PATH", file.string().c_str()));

  email::Context context;
  EXPECT_THROW(context.get_options(), email::ContextNotInitializedError);
  EXPECT_THROW(context.get_receiver(), email::ContextNotInitializedError);
  EXPECT_THROW(context.get_sender(), email::ContextNotInitializedError);
  EXPECT_THROW(context.get_polling_manager(), email::ContextNotInitializedError);
  EXPECT_THROW(context.get_subscription_handler(), email::ContextNotInitializedError);
  EXPECT_THROW(context.get_service_handler(), email::ContextNotInitializedError);

  EXPECT_THROW(context.init(), email::ContextInitFailedError);
  EXPECT_THROW(context.init(), email::ContextInitFailedError);

  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE", NULL));
  ASSERT_TRUE(rcutils_set_env("EMAIL_CONFIG_FILE_DEFAULT_PATH", NULL));
}
