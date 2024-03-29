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

#include <cassert>
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
#include "email/wait_set.hpp"

namespace email
{

std::pair<std::string, MessageInfo>
wait_for_message_with_info(
  Subscription * subscription,
  const std::chrono::milliseconds timeout)
{
  email::WaitSet waitset;
  waitset.add_subscription(subscription);
  const bool timedout = waitset.wait(timeout);
  assert(!timedout);
  static_cast<void>(timedout);

  return subscription->get_message_with_info().value();
}

std::pair<std::string, MessageInfo>
wait_for_message_with_info(
  std::shared_ptr<Subscription> subscription,
  const std::chrono::milliseconds timeout)
{
  return wait_for_message_with_info(subscription.get(), timeout);
}

std::string
wait_for_message(
  Subscription * subscription,
  const std::chrono::milliseconds timeout)
{
  return wait_for_message_with_info(subscription, timeout).first;
}

std::string
wait_for_message(
  std::shared_ptr<Subscription> subscription,
  const std::chrono::milliseconds timeout)
{
  return wait_for_message(subscription.get(), timeout);
}

std::pair<std::string, ServiceInfo>
wait_for_response_with_info(
  const SequenceNumber sequence_number,
  ServiceClient * client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  email::WaitSet waitset;
  waitset.add_client(client);
  const bool timedout = waitset.wait(timeout);
  assert(!timedout);
  static_cast<void>(timedout);

  return client->get_response_with_info(sequence_number).value();
}

std::pair<std::string, ServiceInfo>
wait_for_response_with_info(
  const SequenceNumber sequence_number,
  std::shared_ptr<ServiceClient> client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  return wait_for_response_with_info(sequence_number, client.get(), timeout);
}

std::string
wait_for_response(
  const SequenceNumber sequence_number,
  ServiceClient * client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  return wait_for_response_with_info(sequence_number, client, timeout).first;
}

std::string
wait_for_response(
  const SequenceNumber sequence_number,
  std::shared_ptr<ServiceClient> client,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  return wait_for_response(sequence_number, client.get(), timeout);
}

std::pair<struct ServiceRequest, ServiceInfo>
wait_for_request_with_info(
  ServiceServer * server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  email::WaitSet waitset;
  waitset.add_server(server);
  const bool timedout = waitset.wait(timeout);
  assert(!timedout);
  static_cast<void>(timedout);

  return server->get_request_with_info().value();
}

std::pair<struct ServiceRequest, ServiceInfo>
wait_for_request_with_info(
  std::shared_ptr<ServiceServer> server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  return wait_for_request_with_info(server.get(), timeout);
}

struct ServiceRequest
wait_for_request(
  ServiceServer * server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  return wait_for_request_with_info(server, timeout).first;
}

struct ServiceRequest
wait_for_request(
  std::shared_ptr<ServiceServer> server,
  const std::chrono::milliseconds timeout = std::chrono::milliseconds(-1))
{
  return wait_for_request(server.get(), timeout);
}

}  // namespace email
