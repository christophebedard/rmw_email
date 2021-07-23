// Copyright 2020-2021 Christophe Bedard
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

#include <regex>
#include <string>

#include "email/gid.hpp"
#include "email/service.hpp"

namespace email
{

ServiceObject::ServiceObject(const std::string & service_name)
: GidObject(),
  service_name_(service_name)
{
  validate_service_name(service_name);
}

ServiceObject::~ServiceObject() {}

std::string
ServiceObject::get_service_name() const
{
  return service_name_;
}

void
ServiceObject::validate_service_name(const std::string & service_name)
{
  if (service_name.empty()) {
    throw ServiceNameInvalidError(service_name, "empty");
  }
  if (std::regex_match(service_name, ServiceObject::REGEX_NEWLINE)) {
    throw ServiceNameInvalidError(service_name, "newline");
  }
}

const std::regex ServiceObject::REGEX_NEWLINE(".*[\r]?\n.*", std::regex::extended);

}  // namespace email
