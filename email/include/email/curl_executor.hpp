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

#ifndef EMAIL__CURL_EXECUTOR_HPP_
#define EMAIL__CURL_EXECUTOR_HPP_

#include "email/curl_context.hpp"
#include "email/types.hpp"

namespace email
{

class CurlExecutor
{
public:
  bool init();

protected:
  explicit CurlExecutor(
    const struct UserInfo & user_info,
    const struct ProtocolInfo & protocol_info,
    const bool debug);
  CurlExecutor(const CurlExecutor &) = delete;
  virtual ~CurlExecutor();

  virtual bool init_options() = 0;

  bool is_valid() const;

  CurlContext context_;
  const bool debug_;

private:
  bool is_valid_;
};

}  // namespace email

#endif  // EMAIL__CURL_EXECUTOR_HPP_
