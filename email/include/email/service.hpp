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

#ifndef EMAIL__SERVICE_HPP_
#define EMAIL__SERVICE_HPP_

#include <regex>
#include <stdexcept>
#include <string>

namespace email
{

/// Error when a service name is invalid.
class ServiceNameInvalidError : public std::runtime_error
{
public:
  explicit ServiceNameInvalidError(const std::string & service_name, const std::string & reason)
  : std::runtime_error("service name invalid (" + reason + "): '" + service_name + "'")
  {}
};

/// Abstract service object.
/**
 * Abstract class representing common service elements.
 */
class ServiceObject
{
public:
  /// Get the service name.
  /**
   * \return the service name
   */
  std::string
  get_service_name() const;

protected:
  /// Constructor.
  /**
   * Validates the service name.
   *
   * \param service_name the service name
   * \throw `ServiceNameInvalidError` if the service name is invalid
   */
  explicit ServiceObject(const std::string & service_name);
  ServiceObject(const ServiceObject &) = delete;
  ServiceObject & operator=(const ServiceObject &) = delete;
  virtual ~ServiceObject();

private:
  /// Validate a service name and throw an error with an explanation if it is not valid.
  static
  void
  validate_service_name(const std::string & service_name);

  /// Regex which matches on a newline, with an optional carriage return before.
  static const std::regex REGEX_NEWLINE;

  // TODO(christophebedard) extract service name to/inherit from
  // PubSubObject (rename) to validate the service name itself
  const std::string service_name_;
};

}  // namespace email

#endif  // EMAIL__SERVICE_HPP_
