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

#ifndef EMAIL__EMAIL_H_
#define EMAIL__EMAIL_H_

#include <string>

#include "email/visibility_control.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

// namespace email
// {

/// Send email.
/**
 * \return `true` if successful, `false` otherwise
 */
EMAIL_PUBLIC bool send_email(
  const std::string & from,
  const std::string & to,
  const std::string & username,
  const std::string & password,
  const std::string & subject,
  const std::string & body,
  bool debug = true);

// }  // namespace email

#ifdef __cplusplus
}
#endif

#endif  // EMAIL__EMAIL_H_
