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
#include <vector>

#include "email/curl_executor.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

// namespace email
// {

struct UploadData
{
  const char * payload;
  int lines_read;
};

class EmailSender : public CurlExecutor
{
public:
  explicit EmailSender(
    const struct email::UserInfo & user_info,
    const struct email::EmailRecipients & recipients,
    const bool debug = true);
  EmailSender(const EmailSender &) = delete;
  virtual ~EmailSender();

  bool send(const struct email::EmailContent & content);

protected:
  virtual bool init_options();

private:
  static const std::string build_payload(
    const struct email::EmailRecipients & recipients,
    const struct email::EmailContent & content);
  static const std::string join_list(
    const std::vector<std::string> & list);

  const struct email::EmailRecipients recipients_;
  struct curl_slist * recipients_list_;
  struct UploadData upload_ctx_;
};

// }  // namespace email

#endif  // EMAIL__EMAIL_SENDER_HPP_
