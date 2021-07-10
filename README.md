# rmw_email

[![Latest GitHub tag](https://img.shields.io/github/v/tag/christophebedard/rmw_email?sort=semver&label=v)](https://github.com/christophebedard/rmw_email/tags)
![GitHub workflow status](https://github.com/christophebedard/rmw_email/workflows/Test/badge.svg)
[![codecov](https://codecov.io/gh/christophebedard/rmw_email/branch/master/graph/badge.svg?token=20FSAUKMDB)](https://codecov.io/gh/christophebedard/rmw_email)
[![License](https://img.shields.io/github/license/christophebedard/rmw_email)](https://github.com/christophebedard/rmw_email/blob/master/LICENSE)

ROS 2 over email.

## Configuration

In order to send & receive emails, a YAML configuration file has to be provided.
By default, the path to the config file is `email.yml`, relative to the current working directory.
However, the path can be changed using the `EMAIL_CONFIG_FILE` environment variable, e.g. `EMAIL_CONFIG_FILE=other/dir/myemail.yml`.
If that file does not exist, `~/email.yml` will be used as a backup.

A sample configuration file is provided: [`email.yml`](./email/email.yml).
As for the values:

   * `url-smtp`: SMTP server URL, e.g. `smtp.gmail.com` for Gmail
   * `url-imap`: IMAP server URL, e.g. `imap.gmail.com` for Gmail
   * `username`: your email
   * `password`: your password
      * it is recommended to generate a "unique" password. For Gmail, that is an [app password](https://myaccount.google.com/apppasswords). Under *Select app*, click *Other (Custom name)* and simply enter something like *rmw_email*. Copy the generated password and paste it in the config file.
   * `to`/`cc`/`bcc`: recipients
      * either as simple string values or as an array of string values, e.g.:
         ```yaml
         to: my@email.com
         cc:
           - some@email.com
           - another@email.com
         ```
      * `to` must be defined and must contain at least one email address, but `cc` and `bcc` are optional

Note that you might want to use two different configuration files for two different executables/nodes.

## Debugging

There are a few ways to debug:

1. Set the `EMAIL_CURL_VERBOSE` environment variable to be non-empty, e.g. `EMAIL_CURL_VERBOSE=y`. This will enable libcurl's verbose option.
   * Generally produces too much output to be useful.
1. Set the logging level to "debug" through the `EMAIL_LOG_LEVEL` environment variable, e.g. `EMAIL_LOG_LEVEL=debug`.
   * The logging levels are: `off`, `debug`, `info`, `warn`, `error`, and `fatal`.
   * The default level is `info`.
1. Write all logs to a file by setting the `EMAIL_LOG_FILE` environment variable to a file path.
   * This writes all logs to the file, independently of the logging level set through `EMAIL_LOG_LEVEL`.
   * A leading `~` is expanded to the user's home directory.
