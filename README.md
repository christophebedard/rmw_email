# rmw_email

![GitHub workflow status](https://github.com/christophebedard/rmw_email/workflows/Test/badge.svg)
[![License](https://img.shields.io/github/license/christophebedard/rmw_email)](https://github.com/christophebedard/rmw_email/blob/master/LICENSE)

## Configuration

In order to send & receive emails, a configuration file has to be provided.
By default, the path to the config file is `email.yml`, relative to the current working directory.
However, the path can be changed using the `EMAIL_CONFIG_FILE` environment variable, e.g. `EMAIL_CONFIG_FILE=other/dir/myemail.yml`.

A sample configuration file is provided: [`email.yml`](./email/email.yml).
As for the values:

   * `url-smtp`: SMTP server URL, e.g. `smtp.gmail.com` for GMail
   * `url-imap`: IMAP server URL, e.g. `imap.gmail.com` for GMail
   * `username`: your email
   * `password`: your password
      * it is recommended to generate a "unique" password. For GMail, that is an [app password](https://myaccount.google.com/apppasswords). Under *Select app*, click *Other (Custom name)* and simply enter something like *rmw_email*. Copy the generated password and paste it in the config file.
   * `to`/`cc`/`bcc`: recipients (comma-separated)

Note that you might want to use two different configuration files for two different executables/nodes.
