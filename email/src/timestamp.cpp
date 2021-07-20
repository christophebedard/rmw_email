// Copyright 2021 Christophe Bedard
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

#include <cassert>
#include <chrono>
#include <string>

#include "email/timestamp.hpp"
#include "email/utils.hpp"

namespace email
{

Timestamp
Timestamp::now()
{
  auto now = std::chrono::system_clock::now().time_since_epoch();
  auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now);
  return Timestamp(nanoseconds.count());
}

Timestamp::Timestamp(const int64_t nanoseconds)
: nanoseconds_(nanoseconds)
{}

Timestamp::~Timestamp() {}

int64_t
Timestamp::nanoseconds() const
{
  return nanoseconds_;
}

std::string
Timestamp::to_string() const
{
  return std::to_string(nanoseconds_);
}

Timestamp
Timestamp::from_string(const std::string & timestamp)
{
  auto nanoseconds_opt = utils::optional_stoll(timestamp);
  assert(nanoseconds_opt.has_value());
  return Timestamp(nanoseconds_opt.value());
}

}  // namespace email
