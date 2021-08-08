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
#undef EMAIL__LTTNG_HPP_
#ifndef EMAIL__LTTNG_HPP_
#define EMAIL__LTTNG_HPP_

#include "email/config.hpp"

#ifndef EMAIL_HAS_LTTNG_TRACING

#define EMAIL_TRACEPOINT(event_name, ...) ((void) (0))

#else  // EMAIL_HAS_LTTNG_TRACING

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER email

#define EMAIL_TRACEPOINT(event_name, ...) \
  tracepoint(TRACEPOINT_PROVIDER, event_name, __VA_ARGS__)

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "email/lttng.hpp"

#if !defined(__EMAIL__LTTNG_HPP_) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define __EMAIL__LTTNG_HPP_

#include <lttng/tracepoint.h>

#include <stdint.h>
#include <stdbool.h>

#include "email/gid.hpp"

// TODO(christophebedard) move to rmw_email_cpp
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

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  create_publisher,
  TP_ARGS(
    const void *, publisher_arg,
    const char *, topic_name_arg,
    email::GidValue, gid_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, publisher, publisher_arg)
    ctf_string(topic_name, topic_name_arg)
    ctf_integer(email::GidValue, gid, gid_arg)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  create_subscription,
  TP_ARGS(
    const void *, subscription_arg,
    const char *, topic_name_arg,
    email::GidValue, gid_arg,
    const void *, queue_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, subscription, subscription_arg)
    ctf_string(topic_name, topic_name_arg)
    ctf_integer(email::GidValue, gid, gid_arg)
    ctf_integer_hex(const void *, queue, queue_arg)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  publish,
  TP_ARGS(
    const void *, publisher_arg,
    const void *, message_arg,
    int64_t, timestamp_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, publisher, publisher_arg)
    ctf_integer_hex(const void *, message, message_arg)
    ctf_integer(int64_t, timestamp, timestamp_arg)
  )
)

TRACEPOINT_EVENT(
  TRACEPOINT_PROVIDER,
  subscription_handle,
  TP_ARGS(
    const void *, queue_arg,
    int64_t, timestamp_arg
  ),
  TP_FIELDS(
    ctf_integer_hex(const void *, queue, queue_arg)
    ctf_integer(int64_t, timestamp, timestamp_arg)
  )
)

#endif  // __EMAIL__LTTNG_HPP_

#include <lttng/tracepoint-event.h>

#endif  // EMAIL_HAS_LTTNG_TRACING

#endif  // EMAIL__LTTNG_HPP_
