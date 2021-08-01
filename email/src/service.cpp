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
#include "email/gid_object.hpp"
#include "email/named_object.hpp"
#include "email/service.hpp"

namespace email
{

ServiceObject::ServiceObject(const std::string & service_name)
: GidObject(),
  NamedObject(service_name)
{
  validate_name();
}

ServiceObject::~ServiceObject() {}

const std::string &
ServiceObject::get_service_name() const
{
  return get_object_name();
}

void
ServiceObject::validate_name() const
{
  const auto & service_name = get_service_name();
  if (service_name.empty()) {
    throw ServiceNameInvalidError(service_name, "empty");
  }
  if (has_newline()) {
    throw ServiceNameInvalidError(service_name, "newline");
  }
}

}  // namespace email
