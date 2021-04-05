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

#include <memory>
#include <mutex>
#include <string>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include "email/log.hpp"
#include "email/utils.hpp"

namespace email
{
namespace log
{

static std::mutex logger_mutex;
static std::shared_ptr<spdlog::logger> root_logger = nullptr;
static constexpr const char * ENV_VAR_LOG_LEVEL = "EMAIL_LOG_LEVEL";
static constexpr const char * ENV_VAR_LOG_LEVEL_DEFAULT = "info";

static
spdlog::level::level_enum
level_to_spdlog(const Level & level)
{
  switch (level) {
    case debug:
      return spdlog::level::level_enum::debug;
    case info:
      return spdlog::level::level_enum::info;
    case warn:
      return spdlog::level::level_enum::warn;
    case error:
      return spdlog::level::level_enum::err;
    case fatal:
      return spdlog::level::level_enum::critical;
    case off:  // fallthrough
    default:
      return spdlog::level::level_enum::off;
  }
}

static
Level
level_from_string(const std::string & level)
{
  if ("debug" == level) {
    return debug;
  }
  if ("info" == level) {
    return info;
  }
  if ("warn" == level) {
    return warn;
  }
  if ("error" == level) {
    return error;
  }
  if ("fatal" == level) {
    return fatal;
  }
  return off;
}

void
init()
{
  std::lock_guard<std::mutex> lock(logger_mutex);
  if (nullptr != root_logger) {
    return;
  }
  root_logger = spdlog::stdout_color_mt("root");
}

void
set_level(const Level & level)
{
  std::lock_guard<std::mutex> lock(logger_mutex);
  root_logger->set_level(level_to_spdlog(level));
}

void
set_level_from_env()
{
  const std::string env_log_level = utils::get_env_var_or_default(
    ENV_VAR_LOG_LEVEL,
    ENV_VAR_LOG_LEVEL_DEFAULT);
  set_level(level_from_string(env_log_level));
}

std::shared_ptr<spdlog::logger>
create(const std::string & name)
{
  std::lock_guard<std::mutex> lock(logger_mutex);
  auto & sinks = root_logger->sinks();
  auto logger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
  logger->set_level(root_logger->level());
  spdlog::register_logger(logger);
  return logger;
}

std::shared_ptr<Logger>
get_or_create(const std::string & name)
{
  std::shared_ptr<spdlog::logger> logger = spdlog::get(name);
  if (nullptr == logger) {
    logger = create(name);
  }
  return logger;
}

}  // namespace log
}  // namespace email
