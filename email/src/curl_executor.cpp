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

#include "email/curl_executor.hpp"
#include "email/types.hpp"

CurlExecutor::CurlExecutor(
  struct email::UserInfo user_info,
  struct email::ProtocolInfo protocol_info,
  bool debug)
: context_(user_info, protocol_info, debug),
  debug_(debug),
  is_valid_(false)
{}

CurlExecutor::~CurlExecutor()
{
  context_.fini();
}

bool CurlExecutor::init()
{
  is_valid_ |= context_.init() && init_options();
  return is_valid_;
}

bool CurlExecutor::is_valid() const
{
  return is_valid_;
}
