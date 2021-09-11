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

#include <gtest/gtest.h>

#include <memory>

#include "email/gid.hpp"
#include "email/service_handler.hpp"
#include "email/subscription_handler.hpp"

TEST(TestHandlers, service_handler_fail)
{
  auto service_handler = std::make_shared<email::ServiceHandler>();

  // Register service client & server without having registered the service handler itself
  auto client_gid = email::Gid::new_gid();
  auto client_response_map = std::make_shared<email::ServiceHandler::ResponseMap>();
  EXPECT_DEATH(
    service_handler->register_service_client(client_gid, client_response_map),
    "Assertion .* failed");

  auto server_request_queue = std::make_shared<email::ServiceHandler::RequestQueue>();
  EXPECT_DEATH(
    service_handler->register_service_server("/my_service", server_request_queue),
    "Assertion .* failed");
}

TEST(TestHandlers, subscription_handler_fail)
{
  auto subscription_handler = std::make_shared<email::SubscriptionHandler>();

  // Register subscription without having registered the subscription handler itself
  auto message_queue = std::make_shared<email::SubscriptionHandler::MessageQueue>();
  EXPECT_DEATH(
    subscription_handler->register_subscription("/my_topic", message_queue),
    "Assertion .* failed");
}
