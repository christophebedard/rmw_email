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

#ifndef EMAIL__PUB_SUB_HPP_
#define EMAIL__PUB_SUB_HPP_

#include <regex>
#include <stdexcept>
#include <string>

namespace email
{

/// Error when a topic is invalid.
class TopicInvalidError : public std::runtime_error
{
public:
  explicit TopicInvalidError(const std::string & topic, const std::string & reason)
  : std::runtime_error("topic name invalid (" + reason + "): '" + topic + "'")
  {}
};

/// Abstract pub or sub object.
/**
 * Abstract class representing common publishing and subscribing elements.
 */
class PubSubObject
{
public:
  /// Get the topic.
  /**
   * \return the topic
   */
  std::string
  get_topic() const;

protected:
  /// Constructor.
  /**
   * Validate the topic.
   *
   * \param topic the topic
   * \throw `TopicInvalidError` if the topic is invalid
   */
  explicit PubSubObject(const std::string & topic);
  PubSubObject(const PubSubObject &) = delete;
  virtual ~PubSubObject();

private:
  /// Validate a topic and throw an error with an explanation if it is not valid.
  static
  void
  validate_topic(const std::string & topic);

  /// Regex which matches on a newline, with an optional carriage return before.
  static const std::regex REGEX_NEWLINE;

  const std::string topic_;
};

}  // namespace email

#endif  // EMAIL__PUB_SUB_HPP_
