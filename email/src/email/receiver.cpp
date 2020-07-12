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

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "email/curl/executor.hpp"
#include "email/email/receiver.hpp"
#include "email/email/response_utils.hpp"
#include "email/types.hpp"

namespace email
{

EmailReceiver::EmailReceiver(
  UserInfo::SharedPtrConst user_info,
  const bool debug)
: CurlExecutor(
    {user_info->host_imap, user_info->username, user_info->password},
    {"imaps", 993},
    debug),
  read_buffer_()
{}

EmailReceiver::~EmailReceiver() {}

size_t
EmailReceiver::write_callback(void * contents, size_t size, size_t nmemb, void * userp)
{
  (static_cast<std::string *>(userp))->append(static_cast<char *>(contents), size * nmemb);
  return size * nmemb;
}

bool
EmailReceiver::init_options()
{
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEDATA, static_cast<void *>(&read_buffer_));
  return true;
}

std::optional<struct EmailData>
EmailReceiver::get_email()
{
  if (!is_valid()) {
    std::cerr << "not initialized!" << std::endl;
    return std::nullopt;
  }

  std::optional<int> next_uid = get_nextuid();
  if (!next_uid) {
    return std::nullopt;
  }
  if (debug_) {
    std::cout << "nextuid=" << next_uid.value() << std::endl;
  }
  std::optional<struct EmailData> next_email = std::nullopt;
  // Try until we get an email
  while (!next_email) {
    next_email = get_email_from_uid(next_uid.value());
  }
  return next_email;
}

std::optional<struct EmailData>
EmailReceiver::get_email_from_uid(int uid)
{
  auto execute_result = execute("INBOX/;UID=" + std::to_string(uid), std::nullopt);
  if (!execute_result) {
    return std::nullopt;
  }
  return utils::response::get_email_data_from_response(execute_result.value());
}

std::optional<int>
EmailReceiver::get_nextuid()
{
  std::optional<std::string> response = execute(std::nullopt, "EXAMINE INBOX");
  if (!response) {
    return std::nullopt;
  }
  std::optional<int> next_uid = utils::response::get_nextuid_from_response(response.value());
  return next_uid;
}

std::optional<std::string>
EmailReceiver::execute(
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
  } else {
    // Unset the option in case it was set during a previous call
    curl_easy_setopt(context_.get_handle(), CURLOPT_CUSTOMREQUEST, NULL);
  }

  if (debug_) {
    std::cout << "[EXECUTE]:" << std::endl <<
      "\turl    : " << request_url << std::endl <<
      "\tcommand: " << (custom_request ? custom_request.value() : "") << std::endl;
  }

  if (!context_.execute()) {
    return std::nullopt;
  }
  if (debug_) {
    std::cout << "[RESPONSE]:" << std::endl << read_buffer_ << std::endl;
  }
  return read_buffer_;
}

}  // namespace email
