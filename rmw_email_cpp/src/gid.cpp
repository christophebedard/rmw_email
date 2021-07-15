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

#include "email/gid.hpp"
#include "rmw/types.h"
#include "rmw_email_cpp/identifier.hpp"

rmw_gid_t convert_gid(const email::Gid & gid)
{
  rmw_gid_t rmw_gid = {};
  rmw_gid.implementation_identifier = email_identifier;

  const email::GidValue new_id = gid.value();
  static_assert(
    sizeof(decltype(new_id)) <= RMW_GID_STORAGE_SIZE,
    "RMW_GID_STORAGE_SIZE insufficient to store rmw_email_cpp GID");
  memcpy(rmw_gid.data, &new_id, sizeof(new_id));

  return rmw_gid;
}

void copy_gids(rmw_gid_t * dest, rmw_gid_t * src)
{
  // *dest = *src;
  dest->implementation_identifier = email_identifier;
  memset(dest->data, 0, sizeof(dest->data));
  memcpy(dest->data, &src->data, sizeof(src->data));
}
