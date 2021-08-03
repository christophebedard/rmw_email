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

#ifndef EMAIL__WAIT_HPP_
#define EMAIL__WAIT_HPP_

#include <chrono>
#include <memory>
#include <string>
#include <utility>

#include "email/message_info.hpp"
#include "email/service_client.hpp"
#include "email/service_info.hpp"
#include "email/service_request.hpp"
#include "email/service_server.hpp"
#include "email/subscription.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Get a message with info from a subscription, waiting until one is available.
/**
 * For the meaning of the timeout parameter, see `WaitSet::wait`.
 *
 * \param subscription the subscription
 * \param timeout the timeout
 * \return the message & message info pair
 * \see WaitSet::wait()
 */
EMAIL_PUBLIC
std::pair<std::string, MessageInfo>
wait_for_message_with_info(
  Subscription * subscription,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a message with info from a subscription, waiting until one is available.
/**
 * \see wait_for_message(std::shared_ptr<Subscription>, const std::chrono::milliseconds)
 */
EMAIL_PUBLIC
std::pair<std::string, MessageInfo>
wait_for_message_with_info(
  std::shared_ptr<Subscription> subscription,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a message from a subscription, waiting until one is available.
/**
 * For the meaning of the timeout parameter, see `WaitSet::wait`.
 *
 * \param subscription the subscription
 * \param timeout the timeout
 * \return the message
 * \see WaitSet::wait()
 */
EMAIL_PUBLIC
std::string
wait_for_message(
  Subscription * subscription,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a message from a subscription, waiting until one is available.
/**
 * \see wait_for_message(std::shared_ptr<Subscription>, const std::chrono::milliseconds)
 */
EMAIL_PUBLIC
std::string
wait_for_message(
  std::shared_ptr<Subscription> subscription,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service reponse with info, waiting until it is available.
/**
 * For the meaning of the timeout parameter, see `WaitSet::wait`.
 *
 * \param sequence_number the request sequence number
 * \param client the service client
 * \param timeout the timeout
 * \return the response with info
 */
EMAIL_PUBLIC
std::pair<std::string, ServiceInfo>
wait_for_response_with_info(
  const SequenceNumber sequence_number,
  ServiceClient * client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service reponse with info, waiting until it is available.
/**
 * \see wait_for_response_with_info(
 *    const SequenceNumber, ServiceClient *, const std::chrono::milliseconds)
 */
EMAIL_PUBLIC
std::string
wait_for_response_with_info(
  const SequenceNumber sequence_number,
  std::shared_ptr<ServiceClient> client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service reponse, waiting until it is available.
/**
 * For the meaning of the timeout parameter, see `WaitSet::wait`.
 *
 * \param sequence_number the request sequence number
 * \param client the service client
 * \param timeout the timeout
 * \return the response
 */
EMAIL_PUBLIC
std::string
wait_for_response(
  const SequenceNumber sequence_number,
  ServiceClient * client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service reponse, waiting until it is available.
/**
 * \see wait_for_response(const SequenceNumber, ServiceClient *, const std::chrono::milliseconds)
 */
EMAIL_PUBLIC
std::string
wait_for_response(
  const SequenceNumber sequence_number,
  std::shared_ptr<ServiceClient> client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service request with info, waiting until one is available.
/**
 * For the meaning of the timeout parameter, see `WaitSet::wait`.
 *
 * \param server the server
 * \param timeout the timeout
 * \return the service request with info
 */
EMAIL_PUBLIC
std::pair<struct ServiceRequest, ServiceInfo>
wait_for_request_with_info(
  ServiceServer * server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service request, waiting until one is available.
/**
 * \see wait_for_request_with_info(ServiceServer *, const std::chrono::milliseconds)
 */
EMAIL_PUBLIC
std::pair<struct ServiceRequest, ServiceInfo>
wait_for_request_with_info(
  std::shared_ptr<ServiceServer> server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service request, waiting until one is available.
/**
 * For the meaning of the timeout parameter, see `WaitSet::wait`.
 *
 * \param server the server
 * \param timeout the timeout
 * \return the service request
 */
EMAIL_PUBLIC
struct ServiceRequest
wait_for_request(
  ServiceServer * server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

/// Get a service request, waiting until one is available.
/**
 * \see wait_for_request(ServiceServer *, const std::chrono::milliseconds)
 */
EMAIL_PUBLIC
struct ServiceRequest
wait_for_request(
  std::shared_ptr<ServiceServer> server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1));

}  // namespace email

#endif  // EMAIL__WAIT_HPP_
