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

#ifndef EMAIL__EMAIL_SENDER_HPP_
#define EMAIL__EMAIL_SENDER_HPP_

#include <string>

#include <email/curl_context.hpp>
#include <email/visibility_control.hpp>

// namespace email
// {

struct email_upload {
  const char * payload;
  int lines_read;
};

class EmailSender {
public:
  explicit EmailSender(
    struct UserConnectionInfo user_info,
    bool debug = true);
  EmailSender(const EmailSender &) = delete;
  virtual ~EmailSender();

  bool send(
    const std::string & to,
    const std::string & subject,
    const std::string & body);

private:
  static std::string build_payload(
    const std::string & to,
    const std::string & subject,
    const std::string & body);

  CurlContext context_;
  bool debug_;

};

// }  // namespace email

#endif  // EMAIL__EMAIL_SENDER_HPP_
