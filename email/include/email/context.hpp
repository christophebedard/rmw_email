// Copyright 2020 Christophe Bedard
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

#ifndef EMAIL__CONTEXT_HPP_
#define EMAIL__CONTEXT_HPP_

#include <memory>
#include <stdexcept>
#include <string>

#include "email/curl/context.hpp"
#include "email/email/polling_manager.hpp"
#include "email/email/receiver.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/options.hpp"
#include "email/service_handler.hpp"
#include "email/subscription_handler.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Error when the context is not initialized.
class ContextNotInitializedError : public std::runtime_error
{
public:
  ContextNotInitializedError()
  : std::runtime_error("context not initialized")
  {}
};

/// Error when the context is already initialized.
class ContextAlreadyInitializedError : public std::runtime_error
{
public:
  ContextAlreadyInitializedError()
  : std::runtime_error("context already initialized")
  {}
};

/// Error when the context initialization fails.
class ContextInitFailedError : public std::runtime_error
{
public:
  ContextInitFailedError()
  : std::runtime_error("context init failed")
  {}
};

/// Context object with global resources.
/**
 * It gets initialized only once.
 * It owns global objects which get created & initialized when needed.
 */
class Context
{
public:
  /// Constructor.
  /**
   * Not to be used directly: use `get_global_context()` instead.
   */
  Context();
  Context(const Context &) = delete;
  Context & operator=(const Context &) = delete;
  ~Context();

  /// Initialize context using config file.
  /**
   * Shouldn't be called directly: use `email::init()` instead.
   *
   * \throw `ContextInitFailedError` if context initialization failed
   * \throw `ContextAlreadyInitializedError` if context is already intialized
   */
  void
  init();

  /// Initialize context using commandline arguments.
  /**
   * Shouldn't be called directly: use `email::init(argc, argv)` instead.
   *
   * \throw `ContextInitFailedError` if context initialization failed
   * \throw `ContextAlreadyInitializedError` if context is already intialized
   */
  void init(int argc, char const * const argv[]);

  /// Shut down context.
  /**
   * Shouldn't be called directly: use `email::shutdown()` instead.
   *
   * \return true if successful, false otherwise
   */
  bool shutdown();

  /// Get context validity status.
  /**
   * \return true if valid, false otherwise
   */
  bool
  is_valid() const;

  /// Get options.
  /**
   * \return the options
   * \throw `ContextNotInitializedError` if context has not been initialized
   */
  std::shared_ptr<Options>
  get_options() const;

  /// Get the email reception object.
  /**
   * Will have been initialized.
   *
   * \return the `EmailReceiver` object
   * \throw `ContextNotInitializedError` if context has not been initialized
   */
  std::shared_ptr<EmailReceiver>
  get_receiver() const;

  /// Get the email sender object.
  /**
   * Will have been initialized.
   *
   * \return the `EmailSender` object
   * \throw `ContextNotInitializedError` if context has not been initialized
   */
  std::shared_ptr<EmailSender>
  get_sender() const;

  /// Get the polling manager.
  /**
   * Will have been started.
   *
   * \return the `PollingManager` object
   * \throw `ContextNotInitializedError` if context has not been initialized
   */
  std::shared_ptr<PollingManager>
  get_polling_manager() const;

  /// Get the subscription handler.
  /**
   * \return the `SubscriptionHandler` object
   * \throw `ContextNotInitializedError` if context has not been initialized
   */
  std::shared_ptr<SubscriptionHandler>
  get_subscription_handler() const;

  /// Get the service handler.
  /**
   * \return the `ServiceHandler` object
   * \throw `ContextNotInitializedError` if context has not been initialized
   */
  std::shared_ptr<ServiceHandler>
  get_service_handler() const;

private:
  /// Perform common init tasks.
  void
  init_common();

  std::shared_ptr<Logger> logger_;
  std::shared_ptr<Options> options_;
  bool is_valid_;
  mutable bool is_receiver_init_;
  mutable bool is_polling_manager_init_;
};

/// Get the global context.
/**
 * \return the global context, which should have been initialized using `email::init(*)`
 */
std::shared_ptr<Context>
get_global_context();

}  // namespace email

#endif  // EMAIL__CONTEXT_HPP_
