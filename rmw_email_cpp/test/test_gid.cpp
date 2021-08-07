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

#include "email/gid.hpp"
#include "rmw/types.h"
#include "rmw_email_cpp/gid.hpp"

TEST(TestGid, convert_gid)
{
  const email::Gid gid(42u);
  rmw_gid_t converted_gid = convert_gid(gid);

  email::GidValue reconverted_value = 0u;
  memcpy(&reconverted_value, converted_gid.data, sizeof(reconverted_value));
  EXPECT_EQ(gid.value(), reconverted_value);
}

TEST(TestGid, writer_guid)
{
  const email::Gid gid(42u);

  rmw_request_id_t converted_request_id{};
  copy_email_gid_to_writer_guid(converted_request_id.writer_guid, gid);

  const email::Gid reconverted_gid = convert_writer_guid_to_email_gid(
    converted_request_id.writer_guid);

  EXPECT_EQ(gid.value(), reconverted_gid.value());
}
