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
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <regex>
#include <string>

#include "email/email_receiver.hpp"
#include "email/types.hpp"

// TODO(christophebedard) move to class?
static size_t write_callback(void * contents, size_t size, size_t nmemb, void * userp)
{
  (static_cast<std::string *>(userp))->append(static_cast<char *>(contents), size * nmemb);
  return size * nmemb;
}

EmailReceiver::EmailReceiver(
  struct email::UserInfo user_info,
  bool debug)
: context_(user_info, {"imaps", 993}, debug),
  read_buffer_(),
  debug_(debug)
{
  // TODO(christophebedard) extract to method, because we need to check if it's successful
  context_.init();
  // Recurrent options
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEDATA, static_cast<void *>(&read_buffer_));
}

EmailReceiver::~EmailReceiver()
{
  context_.fini();
}

std::optional<std::string> EmailReceiver::get_email()
{
  std::optional<int> next_uid = get_nextuid();
  if (!next_uid) {
    return std::nullopt;
  }
  std::cout << "nextuid=" << next_uid.value() << std::endl;
  std::optional<std::string> next_email;
  // Try until we get an email
  while (!next_email) {
    next_email = get_email_from_uid(next_uid.value());
  }
  return next_email;
}

std::optional<std::string> EmailReceiver::get_email_from_uid(int uid)
{
  return execute("INBOX/;UID=" + std::to_string(uid), std::nullopt);
}

std::optional<int> EmailReceiver::get_nextuid()
{
  std::optional<std::string> response = execute(std::nullopt, "EXAMINE INBOX");
  if (!response) {
    return std::nullopt;
  }
  std::optional<int> next_uid = get_nextuid_from_response(response.value());
  return next_uid;
}

const std::regex EmailReceiver::regex_nextuid(
  ".*OK \\[UIDNEXT (.*)\\] Predicted next UID.*",
  std::regex::extended);

std::optional<int> EmailReceiver::get_nextuid_from_response(const std::string & response)
{
  std::smatch matches;
  if (!std::regex_search(response, matches, EmailReceiver::regex_nextuid)) {
    return std::nullopt;
  }
  // Only 1 match besides the first global match itself
  if (matches.size() != 2) {
    return std::nullopt;
  }
  return std::stoi(matches[1].str());
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
  } else {
    // Unset the option in case it was set during a previous call
    curl_easy_setopt(context_.get_handle(), CURLOPT_CUSTOMREQUEST, NULL);
  }

  if (debug_) {
    std::cout << "execute:" << std::endl <<
      "\turl    : " << request_url << std::endl <<
      "\tcommand: " << (custom_request ? custom_request.value() : "") << std::endl;
  }

  if (!context_.execute()) {
    return std::nullopt;
  }
  return read_buffer_;
}
