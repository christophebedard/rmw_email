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

#ifndef EMAIL__CURL__CONTEXT_HPP_
#define EMAIL__CURL__CONTEXT_HPP_

#include <curl/curl.h>

#include <memory>
#include <string>

#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{

/// Basic context wrapper for curl.
/**
 * Wraps the init/fini functions.
 * Takes care of setting the common options.
 */
class CurlContext
{
public:
  /// Constructor.
  /**
   * \param connection_info the connection information
   * \param protocol_info the protocol information
   * \param curl_verbose the curl verbose status
   */
  explicit CurlContext(
    const struct ConnectionInfo & connection_info,
    const struct ProtocolInfo & protocol_info,
    const bool curl_verbose);

  ~CurlContext();

  /// Initialize context.
  /**
   * \return true if successful, false otherwise
   */
  bool
  init();

  /// Finalize context.
  void
  fini();

  /// Execute command.
  /**
   * The right command/params must have been set using the handle beforehand.
   *
   * \return true if successful, false otherwise
   */
  bool
  execute();

  /// Get the curl handle.
  /**
   * To be used for setting params before executing a command.
   *
   * \return the curl handle
   */
  CURL *
  get_handle() const;

  /// Get the full URL.
  /**
   * \return the full URL
   */
  const std::string &
  get_full_url() const;

  /// Get the connection info.
  /**
   * \return the connection info
   */
  const struct ConnectionInfo &
  get_connection_info() const;

private:
  EMAIL_DISABLE_COPY(CurlContext)

  std::shared_ptr<Logger> logger_;
  CURL * handle_;
  const struct ConnectionInfo connection_info_;
  const std::string full_url_;
  bool curl_verbose_;
};

}  // namespace email

#endif  // EMAIL__CURL__CONTEXT_HPP_
