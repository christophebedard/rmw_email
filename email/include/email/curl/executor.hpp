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

#ifndef EMAIL__CURL__EXECUTOR_HPP_
#define EMAIL__CURL__EXECUTOR_HPP_

#include "email/curl/context.hpp"
#include "email/types.hpp"

namespace email
{

/// Abstract class for executing commands using curl.
/**
 * Owns a curl context object for setting parameters before executing commands.
 */
class CurlExecutor
{
public:
  /// Initialize executor.
  /**
   * \return true if successful, false otherwise
   */
  bool
  init();

  /// Get validity status of the executor.
  /**
   * \param true if valid, false otherwise
   */
  bool
  is_valid() const;

protected:
  /// Constructor.
  /**
   * \param connection_info the connection info
   * \param protocol_info the protocol info
   * \param curl_verbose the curl verbose status
   */
  explicit CurlExecutor(
    const struct ConnectionInfo & connection_info,
    const struct ProtocolInfo & protocol_info,
    const bool curl_verbose);
  CurlExecutor(const CurlExecutor &) = delete;
  CurlExecutor & operator=(const CurlExecutor &) = delete;
  virtual ~CurlExecutor();

  /// Initialize concrete options.
  /**
   * Inheriting classes should implement this and initialize options specific to them.
   *
   * \return true if success, false otherwise
   */
  virtual
  bool
  init_options() = 0;

  CurlContext context_;

private:
  bool is_valid_;
};

}  // namespace email

#endif  // EMAIL__CURL__EXECUTOR_HPP_
