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

#include <curl/curl.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>
#include <thread>

#include "spdlog/fmt/bundled/chrono.h"

#include "email/curl/executor.hpp"
#include "email/email/curl_receiver.hpp"
#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/email/response_utils.hpp"
#include "email/log.hpp"

namespace email
{

CurlEmailReceiver::CurlEmailReceiver(
  UserInfo::SharedPtrConst user_info,
  const bool curl_verbose)
: EmailReceiver(),
  CurlExecutor(
    {user_info->host_imap, user_info->username, user_info->password},
    {"imaps", 993},
    curl_verbose),
  current_uid_(-1),
  next_uid_(-1),
  read_buffer_()
{}

CurlEmailReceiver::~CurlEmailReceiver()
{
  logger_->debug("destroying");
}

size_t
CurlEmailReceiver::write_callback(void * contents, size_t size, size_t nmemb, void * userp)
{
  (static_cast<std::string *>(userp))->append(static_cast<char *>(contents), size * nmemb);
  return size * nmemb;
}

bool
CurlEmailReceiver::init_options()
{
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEDATA, static_cast<void *>(&read_buffer_));
  return true;
}

std::optional<struct EmailData>
CurlEmailReceiver::get_email(std::optional<std::chrono::nanoseconds> polling_period)
{
  if (!is_valid()) {
    logger_->warn("not initialized!");
    return std::nullopt;
  }
  std::chrono::nanoseconds period = polling_period.value_or(std::chrono::nanoseconds(0));
  logger_->debug("polling: period={}", period);
  // Update next UID
  std::optional<int> next_uid = get_nextuid();
  if (!next_uid) {
    logger_->error("could not get next UID");
    return std::nullopt;
  }
  next_uid_ = next_uid.value();
  // Initalize current UID pointer if needed
  if (0 > current_uid_) {
    current_uid_ = next_uid_;
  }
  logger_->debug("current_uid={}", current_uid_);
  logger_->debug("next_uid   ={}", next_uid_);
  // Try until we get an email or until we have to stop
  std::optional<struct EmailData> next_email = std::nullopt;
  std::chrono::steady_clock::time_point last_poll;
  while (!next_email && !do_shutdown_.load()) {
    last_poll = std::chrono::steady_clock::now();
    next_email = get_email_from_uid(current_uid_);
    if (!do_shutdown_.load() && std::chrono::nanoseconds::zero() != period) {
      std::this_thread::sleep_until(last_poll + period);
    }
  }
  // Increment our current UID pointer, but only up to the previous 'next UID' value + 1.
  // This allows us to not miss emails when there are multiple new ones.
  // If we fetched the only new email (above), current UID will be equal to the initial next UID
  // and so we increment the pointer to wait for the next one.
  // If there was more than one new email, current UID will be lower than next UID and so we
  // increment the pointer to get the next new email.
  if (current_uid_ <= next_uid_) {
    current_uid_++;
  }
  return next_email;
}

std::optional<struct EmailData>
CurlEmailReceiver::get_email_from_uid(int uid)
{
  auto execute_result = execute("INBOX/;UID=" + std::to_string(uid), std::nullopt);
  if (!execute_result) {
    return std::nullopt;
  }
  return utils::response::get_email_data_from_response(execute_result.value());
}

std::optional<int>
CurlEmailReceiver::get_nextuid()
{
  std::optional<std::string> response = execute(std::nullopt, "EXAMINE INBOX");
  if (!response) {
    return std::nullopt;
  }
  std::optional<int> next_uid = utils::response::get_nextuid_from_response(response.value());
  return next_uid;
}

std::optional<std::string>
CurlEmailReceiver::execute(
  std::optional<std::string> url_options,
  std::optional<std::string> custom_request)
{
  if (do_shutdown_.load()) {
    return std::nullopt;
  }

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

  logger_->debug(
    "EXECUTE:\n"
    "\turl    : {}\n"
    "\tcommand: {}",
    request_url,
    (custom_request ? custom_request.value() : ""));

  // Reset read buffer
  read_buffer_.clear();

  if (!context_.execute()) {
    return std::nullopt;
  }
  logger_->debug("RESPONSE:\n{}", read_buffer_);
  return read_buffer_;
}

}  // namespace email
