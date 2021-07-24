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

#include <curl/curl.h>

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/curl/context.hpp"
#include "email/log.hpp"
#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{

CurlContext::CurlContext(
  const struct ConnectionInfo & connection_info,
  const struct ProtocolInfo & protocol_info,
  const bool curl_verbose)
: logger_(log::get_or_create("CurlContext")),
  handle_(nullptr),
  connection_info_(connection_info),
  full_url_(
    utils::full_url(
      protocol_info.protocol,
      connection_info_.host,
      protocol_info.port)),
  curl_verbose_(curl_verbose)
{}

CurlContext::~CurlContext()
{
  logger_->debug("destroying");
}

bool
CurlContext::init()
{
  handle_ = curl_easy_init();
  if (!handle_) {
    logger_->critical("curl_easy_init() failed");
    return false;
  }
  // Validate some parameters first
  if (connection_info_.host.empty()) {
    logger_->critical("host not set for URL: {}", full_url_);
    return false;
  }
  curl_easy_setopt(handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(handle_, CURLOPT_USERNAME, connection_info_.username.c_str());
  curl_easy_setopt(handle_, CURLOPT_PASSWORD, connection_info_.password.c_str());
  if (curl_verbose_) {
    curl_easy_setopt(handle_, CURLOPT_VERBOSE, 1L);
  }
  logger_->debug("initialized");
  return true;
}

void
CurlContext::fini()
{
  curl_easy_cleanup(handle_);
  logger_->debug("finalized");
}

bool
CurlContext::execute()
{
  CURLcode res = curl_easy_perform(handle_);
  if (CURLE_OK != res) {
    // Some error codes are "expected," i.e. they're not real failures
    if (CURLE_REMOTE_FILE_NOT_FOUND != res) {
      logger_->error(
        "curl_easy_perform() failed: {}={}",
        static_cast<int>(res),
        curl_easy_strerror(res));
    }
    return false;
  }
  return true;
}

CURL *
CurlContext::get_handle() const
{
  return handle_;
}

const std::string &
CurlContext::get_full_url() const
{
  return full_url_;
}

const struct ConnectionInfo &
CurlContext::get_connection_info() const
{
  return connection_info_;
}

}  // namespace email
