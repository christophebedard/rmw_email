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

#include <atomic>
#include <memory>

#include "email/log.hpp"
#include "email/guard_condition.hpp"

namespace email
{

GuardCondition::GuardCondition()
: logger_(log::get_or_create("GuardCondition")),
  in_use_(false),
  triggered_(false)
{}

GuardCondition::~GuardCondition() {}

void
GuardCondition::trigger()
{
  triggered_.store(true);
}

bool
GuardCondition::triggered() const
{
  return triggered_.load();
}

bool
GuardCondition::exchange_in_use(bool in_use)
{
  return in_use_.exchange(in_use);
}

void
GuardCondition::reset()
{
  triggered_.store(false);
}

}  // namespace email
