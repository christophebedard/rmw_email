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

// #include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <stdexcept>

#include <iostream>

#include <curl/curl.h>

#include <email/email_sender.hpp>
#include <email/utils.hpp>

// namespace email
// {

static size_t read_payload_callback(void * ptr, size_t size, size_t nmemb, void * userp)
{
  const size_t max_size = size * nmemb;
  if ((size == 0) || (nmemb == 0) || ((max_size) < 1)) {
    return 0;
  }
  struct email_upload * upload_ctx = (struct email_upload *)userp;
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
  struct email::UserConnectionInfo user_info,
  bool debug)
: context_(user_info, {"smtps", 465}, debug),
  debug_(debug)
{
  context_.init();
  curl_easy_setopt(context_.get_handle(), CURLOPT_URL, context_.get_full_url().c_str());
}

EmailSender::~EmailSender()
{
  context_.fini();
}

bool EmailSender::send(
  const std::string & to,
  const std::string & subject,
  const std::string & body)
{
  const std::string payload = build_payload(to, subject, body);
  if (debug_) {
    std::cout << "payload:" << std::endl << payload << std::endl;
  }
  struct email_upload upload_ctx;
  upload_ctx.payload = payload.c_str();
  upload_ctx.lines_read = 0;

  // curl_easy_setopt(context_.get_handle(), CURLOPT_SSL_VERIFYPEER, 0L);
  // curl_easy_setopt(context_.get_handle(), CURLOPT_SSL_VERIFYHOST, 0L);

  curl_easy_setopt(context_.get_handle(), CURLOPT_MAIL_FROM, context_.get_user_info().username.c_str());
  struct curl_slist * recipients = nullptr;
  recipients = curl_slist_append(recipients, to.c_str());
  // recipients = curl_slist_append(recipients, CC);
  curl_easy_setopt(context_.get_handle(), CURLOPT_MAIL_RCPT, recipients);

  curl_easy_setopt(context_.get_handle(), CURLOPT_READFUNCTION, read_payload_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_READDATA, &upload_ctx);
  curl_easy_setopt(context_.get_handle(), CURLOPT_UPLOAD, 1L);

  if (debug_) {
    curl_easy_setopt(context_.get_handle(), CURLOPT_VERBOSE, 1L);
  }

  if (!context_.execute()) {
    return false;
  }
  curl_slist_free_all(recipients);
  return true;
}

std::string EmailSender::build_payload(
  const std::string & to,
  const std::string & subject,
  const std::string & body)
{
  return email::utils::string_format(
    "To: %s\r\nSubject: %s\r\n\r\n%s\r\n",
    to.c_str(), subject.c_str(), body.c_str());
}

// }  // namespace email
