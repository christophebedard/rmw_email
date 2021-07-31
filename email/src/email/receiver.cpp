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

#include <atomic>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "email/curl/executor.hpp"
#include "email/email/info.hpp"
#include "email/email/receiver.hpp"
#include "email/email/response_utils.hpp"
#include "email/log.hpp"

namespace email
{

EmailReceiver::EmailReceiver(
  UserInfo::SharedPtrConst user_info,
  const bool curl_verbose)
: CurlExecutor(
    {user_info->host_imap, user_info->username, user_info->password},
    {"imaps", 993},
    curl_verbose),
  logger_(log::create("EmailReceiver")),
  current_uid_(-1),
  next_uid_(-1),
  read_buffer_(),
  do_shutdown_(false)
{}

EmailReceiver::~EmailReceiver()
{
  logger_->debug("destroying");
}

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

void
EmailReceiver::shutdown()
{
  do_shutdown_ = true;
}

std::optional<struct EmailData>
EmailReceiver::get_email()
{
  if (!is_valid()) {
    logger_->warn("not initialized!");
    return std::nullopt;
  }
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
  while (!next_email && !do_shutdown_.load()) {
    next_email = get_email_from_uid(current_uid_);
  }
  // Increment current UID pointer: this allows us to
  // not miss emails when there are multiple new ones.
  if (current_uid_ < next_uid_) {
    current_uid_++;
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
