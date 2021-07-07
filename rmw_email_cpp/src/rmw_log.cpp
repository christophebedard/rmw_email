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

#include "rmw/rmw.h"

extern "C" rmw_ret_t rmw_set_log_severity(rmw_log_severity_t severity)
{
  // TODO(christophebedard) actually use it
  // Will need to allow setting log level manually with email
  static_cast<void>(severity);
  return RMW_RET_OK;
}
