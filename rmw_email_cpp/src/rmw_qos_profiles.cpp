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

#include "rmw/error_handling.h"
#include "rmw/qos_profiles.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"

#include "rmw_email_cpp/identifier.hpp"
// #include "rmw_email_cpp/macros.hpp"
// #include "rmw_email_cpp/types.hpp"

extern "C" rmw_ret_t rmw_qos_profile_check_compatible(
  const rmw_qos_profile_t publisher_profile,
  const rmw_qos_profile_t subscription_profile,
  rmw_qos_compatibility_type_t * compatibility,
  char * reason,
  size_t reason_size)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(compatibility, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(compatibility, RMW_RET_INVALID_ARGUMENT);
  if (!reason && 0u != reason_size) {
    RMW_SET_ERROR_MSG("reason parameter is null, but reason_size parameter is not zero");
    return RMW_RET_INVALID_ARGUMENT;
  }

  // TODO(christophebedard) figure out
  static_cast<void>(publisher_profile);
  static_cast<void>(subscription_profile);
  *compatibility = RMW_QOS_COMPATIBILITY_OK;
  return RMW_RET_OK;
}
