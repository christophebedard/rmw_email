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

#include "email/context.hpp"
#include "email/init.hpp"

namespace email
{

void init()
{
  get_global_context()->init();
}

void init(int argc, char const * const argv[])
{
  get_global_context()->init(argc, argv);
}

bool shutdown()
{
  return get_global_context()->shutdown();
}

}  // namespace email
