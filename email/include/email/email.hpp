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

/** \mainpage `email`: email-based middleware
 *
 * `email` is a publish/subscribe middleware that uses emails to exchange string messages.
 * It also supports request/response communication.
 *
 * It consists of these main components:
 *
 * - `email` initialization/shutdown
 *   - email::init()
 *   - email::shutdown()
 *   - email/init.hpp
 * - Publisher
 *   - email::Publisher
 *   - email/publisher.hpp
 * - Subscription
 *   - email::Subscription
 *   - email/subscription.hpp
 * - Service Client
 *   - email::ServiceClient
 *   - email/service_client.hpp
 * - Service Server
 *   - email::ServiceServer
 *   - email/service_server.hpp
 *
 * Along with the main components, there are some useful data containers:
 *
 * - Message Info
 *   - email::MessageInfo
 *   - email/message_info.hpp
 * - Service Request
 *   - email::ServiceRequest
 *   - email::ServiceInfo
 *   - email/service_request.hpp
 *   - email/service_info.hpp
 * - GID
 *   - email::Gid
 *   - email/gid.hpp
 * - Timestamp
 *   - email::Timestamp
 *   - email/timestamp.hpp
 *
 * There's also some waiting- and time-related utilities:
 *
 * - Guard Condition
 *   - email::GuardCondition
 *   - email/guard_condition.hpp
 * - Wait Set
 *   - email::WaitSet
 *   - email/wait_set.hpp
 * - Wait-related utilities
 *   - email::wait_for_message()
 *   - email::wait_for_message_with_info()
 *   - email::wait_for_request()
 *   - email::wait_for_request_with_info()
 *   - email::wait_for_response()
 *   - email::wait_for_response_with_info()
 *   - email/wait.hpp
 *
 * Finally, there is a logging component:
 *
 * - Logging
 *   - email::log::create()
 *   - email::log::get_or_create()
 *   - email/log.hpp
 *
 * The remaining headers/components are internal APIs and utilities:
 *
 * - Context
 *   - email/context.hpp
 * - Curl interface
 *   - email/curl/context.hpp
 *   - email/curl/executor.hpp
 *   - email/curl/info.hpp
 * - Email interface
 *   - email/email/curl_receiver.hpp
 *   - email/email/curl_sender.hpp
 *   - email/email/info.hpp
 *   - email/email/intra_receiver.hpp
 *   - email/email/intra_sender.hpp
 *   - email/email/payload_utils.hpp
 *   - email/email/receiver.hpp
 *   - email/email/response_utils.hpp
 *   - email/email/sender.hpp
 * - Internal handling of new emails/messages
 *   - email/email/handler.hpp
 *   - email/email/polling_manager.hpp
 *   - email/subscription_handler.hpp
 *   - email/service_handler.hpp
 * - Interfaces and base classes
 *   - email/communication_info.hpp
 *   - email/gid_object.hpp
 *   - email/named_object.hpp
 *   - email/pub_sub.hpp
 *   - email/service.hpp
 * - Options
 *   - email/options.hpp
 * - Containers
 *   - email/safe_map.hpp
 *   - email/safe_queue.hpp
 * - Utilities
 *   - email/utils.hpp
 * - Macros
 *   - email/macros.hpp
 *   - email/visibility_control.hpp
 */

#ifndef EMAIL__EMAIL_HPP_
#define EMAIL__EMAIL_HPP_

#include "email/init.hpp"
#include "email/publisher.hpp"
#include "email/service_client.hpp"
#include "email/service_server.hpp"
#include "email/subscription.hpp"
#include "email/wait.hpp"
#include "email/wait_set.hpp"

#endif  // EMAIL__EMAIL_HPP_
