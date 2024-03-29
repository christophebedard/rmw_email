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

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "spdlog/fmt/ostr.h"

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
  /// Get a new GID.
  EMAIL_PUBLIC
  static
  Gid
  new_gid();

  /// Constructor.
  /**
   * To create a new GID, see Gid::new().
   *
   * \param value the value for this GID
   */
  EMAIL_PUBLIC
  explicit Gid(const GidValue value);

  EMAIL_PUBLIC
  Gid(const Gid &) = default;

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
   * This string can be converted back to a GID using from_string().
   */
  EMAIL_PUBLIC
  const std::string &
  to_string() const;

  /// Get a GID object from a string.
  /**
   * The string should have been generated using to_string().
   *
   * \return the GID object, or `std::nullopt` if it fails
   */
  EMAIL_PUBLIC
  static
  std::optional<Gid>
  from_string(const std::string & str);

private:
  /// Get a new value.
  static
  GidValue
  new_value();

  /// Convert a GID value to a string.
  static
  std::string
  to_string(const GidValue value);

  const GidValue value_;
  const std::string value_string_;
};

}  // namespace email

/// Formatting for GIDs.
template<>
struct fmt::formatter<email::Gid>: formatter<string_view>
{
  template<typename FormatContext>
  auto format(const email::Gid & gid, FormatContext & ctx)
  {
    return formatter<string_view>::format(gid.to_string(), ctx);
  }
};

#endif  // EMAIL__GID_HPP_
