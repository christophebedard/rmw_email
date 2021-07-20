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
#include "email/pub_sub.hpp"

namespace email
{

PubSubObject::PubSubObject(const std::string & topic_name)
: topic_name_(topic_name),
  gid_(Gid::new_gid())
{
  validate_topic_name(topic_name);
}

PubSubObject::~PubSubObject() {}

std::string
PubSubObject::get_topic_name() const
{
  return topic_name_;
}

const Gid &
PubSubObject::get_gid() const
{
  return gid_;
}

void
PubSubObject::validate_topic_name(const std::string & topic_name)
{
  if (topic_name.empty()) {
    throw TopicNameInvalidError(topic_name, "empty");
  }
  if (std::regex_match(topic_name, PubSubObject::REGEX_NEWLINE)) {
    throw TopicNameInvalidError(topic_name, "newline");
  }
}

const std::regex PubSubObject::REGEX_NEWLINE(".*[\r]?\n.*", std::regex::extended);

}  // namespace email
