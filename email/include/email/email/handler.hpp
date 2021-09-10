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

#ifndef EMAIL__EMAIL__HANDLER_HPP_
#define EMAIL__EMAIL__HANDLER_HPP_

#include "email/email/info.hpp"

namespace email
{

/// Generic email handler.
/**
 * Gets new emails and handles them by conditionally passing them on.
 */
class EmailHandler
{
public:
  /// Register this handler.
  /**
   * Registers this handler so that it is called with new emails.
   * To be called after creation.
   */
  virtual
  void
  register_handler() = 0;

  /// Handle new email.
  /**
   * To be called by the `PollingManager`.
   *
   * \param data the new email data
   */
  virtual
  void
  handle(const struct EmailData & data) = 0;

protected:
  /// Constructor.
  EmailHandler();

  virtual ~EmailHandler();
};

}  // namespace email

#endif  // EMAIL__EMAIL__HANDLER_HPP_
