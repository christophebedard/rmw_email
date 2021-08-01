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

#ifndef EMAIL__SERVICE_HPP_
#define EMAIL__SERVICE_HPP_

#include <regex>
#include <stdexcept>
#include <string>

#include "email/gid.hpp"
#include "email/gid_object.hpp"
#include "email/macros.hpp"
#include "email/named_object.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Error when a service name is invalid.
class ServiceNameInvalidError : public ObjectNameInvalidError
{
public:
  explicit ServiceNameInvalidError(const std::string & service_name, const std::string & reason)
  : ObjectNameInvalidError("service", service_name, reason)
  {}
};

/// Abstract service object.
/**
 * Abstract class representing common service elements.
 */
class ServiceObject : public GidObject, public NamedObject
{
public:
  /// Get the service name.
  /**
   * \return the service name
   */
  EMAIL_PUBLIC
  const std::string &
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

  virtual ~ServiceObject();

private:
  EMAIL_DISABLE_COPY(ServiceObject)

  /// Validate the service name and throw an error with an explanation if it is not valid.
  /**
   * \throw `ServiceNameInvalidError` if the service name is invalid
   */
  void
  virtual validate_name() const;
};

}  // namespace email

#endif  // EMAIL__SERVICE_HPP_
