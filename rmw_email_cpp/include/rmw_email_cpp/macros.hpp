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

#ifndef RMW_EMAIL_CPP__MACROS_HPP_
#define RMW_EMAIL_CPP__MACROS_HPP_

#include "rmw_email_cpp/identifier.hpp"

#define RET_ERR_X(msg, code) do {RMW_SET_ERROR_MSG(msg); code;} while (0)
#define RET_NULL_X(var, code) do {if (!var) {RET_ERR_X(#var " is null", code);}} while (0)
#define RET_ALLOC_X(var, code) do {if (!var) {RET_ERR_X("failed to allocate " #var, code);} \
} while (0)
#define RET_WRONG_IMPLID_X(var, code) do { \
    if ((var)->implementation_identifier != email_identifier) { \
      RET_ERR_X(#var " not from this implementation", code); \
    } \
} while (0)
#define RET_NULL(var) RET_NULL_X(var, return RMW_RET_ERROR)
#define RET_WRONG_IMPLID(var) RET_WRONG_IMPLID_X(var, return RMW_RET_INCORRECT_RMW_IMPLEMENTATION)

#endif  // RMW_EMAIL_CPP__MACROS_HPP_
