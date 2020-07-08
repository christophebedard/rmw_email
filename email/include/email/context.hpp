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
#include <string>

#include "email/curl/context.hpp"
#include "email/email/receiver.hpp"
#include "email/email/sender.hpp"
#include "email/options.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Context object with global resources.
/**
 * It gets initialized only once.
 * It owns global objects which get created & initialized when needed.
 */
class Context
{
public:
  Context();
  Context(const Context &) = delete;
  ~Context();

  /// Initialize context using config file.
  /**
   * Shouldn't be called directly: use `email::init()` instead.
   *
   * \throw `std::runtime_error` if context initialization failed
   * \throw `std::runtime_error` if context is already intialized
   */
  void
  init();

  /// Initialize context using commandline arguments.
  /**
   * Shouldn't be called directly: use `email::init(argc, argv)` instead.
   *
   * \throw `std::runtime_error` if context initialization failed
   * \throw `std::runtime_error` if context is already intialized
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
   * \throw `std::runtime_error` if context has not been initialized
   */
  std::shared_ptr<Options>
  get_options() const;

  /// Get the email reception object.
  /**
   * Will have been initialized.
   *
   * \return the `EmailReceiver` object
   * \throw `std::runtime_error` if context has not been initialized
   */
  std::shared_ptr<EmailReceiver>
  get_receiver() const;

  /// Get the email sender object.
  /**
   * Will have been initialized.
   *
   * \return the `EmailSender` object
   * \throw `std::runtime_error` if context has not been initialized
   */
  std::shared_ptr<EmailSender>
  get_sender() const;

private:
  std::shared_ptr<Options> options_;
  bool is_valid_;
};

/// Get the global context.
/**
 * \return the global context, which should have been initialized using `email::init(*)`
 */
std::shared_ptr<Context>
get_global_context();

}  // namespace email

#endif  // EMAIL__CONTEXT_HPP_
