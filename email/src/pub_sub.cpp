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

#include <regex>
#include <string>

#include "email/pub_sub.hpp"

namespace email
{

PubSubObject::PubSubObject(const std::string & topic)
: topic_(topic)
{
  validate_topic(topic_);
}

PubSubObject::~PubSubObject() {}

std::string
PubSubObject::get_topic() const
{
  return topic_;
}

void
PubSubObject::validate_topic(const std::string & topic)
{
  if (topic.empty()) {
    throw TopicInvalidError(topic, "empty");
  }
  if (std::regex_match(topic, PubSubObject::REGEX_NEWLINE)) {
    throw TopicInvalidError(topic, "newline");
  }
}

const std::regex PubSubObject::REGEX_NEWLINE(".*[\r]?\n.*", std::regex::extended);

}  // namespace email
