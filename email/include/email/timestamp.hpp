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

#ifndef EMAIL__TIMESTAMP_HPP_
#define EMAIL__TIMESTAMP_HPP_

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "spdlog/fmt/ostr.h"

#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Timestamp with nanoseconds.
/**
 * Unix timestamp in nanoseconds.
 */
class Timestamp
{
public:
  /// Get a new timestamp pointing to now from the Unix epoch.
  EMAIL_PUBLIC
  static
  Timestamp
  now();

  /// Constructor.
  /**
   * \param nanoseconds the number of nanoseconds
   */
  EMAIL_PUBLIC
  explicit Timestamp(const int64_t nanoseconds);

  EMAIL_PUBLIC
  Timestamp(const Timestamp &) = default;

  EMAIL_PUBLIC
  ~Timestamp();

  /// Get the number of nanoseconds.
  EMAIL_PUBLIC
  int64_t
  nanoseconds() const;

  /// Convert the timestamp to a string.
  /**
   * This string can be converted back to a timestamp using from_string().
   */
  EMAIL_PUBLIC
  std::string
  to_string() const;

  /// Get a timestamp object from a string.
  /**
   * The string should have been generated using to_string().
   *
   * \return the timestamp object, or `std::nullopt` if it fails
   */
  EMAIL_PUBLIC
  static
  std::optional<Timestamp>
  from_string(const std::string & timestamp);

  EMAIL_PUBLIC
  bool
  operator==(const Timestamp & rhs) const;

private:
  int64_t nanoseconds_;
};

}  // namespace email

/// Formatting for Timestamp objects.
template<>
struct fmt::formatter<email::Timestamp>: formatter<string_view>
{
  template<typename FormatContext>
  auto format(const email::Timestamp & ts, FormatContext & ctx)
  {
    return formatter<string_view>::format(ts.to_string(), ctx);
  }
};

#endif  // EMAIL__TIMESTAMP_HPP_
