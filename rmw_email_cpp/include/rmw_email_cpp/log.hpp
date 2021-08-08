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

#ifndef RMW_EMAIL_CPP__LOG_HPP_
#define RMW_EMAIL_CPP__LOG_HPP_

#include "rcutils/logging_macros.h"

#include "rmw_email_cpp/identifier.hpp"

#define RMW_EMAIL_LOG_DEBUG(...) RCUTILS_LOG_DEBUG_NAMED(rmw_email_cpp::identifier, __VA_ARGS__)

#endif  // RMW_EMAIL_CPP__LOG_HPP_
