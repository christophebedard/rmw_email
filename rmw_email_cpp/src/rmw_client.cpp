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

#include "email/service_client.hpp"
#include "rcpputils/scope_exit.hpp"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"
#include "rmw/types.h"

#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/macros.hpp"
#include "rmw_email_cpp/qos.hpp"
#include "rmw_email_cpp/topic_service_name.hpp"
#include "rmw_email_cpp/type_support.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_client_t * rmw_create_client(
  const rmw_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * service_name,
  const rmw_qos_profile_t * qos_policies)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(type_support, nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(service_name, nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(qos_policies, nullptr);
  if (!rmw_email_cpp::is_valid_qos(qos_policies)) {
    RMW_SET_ERROR_MSG("qos_policies is invalid");
    return nullptr;
  }

  // Validate type support
  const rosidl_service_type_support_t * valid_type_support =
    rmw_email_cpp::validate_type_support_service(type_support);
  if (nullptr == valid_type_support) {
    return nullptr;
  }

  // Validate service name
  if (RMW_RET_OK != rmw_email_cpp::validate_service_name(service_name, qos_policies)) {
    return nullptr;
  }

  // Create email service client
  email::ServiceClient * email_client = new (std::nothrow) email::ServiceClient(service_name);
  RET_ALLOC_X(email_client, return nullptr);
  auto cleanup_email_client = rcpputils::make_scope_exit(
    [email_client]() {
      delete email_client;
    });

  rmw_email_client_t * rmw_email_client = new (std::nothrow) rmw_email_client_t;
  RET_ALLOC_X(rmw_email_client, return nullptr);
  auto cleanup_rmw_email_client = rcpputils::make_scope_exit(
    [rmw_email_client]() {
      delete rmw_email_client;
    });
  rmw_email_client->email_client = email_client;
  rmw_email_client->type_supports = *valid_type_support;

  rmw_client_t * rmw_client = rmw_client_allocate();
  RET_NULL_X(rmw_client, return nullptr);
  auto cleanup_rmw_client = rcpputils::make_scope_exit(
    [rmw_client]() {
      rmw_client_free(rmw_client);
    });
  rmw_client->implementation_identifier = rmw_email_cpp::identifier;
  rmw_client->data = rmw_email_client;
  rmw_client->service_name = reinterpret_cast<const char *>(rmw_allocate(strlen(service_name) + 1));
  RET_NULL_X(rmw_client->service_name, rmw_client_free(rmw_client); return nullptr);
  memcpy(const_cast<char *>(rmw_client->service_name), service_name, strlen(service_name) + 1);

  cleanup_rmw_client.cancel();
  cleanup_rmw_email_client.cancel();
  cleanup_email_client.cancel();
  return rmw_client;
}

extern "C" rmw_ret_t rmw_destroy_client(
  rmw_node_t * node,
  rmw_client_t * client)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    client,
    client->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INVALID_ARGUMENT);

  rmw_email_client_t * rmw_email_client = static_cast<rmw_email_client_t *>(client->data);
  email::ServiceClient * email_client = rmw_email_client->email_client;
  delete email_client;
  delete rmw_email_client;
  rmw_free(const_cast<char *>(client->service_name));
  rmw_client_free(client);
  return RMW_RET_OK;
}
