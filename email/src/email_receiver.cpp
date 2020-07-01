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

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <string>
#include <optional>

#include <curl/curl.h>

#include <email/email_receiver.hpp>

// Move to class?
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

EmailReceiver::EmailReceiver(
  struct email::UserConnectionInfo user_info,
  bool debug)
: context_(user_info, {"imaps", 993}, debug),
  debug_(debug)
{
  // Extract to method, because we need to check if it's successful
  context_.init();
}

EmailReceiver::~EmailReceiver()
{
  context_.fini();
}

std::optional<std::string> EmailReceiver::get_email()
{
  std::optional<std::string> response = execute(std::nullopt, "EXAMINE INBOX");
  return response;
}

std::optional<std::string> EmailReceiver::execute(
std::optional<std::string> url_options,
std::optional<std::string> custom_request)
{
  std::string request_url(context_.get_full_url());
  if (url_options) {
    request_url += url_options.value();
  }
  curl_easy_setopt(context_.get_handle(), CURLOPT_URL, request_url.c_str());
  if (custom_request) {
    curl_easy_setopt(context_.get_handle(), CURLOPT_CUSTOMREQUEST, custom_request.value().c_str());
  }

  if (debug_) {
    std::cout << "execute:" << std::endl <<
      "\turl    : " << request_url << std::endl <<
      "\tcommand: " << (custom_request ? custom_request.value() : "") << std::endl;
  }

  std::string buffer;
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEDATA, (void *)&buffer);

  if (!context_.execute()) {
    return std::nullopt;
  }
  return buffer;
}
