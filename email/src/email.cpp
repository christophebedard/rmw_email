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
#include <memory>
#include <string>
#include <stdexcept>

#include <curl/curl.h>

#include <email/email.hpp>
#include <email/utils.hpp>

// namespace email
// {

static std::string build_payload(
  const std::string & to,
  const std::string & subject,
  const std::string & body)
{
  return string_format(
    "To: %s\r\nSubject: %s\r\n\r\n%s\r\n",
    to.c_str(), subject.c_str(), body.c_str());
}

struct email_upload {
  const char * payload;
  int lines_read;
};

static size_t payload_source(void * ptr, size_t size, size_t nmemb, void * userp)
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
      fprintf(stderr, "truncated to len=%ld\n", len);
    }
    memcpy(ptr, data, len);
    upload_ctx->lines_read += len;
    return len;
  }
  return 0;
}

bool send_email(
  const std::string & from,
  const std::string & to,
  const std::string & username,
  const std::string & password,
  const std::string & subject,
  const std::string & body,
  bool debug)
{
  CURLcode res = CURLE_OK;
  CURL * curl = curl_easy_init();
  if (!curl) {
    return false;
  }

  const std::string payload = build_payload(to, subject, body);
  if (debug) {
    printf("payload:\n%s\n", payload.c_str());
  }
  struct email_upload upload_ctx;
  upload_ctx.payload = payload.c_str();
  upload_ctx.lines_read = 0;

  curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
  curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());

  curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");

  // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

  curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());
  struct curl_slist * recipients = nullptr;
  recipients = curl_slist_append(recipients, to.c_str());
  // recipients = curl_slist_append(recipients, CC);
  curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

  curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
  curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

  if (debug) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  }

  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }

  curl_slist_free_all(recipients);
  curl_easy_cleanup(curl);

  return CURLE_OK == res;
}

// }  // namespace email
