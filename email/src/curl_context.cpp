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

#include <iostream>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/curl_context.hpp"
#include "email/types.hpp"

namespace email
{

CurlContext::CurlContext(
  const struct UserInfo & user_info,
  const struct ProtocolInfo & protocol_info,
  const bool debug)
: handle_(nullptr),
  user_info_(user_info),
  protocol_info_(protocol_info),
  debug_(debug)
{
  full_url_ = protocol_info_.protocol + "://" +
    user_info_.url + ":" + std::to_string(protocol_info_.port) + "/";
}
CurlContext::~CurlContext() {}

bool CurlContext::init()
{
  handle_ = curl_easy_init();
  if (!handle_) {
    std::cerr << "curl_easy_init() failed" << std::endl;
    return false;
  }
  curl_easy_setopt(handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(handle_, CURLOPT_USERNAME, user_info_.username.c_str());
  curl_easy_setopt(handle_, CURLOPT_PASSWORD, user_info_.password.c_str());
  if (debug_) {
    curl_easy_setopt(handle_, CURLOPT_VERBOSE, 1L);
  }
  return true;
}

void CurlContext::fini()
{
  curl_easy_cleanup(handle_);
}

bool CurlContext::execute()
{
  CURLcode res = curl_easy_perform(handle_);
  if (CURLE_OK != res) {
    // Some error codes are "expected," i.e. they're not real failures
    if (debug_ || CURLE_REMOTE_FILE_NOT_FOUND != res) {
      std::cerr << "curl_easy_perform() failed: " << static_cast<int>(res) <<
        "=" << curl_easy_strerror(res) << std::endl;
    }
    return false;
  }
  return true;
}

}  // namespace email
