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

#include <cstring>
#include <memory>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <stdexcept>
#include <string>

#include "email/curl/executor.hpp"
#include "email/email/curl_sender.hpp"
#include "email/email/info.hpp"
#include "email/email/payload_utils.hpp"
#include "email/email/sender.hpp"
#include "email/log.hpp"
#include "email/utils.hpp"

namespace email
{

CurlEmailSender::CurlEmailSender(
  UserInfo::SharedPtrConst user_info,
  EmailRecipients::SharedPtrConst recipients,
  const bool curl_verbose)
: EmailSender(user_info, recipients),
  CurlExecutor(
    {user_info->host_smtp, user_info->username, user_info->password},
    {"smtps", 465},
    curl_verbose),
  recipients_(recipients),
  recipients_list_(nullptr),
  upload_ctx_()
{}

CurlEmailSender::~CurlEmailSender()
{
  if (recipients_list_) {
    curl_slist_free_all(recipients_list_);
    recipients_list_ = nullptr;
  }
  logger()->debug("destroying");
}

size_t
CurlEmailSender::read_payload_callback(void * ptr, size_t size, size_t nmemb, void * userp)
{
  const size_t max_size = size * nmemb;
  if ((0 == size) || (0 == nmemb) || (1 > max_size)) {
    return 0;
  }
  struct UploadData * upload_ctx = (struct UploadData *)userp;
  const char * data = &upload_ctx->payload[upload_ctx->lines_read];
  if (!data) {
    return 0;
  }
  size_t len = strlen(data);
  if (len > max_size) {
    len = max_size;
    logger()->error("truncated to len={}", len);
  }
  memcpy(ptr, data, len);
  upload_ctx->lines_read += len;
  return len;
}

bool
CurlEmailSender::init_options()
{
  curl_easy_setopt(context_.get_handle(), CURLOPT_URL, context_.get_full_url().c_str());
  curl_easy_setopt(
    context_.get_handle(), CURLOPT_MAIL_FROM, context_.get_connection_info().username.c_str());
  // Add all destination emails to the list of recipients
  if (0 == recipients_->to.size() + recipients_->cc.size() + recipients_->bcc.size()) {
    logger()->critical("no recipients for CurlEmailSender");
    return false;
  }
  for (auto & email_to : recipients_->to) {
    recipients_list_ = curl_slist_append(recipients_list_, email_to.c_str());
  }
  for (auto & email_cc : recipients_->cc) {
    recipients_list_ = curl_slist_append(recipients_list_, email_cc.c_str());
  }
  for (auto & email_bcc : recipients_->bcc) {
    recipients_list_ = curl_slist_append(recipients_list_, email_bcc.c_str());
  }
  curl_easy_setopt(context_.get_handle(), CURLOPT_MAIL_RCPT, recipients_list_);
  curl_easy_setopt(context_.get_handle(), CURLOPT_READFUNCTION, read_payload_callback);
  curl_easy_setopt(context_.get_handle(), CURLOPT_READDATA, static_cast<void *>(&upload_ctx_));
  curl_easy_setopt(context_.get_handle(), CURLOPT_UPLOAD, 1L);
  // curl_easy_setopt(context_.get_handle(), CURLOPT_SSL_VERIFYPEER, 0L);
  // curl_easy_setopt(context_.get_handle(), CURLOPT_SSL_VERIFYHOST, 0L);
  return true;
}

bool
CurlEmailSender::send(
  const struct EmailContent & content,
  std::optional<EmailHeaders> additional_headers)
{
  logger()->debug("send");
  return send_payload(
    utils::payload::build_payload(recipients_, content, additional_headers, std::nullopt));
}

bool
CurlEmailSender::reply(
  const struct EmailContent & content,
  const struct EmailData & email,
  std::optional<EmailHeaders> additional_headers)
{
  return send_payload(
    utils::payload::build_payload(
      {email.from},
      {},
      {},
      content,
      additional_headers,
      email.message_id));
}

bool
CurlEmailSender::send_payload(const std::string & payload)
{
  if (!is_valid()) {
    logger()->warn("not initialized!");
    return false;
  }
  logger()->debug("PAYLOAD:\n{}", payload);
  // Reset upload data
  upload_ctx_.payload = payload.c_str();
  // TODO(christophebedard) use 'uz' suffix when switching to C++23
  upload_ctx_.lines_read = 0UL;
  if (!context_.execute()) {
    return false;
  }
  return true;
}

}  // namespace email
