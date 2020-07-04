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

#include "email/curl_executor.hpp"
#include "email/email_receiver.hpp"
#include "email/types.hpp"

namespace email
{

// TODO(christophebedard) move to class?
static size_t write_callback(void * contents, size_t size, size_t nmemb, void * userp)
{
  (static_cast<std::string *>(userp))->append(static_cast<char *>(contents), size * nmemb);
  return size * nmemb;
}

EmailReceiver::EmailReceiver(
  const struct UserInfo & user_info,
  const bool debug)
: CurlExecutor(user_info, {"imaps", 993}, debug),
  read_buffer_()
{}

EmailReceiver::~EmailReceiver()
{}

bool EmailReceiver::init_options()
{
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_WRITEDATA, static_cast<void *>(&read_buffer_));
  return true;
}

std::optional<struct EmailContent> EmailReceiver::get_email()
{
  if (!is_valid()) {
    std::cerr << "not initialized!" << std::endl;
    return std::nullopt;
  }

  std::optional<int> next_uid = get_nextuid();
  if (!next_uid) {
    return std::nullopt;
  }
  std::cout << "nextuid=" << next_uid.value() << std::endl;
  std::optional<struct EmailContent> next_email;
  // Try until we get an email
  while (!next_email) {
    next_email = get_email_from_uid(next_uid.value());
  }
  return next_email;
}

std::optional<struct EmailContent> EmailReceiver::get_email_from_uid(int uid)
{
  auto execute_result = execute("INBOX/;UID=" + std::to_string(uid), std::nullopt);
  if (!execute_result) {
    return std::nullopt;
  }
  return result_to_email_content(execute_result.value());
}

std::optional<struct EmailContent> EmailReceiver::result_to_email_content(
  const std::string & curl_result)
{
  auto match_group_subject = get_first_match_group(curl_result, EmailReceiver::regex_subject);
  auto match_group_body = get_first_match_group(curl_result, EmailReceiver::regex_body);
  if (!match_group_subject || !match_group_body) {
    return std::nullopt;
  }
  struct EmailContent content;
  content.subject = match_group_subject.value();
  content.body = match_group_body.value();
  return content;
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

std::optional<int> EmailReceiver::get_nextuid_from_response(const std::string & response)
{
  auto match_group = get_first_match_group(response, EmailReceiver::regex_nextuid);
  if (!match_group) {
    return std::nullopt;
  }
  return std::stoi(match_group.value());
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

std::optional<std::string> EmailReceiver::get_first_match_group(
  const std::string & string,
  const std::regex & regex)
{
  std::smatch matches;
  if (!std::regex_search(string, matches, regex)) {
    return std::nullopt;
  }
  // Only expecting one group besides the first global match itself
  if (matches.size() != 2) {
    return std::nullopt;
  }
  return matches[1].str();
}

const std::regex EmailReceiver::regex_nextuid(
  R"(.*OK \[UIDNEXT (.*)\] Predicted next UID.*)",
  std::regex::extended);
const std::regex EmailReceiver::regex_subject(
  R"(Subject: (.*)\r?\n)");
const std::regex EmailReceiver::regex_body(
  R"((?:\r?\n){2}((?:.*\n*)*)(?:\r?\n)?)");

}  // namespace email
