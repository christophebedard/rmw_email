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

#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "email/curl_executor.hpp"
#include "email/email_sender.hpp"
#include "email/payload_utils.hpp"
#include "email/utils.hpp"
#include "email/types.hpp"

// namespace email
// {

static size_t read_payload_callback(void * ptr, size_t size, size_t nmemb, void * userp)
{
  const size_t max_size = size * nmemb;
  if ((size == 0) || (nmemb == 0) || ((max_size) < 1)) {
    return 0;
  }
  struct UploadData * upload_ctx = (struct UploadData *)userp;
  const char * data = &upload_ctx->payload[upload_ctx->lines_read];
  if (data) {
    size_t len = strlen(data);
    if (len > max_size) {
      len = max_size;
      std::cerr << "truncated to len=" << len << std::endl;
    }
    memcpy(ptr, data, len);
    upload_ctx->lines_read += len;
    return len;
  }
  return 0;
}

EmailSender::EmailSender(
  const struct email::UserInfo & user_info,
  const struct email::EmailRecipients & recipients,
  const bool debug)
: CurlExecutor(user_info, {"smtps", 465}, debug),
  recipients_(recipients),
  recipients_list_(nullptr),
  upload_ctx_()
{}

EmailSender::~EmailSender()
{
  curl_slist_free_all(recipients_list_);
  recipients_list_ = nullptr;
}

bool EmailSender::init_options()
{
  curl_easy_setopt(context_.get_handle(), CURLOPT_URL, context_.get_full_url().c_str());
  // curl_easy_setopt(context_.get_handle(), CURLOPT_SSL_VERIFYPEER, 0L);
  // curl_easy_setopt(context_.get_handle(), CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(
    context_.get_handle(), CURLOPT_MAIL_FROM, context_.get_user_info().username.c_str());
  // Add all destination emails to the list of recipients
  for (auto & email_to : recipients_.to) {
    recipients_list_ = curl_slist_append(recipients_list_, email_to.c_str());
  }
  for (auto & email_cc : recipients_.cc) {
    recipients_list_ = curl_slist_append(recipients_list_, email_cc.c_str());
  }
  for (auto & email_bcc : recipients_.bcc) {
    recipients_list_ = curl_slist_append(recipients_list_, email_bcc.c_str());
  }
  // recipients_list_ = curl_slist_append(recipients_list_, CC);
  curl_easy_setopt(context_.get_handle(), CURLOPT_MAIL_RCPT, recipients_list_);
  curl_easy_setopt(context_.get_handle(), CURLOPT_READFUNCTION, read_payload_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_READDATA, static_cast<void *>(&upload_ctx_));
  curl_easy_setopt(context_.get_handle(), CURLOPT_UPLOAD, 1L);
  if (debug_) {
    curl_easy_setopt(context_.get_handle(), CURLOPT_VERBOSE, 1L);
  }
  return true;
}

bool EmailSender::send(
  const struct email::EmailContent & content)
{
  if (!is_valid()) {
    std::cerr << "not initialized!" << std::endl;
    return false;
  }

  const std::string payload = email::utils::PayloadUtils::build_payload(recipients_, content);
  if (debug_) {
    std::cout << "payload:" << std::endl << payload << std::endl;
  }

  // Reset upload data
  upload_ctx_.payload = payload.c_str();
  upload_ctx_.lines_read = 0;

  if (!context_.execute()) {
    return false;
  }
  return true;
}

// }  // namespace email
