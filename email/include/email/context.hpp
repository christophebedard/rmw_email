// Copyright 2020-2021 Christophe Bedard
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
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <stdexcept>
#include <string>

#include "email/curl/context.hpp"
#include "email/email/info.hpp"
#include "email/email/polling_manager.hpp"
#include "email/email/receiver.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/options.hpp"
#include "email/service_handler.hpp"
#include "email/subscription_handler.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Generic context error.
class ContextError : public std::runtime_error
{
public:
  explicit ContextError(const std::string & msg)
  : std::runtime_error(msg)
  {}
};

/// Error when the context is not initialized.
class ContextNotInitializedError : public ContextError
{
public:
  ContextNotInitializedError()
  : ContextError("context not initialized")
  {}
};

/// Error when the context is already initialized.
class ContextAlreadyInitializedError : public ContextError
{
public:
  ContextAlreadyInitializedError()
  : ContextError("context already initialized")
  {}
};

/// Error when the context initialization fails.
class ContextInitFailedError : public ContextError
{
public:
  explicit ContextInitFailedError(std::optional<std::string> reason = std::nullopt)
  : ContextError("context init failed: " + reason.value_or("(unknown)"))
  {}
};

/// Context object with global resources.
/**
 * It gets initialized only once.
 * It owns global objects which get created & initialized.
 */
class Context
{
public:
  /// Constructor.
  /**
   * Not to be used directly: use `get_global_context()` instead.
   */
  Context();

  ~Context();

  /// Initialize context using config file.
  /**
   * Shouldn't be called directly: use `email::init()` instead.
   *
   * \throw ContextInitFailedError if context initialization failed
   * \throw ContextAlreadyInitializedError if context is already intialized
   */
  void
  init();

  /// Initialize context using commandline arguments.
  /**
   * Shouldn't be called directly: use `email::init(argc, argv)` instead.
   *
   * The process will exit with error code 1 if parsing of CLI options fails.
   *
   * \throw ContextInitFailedError if context initialization failed
   * \throw ContextAlreadyInitializedError if context is already intialized
   */
  void init(int argc, char const * const argv[]);

  /// Shut down context.
  /**
   * This should be called at the end before context destruction.
   * However, it shouldn't be called directly: use `email::shutdown()` instead.
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
   * \throw ContextNotInitializedError if context has not been initialized
   */
  EMAIL_PUBLIC
  std::shared_ptr<Options>
  get_options() const;

  /// Get the email reception object.
  /**
   * Will have been initialized.
   *
   * \return the `EmailReceiver` object
   * \throw ContextNotInitializedError if context has not been initialized
   */
  std::shared_ptr<EmailReceiver>
  get_receiver() const;

  /// Get the email sender object.
  /**
   * Will have been initialized.
   *
   * \return the `EmailSender` object
   * \throw ContextNotInitializedError if context has not been initialized
   */
  std::shared_ptr<EmailSender>
  get_sender() const;

  /// Get the polling manager.
  /**
   * Will have been started.
   *
   * \return the `PollingManager` object
   * \throw ContextNotInitializedError if context has not been initialized
   */
  std::shared_ptr<PollingManager>
  get_polling_manager() const;

  /// Get the subscription handler.
  /**
   * \return the `SubscriptionHandler` object
   * \throw ContextNotInitializedError if context has not been initialized
   */
  std::shared_ptr<SubscriptionHandler>
  get_subscription_handler() const;

  /// Get the service handler.
  /**
   * \return the `ServiceHandler` object
   * \throw ContextNotInitializedError if context has not been initialized
   */
  std::shared_ptr<ServiceHandler>
  get_service_handler() const;

private:
  EMAIL_DISABLE_COPY(Context)

  /// Perform common init tasks.
  void
  init_common();

  bool is_valid_;
  std::shared_ptr<Options> options_;
  std::shared_ptr<Logger> logger_;
  std::shared_ptr<EmailReceiver> receiver_;
  std::shared_ptr<EmailSender> sender_;
  std::shared_ptr<PollingManager> polling_manager_;
  std::shared_ptr<SubscriptionHandler> subscription_handler_;
  std::shared_ptr<ServiceHandler> service_handler_;
};

/// Get the global context.
/**
 * \return the global context, which should have been initialized using `email::init(*)`
 */
EMAIL_PUBLIC
std::shared_ptr<Context>
get_global_context();

}  // namespace email

#endif  // EMAIL__CONTEXT_HPP_
