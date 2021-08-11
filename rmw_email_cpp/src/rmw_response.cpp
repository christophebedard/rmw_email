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

extern "C" rmw_ret_t rmw_send_response(
  const rmw_service_t * service,
  rmw_request_id_t * request_header,
  void * ros_response)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(service, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    service,
    service->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(request_header, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(ros_response, RMW_RET_INVALID_ARGUMENT);

  auto rmw_email_server = static_cast<rmw_email_server_t *>(service->data);
  email::ServiceServer * email_server = rmw_email_server->email_server;

  // Convert response to YAML string
  const std::string response =
    rmw_email_cpp::msg_to_yaml_service(&rmw_email_server->type_supports, ros_response, true);

  // Convert request header to request ID
  const email::Gid client_gid =
    rmw_email_cpp::convert_writer_guid_to_email_gid(request_header->writer_guid);
  const struct email::ServiceRequestId request_id(request_header->sequence_number, client_gid);

  // And send both
  RMW_EMAIL_LOG_DEBUG(
    "sending response with sequence number: %ld", request_header->sequence_number);
  email_server->send_response(request_id, response);
  return RMW_RET_OK;
}

extern "C" rmw_ret_t rmw_take_response(
  const rmw_client_t * client,
  rmw_service_info_t * response_header,
  void * ros_response,
  bool * taken)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(client, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    client,
    client->implementation_identifier,
    rmw_email_cpp::identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(response_header, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(ros_response, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

  auto rmw_email_client = static_cast<rmw_email_client_t *>(client->data);
  email::ServiceClient * email_client = rmw_email_client->email_client;

  // Take response and info using the sequence number from the request header
  rmw_ret_t ret = RMW_RET_OK;
  RMW_EMAIL_LOG_DEBUG("taking response with info");
  auto response_with_info_opt = email_client->get_response_with_info();
  if (!response_with_info_opt.has_value()) {
    *taken = false;
    RMW_EMAIL_LOG_DEBUG("taking response with info failed");
    return ret;
  }
  *taken = true;
  auto response_with_info = response_with_info_opt.value();
  const std::string response = response_with_info.first;
  const email::ServiceInfo info = response_with_info.second;

  // Convert YAML string back to response
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (!rmw_email_cpp::yaml_to_msg_service(
      &rmw_email_client->type_supports, response, ros_response, &allocator, false))
  {
    ret = RMW_RET_ERROR;
  }

  // Copy info to response header
  response_header->request_id.sequence_number = info.sequence_number();
  rmw_email_cpp::copy_email_gid_to_writer_guid(
    response_header->request_id.writer_guid, info.client_gid());
  response_header->source_timestamp = rmw_email_cpp::convert_timestamp(info.source_timestamp());
  response_header->received_timestamp = rmw_email_cpp::convert_timestamp(info.received_timestamp());
  return ret;
}
