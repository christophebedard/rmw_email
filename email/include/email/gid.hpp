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

#ifndef EMAIL__GID_HPP_
#define EMAIL__GID_HPP_

#include <string>

#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Value type for GIDs.
typedef uint32_t GidValue;

/// Unique ID (GID).
/**
 * Wrapper for unique ID (aka GID).
 */
class Gid
{
public:
  /// Constructor.
  /**
   * A new GID is automatically created.
   */
  EMAIL_PUBLIC
  Gid();

  EMAIL_PUBLIC
  virtual ~Gid();

  /// Get the GID value.
  /**
   * \return the value
   */
  EMAIL_PUBLIC
  GidValue
  value() const;

  /// Get the GID as a string.
  /**
   * \return the GID as a string
   */
  const std::string &
  as_string() const;

private:
  EMAIL_DISABLE_COPY(Gid)

  /// Get a new value.
  static
  GidValue
  new_value();

  /// Convert a GID value to a string.
  /**
   * \return the GID value as a string
   */
  static
  std::string
  to_string(const GidValue value);

  const GidValue value_;
  const std::string value_string_;
};

}  // namespace email

#endif  // EMAIL__GID_HPP_
