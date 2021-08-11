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

#ifndef RMW_EMAIL_CPP__TYPES_HPP_
#define RMW_EMAIL_CPP__TYPES_HPP_

#include <mutex>

#include "email/init.hpp"
#include "email/guard_condition.hpp"
#include "email/publisher.hpp"
#include "email/service_client.hpp"
#include "email/service_server.hpp"
#include "email/subscription.hpp"
#include "email/wait_set.hpp"
#include "rmw/rmw.h"

struct rmw_context_impl_t
{
  // TODO(christophebedard) add missing stuff

  // TODO(christophebedard) move to graph cache handler?
  rmw_guard_condition_t * graph_guard_condition{nullptr};

  size_t node_count{0};
  std::mutex mutex_initialization;

  bool is_shutdown{false};

  rmw_context_impl_t()
  {}

  /// Context destruction, called when deleting this.
  ~rmw_context_impl_t()
  {
    // Shutdown middleware
    email::shutdown();

    // Make sure we didn't get destroyed while there's still a node
    if (0u != this->node_count) {
      RCUTILS_SAFE_FWRITE_TO_STDERR(
        "Not all nodes were finished before finishing the context\n."
        "Ensure `rmw_destroy_node` is called for all nodes before `rmw_context_fini`,"
        "to avoid leaking.\n");
    }
  }

  /// Called whenever a new node is created.
  rmw_ret_t
  init(rmw_init_options_t * options, size_t domain_id);

  /// Called whenever a node is destroy.
  rmw_ret_t
  fini();

  /// Cleanup on init failure and on fini.
  void
  cleanup();
};

// TODO(christophebedard) add concept of "node" to email?
typedef struct rmw_email_node_t
{
} rmw_email_node_t;

typedef struct rmw_email_pub_t
{
  /// Pointer to the actual publisher
  email::Publisher * email_pub;
  /// gid
  rmw_gid_t gid;
  /// Type supports
  rosidl_message_type_support_t type_supports;
} rmw_email_pub_t;

typedef struct rmw_email_sub_t
{
  /// Pointer to the actual subscription
  email::Subscription * email_sub;
  /// gid
  rmw_gid_t gid;
  /// Type supports
  rosidl_message_type_support_t type_supports;
} rmw_email_sub_t;

typedef struct rmw_email_guard_condition_t
{
  /// Pointer to the actual guard condition
  email::GuardCondition * email_guard_condition;
} rmw_email_guard_condition_t;

typedef struct rmw_email_client_t
{
  /// Pointer to the actual service client
  email::ServiceClient * email_client;
  /// Type supports
  rosidl_service_type_support_t type_supports;
} rmw_email_client_t;

typedef struct rmw_email_server_t
{
  /// Pointer to the actual service server
  email::ServiceServer * email_server;
  /// Type supports
  rosidl_service_type_support_t type_supports;
} rmw_email_server_t;

typedef struct rmw_email_wait_set_t
{
  /// Pointer to the actual wait set
  email::WaitSet * email_waitset;
} rmw_email_wait_set_t;

#endif  // RMW_EMAIL_CPP__TYPES_HPP_
