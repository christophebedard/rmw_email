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

#include "email/service_server.hpp"
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

extern "C" rmw_service_t * rmw_create_service(
  const rmw_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * service_name,
  const rmw_qos_profile_t * qos_profile)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, nullptr);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(type_support, nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(service_name, nullptr);
  RMW_CHECK_ARGUMENT_FOR_NULL(qos_profile, nullptr);
  if (!rmw_email_cpp::is_valid_qos(qos_profile)) {
    RMW_SET_ERROR_MSG("qos_profile is invalid");
    return nullptr;
  }

  // Validate type support
  const rosidl_service_type_support_t * valid_type_support =
    rmw_email_cpp::validate_type_support_service(type_support);
  if (nullptr == valid_type_support) {
    return nullptr;
  }

  // Validate service name
  if (RMW_RET_OK != rmw_email_cpp::validate_service_name(service_name, qos_profile)) {
    return nullptr;
  }

  // Create email service server
  email::ServiceServer * email_server = new (std::nothrow) email::ServiceServer(service_name);
  RET_ALLOC_X(email_server, return nullptr);
  auto cleanup_email_server = rcpputils::make_scope_exit(
    [email_server]() {
      delete email_server;
    });

  rmw_email_server_t * rmw_email_server = new (std::nothrow) rmw_email_server_t;
  RET_ALLOC_X(rmw_email_server, return nullptr);
  auto cleanup_rmw_email_server = rcpputils::make_scope_exit(
    [rmw_email_server]() {
      delete rmw_email_server;
    });
  rmw_email_server->email_server = email_server;
  rmw_email_server->type_supports = *valid_type_support;

  rmw_service_t * rmw_service = rmw_service_allocate();
  RET_NULL_X(rmw_service, return nullptr);
  auto cleanup_rmw_service = rcpputils::make_scope_exit(
    [rmw_service]() {
      rmw_service_free(rmw_service);
    });
  rmw_service->implementation_identifier = rmw_email_cpp::identifier;
  rmw_service->data = rmw_email_server;
  rmw_service->service_name =
    reinterpret_cast<const char *>(rmw_allocate(strlen(service_name) + 1));
  RET_NULL_X(rmw_service->service_name, rmw_service_free(rmw_service); return nullptr);
  memcpy(const_cast<char *>(rmw_service->service_name), service_name, strlen(service_name) + 1);

  cleanup_rmw_service.cancel();
  cleanup_rmw_email_server.cancel();
  cleanup_email_server.cancel();
  return rmw_service;
}

extern "C" rmw_ret_t rmw_destroy_service(
  rmw_node_t * node,
  rmw_service_t * service)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    service,
    service->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INVALID_ARGUMENT);

  rmw_email_server_t * rmw_email_server = static_cast<rmw_email_server_t *>(service->data);
  email::ServiceServer * email_server = rmw_email_server->email_server;
  delete email_server;
  delete rmw_email_server;
  rmw_free(const_cast<char *>(service->service_name));
  rmw_service_free(service);
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_service_server_is_available(
  const rmw_node_t * node,
  const rmw_client_t * client,
  bool * is_available)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_ERROR);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_ERROR);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    client,
    client->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(is_available, RMW_RET_ERROR);

  // TODO(christophebedard) figure out

  // Always ready
  *is_available = true;
  return RMW_RET_OK;
}
