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

#ifndef EMAIL__NAMED_OBJECT_HPP_
#define EMAIL__NAMED_OBJECT_HPP_

#include <regex>
#include <stdexcept>
#include <string>

#include "email/macros.hpp"

namespace email
{

/// Error when an object name is invalid.
class ObjectNameInvalidError : public std::runtime_error
{
protected:
  explicit ObjectNameInvalidError(
    const std::string & object_type_name,
    const std::string & object_name,
    const std::string & reason)
  : std::runtime_error(object_type_name + " name invalid (" + reason + "): '" + object_name + "'")
  {}
};

/// Abstract object with a name.
/**
 * Abstract class for objects that have a name (like a
 * topic name or a service name) that needs to be validated.
 */
class NamedObject
{
protected:
  /// Get the object's name.
  /**
   * \return the name
   */
  const std::string &
  get_object_name() const;

  /// Constructor.
  /**
   * \param name the name
   */
  explicit NamedObject(const std::string & name);

  virtual ~NamedObject();

  /// Validate the object's name and throw an error with an explanation if it is not valid.
  void
  virtual validate_name() const = 0;

  /// Check if the object's name contains a newline.
  bool
  has_newline() const;

private:
  EMAIL_DISABLE_COPY(NamedObject)

  /// Regex which matches on a newline, with an optional carriage return before.
  static const std::regex REGEX_NEWLINE;

  const std::string object_name_;
};

}  // namespace email

#endif  // EMAIL__NAMED_OBJECT_HPP_
