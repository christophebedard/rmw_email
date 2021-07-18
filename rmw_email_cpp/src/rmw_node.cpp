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

#include "rcpputils/scope_exit.hpp"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"
#include "rmw/validate_namespace.h"
#include "rmw/validate_node_name.h"

#include "rmw_email_cpp/macros.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_node_t * rmw_create_node(
  rmw_context_t * context, const char * name, const char * namespace_)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(context, nullptr);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    context,
    context->implementation_identifier,
    email_identifier,
    return nullptr);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    context->impl,
    "expected initialized context",
    return nullptr);
  if (context->impl->is_shutdown) {
    RCUTILS_SET_ERROR_MSG("context has been shutdown");
    return nullptr;
  }

  // Validate node name
  int validation_result = RMW_NODE_NAME_VALID;
  rmw_ret_t ret = rmw_validate_node_name(name, &validation_result, nullptr);
  if (RMW_RET_OK != ret) {
    return nullptr;
  }
  if (RMW_NODE_NAME_VALID != validation_result) {
    const char * reason = rmw_node_name_validation_result_string(validation_result);
    RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("invalid node name: %s", reason);
    return nullptr;
  }
  // Validate namespace
  validation_result = RMW_NAMESPACE_VALID;
  ret = rmw_validate_namespace(namespace_, &validation_result, nullptr);
  if (RMW_RET_OK != ret) {
    return nullptr;
  }
  if (RMW_NAMESPACE_VALID != validation_result) {
    const char * reason = rmw_node_name_validation_result_string(validation_result);
    RMW_SET_ERROR_MSG_WITH_FORMAT_STRING("invalid node namespace: %s", reason);
    return nullptr;
  }

  // Init context implementation
  ret = context->impl->init(&context->options, context->actual_domain_id);
  if (RMW_RET_OK != ret) {
    return nullptr;
  }
  auto finalize_context = rcpputils::make_scope_exit(
    [context]() {context->impl->fini();});


  auto rmw_email_node = new (std::nothrow) rmw_email_node_t;
  RET_ALLOC_X(rmw_email_node, return nullptr);
  auto cleanup_rmw_email_node = rcpputils::make_scope_exit(
    [rmw_email_node]() {
      delete rmw_email_node;
    });

  // Create node handle
  rmw_node_t * node = rmw_node_allocate();
  RET_ALLOC_X(node, return nullptr);
  auto cleanup_node = rcpputils::make_scope_exit(
    [node]() {
      rmw_free(const_cast<char *>(node->name));
      rmw_free(const_cast<char *>(node->namespace_));
      rmw_node_free(node);
    });

  // Set up node name
  node->name = static_cast<const char *>(rmw_allocate(sizeof(char) * strlen(name) + 1));
  RET_ALLOC_X(node->name, return nullptr);
  memcpy(const_cast<char *>(node->name), name, strlen(name) + 1);

  // Set up node namespace
  node->namespace_ =
    static_cast<const char *>(rmw_allocate(sizeof(char) * strlen(namespace_) + 1));
  RET_ALLOC_X(node->namespace_, return nullptr);
  memcpy(const_cast<char *>(node->namespace_), namespace_, strlen(namespace_) + 1);

  cleanup_rmw_email_node.cancel();
  cleanup_node.cancel();
  node->implementation_identifier = email_identifier;
  node->data = rmw_email_node;
  node->context = context;
  finalize_context.cancel();
  return node;
}

extern "C" rmw_ret_t rmw_destroy_node(rmw_node_t * node)
{
  rmw_ret_t result_ret = RMW_RET_OK;
  RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    node,
    node->implementation_identifier,
    email_identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  rmw_context_t * context = node->context;
  rcutils_allocator_t allocator = context->options.allocator;
  allocator.deallocate(const_cast<char *>(node->name), allocator.state);
  allocator.deallocate(const_cast<char *>(node->namespace_), allocator.state);
  allocator.deallocate(node, allocator.state);
  context->impl->fini();
  return result_ret;
}

extern "C" const rmw_guard_condition_t * rmw_node_get_graph_guard_condition(const rmw_node_t * node)
{
  RET_NULL_X(node, return nullptr);
  RET_WRONG_IMPLID_X(node, return nullptr);

  auto node_impl = static_cast<rmw_email_node_t *>(node->data);
  RET_NULL_X(node_impl, return nullptr);

  return node->context->impl->graph_guard_condition;
}
