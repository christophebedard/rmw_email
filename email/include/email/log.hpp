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

#ifndef EMAIL__LOG_HPP_
#define EMAIL__LOG_HPP_

#include <memory>
#include <string>

#include "spdlog/spdlog.h"

namespace email
{

/// Abstract away the logger implementation.
using Logger = spdlog::logger;

namespace log
{

/// Initialize logging.
void
init();

/// Logging level.
enum Level
{
  debug,
  info,
  warn,
  error,
  fatal,
  off
};

/// Set global logging level.
/**
 * \param level the logging level
 */
void
set_level(Level level);

/// Set global logging level from environment variable value.
void
set_level_from_env();

/// Create logger from the root logger.
/**
 * Uses sink(s) and log level from the root logger.
 *
 * \param name the name of the logger
 * \return the logger
 */
std::shared_ptr<Logger>
create(const std::string & name);

/// Get an existing logger or create it from the root logger.
/**
 * Useful for sharing a logger.
 *
 * \param name the name of the logger
 * \return the logger
 */
std::shared_ptr<Logger>
get_or_create(const std::string & name);

}  // namespace log
}  // namespace email

#endif  // EMAIL__LOG_HPP_
