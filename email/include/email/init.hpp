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

#ifndef EMAIL__INIT_HPP_
#define EMAIL__INIT_HPP_

#include "email/visibility_control.hpp"

namespace email
{

/// Initialize context using config file.
/**
 * \throw `std::runtime_error` if context initialization failed
 * \throw `std::runtime_error` if context is already intialized
 */
void
init();

/// Initialize context using commandline arguments.
/**
 * \param argc the argument count
 * \param argv the argument vector
 * \throw `std::runtime_error` if context initialization failed
 * \throw `std::runtime_error` if context is already intialized
 */
void
init(int argc, char const * const argv[]);

/// Shut down context.
/**
 * \return true if successful, false otherwise
 */
bool
shutdown();

}  // namespace email

#endif  // EMAIL__INIT_HPP_
