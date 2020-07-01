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

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

int main(void)
{
  // bool debug = true;
  bool debug = false;

  CURL *curl;
 
  curl = curl_easy_init();
  if (!curl) {
    return 1;
  }

  curl_easy_setopt(curl, CURLOPT_USERNAME, "");
  curl_easy_setopt(curl, CURLOPT_PASSWORD, "");

  // curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993/");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXAMINE INBOX");
  curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993/INBOX;UID=*");

  // curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993/INBOX");
  // curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993/INBOX;EXAMINE");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SEARCH NEW");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SELECT \"[Gmail]/All Mail\"");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "FETCH 1 BODY[TEXT]");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SELECT \"[Gmail]/All Mail\"");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SELECT \"INBOX\"");
  // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "FETCH * (BODY[TEXT])");

  std::string buffer;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buffer);
  // Some servers need this validation
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  // curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

  if (debug) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  }

  CURLcode res = CURLE_OK;
  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }
  printf("response:\n%s\n", buffer.c_str());

  curl_easy_cleanup(curl);
  return (int)res;
}
