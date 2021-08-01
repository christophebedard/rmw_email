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

#ifndef EMAIL__PUB_SUB_HPP_
#define EMAIL__PUB_SUB_HPP_

#include <regex>
#include <stdexcept>
#include <string>

#include "email/gid.hpp"
#include "email/macros.hpp"
#include "email/named_object.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Error when a topic name is invalid.
class TopicNameInvalidError : public ObjectNameInvalidError
{
public:
  explicit TopicNameInvalidError(const std::string & topic_name, const std::string & reason)
  : ObjectNameInvalidError("topic", topic_name, reason)
  {}
};

/// Abstract pub or sub object.
/**
 * Abstract class with common publisher and subscription elements.
 */
class PubSubObject : public GidObject, public NamedObject
{
public:
  /// Get the topic name.
  /**
   * \return the topic name
   */
  EMAIL_PUBLIC
  const std::string &
  get_topic_name() const;

protected:
  /// Constructor.
  /**
   * Validates the topic name.
   *
   * \param topic_name the topic name
   * \throw `TopicNameInvalidError` if the topic name is invalid
   */
  explicit PubSubObject(const std::string & topic_name);

  virtual ~PubSubObject();

private:
  EMAIL_DISABLE_COPY(PubSubObject)

  /// Validate the topic name and throw an error with an explanation if it is not valid.
  /**
   * \throw `TopicNameInvalidError` if the topic name is invalid
   */
  void
  virtual validate_name() const;
};

}  // namespace email

#endif  // EMAIL__PUB_SUB_HPP_
