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

#ifndef EMAIL__TYPES_HPP_
#define EMAIL__TYPES_HPP_

#define SHARED_PTR_CONST(name) \
  using SharedPtrConst = std::shared_ptr<const struct name>;

#include <memory>
#include <string>
#include <vector>

namespace email
{

/// Info for connecting to server.
struct ConnectionInfo
{
  /// Host name without protocol or port.
  std::string host;
  /// Username (i.e. email).
  std::string username;
  /// Password.
  std::string password;
};

/// Info for a standard protocol.
struct ProtocolInfo
{
  /// Protocol, i.e. "<protocol>://".
  std::string protocol;
  /// Port.
  int port;
};

/// Info for a user.
struct UserInfo
{
  /// SMTP host, without the port or protocol.
  std::string host_smtp;
  /// IMAP host, without the port or protocol.
  std::string host_imap;
  /// Username (i.e. email).
  std::string username;
  /// Password.
  std::string password;
  /// Constructor.
  UserInfo(
    const std::string & host_smtp_,
    const std::string & host_imap_,
    const std::string & username_,
    const std::string & password_)
  : host_smtp(host_smtp_), host_imap(host_imap_), username(username_), password(password_)
  {}
  SHARED_PTR_CONST(UserInfo)
};

/// Recipients of an email.
struct EmailRecipients
{
  /// The "to" emails.
  const std::vector<std::string> to;
  /// The "cc" emails.
  const std::vector<std::string> cc;
  /// The "bcc" emails.
  const std::vector<std::string> bcc;
  /// Default constructor.
  EmailRecipients(
    const std::vector<std::string> & to_,
    const std::vector<std::string> & cc_,
    const std::vector<std::string> & bcc_)
  : to(to_), cc(cc_), bcc(bcc_)
  {}
  /// Constructor with only a single "to" email.
  explicit EmailRecipients(const std::string & to_)
  : to({to_}), cc(), bcc()
  {}
  SHARED_PTR_CONST(EmailRecipients)
};

/// Content of an email.
struct EmailContent
{
  // Subject, which should be one line without any newlines
  std::string subject;
  // Body/content, which may have multiple lines
  std::string body;
};

}  // namespace email

#endif  // EMAIL__TYPES_HPP_
