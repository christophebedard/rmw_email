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

#include <mutex>

#include "email/init.hpp"
#include "rcutils/error_handling.h"
#include "rcutils/strdup.h"
#include "rcpputils/scope_exit.hpp"
#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rmw_email_cpp/guard_condition.hpp"
#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/log.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_ret_t rmw_init_options_init(
  rmw_init_options_t * init_options,
  rcutils_allocator_t allocator)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(init_options, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ALLOCATOR(&allocator, return RMW_RET_INVALID_ARGUMENT);
  if (NULL != init_options->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected zero-initialized init_options");
    return RMW_RET_INVALID_ARGUMENT;
  }
  init_options->instance_id = 0;
  init_options->implementation_identifier = rmw_email_cpp::identifier;
  init_options->allocator = allocator;
  init_options->impl = nullptr;
  init_options->localhost_only = RMW_LOCALHOST_ONLY_DEFAULT;
  init_options->domain_id = RMW_DEFAULT_DOMAIN_ID;
  init_options->enclave = NULL;
  init_options->security_options = rmw_get_zero_initialized_security_options();
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_init_options_copy(const rmw_init_options_t * src, rmw_init_options_t * dst)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(src, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(dst, RMW_RET_INVALID_ARGUMENT);
  if (NULL == src->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected initialized dst");
    return RMW_RET_INVALID_ARGUMENT;
  }
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    src,
    src->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  if (NULL != dst->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected zero-initialized dst");
    return RMW_RET_INVALID_ARGUMENT;
  }
  const rcutils_allocator_t * allocator = &src->allocator;

  rmw_init_options_t tmp = *src;
  tmp.enclave = rcutils_strdup(tmp.enclave, *allocator);
  if (NULL != src->enclave && NULL == tmp.enclave) {
    return RMW_RET_BAD_ALLOC;
  }
  tmp.security_options = rmw_get_zero_initialized_security_options();
  rmw_ret_t ret =
    rmw_security_options_copy(&src->security_options, allocator, &tmp.security_options);
  if (RMW_RET_OK != ret) {
    allocator->deallocate(tmp.enclave, allocator->state);
    return ret;
  }
  *dst = tmp;
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_init_options_fini(rmw_init_options_t * init_options)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(init_options, RMW_RET_INVALID_ARGUMENT);
  if (NULL == init_options->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected initialized init_options");
    return RMW_RET_INVALID_ARGUMENT;
  }
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    init_options,
    init_options->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  rcutils_allocator_t * allocator = &init_options->allocator;
  RCUTILS_CHECK_ALLOCATOR(allocator, return RMW_RET_INVALID_ARGUMENT);
  allocator->deallocate(init_options->enclave, allocator->state);
  rmw_ret_t ret = rmw_security_options_fini(&init_options->security_options, allocator);
  *init_options = rmw_get_zero_initialized_init_options();
  return ret;
}

rmw_context_impl_s::rmw_context_impl_s()
{
  RMW_EMAIL_LOG_DEBUG("initializing context implementation");
}

rmw_context_impl_s::~rmw_context_impl_s()
{
  RMW_EMAIL_LOG_DEBUG("shutting down context implementation");
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

rmw_ret_t
rmw_context_impl_s::init(rmw_init_options_t * options, size_t domain_id)
{
  static_cast<void>(options);
  // There's no concept of "domain" with email, duh
  static_cast<void>(domain_id);

  // If this isn't the first node, just increment the node counter;
  // we only do the rest if this was the first node
  std::scoped_lock<std::mutex> lock(mutex_initialization);
  if (0u != this->node_count) {
    this->node_count++;
    return RMW_RET_OK;
  }

  // TODO(christophebedard) move to graph cache handler
  this->graph_guard_condition = rmw_email_cpp::create_guard_condition();
  if (nullptr == this->graph_guard_condition) {
    cleanup();
    return RMW_RET_BAD_ALLOC;
  }

  // Init middleware
  try {
    email::init();
  } catch (const std::runtime_error & e) {
    RMW_SET_ERROR_MSG(e.what());
    cleanup();
    return RMW_RET_ERROR;
  }

  this->node_count++;
  return RMW_RET_OK;
}

rmw_ret_t
rmw_context_impl_s::fini()
{
  std::scoped_lock<std::mutex> lock(mutex_initialization);
  if (0u != --this->node_count) {
    return RMW_RET_OK;
  }

  cleanup();
  return RMW_RET_OK;
}

void
rmw_context_impl_s::cleanup()
{
  if (this->graph_guard_condition) {
    rmw_email_cpp::destroy_guard_condition(this->graph_guard_condition);
  }
}

extern "C" rmw_ret_t rmw_init(const rmw_init_options_t * options, rmw_context_t * context)
{
  rmw_ret_t ret;

  // Check args
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(options, RMW_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(context, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    options->implementation_identifier,
    "expected initialized init options",
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    options,
    options->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    options->enclave,
    "expected non-null enclave",
    return RMW_RET_INVALID_ARGUMENT);
  if (NULL != context->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected a zero-initialized context");
    return RMW_RET_INVALID_ARGUMENT;
  }

  auto restore_context = rcpputils::make_scope_exit(
    [context]() {*context = rmw_get_zero_initialized_context();});

  context->instance_id = options->instance_id;
  context->implementation_identifier = rmw_email_cpp::identifier;
  // Domain ID isn't used
  context->actual_domain_id = 0u;

  context->impl = new (std::nothrow) rmw_context_impl_t();
  if (nullptr == context->impl) {
    RMW_SET_ERROR_MSG("failed to allocate context impl");
    return RMW_RET_BAD_ALLOC;
  }
  auto cleanup_impl = rcpputils::make_scope_exit(
    [context]() {delete context->impl;});

  if ((ret = rmw_init_options_copy(options, &context->options)) != RMW_RET_OK) {
    return ret;
  }

  cleanup_impl.cancel();
  restore_context.cancel();
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_shutdown(rmw_context_t * context)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(context, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    context->impl,
    "expected initialized context",
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    context,
    context->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  context->impl->is_shutdown = true;
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_context_fini(rmw_context_t * context)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(context, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_FOR_NULL_WITH_MSG(
    context->impl,
    "expected initialized context",
    return RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    context,
    context->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  if (!context->impl->is_shutdown) {
    RMW_SET_ERROR_MSG("context has not been shutdown");
    return RMW_RET_INVALID_ARGUMENT;
  }

  rmw_ret_t ret = rmw_init_options_fini(&context->options);
  // Will destroy the context implementation object and call shutdown() on the middleware
  delete context->impl;
  *context = rmw_get_zero_initialized_context();
  return ret;
}
