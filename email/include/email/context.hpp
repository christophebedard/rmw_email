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

#ifndef EMAIL__CONTEXT_HPP_
#define EMAIL__CONTEXT_HPP_

#include <memory>
#include <string>

#include "email/curl_context.hpp"
#include "email/email_receiver.hpp"
#include "email/email_sender.hpp"
#include "email/options.hpp"
#include "email/types.hpp"
#include "email/visibility_control.hpp"

namespace email
{

// void init();
void init(int argc, char const * const argv[]);

bool shutdown();

class Context
{
public:
  Context();
  Context(const Context &) = delete;
  ~Context();

  // void init();
  void init(int argc, char const * const argv[]);

  bool shutdown();

  // bool is_valid();

  std::shared_ptr<Options> get_options();

  std::shared_ptr<EmailReceiver> get_receiver();
  std::shared_ptr<EmailSender> get_sender();

private:
  std::shared_ptr<Options> options_;
  bool is_valid_;
};

std::shared_ptr<Context> get_global_context();

}  // namespace email

#endif  // EMAIL__CONTEXT_HPP_
