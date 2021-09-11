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

#ifndef EMAIL__MACROS_HPP_
#define EMAIL__MACROS_HPP_

#include <memory>

#define EMAIL_SHARED_PTR_CONST(name) \
  using SharedPtrConst = std::shared_ptr<const struct name>;

/**
 * Disables the copy constructor and operator= for the given class.
 *
 * Use in the private section of the class.
 */
#define EMAIL_DISABLE_COPY(...) \
  __VA_ARGS__(const __VA_ARGS__ &) = delete; \
  __VA_ARGS__ & operator=(const __VA_ARGS__ &) = delete;

/**
 * Declare std::shared_ptr<T>.
 */
#define EMAIL_SHARED_PTR(...) \
  using SharedPtr = std::shared_ptr<__VA_ARGS__>;

/**
 * Declare std::weak_ptr<T>.
 */
#define EMAIL_WEAK_PTR(...) \
  using WeakPtr = std::weak_ptr<__VA_ARGS__>;

#endif  // EMAIL__MACROS_HPP_
