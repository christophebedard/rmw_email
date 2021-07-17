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

#ifndef EMAIL__GUARD_CONDITION_HPP_
#define EMAIL__GUARD_CONDITION_HPP_

#include <atomic>
#include <memory>
#include <stdexcept>

#include "email/log.hpp"
#include "email/macros.hpp"
#include "email/visibility_control.hpp"

namespace email
{

/// Guard condition already in use error.
class GuardConditionAlreadyInUseError : public std::runtime_error
{
public:
  GuardConditionAlreadyInUseError()
  : std::runtime_error("guard condition already in use")
  {}
};

/// Guard condition.
/**
 * Condition that can be waited on and triggered by another thread.
 * \see WaitSet
 */
class GuardCondition
{
public:
  /// Constructor.
  EMAIL_PUBLIC
  GuardCondition();

  EMAIL_PUBLIC
  ~GuardCondition();

  EMAIL_PUBLIC
  void
  trigger();

  EMAIL_PUBLIC
  bool
  triggered() const;

  EMAIL_PUBLIC
  bool
  exchange_in_use(bool in_use);

private:
  EMAIL_DISABLE_COPY(GuardCondition)

  std::shared_ptr<Logger> logger_;
  std::atomic<bool> in_use_;
  std::atomic<bool> triggered_;
};

}  // namespace email

#endif  // EMAIL__GUARD_CONDITION_HPP_
