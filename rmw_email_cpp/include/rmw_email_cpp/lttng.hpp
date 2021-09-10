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

// Provide fake header guard for cpplint
#undef RMW_EMAIL_CPP__LTTNG_HPP_
#ifndef RMW_EMAIL_CPP__LTTNG_HPP_
#define RMW_EMAIL_CPP__LTTNG_HPP_

#include "rmw_email_cpp/config.hpp"

#ifndef RMW_EMAIL_CPP_LTTNG_ENABLED

#define RMW_EMAIL_CPP_TRACEPOINT(event_name, ...) ((void) (0))

#else  // RMW_EMAIL_CPP_LTTNG_ENABLED

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER ros2

#define RMW_EMAIL_CPP_TRACEPOINT(event_name, ...) \
  tracepoint(TRACEPOINT_PROVIDER, event_name, __VA_ARGS__)

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "rmw_email_cpp/lttng.hpp"

#if !defined(__RMW_EMAIL_CPP__LTTNG_HPP_) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define __RMW_EMAIL_CPP__LTTNG_HPP_

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  rmw_publish_yaml,
  TP_ARGS(
    const void *, message_arg,
    const void *, message_yaml_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, message, message_arg)
    ctf_integer_hex(const void *, message_yaml, message_yaml_arg)
  )
)

#endif  // __RMW_EMAIL_CPP__LTTNG_HPP_

#include <lttng/tracepoint-event.h>

#endif  // RMW_EMAIL_CPP_LTTNG_ENABLED

#endif  // RMW_EMAIL_CPP__LTTNG_HPP_
