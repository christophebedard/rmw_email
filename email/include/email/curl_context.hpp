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

#ifndef EMAIL__CURL_CONTEXT_HPP_
#define EMAIL__CURL_CONTEXT_HPP_

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <string>
#include <optional>

#include <curl/curl.h>

struct ProtocolConnectionInfo {
  // Protocol, i.e. <protocol>://
  std::string protocol;
  // Port
  int port;
};

struct UserConnectionInfo {
  // URL without the port or <protocol>://
  std::string url;
  // Username (i.e. email)
  std::string username;
  // Password
  std::string password;
};

class CurlContext {
public:
  explicit CurlContext(
    struct UserConnectionInfo user_info,
    struct ProtocolConnectionInfo protocol_info,
    bool debug = true)
  : user_info_(user_info),
    protocol_info_(protocol_info),
    debug_(debug)
  {
    full_url_ = protocol_info_.protocol + "://" + user_info_.url + ":" + std::to_string(protocol_info_.port) + "/";
  }
  CurlContext(const CurlContext &) = delete;
  virtual ~CurlContext() {}

  bool init()
  {
    handle_ = curl_easy_init();
    if (!handle_) {
      fprintf(stderr, "curl_easy_init() failed\n");
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

  void fini()
  {
    curl_easy_cleanup(handle_);
  }

  bool execute()
  {
    CURLcode res = curl_easy_perform(handle_);
    if (CURLE_OK != res) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      return false;
    }
    return true;
  }

  CURL * get_handle()
  {
    return handle_;
  }

  const std::string & get_full_url()
  {
    return full_url_;
  }

  struct UserConnectionInfo & get_user_info()
  {
    return user_info_;
  }

private:

  // virtual std::optional<std::string> execute(
  //   std::optional<std::string> url_options,
  //   std::optional<std::string> custom_request) = 0;

  CURL * handle_;
  struct UserConnectionInfo user_info_;
  struct ProtocolConnectionInfo protocol_info_;
  std::string full_url_;
  bool debug_;

};

#endif  // EMAIL__CURL_CONTEXT_HPP_
