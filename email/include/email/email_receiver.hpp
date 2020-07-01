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

#ifndef EMAIL__EMAIL_RECEIVER_HPP_
#define EMAIL__EMAIL_RECEIVER_HPP_

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <string>
#include <optional>

#include <curl/curl.h>

#include <email/curl_context.hpp>

class EmailReceiver {
public:
  explicit EmailReceiver(
    struct email::UserConnectionInfo user_info,
    bool debug = true);
  EmailReceiver(const EmailReceiver &) = delete;
  virtual ~EmailReceiver();

  std::optional<std::string> get_email();

private:
  virtual std::optional<std::string> execute(
    std::optional<std::string> url_options,
    std::optional<std::string> custom_request);

  CurlContext context_;
  bool debug_;

};

#endif  // EMAIL__EMAIL_RECEIVER_HPP_
