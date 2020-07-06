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

#include <memory>
#include <string>

#include "email/context.hpp"
#include "email/email/sender.hpp"
#include "email/init.hpp"
#include "email/types.hpp"
#include "email/options.hpp"

int main(int argc, char ** argv)
{
  email::init(argc, argv);
  std::shared_ptr<email::Options> options = email::get_global_context()->get_options();
  if (!options->get_recipients().has_value()) {
    return 1;
  }
  email::EmailSender sender(
    *options->get_user_info().get(),
    *options->get_recipients().value().get());
  if (!sender.init()) {
    return 1;
  }
  const std::string subject = "this is the subject\nwoopsies";
  const std::string body = "this is the body!\nthis is on another line";
  bool ret = sender.send({subject, body});
  return ret ? 0 : 1;
}
