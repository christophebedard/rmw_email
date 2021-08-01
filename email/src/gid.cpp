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

#include <atomic>
#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <random>
#include <string>

#include "email/gid.hpp"
#include "email/utils.hpp"

namespace email
{

Gid
Gid::new_gid()
{
  return Gid(Gid::new_value());
}

Gid::Gid(const GidValue value)
: value_(value),
  value_string_(Gid::to_string(value_))
{}

Gid::~Gid() {}

GidValue
Gid::value() const
{
  return value_;
}

const std::string &
Gid::to_string() const
{
  return value_string_;
}

std::optional<Gid>
Gid::from_string(const std::string & str)
{
  auto value_opt = utils::optional_stoul(str);
  if (!value_opt) {
    return std::nullopt;
  }
  return Gid(value_opt.value());
}

GidValue
Gid::new_value()
{
  // Generate random prefix
  static std::random_device random_device;
  static std::mt19937 gen(random_device());
  static auto prefix = gen();
  // Add sequence sequence number to prefix
  static std::atomic<GidValue> sequence;
  return prefix + sequence++;
}

std::string
Gid::to_string(const GidValue value)
{
  return std::to_string(value);
}

}  // namespace email
