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

#include <string>

#include "email/service_client.hpp"
#include "email/service_info.hpp"
#include "email/service_request.hpp"
#include "email/service_server.hpp"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"

#include "rmw_email_cpp/conversion.hpp"
#include "rmw_email_cpp/gid.hpp"
#include "rmw_email_cpp/identifier.hpp"
#include "rmw_email_cpp/log.hpp"
#include "rmw_email_cpp/timestamp.hpp"
#include "rmw_email_cpp/types.hpp"

extern "C" rmw_ret_t rmw_send_request(
  const rmw_client_t * client,
  const void * ros_request,
  int64_t * sequence_id)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    client,
    client->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(ros_request, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(sequence_id, RMW_RET_INVALID_ARGUMENT);

  auto rmw_email_client = static_cast<rmw_email_client_t *>(client->data);
  email::ServiceClient * email_client = rmw_email_client->email_client;

  // Convert request to YAML string
  const std::string request =
    rmw_email_cpp::msg_to_yaml_service(&rmw_email_client->type_supports, ros_request, false);

  // Send request
  const auto sequence_number = email_client->send_request(request);
  *sequence_id = sequence_number;
  RMW_EMAIL_LOG_DEBUG("sent request with sequence number: %ld", *sequence_id);
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_take_request(
  const rmw_service_t * service,
  rmw_service_info_t * request_header,
  void * ros_request,
  bool * taken)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    service,
    service->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(request_header, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(ros_request, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

  auto rmw_email_server = static_cast<rmw_email_server_t *>(service->data);
  email::ServiceServer * email_server = rmw_email_server->email_server;

  // Take request and info
  rmw_ret_t ret = RMW_RET_OK;
  auto request_with_info_opt = email_server->get_request_with_info();
  if (!request_with_info_opt.has_value()) {
    *taken = false;
    RMW_EMAIL_LOG_DEBUG("taking request with info failed");
    return ret;
  }
  *taken = true;
  const auto [request, info] = request_with_info_opt.value();

  // Convert YAML string back to request
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (!rmw_email_cpp::yaml_to_msg_service(
      &rmw_email_server->type_supports, request.content, ros_request, &allocator, true))
  {
    ret = RMW_RET_ERROR;
  }

  // Copy info to request header
  request_header->request_id.sequence_number = request.id.sequence_number;
  rmw_email_cpp::copy_email_gid_to_writer_guid(
    request_header->request_id.writer_guid, info.client_gid());
  request_header->source_timestamp = rmw_email_cpp::convert_timestamp(info.source_timestamp());
  request_header->received_timestamp = rmw_email_cpp::convert_timestamp(info.received_timestamp());
  RMW_EMAIL_LOG_DEBUG("request taken with sequence number: %ld", request.id.sequence_number);
  return ret;
}
