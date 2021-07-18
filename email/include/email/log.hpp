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

#ifndef EMAIL__LOG_HPP_
#define EMAIL__LOG_HPP_

#include <memory>
#include <stdexcept>
#include <string>

#include "rcpputils/filesystem_helper.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "yaml-cpp/yaml.h"

#include "email/utils.hpp"

namespace email
{

/// Abstract away the logger implementation.
using Logger = spdlog::logger;

namespace log
{

/// Generic logging error.
class LoggingError : public std::runtime_error
{
public:
  explicit LoggingError(const std::string & msg)
  : std::runtime_error(msg)
  {}
};

/// Error when logging is not initialized.
class LoggingNotInitializedError : public LoggingError
{
public:
  LoggingNotInitializedError()
  : LoggingError("logging not initialized")
  {}
};

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

/// Initialize logging.
/**
 * \param level the console logging level
 * \throw `LoggingAlreadyInitializedError` if logging is already intialized
 */
void
init(const Level & level);

/// Initialize logging using environment variable value for the logging level.
/**
 * \throw `LoggingAlreadyInitializedError` if logging is already intialized
 */
void
init_from_env();

/// Create logger from the root logger.
/**
 * Uses sink(s) and log level from the root logger.
 *
 * Will initialize logging from environment if not initialized.
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
 * Will initialize logging from environment if not initialized.
 *
 * \param name the name of the logger
 * \return the logger
 */
std::shared_ptr<Logger>
get_or_create(const std::string & name);

/// Remove an existing logger.
/**
 * \param name the logger
 * \throw `LoggingNotInitializedError` if logging is not intialized
 */
void
remove(const std::shared_ptr<Logger> & logger);

/// Shutdown and finalize.
void
shutdown();

}  // namespace log
}  // namespace email

/// Formatting for rcpputils::fs::path objects.
template<>
struct fmt::formatter<rcpputils::fs::path>: formatter<string_view>
{
  template<typename FormatContext>
  auto format(const rcpputils::fs::path & p, FormatContext & ctx)
  {
    return formatter<string_view>::format(p.string(), ctx);
  }
};

/// Formatting for YAML::Node objects.
template<>
struct fmt::formatter<YAML::Node>: formatter<string_view>
{
  template<typename FormatContext>
  auto format(const YAML::Node & node, FormatContext & ctx)
  {
    return formatter<string_view>::format(email::utils::yaml_to_string(node), ctx);
  }
};

#endif  // EMAIL__LOG_HPP_
