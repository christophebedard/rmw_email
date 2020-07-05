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

#ifndef EMAIL__CURL__CONTEXT_HPP_
#define EMAIL__CURL__CONTEXT_HPP_

#include <curl/curl.h>

#include <string>

#include "email/types.hpp"
#include "email/utils.hpp"

namespace email
{

class CurlContext
{
public:
  explicit CurlContext(
    const struct UserInfo & user_info,
    const struct ProtocolInfo & protocol_info,
    const bool debug);
  CurlContext(const CurlContext &) = delete;
  virtual ~CurlContext();

  bool init();

  void fini();

  bool execute();

  CURL * get_handle()
  {
    return handle_;
  }

  const std::string & get_full_url()
  {
    return full_url_;
  }

  const struct UserInfo & get_user_info()
  {
    return user_info_;
  }

private:
  CURL * handle_;
  const struct UserInfo user_info_;
  const struct ProtocolInfo protocol_info_;
  std::string full_url_;
  bool debug_;
};

}  // namespace email

#endif  // EMAIL__CURL__CONTEXT_HPP_
