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

#ifndef EMAIL__GID_OBJECT_HPP_
#define EMAIL__GID_OBJECT_HPP_

#include <optional>  // NOLINT cpplint mistakes <optional> for a C system header
#include <string>

#include "email/gid.hpp"
#include "email/macros.hpp"

namespace email
{

/// Abstract object with a GID.
class GidObject
{
public:
  /// Get the unique ID (GID) for this object.
  /**
   * \return the GID
   */
  EMAIL_PUBLIC
  const Gid &
  get_gid() const;

protected:
  /// Constructor
  GidObject();

  virtual ~GidObject();

private:
  EMAIL_DISABLE_COPY(GidObject)

  const Gid gid_;
};

}  // namespace email

#endif  // EMAIL__GID_OBJECT_HPP_
