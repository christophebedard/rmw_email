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

#ifndef RMW_EMAIL_CPP__GID_HPP_
#define RMW_EMAIL_CPP__GID_HPP_

#include <stdint.h>

#include "rmw/types.h"

rmw_gid_t get_new_gid();

void copy_gids(rmw_gid_t * dest, rmw_gid_t * src);

#endif  // RMW_EMAIL_CPP__GID_HPP_