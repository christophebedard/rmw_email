<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.1">
  <compound kind="file">
    <name>communication_info.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>communication__info_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="timestamp_8hpp" name="timestamp.hpp" local="yes" imported="no">email/timestamp.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::CommunicationInfo</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>context.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>context_8hpp.html</filename>
    <includes id="curl_2context_8hpp" name="context.hpp" local="yes" imported="no">email/curl/context.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="polling__manager_8hpp" name="polling_manager.hpp" local="yes" imported="no">email/email/polling_manager.hpp</includes>
    <includes id="receiver_8hpp" name="receiver.hpp" local="yes" imported="no">email/email/receiver.hpp</includes>
    <includes id="sender_8hpp" name="sender.hpp" local="yes" imported="no">email/email/sender.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="options_8hpp" name="options.hpp" local="yes" imported="no">email/options.hpp</includes>
    <includes id="service__handler_8hpp" name="service_handler.hpp" local="yes" imported="no">email/service_handler.hpp</includes>
    <includes id="subscription__handler_8hpp" name="subscription_handler.hpp" local="yes" imported="no">email/subscription_handler.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::ContextError</class>
    <class kind="class">email::ContextNotInitializedError</class>
    <class kind="class">email::ContextAlreadyInitializedError</class>
    <class kind="class">email::ContextInitFailedError</class>
    <class kind="class">email::Context</class>
    <namespace>email</namespace>
    <member kind="function">
      <type>std::shared_ptr&lt; Context &gt;</type>
      <name>get_global_context</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a32664596f7a3d0177434519dc03ea38d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>context.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/curl/</path>
    <filename>curl_2context_8hpp.html</filename>
    <includes id="curl_2info_8hpp" name="info.hpp" local="yes" imported="no">email/curl/info.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="yes" imported="no">email/utils.hpp</includes>
    <class kind="class">email::CurlContext</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>executor.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/curl/</path>
    <filename>executor_8hpp.html</filename>
    <includes id="curl_2context_8hpp" name="context.hpp" local="yes" imported="no">email/curl/context.hpp</includes>
    <includes id="curl_2info_8hpp" name="info.hpp" local="yes" imported="no">email/curl/info.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::CurlExecutor</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>info.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/curl/</path>
    <filename>curl_2info_8hpp.html</filename>
    <class kind="struct">email::ConnectionInfo</class>
    <class kind="struct">email::ProtocolInfo</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>info.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>email_2info_8hpp.html</filename>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <class kind="struct">email::UserInfo</class>
    <class kind="struct">email::EmailRecipients</class>
    <class kind="struct">email::EmailContent</class>
    <class kind="struct">email::EmailData</class>
    <class kind="struct">fmt::formatter&lt; email::EmailRecipients &gt;</class>
    <class kind="struct">fmt::formatter&lt; email::EmailContent &gt;</class>
    <class kind="struct">fmt::formatter&lt; email::EmailHeaders &gt;</class>
    <class kind="struct">fmt::formatter&lt; email::EmailData &gt;</class>
    <namespace>email</namespace>
    <member kind="typedef">
      <type>std::map&lt; std::string, std::string &gt;</type>
      <name>EmailHeaders</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ae41e6fb7cb5a3b87ee3effdc2aa2065f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>EmailHeaders::value_type</type>
      <name>EmailHeader</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a79f0f6247c3270688400eb20c9564c96</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>email.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>email_8hpp.html</filename>
    <includes id="init_8hpp" name="init.hpp" local="yes" imported="no">email/init.hpp</includes>
    <includes id="publisher_8hpp" name="publisher.hpp" local="yes" imported="no">email/publisher.hpp</includes>
    <includes id="service__client_8hpp" name="service_client.hpp" local="yes" imported="no">email/service_client.hpp</includes>
    <includes id="service__server_8hpp" name="service_server.hpp" local="yes" imported="no">email/service_server.hpp</includes>
    <includes id="subscription_8hpp" name="subscription.hpp" local="yes" imported="no">email/subscription.hpp</includes>
    <includes id="wait_8hpp" name="wait.hpp" local="yes" imported="no">email/wait.hpp</includes>
    <includes id="wait__set_8hpp" name="wait_set.hpp" local="yes" imported="no">email/wait_set.hpp</includes>
  </compound>
  <compound kind="file">
    <name>curl_receiver.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>curl__receiver_8hpp.html</filename>
    <includes id="executor_8hpp" name="executor.hpp" local="yes" imported="no">email/curl/executor.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="receiver_8hpp" name="receiver.hpp" local="yes" imported="no">email/email/receiver.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::CurlEmailReceiver</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>curl_sender.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>curl__sender_8hpp.html</filename>
    <includes id="executor_8hpp" name="executor.hpp" local="yes" imported="no">email/curl/executor.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="sender_8hpp" name="sender.hpp" local="yes" imported="no">email/email/sender.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::CurlEmailSender</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>handler.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>handler_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="polling__manager_8hpp" name="polling_manager.hpp" local="yes" imported="no">email/email/polling_manager.hpp</includes>
    <class kind="class">email::EmailHandler</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>intra_receiver.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>intra__receiver_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="receiver_8hpp" name="receiver.hpp" local="yes" imported="no">email/email/receiver.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="safe__queue_8hpp" name="safe_queue.hpp" local="yes" imported="no">email/safe_queue.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::IntraEmailReceiver</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>intra_sender.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>intra__sender_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="intra__receiver_8hpp" name="intra_receiver.hpp" local="yes" imported="no">email/email/intra_receiver.hpp</includes>
    <includes id="sender_8hpp" name="sender.hpp" local="yes" imported="no">email/email/sender.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::IntraEmailSender</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>payload_utils.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>payload__utils_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <namespace>email</namespace>
    <namespace>email::utils</namespace>
    <namespace>email::utils::payload</namespace>
    <member kind="function">
      <type>const std::string</type>
      <name>build_payload</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>ad30b9776687e2e98638b32759ad2bc3d</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;to, const std::vector&lt; std::string &gt; &amp;cc, const std::vector&lt; std::string &gt; &amp;bcc, const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt, std::optional&lt; std::string &gt; reply_ref=std::nullopt)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>build_payload</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>ac522857948a8c609ea73e96600cb8e2a</anchor>
      <arglist>(EmailRecipients::SharedPtrConst recipients, const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt, std::optional&lt; std::string &gt; reply_ref=std::nullopt)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>join_list</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>ae288cd99e7a54273aea6372c959f76c9</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;list)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>cut_string_if_newline</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>a455c37a8a129ddcf90c1835f001c0579</anchor>
      <arglist>(const std::string &amp;string)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>polling_manager.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>polling__manager_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="receiver_8hpp" name="receiver.hpp" local="yes" imported="no">email/email/receiver.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::PollingManager</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>receiver.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>receiver_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::EmailReceiver</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>response_utils.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>response__utils_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <namespace>email</namespace>
    <namespace>email::utils</namespace>
    <namespace>email::utils::response</namespace>
    <member kind="function">
      <type>std::optional&lt; int &gt;</type>
      <name>get_nextuid_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a86761af16b95987441640bea6861132a</anchor>
      <arglist>(const std::string &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>EmailHeaders</type>
      <name>get_email_headers_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a5a53dc0d1ceb86baec63678cc7dc060b</anchor>
      <arglist>(const std::string &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; struct EmailContent &gt;</type>
      <name>get_email_content_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a6b5d710f645d106f79a0c1d15c7f9d75</anchor>
      <arglist>(const std::string &amp;response, EmailHeaders &amp;headers)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; struct EmailData &gt;</type>
      <name>get_email_data_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a653d46e023a23fecac67b8b95e32ff6b</anchor>
      <arglist>(const std::string &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::string &gt;</type>
      <name>get_header_value</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a30fbb8f3e4152b10b3998d176b5212d0</anchor>
      <arglist>(const std::string &amp;header_name, const EmailHeaders &amp;headers)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sender.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/email/</path>
    <filename>sender_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::EmailSender</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>gid.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>gid_8hpp.html</filename>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::Gid</class>
    <class kind="struct">fmt::formatter&lt; email::Gid &gt;</class>
    <namespace>email</namespace>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>GidValue</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a75eac80413e3a15a1adff727b822a70c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gid_object.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>gid__object_8hpp.html</filename>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <class kind="class">email::GidObject</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>guard_condition.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>guard__condition_8hpp.html</filename>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::GuardConditionAlreadyInUseError</class>
    <class kind="class">email::GuardCondition</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>init.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>init_8hpp.html</filename>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <namespace>email</namespace>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a3d225be7f22f802190fb1f2e49f5b1d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a31064318c3c135912c70c384f25d3305</anchor>
      <arglist>(int argc, char const *const argv[])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>shutdown</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a7a0e2779940792a4753a9b163fd1bbc4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>log.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>log_8hpp.html</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="yes" imported="no">email/utils.hpp</includes>
    <class kind="class">email::log::LoggingError</class>
    <class kind="class">email::log::LoggingNotInitializedError</class>
    <class kind="struct">fmt::formatter&lt; rcpputils::fs::path &gt;</class>
    <class kind="struct">fmt::formatter&lt; YAML::Node &gt;</class>
    <namespace>email</namespace>
    <namespace>email::log</namespace>
    <member kind="typedef">
      <type>spdlog::logger</type>
      <name>Logger</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a8d76c558a86ae3983f1b8f138c036e61</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>debug</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fab854c88759c3923a679b84586ca1197c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>info</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8faa7c9183950be07c0f6e85a5b10a45087</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>warn</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fa3e9bbe69f71687a336604c2482f4366c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>error</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8faba726552e49985a6cc8f897f16e99793</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>fatal</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fa6df5a6c39d2a59dd7477e58e07c0bffa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>off</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fa0d42315cc89e99a312b0445743128878</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a70e2c4b9640f8b10a086f14269d4681d</anchor>
      <arglist>(const Level &amp;level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_from_env</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>aba50b69230431fca149b16fe3fbcaa9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; Logger &gt;</type>
      <name>create</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a82cb3ebe95d6b4e4bc16fd417bf65b8e</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; Logger &gt;</type>
      <name>get_or_create</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>ab5f6effef314d9faef6dee3b4d78f4ce</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>remove</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>aae637767284f0246349f0c09c4a7b30f</anchor>
      <arglist>(const std::shared_ptr&lt; Logger &gt; &amp;logger)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shutdown</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>ab7f5f3d63616c0073e304d2b20f86841</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>lttng.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>lttng_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_TRACEPOINT</name>
      <anchorfile>lttng_8hpp.html</anchorfile>
      <anchor>a41a6d81b1a679e3ef9d0f0ada1e3cbd3</anchor>
      <arglist>(event_name,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>macros.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>macros_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_SHARED_PTR_CONST</name>
      <anchorfile>macros_8hpp.html</anchorfile>
      <anchor>a63182df5328e6f5ffc3eb22859132adf</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_DISABLE_COPY</name>
      <anchorfile>macros_8hpp.html</anchorfile>
      <anchor>a976d2e468dffeeeb1bf3ca99c127fa4e</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_SHARED_PTR</name>
      <anchorfile>macros_8hpp.html</anchorfile>
      <anchor>ad5446eac67f26846b66708ecf55bf0aa</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_WEAK_PTR</name>
      <anchorfile>macros_8hpp.html</anchorfile>
      <anchor>afb828ba1d458a13870c719025fcbf806</anchor>
      <arglist>(...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>message_info.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>message__info_8hpp.html</filename>
    <includes id="communication__info_8hpp" name="communication_info.hpp" local="yes" imported="no">email/communication_info.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="timestamp_8hpp" name="timestamp.hpp" local="yes" imported="no">email/timestamp.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::MessageInfo</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>named_object.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>named__object_8hpp.html</filename>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <class kind="class">email::ObjectNameInvalidError</class>
    <class kind="class">email::NamedObject</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>options.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>options_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::Options</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>pub_sub.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>pub__sub_8hpp.html</filename>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="gid__object_8hpp" name="gid_object.hpp" local="yes" imported="no">email/gid_object.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="named__object_8hpp" name="named_object.hpp" local="yes" imported="no">email/named_object.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::TopicNameInvalidError</class>
    <class kind="class">email::PubSubObject</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>publisher.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>publisher_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="sender_8hpp" name="sender.hpp" local="yes" imported="no">email/email/sender.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="pub__sub_8hpp" name="pub_sub.hpp" local="yes" imported="no">email/pub_sub.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::Publisher</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>safe_map.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>safe__map_8hpp.html</filename>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <class kind="class">email::SafeMap</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>safe_queue.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>safe__queue_8hpp.html</filename>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <class kind="class">email::SafeQueue</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>service.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>service_8hpp.html</filename>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="gid__object_8hpp" name="gid_object.hpp" local="yes" imported="no">email/gid_object.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="named__object_8hpp" name="named_object.hpp" local="yes" imported="no">email/named_object.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::ServiceNameInvalidError</class>
    <class kind="class">email::ServiceObject</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>service_client.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>service__client_8hpp.html</filename>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="publisher_8hpp" name="publisher.hpp" local="yes" imported="no">email/publisher.hpp</includes>
    <includes id="safe__map_8hpp" name="safe_map.hpp" local="yes" imported="no">email/safe_map.hpp</includes>
    <includes id="service_8hpp" name="service.hpp" local="yes" imported="no">email/service.hpp</includes>
    <includes id="service__handler_8hpp" name="service_handler.hpp" local="yes" imported="no">email/service_handler.hpp</includes>
    <includes id="service__info_8hpp" name="service_info.hpp" local="yes" imported="no">email/service_info.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::ServiceClient</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>service_handler.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>service__handler_8hpp.html</filename>
    <includes id="handler_8hpp" name="handler.hpp" local="yes" imported="no">email/email/handler.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="polling__manager_8hpp" name="polling_manager.hpp" local="yes" imported="no">email/email/polling_manager.hpp</includes>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="safe__map_8hpp" name="safe_map.hpp" local="yes" imported="no">email/safe_map.hpp</includes>
    <includes id="safe__queue_8hpp" name="safe_queue.hpp" local="yes" imported="no">email/safe_queue.hpp</includes>
    <includes id="service__info_8hpp" name="service_info.hpp" local="yes" imported="no">email/service_info.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::ServiceHandler</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>service_info.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>service__info_8hpp.html</filename>
    <includes id="communication__info_8hpp" name="communication_info.hpp" local="yes" imported="no">email/communication_info.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="timestamp_8hpp" name="timestamp.hpp" local="yes" imported="no">email/timestamp.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::ServiceInfo</class>
    <namespace>email</namespace>
    <member kind="typedef">
      <type>int64_t</type>
      <name>SequenceNumber</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a0de800b4ba159d6e3892ce756a690103</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>service_request.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>service__request_8hpp.html</filename>
    <includes id="gid_8hpp" name="gid.hpp" local="yes" imported="no">email/gid.hpp</includes>
    <includes id="service__info_8hpp" name="service_info.hpp" local="yes" imported="no">email/service_info.hpp</includes>
    <class kind="struct">email::ServiceRequestId</class>
    <class kind="struct">email::ServiceRequest</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>service_server.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>service__server_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="sender_8hpp" name="sender.hpp" local="yes" imported="no">email/email/sender.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="safe__queue_8hpp" name="safe_queue.hpp" local="yes" imported="no">email/safe_queue.hpp</includes>
    <includes id="service_8hpp" name="service.hpp" local="yes" imported="no">email/service.hpp</includes>
    <includes id="service__handler_8hpp" name="service_handler.hpp" local="yes" imported="no">email/service_handler.hpp</includes>
    <includes id="service__info_8hpp" name="service_info.hpp" local="yes" imported="no">email/service_info.hpp</includes>
    <includes id="service__request_8hpp" name="service_request.hpp" local="yes" imported="no">email/service_request.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::ServiceServer</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>subscription.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>subscription_8hpp.html</filename>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="message__info_8hpp" name="message_info.hpp" local="yes" imported="no">email/message_info.hpp</includes>
    <includes id="pub__sub_8hpp" name="pub_sub.hpp" local="yes" imported="no">email/pub_sub.hpp</includes>
    <includes id="safe__queue_8hpp" name="safe_queue.hpp" local="yes" imported="no">email/safe_queue.hpp</includes>
    <includes id="subscription__handler_8hpp" name="subscription_handler.hpp" local="yes" imported="no">email/subscription_handler.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::Subscription</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>subscription_handler.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>subscription__handler_8hpp.html</filename>
    <includes id="handler_8hpp" name="handler.hpp" local="yes" imported="no">email/email/handler.hpp</includes>
    <includes id="email_2info_8hpp" name="info.hpp" local="yes" imported="no">email/email/info.hpp</includes>
    <includes id="polling__manager_8hpp" name="polling_manager.hpp" local="yes" imported="no">email/email/polling_manager.hpp</includes>
    <includes id="safe__queue_8hpp" name="safe_queue.hpp" local="yes" imported="no">email/safe_queue.hpp</includes>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="message__info_8hpp" name="message_info.hpp" local="yes" imported="no">email/message_info.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::SubscriptionHandler</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>timestamp.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>timestamp_8hpp.html</filename>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::Timestamp</class>
    <class kind="struct">fmt::formatter&lt; email::Timestamp &gt;</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="file">
    <name>utils.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>utils_8hpp.html</filename>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <namespace>email</namespace>
    <namespace>email::utils</namespace>
    <member kind="function">
      <type>std::string</type>
      <name>string_format</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a36d04ae0600a820016e9a547222bad1a</anchor>
      <arglist>(const std::string &amp;format, Args... args)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_env_var</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a48891b8793ba17bf280aef8d8c62f392</anchor>
      <arglist>(const std::string &amp;env_var)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_env_var_or_default</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>ae02d06fc8aab9fc0e6c0e2f08e4bb976</anchor>
      <arglist>(const std::string &amp;env_var, const std::string &amp;default_value)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::string &gt;</type>
      <name>read_file</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a88a5169377c5fdee4455ee6b38723745</anchor>
      <arglist>(const std::string &amp;path)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>split_email_list</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a45df7fc739ac9b6a5f5f8dd28eec92e1</anchor>
      <arglist>(const std::string &amp;list, const bool has_space_after_comma=false)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>split_email_list</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>aef6154f77c351ae81abb1544e8a5f3fd</anchor>
      <arglist>(const YAML::Node &amp;node)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>yaml_to_string</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a82ee838f6167a4af1146f59b82a26933</anchor>
      <arglist>(const YAML::Node &amp;node)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>full_url</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a40a0b74a4dfabc0575e10367ff64f14f</anchor>
      <arglist>(const std::string &amp;protocol, const std::string &amp;host, const int port)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; uint32_t &gt;</type>
      <name>optional_stoul</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a1426a6b72c22a41e717f2dddb9fe6f47</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; int &gt;</type>
      <name>optional_stoi</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a2a5c92f770d0c27fefe339dd2ba426a1</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; int64_t &gt;</type>
      <name>optional_stoll</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a205d62958aa3a9111c4c17da561743fc</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>thread_get_name</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a3f1ec15b0fb2fe7708248d9144068e69</anchor>
      <arglist>(char *name, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>thread_set_name</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>abb5cc15dac76b938b897a32a94d29387</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>thread_append_name</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a6de7445821178c24df09d19ede5b3700</anchor>
      <arglist>(const char *suffix)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>visibility_control.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>visibility__control_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_EXPORT</name>
      <anchorfile>visibility__control_8hpp.html</anchorfile>
      <anchor>a94c93836ac70e948a23100bef086e18d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_IMPORT</name>
      <anchorfile>visibility__control_8hpp.html</anchorfile>
      <anchor>a43b93e86e1237b12352cbe1a0bf6037b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_PUBLIC</name>
      <anchorfile>visibility__control_8hpp.html</anchorfile>
      <anchor>a87d02dff5661f1945bc5f4a77097bf75</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_LOCAL</name>
      <anchorfile>visibility__control_8hpp.html</anchorfile>
      <anchor>a6d306507fc30a742b84e4618b31f0a06</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EMAIL_PUBLIC_TYPE</name>
      <anchorfile>visibility__control_8hpp.html</anchorfile>
      <anchor>a5c16dda9cae66fb57f21b90ad814a120</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>wait.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>wait_8hpp.html</filename>
    <includes id="message__info_8hpp" name="message_info.hpp" local="yes" imported="no">email/message_info.hpp</includes>
    <includes id="service__client_8hpp" name="service_client.hpp" local="yes" imported="no">email/service_client.hpp</includes>
    <includes id="service__info_8hpp" name="service_info.hpp" local="yes" imported="no">email/service_info.hpp</includes>
    <includes id="service__request_8hpp" name="service_request.hpp" local="yes" imported="no">email/service_request.hpp</includes>
    <includes id="service__server_8hpp" name="service_server.hpp" local="yes" imported="no">email/service_server.hpp</includes>
    <includes id="subscription_8hpp" name="subscription.hpp" local="yes" imported="no">email/subscription.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <namespace>email</namespace>
    <member kind="function">
      <type>std::pair&lt; std::string, MessageInfo &gt;</type>
      <name>wait_for_message_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>aa59c37dd2056e5079d933232a16a3396</anchor>
      <arglist>(Subscription *subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, MessageInfo &gt;</type>
      <name>wait_for_message_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a03feb199db737e274a1e6f0750d203a6</anchor>
      <arglist>(std::shared_ptr&lt; Subscription &gt; subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_message</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ab5721e49aa88b793a84361690e62cff6</anchor>
      <arglist>(Subscription *subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_message</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ae337962e644aa83d44bb241471fcb5a2</anchor>
      <arglist>(std::shared_ptr&lt; Subscription &gt; subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, ServiceInfo &gt;</type>
      <name>wait_for_response_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a79fde927095f94957025da12c6283edb</anchor>
      <arglist>(const SequenceNumber sequence_number, ServiceClient *client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, ServiceInfo &gt;</type>
      <name>wait_for_response_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a2cdbe450415e49215d4a2d869eb577e7</anchor>
      <arglist>(const SequenceNumber sequence_number, std::shared_ptr&lt; ServiceClient &gt; client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_response</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a5f80f51854175a635e2ce28ec401e8a9</anchor>
      <arglist>(const SequenceNumber sequence_number, ServiceClient *client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_response</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a81ce8fcb498eb5e3074e69043bccbff0</anchor>
      <arglist>(const SequenceNumber sequence_number, std::shared_ptr&lt; ServiceClient &gt; client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; struct ServiceRequest, ServiceInfo &gt;</type>
      <name>wait_for_request_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ad5dd2091a29213c9aa3859d817376d10</anchor>
      <arglist>(ServiceServer *server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; struct ServiceRequest, ServiceInfo &gt;</type>
      <name>wait_for_request_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>afdc469e72e9b1ab69445fdb82082f050</anchor>
      <arglist>(std::shared_ptr&lt; ServiceServer &gt; server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>struct ServiceRequest</type>
      <name>wait_for_request</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ad0a6b760f7e08068416acceebb60a199</anchor>
      <arglist>(ServiceServer *server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>struct ServiceRequest</type>
      <name>wait_for_request</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a7dfbb8a3972445ace7e5b33b3b8cf18e</anchor>
      <arglist>(std::shared_ptr&lt; ServiceServer &gt; server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>wait_set.hpp</name>
    <path>/home/runner/work/rmw_email/rmw_email/rmw_email/email/include/email/</path>
    <filename>wait__set_8hpp.html</filename>
    <includes id="log_8hpp" name="log.hpp" local="yes" imported="no">email/log.hpp</includes>
    <includes id="guard__condition_8hpp" name="guard_condition.hpp" local="yes" imported="no">email/guard_condition.hpp</includes>
    <includes id="service__client_8hpp" name="service_client.hpp" local="yes" imported="no">email/service_client.hpp</includes>
    <includes id="service__server_8hpp" name="service_server.hpp" local="yes" imported="no">email/service_server.hpp</includes>
    <includes id="subscription_8hpp" name="subscription.hpp" local="yes" imported="no">email/subscription.hpp</includes>
    <includes id="macros_8hpp" name="macros.hpp" local="yes" imported="no">email/macros.hpp</includes>
    <includes id="visibility__control_8hpp" name="visibility_control.hpp" local="yes" imported="no">email/visibility_control.hpp</includes>
    <class kind="class">email::WaitSet</class>
    <namespace>email</namespace>
  </compound>
  <compound kind="class">
    <name>email::CommunicationInfo</name>
    <filename>classemail_1_1CommunicationInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>CommunicationInfo</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>aa83f5465d5c50fe678aa9329afba8e9f</anchor>
      <arglist>(const Timestamp &amp;source_timestamp, const Timestamp &amp;received_timestamp, const Gid &amp;source_gid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CommunicationInfo</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>aa2e99492c54b6d24fddfd1fab62ec833</anchor>
      <arglist>(const CommunicationInfo &amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CommunicationInfo</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>a6e0097239f585e0bfae824fc3ac94f3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Timestamp &amp;</type>
      <name>source_timestamp</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>a690cb702fb6fd6767d0fc2915a21084c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Timestamp &amp;</type>
      <name>received_timestamp</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>a51f763fcc089f6bba8234c9193d476bf</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Gid &amp;</type>
      <name>source_gid</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>a0e848c80f65edbbb7f3a1df3af47ab9d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; CommunicationInfo &gt;</type>
      <name>from_headers</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>ad3cff0500c8627f61a85cd745e049403</anchor>
      <arglist>(const EmailHeaders &amp;headers, const std::string &amp;source_gid_header)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>HEADER_SOURCE_TIMESTAMP</name>
      <anchorfile>classemail_1_1CommunicationInfo.html</anchorfile>
      <anchor>a622376971c805f20168100d046ac1fa9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::ConnectionInfo</name>
    <filename>structemail_1_1ConnectionInfo.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>host</name>
      <anchorfile>structemail_1_1ConnectionInfo.html</anchorfile>
      <anchor>a2432cbfd520eba7169a0da728998b0ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>username</name>
      <anchorfile>structemail_1_1ConnectionInfo.html</anchorfile>
      <anchor>ae80c12163b0f5c970949cd2ba916c101</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>password</name>
      <anchorfile>structemail_1_1ConnectionInfo.html</anchorfile>
      <anchor>a3be0ffc294c7adbd3789080f627d7101</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::Context</name>
    <filename>classemail_1_1Context.html</filename>
    <member kind="function">
      <type></type>
      <name>Context</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a83781e2984ad65b512ae6e8575e4bb40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Context</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a468df36ab9aafe4451b8ceaf5bf7fced</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a5cb569c5c2022ad609434a0407e5d12a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>ad3b1f40974f3d60bad995af07afcdad9</anchor>
      <arglist>(int argc, char const *const argv[])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>shutdown</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>acd290417c0afb3a27f635a7e7ad34b1a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a3cfe3bd2a1d5ab27c9c249474b13f4a3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; Options &gt;</type>
      <name>get_options</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a5e93b3ce58fa2cd5f99bb11f87a42129</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; EmailReceiver &gt;</type>
      <name>get_receiver</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a2754eb1610b656e5f2938d4c498660e5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; EmailSender &gt;</type>
      <name>get_sender</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a418192e88b8dc0abc13f9a4a2cf69d7f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; PollingManager &gt;</type>
      <name>get_polling_manager</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a60a73157c8f1dc0029bbbc519f4a5ffd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; SubscriptionHandler &gt;</type>
      <name>get_subscription_handler</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>abeaf1ab14e801b1ae8f2d15bee3c8bd3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; ServiceHandler &gt;</type>
      <name>get_service_handler</name>
      <anchorfile>classemail_1_1Context.html</anchorfile>
      <anchor>a92ea51482059927667585017b1730dd0</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ContextAlreadyInitializedError</name>
    <filename>classemail_1_1ContextAlreadyInitializedError.html</filename>
    <base>email::ContextError</base>
    <member kind="function">
      <type></type>
      <name>ContextAlreadyInitializedError</name>
      <anchorfile>classemail_1_1ContextAlreadyInitializedError.html</anchorfile>
      <anchor>a3a59f50c7a27533d9190128c41740e08</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ContextError</name>
    <filename>classemail_1_1ContextError.html</filename>
    <member kind="function">
      <type></type>
      <name>ContextError</name>
      <anchorfile>classemail_1_1ContextError.html</anchorfile>
      <anchor>aff88898a3f013d39dc254b1d0e29656c</anchor>
      <arglist>(const std::string &amp;msg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ContextInitFailedError</name>
    <filename>classemail_1_1ContextInitFailedError.html</filename>
    <base>email::ContextError</base>
    <member kind="function">
      <type></type>
      <name>ContextInitFailedError</name>
      <anchorfile>classemail_1_1ContextInitFailedError.html</anchorfile>
      <anchor>af6b1acc781a3363ca982676c6d6893cc</anchor>
      <arglist>(std::optional&lt; std::string &gt; reason=std::nullopt)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ContextNotInitializedError</name>
    <filename>classemail_1_1ContextNotInitializedError.html</filename>
    <base>email::ContextError</base>
    <member kind="function">
      <type></type>
      <name>ContextNotInitializedError</name>
      <anchorfile>classemail_1_1ContextNotInitializedError.html</anchorfile>
      <anchor>af8441171b76eac03a72960bee5211620</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::CurlContext</name>
    <filename>classemail_1_1CurlContext.html</filename>
    <member kind="function">
      <type></type>
      <name>CurlContext</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>a05805020a023b47fab92985e7c21ce3e</anchor>
      <arglist>(const struct ConnectionInfo &amp;connection_info, const struct ProtocolInfo &amp;protocol_info, const bool curl_verbose)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CurlContext</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>ababd71abdd6235340dd2eef62959b71e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>init</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>afecdec140c06377b37f90d5b6e1d08aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fini</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>a279da87c494f8647d1e688a43bf1ed2a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>execute</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>a0eaa473cb92d0f8a608df01ee33d54ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>CURL *</type>
      <name>get_handle</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>aac5561bf32e05ce657b348fcfd2f2e01</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>get_full_url</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>a14124af9ca8da6dece85f64e79689469</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const struct ConnectionInfo &amp;</type>
      <name>get_connection_info</name>
      <anchorfile>classemail_1_1CurlContext.html</anchorfile>
      <anchor>a167a9a69eebe08cf168048c3319f4b23</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::CurlEmailReceiver</name>
    <filename>classemail_1_1CurlEmailReceiver.html</filename>
    <base>email::EmailReceiver</base>
    <base>email::CurlExecutor</base>
    <member kind="function">
      <type></type>
      <name>CurlEmailReceiver</name>
      <anchorfile>classemail_1_1CurlEmailReceiver.html</anchorfile>
      <anchor>a6923b1242fbb12b56ded6e9800c5c252</anchor>
      <arglist>(UserInfo::SharedPtrConst user_info, const bool curl_verbose)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CurlEmailReceiver</name>
      <anchorfile>classemail_1_1CurlEmailReceiver.html</anchorfile>
      <anchor>a14ff395707e713ab7616fa2c39ee6a6a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::optional&lt; struct EmailData &gt;</type>
      <name>get_email</name>
      <anchorfile>classemail_1_1CurlEmailReceiver.html</anchorfile>
      <anchor>a7d020227e4a7e769e886310d6f27f653</anchor>
      <arglist>(std::optional&lt; std::chrono::nanoseconds &gt; polling_period=std::nullopt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>init_options</name>
      <anchorfile>classemail_1_1CurlEmailReceiver.html</anchorfile>
      <anchor>a5301e5427dedada2756b458137ac0c89</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::CurlEmailSender</name>
    <filename>classemail_1_1CurlEmailSender.html</filename>
    <base>email::EmailSender</base>
    <base>email::CurlExecutor</base>
    <member kind="function">
      <type></type>
      <name>CurlEmailSender</name>
      <anchorfile>classemail_1_1CurlEmailSender.html</anchorfile>
      <anchor>a3be4b4a980e15114735e55ecfbee0d74</anchor>
      <arglist>(UserInfo::SharedPtrConst user_info, EmailRecipients::SharedPtrConst recipients, const bool curl_verbose)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CurlEmailSender</name>
      <anchorfile>classemail_1_1CurlEmailSender.html</anchorfile>
      <anchor>ab42fc6136b2c5b1dc83c346e221df588</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>send</name>
      <anchorfile>classemail_1_1CurlEmailSender.html</anchorfile>
      <anchor>a8aacb118cf3750a293f1b48e8c035252</anchor>
      <arglist>(const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>reply</name>
      <anchorfile>classemail_1_1CurlEmailSender.html</anchorfile>
      <anchor>a1abbf80344254931d8107ef757a2a13a</anchor>
      <arglist>(const struct EmailContent &amp;content, const struct EmailData &amp;email, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>init_options</name>
      <anchorfile>classemail_1_1CurlEmailSender.html</anchorfile>
      <anchor>a2d3d8d8ad4f4f94e2ac3aaabab3b86c1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::CurlExecutor</name>
    <filename>classemail_1_1CurlExecutor.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>init</name>
      <anchorfile>classemail_1_1CurlExecutor.html</anchorfile>
      <anchor>aa00b5d609f9ebeead4f82afaf5f0e3f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classemail_1_1CurlExecutor.html</anchorfile>
      <anchor>ab0752abd31f6fff2cba1ca0de2e10a3c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>CurlExecutor</name>
      <anchorfile>classemail_1_1CurlExecutor.html</anchorfile>
      <anchor>a1e0617765bd8951450ad9aa9f6ae2174</anchor>
      <arglist>(const struct ConnectionInfo &amp;connection_info, const struct ProtocolInfo &amp;protocol_info, const bool curl_verbose)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~CurlExecutor</name>
      <anchorfile>classemail_1_1CurlExecutor.html</anchorfile>
      <anchor>a6052227ea05131b3dd23ac5c929caaa8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>init_options</name>
      <anchorfile>classemail_1_1CurlExecutor.html</anchorfile>
      <anchor>adbb7b4a2ce5bb123945c8f7aecc40a08</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CurlContext</type>
      <name>context_</name>
      <anchorfile>classemail_1_1CurlExecutor.html</anchorfile>
      <anchor>a676e59d46679416f46930f314f760b0d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::EmailContent</name>
    <filename>structemail_1_1EmailContent.html</filename>
    <member kind="function">
      <type></type>
      <name>EmailContent</name>
      <anchorfile>structemail_1_1EmailContent.html</anchorfile>
      <anchor>af724d227f2cde94a19ca2881ca257d54</anchor>
      <arglist>(const std::string &amp;subject_, const std::string &amp;body_)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EmailContent</name>
      <anchorfile>structemail_1_1EmailContent.html</anchorfile>
      <anchor>a7ad63ee616d71ace6311eb40899c3e7a</anchor>
      <arglist>(const EmailContent &amp;)=default</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>subject</name>
      <anchorfile>structemail_1_1EmailContent.html</anchorfile>
      <anchor>a77bd9eb7cbea591d799bcc305e43b611</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>body</name>
      <anchorfile>structemail_1_1EmailContent.html</anchorfile>
      <anchor>aee35c198a24df4a44429242f2349f252</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::EmailData</name>
    <filename>structemail_1_1EmailData.html</filename>
    <member kind="function">
      <type></type>
      <name>EmailData</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>a9f77470450820644aaa39f4f56cd0600</anchor>
      <arglist>(const std::string &amp;message_id_, const std::string &amp;in_reply_to_, const std::string &amp;from_, const struct EmailRecipients &amp;recipients_, const struct EmailContent &amp;content_, std::optional&lt; EmailHeaders &gt; additional_headers_=std::nullopt)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EmailData</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>a46c7549ef1fe19897e30d030eab50127</anchor>
      <arglist>(const EmailData &amp;)=default</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>message_id</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>ae160e414dfee99357f5a2e0252ac1278</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>in_reply_to</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>ab897397c43749238bb5b120f94558844</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>from</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>a2e5bee79a2fd21d2f47090eb3c84c08b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct EmailRecipients</type>
      <name>recipients</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>a10accb9e498602cf7841471741e41fdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct EmailContent</type>
      <name>content</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>a04533d7a6670f809da51c335c7449a01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EmailHeaders</type>
      <name>additional_headers</name>
      <anchorfile>structemail_1_1EmailData.html</anchorfile>
      <anchor>aad420bf006f31f4a9f6a95db90581f49</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::EmailHandler</name>
    <filename>classemail_1_1EmailHandler.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>register_handler</name>
      <anchorfile>classemail_1_1EmailHandler.html</anchorfile>
      <anchor>a4760f8a9513bc50c2d453644da51ab1e</anchor>
      <arglist>(std::shared_ptr&lt; PollingManager &gt; polling_manager)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>handle</name>
      <anchorfile>classemail_1_1EmailHandler.html</anchorfile>
      <anchor>a4f58d53157b09b2b8e70a77538f2b37f</anchor>
      <arglist>(const struct EmailData &amp;data)=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>EmailHandler</name>
      <anchorfile>classemail_1_1EmailHandler.html</anchorfile>
      <anchor>ae11713a20d4aa3bf7a9913e8853f3c24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~EmailHandler</name>
      <anchorfile>classemail_1_1EmailHandler.html</anchorfile>
      <anchor>ad2fa34d6911cb7e54a99be33e449373f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::atomic_bool</type>
      <name>registered_</name>
      <anchorfile>classemail_1_1EmailHandler.html</anchorfile>
      <anchor>a3a2341fe5a385c0948851ffc602b68ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::EmailReceiver</name>
    <filename>classemail_1_1EmailReceiver.html</filename>
    <member kind="function">
      <type></type>
      <name>EmailReceiver</name>
      <anchorfile>classemail_1_1EmailReceiver.html</anchorfile>
      <anchor>a72726a74b1cd15878e09b792946db159</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~EmailReceiver</name>
      <anchorfile>classemail_1_1EmailReceiver.html</anchorfile>
      <anchor>a8d5b33a13fa468c0ce8843ffacf950cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shutdown</name>
      <anchorfile>classemail_1_1EmailReceiver.html</anchorfile>
      <anchor>acc9eaabaf2588628089e3a9ddffb7de4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::optional&lt; struct EmailData &gt;</type>
      <name>get_email</name>
      <anchorfile>classemail_1_1EmailReceiver.html</anchorfile>
      <anchor>a39b6a8bb1b4ca5da66b76a5a317d6e6b</anchor>
      <arglist>(std::optional&lt; std::chrono::nanoseconds &gt; polling_period=std::nullopt)=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::shared_ptr&lt; Logger &gt;</type>
      <name>logger_</name>
      <anchorfile>classemail_1_1EmailReceiver.html</anchorfile>
      <anchor>a5bdc7fcdd8d02a1070b8d45d80caf0c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::atomic_bool</type>
      <name>do_shutdown_</name>
      <anchorfile>classemail_1_1EmailReceiver.html</anchorfile>
      <anchor>aaea4bf463066dac619bdfad0849f9d40</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::EmailRecipients</name>
    <filename>structemail_1_1EmailRecipients.html</filename>
    <member kind="function">
      <type></type>
      <name>EmailRecipients</name>
      <anchorfile>structemail_1_1EmailRecipients.html</anchorfile>
      <anchor>a879ed18bb87c9a7b45d4cd050eb636e0</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;to_, const std::vector&lt; std::string &gt; &amp;cc_, const std::vector&lt; std::string &gt; &amp;bcc_)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EmailRecipients</name>
      <anchorfile>structemail_1_1EmailRecipients.html</anchorfile>
      <anchor>a53e2c3f070b41c602df6e2b5bfb7abba</anchor>
      <arglist>(const std::string &amp;to_)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EmailRecipients</name>
      <anchorfile>structemail_1_1EmailRecipients.html</anchorfile>
      <anchor>a12fb7fe3945afc13cd2bd02d9f2cb100</anchor>
      <arglist>(const EmailRecipients &amp;)=default</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::string &gt;</type>
      <name>to</name>
      <anchorfile>structemail_1_1EmailRecipients.html</anchorfile>
      <anchor>a0f5c1ef98bc6030b7026b9ff7250e466</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::string &gt;</type>
      <name>cc</name>
      <anchorfile>structemail_1_1EmailRecipients.html</anchorfile>
      <anchor>a1abf873bc70b6d1ebb3817d7c2977808</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::string &gt;</type>
      <name>bcc</name>
      <anchorfile>structemail_1_1EmailRecipients.html</anchorfile>
      <anchor>a9255bf9879cfa1748d17d142b84fb18f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::EmailSender</name>
    <filename>classemail_1_1EmailSender.html</filename>
    <member kind="function">
      <type></type>
      <name>EmailSender</name>
      <anchorfile>classemail_1_1EmailSender.html</anchorfile>
      <anchor>a6a067e65d5a0c78bd30217eaab577420</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~EmailSender</name>
      <anchorfile>classemail_1_1EmailSender.html</anchorfile>
      <anchor>a84b1193de252540aca30a78973f30ff9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>send</name>
      <anchorfile>classemail_1_1EmailSender.html</anchorfile>
      <anchor>a12487f6d865d3839438cfb0814bbf1ec</anchor>
      <arglist>(const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>reply</name>
      <anchorfile>classemail_1_1EmailSender.html</anchorfile>
      <anchor>ad7b5de33bdb15b17f88cfccde80aa881</anchor>
      <arglist>(const struct EmailContent &amp;content, const struct EmailData &amp;email, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)=0</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static std::shared_ptr&lt; Logger &gt;</type>
      <name>logger</name>
      <anchorfile>classemail_1_1EmailSender.html</anchorfile>
      <anchor>af10fd3a823d5f5355f6cd3a784a7d3d8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; email::EmailContent &gt;</name>
    <filename>structfmt_1_1formatter_3_01email_1_1EmailContent_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01email_1_1EmailContent_01_4.html</anchorfile>
      <anchor>a21811966bf13ebcebbb6134043c979bf</anchor>
      <arglist>(const email::EmailContent &amp;c, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; email::EmailData &gt;</name>
    <filename>structfmt_1_1formatter_3_01email_1_1EmailData_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01email_1_1EmailData_01_4.html</anchorfile>
      <anchor>a44d13c201093db0d5837b1876e1d1544</anchor>
      <arglist>(const email::EmailData &amp;d, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; email::EmailHeaders &gt;</name>
    <filename>structfmt_1_1formatter_3_01email_1_1EmailHeaders_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01email_1_1EmailHeaders_01_4.html</anchorfile>
      <anchor>a5f916790af4e6e756ecd373b29814f45</anchor>
      <arglist>(const email::EmailHeaders &amp;h, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; email::EmailRecipients &gt;</name>
    <filename>structfmt_1_1formatter_3_01email_1_1EmailRecipients_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01email_1_1EmailRecipients_01_4.html</anchorfile>
      <anchor>af3b2b9019c5c223e050189f63872357f</anchor>
      <arglist>(const email::EmailRecipients &amp;r, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; email::Gid &gt;</name>
    <filename>structfmt_1_1formatter_3_01email_1_1Gid_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01email_1_1Gid_01_4.html</anchorfile>
      <anchor>a490248b579a465153216af11d87ca89c</anchor>
      <arglist>(const email::Gid &amp;gid, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; email::Timestamp &gt;</name>
    <filename>structfmt_1_1formatter_3_01email_1_1Timestamp_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01email_1_1Timestamp_01_4.html</anchorfile>
      <anchor>a1863002ca9a1269d1f2b2451416ef191</anchor>
      <arglist>(const email::Timestamp &amp;ts, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; rcpputils::fs::path &gt;</name>
    <filename>structfmt_1_1formatter_3_01rcpputils_1_1fs_1_1path_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01rcpputils_1_1fs_1_1path_01_4.html</anchorfile>
      <anchor>ab6180187d5aef0dc33458706c9e718c1</anchor>
      <arglist>(const rcpputils::fs::path &amp;p, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmt::formatter&lt; YAML::Node &gt;</name>
    <filename>structfmt_1_1formatter_3_01YAML_1_1Node_01_4.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmt_1_1formatter_3_01YAML_1_1Node_01_4.html</anchorfile>
      <anchor>a353907f58dfb5520e37fc5fe4b9d4265</anchor>
      <arglist>(const YAML::Node &amp;node, FormatContext &amp;ctx)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::Gid</name>
    <filename>classemail_1_1Gid.html</filename>
    <member kind="function">
      <type></type>
      <name>Gid</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>abecaf9fb1ba2a8c1eb96f44225c70a2b</anchor>
      <arglist>(const GidValue value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Gid</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>ace01480d09f409d1b6dea1eae7d657cc</anchor>
      <arglist>(const Gid &amp;)=default</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Gid</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>a3e9a180384b627de0cb19ae24c7ca7df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>GidValue</type>
      <name>value</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>aa4ac19221b7be24f6ff62aeb60d44cf2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>to_string</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>a9e27fd06dfa8c387fdee7a0cea89dcac</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Gid</type>
      <name>new_gid</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>a7b577f26c3c1c5b652871313b4b378ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; Gid &gt;</type>
      <name>from_string</name>
      <anchorfile>classemail_1_1Gid.html</anchorfile>
      <anchor>a335e1b70ba71daad276439074fd84726</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::GidObject</name>
    <filename>classemail_1_1GidObject.html</filename>
    <member kind="function">
      <type>const Gid &amp;</type>
      <name>get_gid</name>
      <anchorfile>classemail_1_1GidObject.html</anchorfile>
      <anchor>a8606636aba92bce5b2c81ae0e0289d8e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>GidObject</name>
      <anchorfile>classemail_1_1GidObject.html</anchorfile>
      <anchor>a29ebb428c2827e00fe71660de6721c5e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~GidObject</name>
      <anchorfile>classemail_1_1GidObject.html</anchorfile>
      <anchor>a8fce88afdc622182418d32b1c43cc17b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::GuardCondition</name>
    <filename>classemail_1_1GuardCondition.html</filename>
    <member kind="function">
      <type></type>
      <name>GuardCondition</name>
      <anchorfile>classemail_1_1GuardCondition.html</anchorfile>
      <anchor>aad2ca2fad5110992f0ab770fc9767a86</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GuardCondition</name>
      <anchorfile>classemail_1_1GuardCondition.html</anchorfile>
      <anchor>a8726f63c5f17c97999f9375d8ed02562</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trigger</name>
      <anchorfile>classemail_1_1GuardCondition.html</anchorfile>
      <anchor>af5b7229bfff55135b648e5ad952662ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>triggered</name>
      <anchorfile>classemail_1_1GuardCondition.html</anchorfile>
      <anchor>acc1fcecf964084e4802fbac2570cb3eb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>exchange_in_use</name>
      <anchorfile>classemail_1_1GuardCondition.html</anchorfile>
      <anchor>a7cc9a581f7101e588984f1a5c98b33c6</anchor>
      <arglist>(bool in_use)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classemail_1_1GuardCondition.html</anchorfile>
      <anchor>a65e1eece1c8ea4b7b3afcf6e605dc29c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::GuardConditionAlreadyInUseError</name>
    <filename>classemail_1_1GuardConditionAlreadyInUseError.html</filename>
    <member kind="function">
      <type></type>
      <name>GuardConditionAlreadyInUseError</name>
      <anchorfile>classemail_1_1GuardConditionAlreadyInUseError.html</anchorfile>
      <anchor>a57d4ab9271b91ef41470c20711ceb732</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::IntraEmailReceiver</name>
    <filename>classemail_1_1IntraEmailReceiver.html</filename>
    <base>email::EmailReceiver</base>
    <member kind="function">
      <type></type>
      <name>IntraEmailReceiver</name>
      <anchorfile>classemail_1_1IntraEmailReceiver.html</anchorfile>
      <anchor>a931d5a8452bb052bc60d04cb8ff7f674</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IntraEmailReceiver</name>
      <anchorfile>classemail_1_1IntraEmailReceiver.html</anchorfile>
      <anchor>a565e517a247aeaadceb180163d29cee1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::optional&lt; struct EmailData &gt;</type>
      <name>get_email</name>
      <anchorfile>classemail_1_1IntraEmailReceiver.html</anchorfile>
      <anchor>a2046c9a7ce1774fa43c0a5dc9cea340a</anchor>
      <arglist>(std::optional&lt; std::chrono::nanoseconds &gt; polling_period=std::nullopt)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>receive</name>
      <anchorfile>classemail_1_1IntraEmailReceiver.html</anchorfile>
      <anchor>a804e589d1c329ed4862d01d02a3d74b0</anchor>
      <arglist>(const struct EmailData &amp;data)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::IntraEmailSender</name>
    <filename>classemail_1_1IntraEmailSender.html</filename>
    <base>email::EmailSender</base>
    <member kind="function">
      <type></type>
      <name>IntraEmailSender</name>
      <anchorfile>classemail_1_1IntraEmailSender.html</anchorfile>
      <anchor>adb317c2f33b19f554f508463530c800c</anchor>
      <arglist>(std::shared_ptr&lt; IntraEmailReceiver &gt; receiver)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IntraEmailSender</name>
      <anchorfile>classemail_1_1IntraEmailSender.html</anchorfile>
      <anchor>a6a9406be1e44e4e1def10e5577d69031</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>send</name>
      <anchorfile>classemail_1_1IntraEmailSender.html</anchorfile>
      <anchor>acf49287658ab7a3325ac99b4d6eb68ee</anchor>
      <arglist>(const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>reply</name>
      <anchorfile>classemail_1_1IntraEmailSender.html</anchorfile>
      <anchor>acf01f816b22eee5c16173f6c7dedaafd</anchor>
      <arglist>(const struct EmailContent &amp;content, const struct EmailData &amp;email, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::log::LoggingError</name>
    <filename>classemail_1_1log_1_1LoggingError.html</filename>
    <member kind="function">
      <type></type>
      <name>LoggingError</name>
      <anchorfile>classemail_1_1log_1_1LoggingError.html</anchorfile>
      <anchor>ac54a103a90bf6885137353f84bd01896</anchor>
      <arglist>(const std::string &amp;msg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::log::LoggingNotInitializedError</name>
    <filename>classemail_1_1log_1_1LoggingNotInitializedError.html</filename>
    <base>email::log::LoggingError</base>
    <member kind="function">
      <type></type>
      <name>LoggingNotInitializedError</name>
      <anchorfile>classemail_1_1log_1_1LoggingNotInitializedError.html</anchorfile>
      <anchor>a52a8bd2fa6ca2951b2661130dc8e05c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::MessageInfo</name>
    <filename>classemail_1_1MessageInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>MessageInfo</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>adfcdd34961d98458ea77ba578603f568</anchor>
      <arglist>(const Timestamp &amp;source_timestamp, const Timestamp &amp;received_timestamp, const Gid &amp;publisher_gid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MessageInfo</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>a7bf3afa991c4521cee2dcee15f7d9e39</anchor>
      <arglist>(const MessageInfo &amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MessageInfo</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>ab2fd3c813c7e203b120f822decc6c059</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Timestamp &amp;</type>
      <name>source_timestamp</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>ab24b647d3cb643b22d3c4795786dac92</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Timestamp &amp;</type>
      <name>received_timestamp</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>a8512b1b86f29c443fc6ae57668dda502</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Gid &amp;</type>
      <name>publisher_gid</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>acd94687199ad591af14bdf2f4c08276e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; MessageInfo &gt;</type>
      <name>from_headers</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>a80ee636f9d57b53f46ed026135c396f4</anchor>
      <arglist>(const EmailHeaders &amp;headers)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>HEADER_PUBLISHER_GID</name>
      <anchorfile>classemail_1_1MessageInfo.html</anchorfile>
      <anchor>a5ed56efb75a30f169e2e5be67c28c133</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::NamedObject</name>
    <filename>classemail_1_1NamedObject.html</filename>
    <member kind="function" protection="protected">
      <type>const std::string &amp;</type>
      <name>get_object_name</name>
      <anchorfile>classemail_1_1NamedObject.html</anchorfile>
      <anchor>a73cb596f0cb6c525566738fea946ae3a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>NamedObject</name>
      <anchorfile>classemail_1_1NamedObject.html</anchorfile>
      <anchor>a0f9a29567389176f23b61b8d0d71e774</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~NamedObject</name>
      <anchorfile>classemail_1_1NamedObject.html</anchorfile>
      <anchor>ab6de668d7cc2c1eefda15c5822599a46</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>validate_name</name>
      <anchorfile>classemail_1_1NamedObject.html</anchorfile>
      <anchor>ab2b95bd3169bcecfbda7002cbf3c8586</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>has_newline</name>
      <anchorfile>classemail_1_1NamedObject.html</anchorfile>
      <anchor>a41b4dd034b6ebdbf1bbde94d595d30fa</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ObjectNameInvalidError</name>
    <filename>classemail_1_1ObjectNameInvalidError.html</filename>
    <member kind="function" protection="protected">
      <type></type>
      <name>ObjectNameInvalidError</name>
      <anchorfile>classemail_1_1ObjectNameInvalidError.html</anchorfile>
      <anchor>afcb2be70cb184aba3aa9c699b220dab5</anchor>
      <arglist>(const std::string &amp;object_type_name, const std::string &amp;object_name, const std::string &amp;reason)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::Options</name>
    <filename>classemail_1_1Options.html</filename>
    <member kind="function">
      <type></type>
      <name>Options</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>a9e49710bb8d52a05b74a40868ebbb375</anchor>
      <arglist>(std::optional&lt; UserInfo::SharedPtrConst &gt; user_info, std::optional&lt; EmailRecipients::SharedPtrConst &gt; recipients, const bool curl_verbose, const bool intraprocess, const std::optional&lt; std::chrono::nanoseconds &gt; polling_period)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Options</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>aedb8a8691febda54ef6646ea841e0199</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; UserInfo::SharedPtrConst &gt;</type>
      <name>get_user_info</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>ad3aab8a980c818d44f7b4c453456dd2e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; EmailRecipients::SharedPtrConst &gt;</type>
      <name>get_recipients</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>ae706e9b4864156502045cbba7d0fd018</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curl_verbose</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>afb4cf15d89daec778cb29e4c4cdb5c85</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>intraprocess</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>a289fed51e2e140b89f31b30ec7f34269</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::chrono::nanoseconds &gt;</type>
      <name>polling_period</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>a1db5c0402e0349f0430dc108460a6728</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; std::shared_ptr&lt; Options &gt; &gt;</type>
      <name>parse_options_from_args</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>a80b79667d350d2ed10d22537580b2bc8</anchor>
      <arglist>(int argc, char const *const argv[])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; std::shared_ptr&lt; Options &gt; &gt;</type>
      <name>parse_options_from_file</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>aecc89940a2c5923d049cf22d4a11a521</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; std::shared_ptr&lt; Options &gt; &gt;</type>
      <name>yaml_to_options</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>a3c2b027f4ad3a89de10a415afeaca4db</anchor>
      <arglist>(YAML::Node)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; std::shared_ptr&lt; Options &gt; &gt;</type>
      <name>parse_options_file</name>
      <anchorfile>classemail_1_1Options.html</anchorfile>
      <anchor>a0414d9ab8ccd80f7e31ddfd49899c12c</anchor>
      <arglist>(const rcpputils::fs::path &amp;file_path)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::PollingManager</name>
    <filename>classemail_1_1PollingManager.html</filename>
    <member kind="typedef">
      <type>std::function&lt; void(const struct EmailData &amp;)&gt;</type>
      <name>HandlerFunction</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>afa05fad5b42110b2dfcda3f5103d0de6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PollingManager</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>a21701ede1e27783c03b8f4103f057387</anchor>
      <arglist>(std::shared_ptr&lt; EmailReceiver &gt; receiver, const std::optional&lt; std::chrono::nanoseconds &gt; polling_period)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PollingManager</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>a9fe590820846230f5280bc8b1b625bfa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_handler</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>ada4ac3a931faab269f51bf3eb47107be</anchor>
      <arglist>(const HandlerFunction &amp;handler)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_started</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>a296452624039c89821173b200d26074b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>aa783b059813426b2508da384cb9e8b74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shutdown</name>
      <anchorfile>classemail_1_1PollingManager.html</anchorfile>
      <anchor>a896bf5d847844d5c5ef8cad3599b67ca</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::ProtocolInfo</name>
    <filename>structemail_1_1ProtocolInfo.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>protocol</name>
      <anchorfile>structemail_1_1ProtocolInfo.html</anchorfile>
      <anchor>ad0780b8e284c99614dd3112bb9d1a851</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>port</name>
      <anchorfile>structemail_1_1ProtocolInfo.html</anchorfile>
      <anchor>a4053b3cd3367f009612736d3d15d8311</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::Publisher</name>
    <filename>classemail_1_1Publisher.html</filename>
    <base>email::PubSubObject</base>
    <member kind="function">
      <type></type>
      <name>Publisher</name>
      <anchorfile>classemail_1_1Publisher.html</anchorfile>
      <anchor>a38811fe95dd19f2f704e589b34251682</anchor>
      <arglist>(const std::string &amp;topic_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Publisher</name>
      <anchorfile>classemail_1_1Publisher.html</anchorfile>
      <anchor>acaafeeb59a87dde27dc82c57090781ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>publish</name>
      <anchorfile>classemail_1_1Publisher.html</anchorfile>
      <anchor>afe640abb7111f5ac3aa3588a7e643bb1</anchor>
      <arglist>(const std::string &amp;message, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::PubSubObject</name>
    <filename>classemail_1_1PubSubObject.html</filename>
    <base>email::GidObject</base>
    <base>email::NamedObject</base>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>get_topic_name</name>
      <anchorfile>classemail_1_1PubSubObject.html</anchorfile>
      <anchor>a00a22d18eebc82496581344c21e02c32</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>PubSubObject</name>
      <anchorfile>classemail_1_1PubSubObject.html</anchorfile>
      <anchor>a601bed08338a20e2d63e2332661a61e5</anchor>
      <arglist>(const std::string &amp;topic_name)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~PubSubObject</name>
      <anchorfile>classemail_1_1PubSubObject.html</anchorfile>
      <anchor>a30f73a71f66b22671b2be92884e6c81f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::SafeMap</name>
    <filename>classemail_1_1SafeMap.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>SafeMap</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a563ab30f2d67ffe0303fb7a7637a7dd4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SafeMap</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a28c78d46002ecb2d43b866aa03a06c3f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>afa02ff889b01bf6b6d7d5907f0effdc1</anchor>
      <arglist>(std::pair&lt; const K, T &gt; &amp;&amp;p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>erase</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>aed35e5730013f7a427f46896696c443e</anchor>
      <arglist>(typename std::map&lt; K, T &gt;::const_iterator &amp;it)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>erase</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a804ed1b4f45d89f4860171b46ecd68a5</anchor>
      <arglist>(typename std::map&lt; K, T &gt;::iterator &amp;it)</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; K, T &gt;::const_iterator</type>
      <name>find</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>aff4db055c899b8d4103fed639fc6f300</anchor>
      <arglist>(const K &amp;k) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a97478e47a15235d9d08a9ea19f789968</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>contains</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a8060a7e82eb56a7c26bb0ec1db3b26cb</anchor>
      <arglist>(const K &amp;k) const</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; typename std::map&lt; K, T &gt;::const_iterator, typename std::map&lt; K, T &gt;::const_iterator &gt;</type>
      <name>equal_range</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>af0f1ce1776d7e4c46b24b07d72d23ec9</anchor>
      <arglist>(const K &amp;k) const</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; K, T &gt;::iterator</type>
      <name>begin</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a3e3ced069a9413c52681a03948893587</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; K, T &gt;::iterator</type>
      <name>end</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a60b6d858638f84927240c6923a301661</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; K, T &gt;::const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>a504fe23def42764bc68fbd39c7a51b90</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; K, T &gt;::const_iterator</type>
      <name>cend</name>
      <anchorfile>classemail_1_1SafeMap.html</anchorfile>
      <anchor>aaf04df2a744013504ee3137e3f7a21ec</anchor>
      <arglist>() const noexcept</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::SafeQueue</name>
    <filename>classemail_1_1SafeQueue.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>SafeQueue</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>a22036feff6b0264298c3b8780f318fed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SafeQueue</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>add6639ea70ecb072ff4472af0a674471</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>a548ee01f7a0733d5f8760bf85c762d68</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>af490c5923c3e2567357ba39580b01729</anchor>
      <arglist>(const T &amp;element)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pop</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>a9a939e531527ca5d84da0586f1341532</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>front</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>ab982a1cb410d935efe1a438c80bffa97</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const T</type>
      <name>dequeue</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>abbc26904adc2e3180df5c12e16bc5307</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SafeQueue&lt; struct email::EmailData &gt;</name>
    <filename>classemail_1_1SafeQueue.html</filename>
    <member kind="function">
      <type></type>
      <name>SafeQueue</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>a22036feff6b0264298c3b8780f318fed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SafeQueue</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>add6639ea70ecb072ff4472af0a674471</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>empty</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>a548ee01f7a0733d5f8760bf85c762d68</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>af490c5923c3e2567357ba39580b01729</anchor>
      <arglist>(const struct email::EmailData &amp;element)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pop</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>a9a939e531527ca5d84da0586f1341532</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const struct email::EmailData &amp;</type>
      <name>front</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>ab982a1cb410d935efe1a438c80bffa97</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const struct email::EmailData</type>
      <name>dequeue</name>
      <anchorfile>classemail_1_1SafeQueue.html</anchorfile>
      <anchor>abbc26904adc2e3180df5c12e16bc5307</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ServiceClient</name>
    <filename>classemail_1_1ServiceClient.html</filename>
    <base>email::ServiceObject</base>
    <member kind="function">
      <type></type>
      <name>ServiceClient</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>a5886f94bb1d643190851f39d55e9744c</anchor>
      <arglist>(const std::string &amp;service_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ServiceClient</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>a1756de449953a1e333baa595d0b290b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>send_request</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>a264ad9aea4e1f069720f17cf40c1992e</anchor>
      <arglist>(const std::string &amp;request, const SequenceNumber sequence_number)</arglist>
    </member>
    <member kind="function">
      <type>SequenceNumber</type>
      <name>send_request</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>ab34679e8f8f5fdfed3b3241a4ada78a6</anchor>
      <arglist>(const std::string &amp;request)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_response</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>a574ead1860f97d09941cd2b013fb4d37</anchor>
      <arglist>(const SequenceNumber sequence_number)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_response</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>a69bb6e1a7db8495b79aa19e47f0236d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::string &gt;</type>
      <name>get_response</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>a71b844e2b5f1ff60f059d7658f9c11df</anchor>
      <arglist>(const SequenceNumber sequence_number)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::pair&lt; std::string, ServiceInfo &gt; &gt;</type>
      <name>get_response_with_info</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>abfc9d9d393aefa5052e6940e9125782b</anchor>
      <arglist>(const SequenceNumber sequence_number)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::pair&lt; std::string, ServiceInfo &gt; &gt;</type>
      <name>get_response_with_info</name>
      <anchorfile>classemail_1_1ServiceClient.html</anchorfile>
      <anchor>acf7b778520df726f526d6de97637038f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ServiceHandler</name>
    <filename>classemail_1_1ServiceHandler.html</filename>
    <base>email::EmailHandler</base>
    <member kind="typedef">
      <type>SafeMap&lt; SequenceNumber, std::pair&lt; struct EmailData, ServiceInfo &gt; &gt;</type>
      <name>ResponseMap</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>ae3c029c330a62190ed1c6f5d99fcd22c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SafeQueue&lt; std::pair&lt; struct EmailData, ServiceInfo &gt; &gt;</type>
      <name>RequestQueue</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>ade298da509aef85142d98c336c1e7058</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ServiceHandler</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>ac8b733ebb32ee7203ad714aedd911601</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ServiceHandler</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>a71953e56a4f95c3154e6d815bd67e624</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_service_client</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>abf9a84643b846d50a59e707989af52be</anchor>
      <arglist>(const Gid &amp;gid, ResponseMap::WeakPtr response_map)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_service_server</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>aa6c2a8e5bdcee9c8f68ef5f48160736b</anchor>
      <arglist>(const std::string &amp;service_name, RequestQueue::WeakPtr request_queue)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>register_handler</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>a1ffdec6079165b77924bc0e7e4fc7382</anchor>
      <arglist>(std::shared_ptr&lt; PollingManager &gt; polling_manager)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>handle</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>a19fc6c955eeecce3e61e7b4efd9fa174</anchor>
      <arglist>(const struct EmailData &amp;data)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>HEADER_SEQUENCE_NUMBER</name>
      <anchorfile>classemail_1_1ServiceHandler.html</anchorfile>
      <anchor>af8bc3076e7f671a33407a8cfd461ff0e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ServiceInfo</name>
    <filename>classemail_1_1ServiceInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>ServiceInfo</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>aefebdb81432c3a220ed9fe493cbb0d80</anchor>
      <arglist>(const Timestamp &amp;source_timestamp, const Timestamp &amp;received_timestamp, const Gid &amp;client_gid, const SequenceNumber sequence_number)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ServiceInfo</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>a0e61b08f5bc6a1c6c779bc59aeaed8c3</anchor>
      <arglist>(const ServiceInfo &amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ServiceInfo</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>a771610c25c91d4aab45c9bc8c0d9989c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Timestamp &amp;</type>
      <name>source_timestamp</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>aa43d1644eb146528c2d6f48231b6c721</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Timestamp &amp;</type>
      <name>received_timestamp</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>a3c0d5e5899c80a2a989056d1ed70c441</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Gid &amp;</type>
      <name>client_gid</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>ad77d23bb1f88131cda1583b1afb2441a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SequenceNumber</type>
      <name>sequence_number</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>a5791f0d08dabaa8fe7c8cc1a1cef0326</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; ServiceInfo &gt;</type>
      <name>from_headers</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>a34fd237258ec87524ee5edddd1550b21</anchor>
      <arglist>(const EmailHeaders &amp;headers)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>HEADER_CLIENT_GID</name>
      <anchorfile>classemail_1_1ServiceInfo.html</anchorfile>
      <anchor>ae1a34f4d40383fe81f2487bdaf14edfb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ServiceNameInvalidError</name>
    <filename>classemail_1_1ServiceNameInvalidError.html</filename>
    <base>email::ObjectNameInvalidError</base>
    <member kind="function">
      <type></type>
      <name>ServiceNameInvalidError</name>
      <anchorfile>classemail_1_1ServiceNameInvalidError.html</anchorfile>
      <anchor>acd75c64744ee8299b87b78697e21cab9</anchor>
      <arglist>(const std::string &amp;service_name, const std::string &amp;reason)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ServiceObject</name>
    <filename>classemail_1_1ServiceObject.html</filename>
    <base>email::GidObject</base>
    <base>email::NamedObject</base>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>get_service_name</name>
      <anchorfile>classemail_1_1ServiceObject.html</anchorfile>
      <anchor>a7f96bf4bb03c956939682468cd5dd4ea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ServiceObject</name>
      <anchorfile>classemail_1_1ServiceObject.html</anchorfile>
      <anchor>a6adfe99b703c35e74156ecd4336cd2da</anchor>
      <arglist>(const std::string &amp;service_name)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~ServiceObject</name>
      <anchorfile>classemail_1_1ServiceObject.html</anchorfile>
      <anchor>a96f6d5e8cd18f0e2ec7f1229fdd6f110</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::ServiceRequest</name>
    <filename>structemail_1_1ServiceRequest.html</filename>
    <member kind="function">
      <type></type>
      <name>ServiceRequest</name>
      <anchorfile>structemail_1_1ServiceRequest.html</anchorfile>
      <anchor>ad530cc6cd2cfb64b90397085fdfbdab4</anchor>
      <arglist>(const SequenceNumber sequence_number_, const Gid &amp;client_gid_, const std::string &amp;content_)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ServiceRequest</name>
      <anchorfile>structemail_1_1ServiceRequest.html</anchorfile>
      <anchor>a3c9bc09105fca13fb6e1221a7f43f96b</anchor>
      <arglist>(const ServiceRequest &amp;)=default</arglist>
    </member>
    <member kind="variable">
      <type>ServiceRequestId</type>
      <name>id</name>
      <anchorfile>structemail_1_1ServiceRequest.html</anchorfile>
      <anchor>a7854c6a65f5a8f8dd6cad195cd826be5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>content</name>
      <anchorfile>structemail_1_1ServiceRequest.html</anchorfile>
      <anchor>a3272812ec88a2a775c8cb800c169344b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::ServiceRequestId</name>
    <filename>structemail_1_1ServiceRequestId.html</filename>
    <member kind="function">
      <type></type>
      <name>ServiceRequestId</name>
      <anchorfile>structemail_1_1ServiceRequestId.html</anchorfile>
      <anchor>a4ecb68274a8a59ed1c03d5b2d6f8be9a</anchor>
      <arglist>(const SequenceNumber sequence_number_, const Gid &amp;client_gid_)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ServiceRequestId</name>
      <anchorfile>structemail_1_1ServiceRequestId.html</anchorfile>
      <anchor>a3b10965d77fc9cb89d4406eaea20be59</anchor>
      <arglist>(const ServiceRequestId &amp;)=default</arglist>
    </member>
    <member kind="variable">
      <type>SequenceNumber</type>
      <name>sequence_number</name>
      <anchorfile>structemail_1_1ServiceRequestId.html</anchorfile>
      <anchor>aebfd4e4852b50376f5748d53fc343dc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Gid</type>
      <name>client_gid</name>
      <anchorfile>structemail_1_1ServiceRequestId.html</anchorfile>
      <anchor>a100c11e098d31a3484ae73cf1350a9ca</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::ServiceServer</name>
    <filename>classemail_1_1ServiceServer.html</filename>
    <base>email::ServiceObject</base>
    <member kind="function">
      <type></type>
      <name>ServiceServer</name>
      <anchorfile>classemail_1_1ServiceServer.html</anchorfile>
      <anchor>abba58df55b0930d3f33741ffa8950d3f</anchor>
      <arglist>(const std::string &amp;service_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ServiceServer</name>
      <anchorfile>classemail_1_1ServiceServer.html</anchorfile>
      <anchor>aad38fdd9a7af24307b11d0550700a556</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_request</name>
      <anchorfile>classemail_1_1ServiceServer.html</anchorfile>
      <anchor>a5f9a2b5d05d50b4cfe890ebfd077d509</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; struct ServiceRequest &gt;</type>
      <name>get_request</name>
      <anchorfile>classemail_1_1ServiceServer.html</anchorfile>
      <anchor>a35e70cc848d14c82cd6185499998af36</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::pair&lt; struct ServiceRequest, ServiceInfo &gt; &gt;</type>
      <name>get_request_with_info</name>
      <anchorfile>classemail_1_1ServiceServer.html</anchorfile>
      <anchor>a61296d41cf3f59fafcf5aa87e51e81e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>send_response</name>
      <anchorfile>classemail_1_1ServiceServer.html</anchorfile>
      <anchor>a47867e8fbd4b21d56681e39f82635ca3</anchor>
      <arglist>(const struct ServiceRequestId &amp;request_id, const std::string &amp;response)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::Subscription</name>
    <filename>classemail_1_1Subscription.html</filename>
    <base>email::PubSubObject</base>
    <member kind="function">
      <type></type>
      <name>Subscription</name>
      <anchorfile>classemail_1_1Subscription.html</anchorfile>
      <anchor>aafc179a5eb735b80831c5be18c23dd71</anchor>
      <arglist>(const std::string &amp;topic_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Subscription</name>
      <anchorfile>classemail_1_1Subscription.html</anchorfile>
      <anchor>a49048c43296a15ca21dd4f929f039a7b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_message</name>
      <anchorfile>classemail_1_1Subscription.html</anchorfile>
      <anchor>aa839176898e4ce3c244020eb3134adb9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::string &gt;</type>
      <name>get_message</name>
      <anchorfile>classemail_1_1Subscription.html</anchorfile>
      <anchor>a859e4294eabcfd55e07d115c93c3681b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::pair&lt; std::string, MessageInfo &gt; &gt;</type>
      <name>get_message_with_info</name>
      <anchorfile>classemail_1_1Subscription.html</anchorfile>
      <anchor>a85751be20bb1ffb135879a968f4d518a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::SubscriptionHandler</name>
    <filename>classemail_1_1SubscriptionHandler.html</filename>
    <base>email::EmailHandler</base>
    <member kind="typedef">
      <type>SafeQueue&lt; std::pair&lt; std::string, MessageInfo &gt; &gt;</type>
      <name>MessageQueue</name>
      <anchorfile>classemail_1_1SubscriptionHandler.html</anchorfile>
      <anchor>a074215e7cbbd40683d3760a914b0d265</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SubscriptionHandler</name>
      <anchorfile>classemail_1_1SubscriptionHandler.html</anchorfile>
      <anchor>a4f580d0f7505ff64e14b7e74ee38861c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~SubscriptionHandler</name>
      <anchorfile>classemail_1_1SubscriptionHandler.html</anchorfile>
      <anchor>af5da1131267e3764c91e22b9c8c4d786</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_subscription</name>
      <anchorfile>classemail_1_1SubscriptionHandler.html</anchorfile>
      <anchor>a4b2d9f6a6346020e67447c2117300434</anchor>
      <arglist>(const std::string &amp;topic_name, MessageQueue::WeakPtr message_queue)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>register_handler</name>
      <anchorfile>classemail_1_1SubscriptionHandler.html</anchorfile>
      <anchor>aa57488fcda9056d279f87d474306525a</anchor>
      <arglist>(std::shared_ptr&lt; PollingManager &gt; polling_manager)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>handle</name>
      <anchorfile>classemail_1_1SubscriptionHandler.html</anchorfile>
      <anchor>a59ca1ab4299475b961cdbb7baf252da8</anchor>
      <arglist>(const struct EmailData &amp;data)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::Timestamp</name>
    <filename>classemail_1_1Timestamp.html</filename>
    <member kind="function">
      <type></type>
      <name>Timestamp</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>a653badfe8b13db09b2b6d3b41368a973</anchor>
      <arglist>(const int64_t nanoseconds)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Timestamp</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>a3475a215fac8ccfe8241f6c4d18f9a22</anchor>
      <arglist>(const Timestamp &amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Timestamp</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>accbcf82dcfd93ec893527ad9131c0889</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int64_t</type>
      <name>nanoseconds</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>ab32931c11f5356865899e3c828327feb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>to_string</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>aacf325af0fe8a37d9661686cc8c4e9bf</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Timestamp</type>
      <name>now</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>acd6a1543ca548deb496e54f7d4dd616c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::optional&lt; Timestamp &gt;</type>
      <name>from_string</name>
      <anchorfile>classemail_1_1Timestamp.html</anchorfile>
      <anchor>a9576b9bd5328f436b0cf00ca4e7be128</anchor>
      <arglist>(const std::string &amp;timestamp)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::TopicNameInvalidError</name>
    <filename>classemail_1_1TopicNameInvalidError.html</filename>
    <base>email::ObjectNameInvalidError</base>
    <member kind="function">
      <type></type>
      <name>TopicNameInvalidError</name>
      <anchorfile>classemail_1_1TopicNameInvalidError.html</anchorfile>
      <anchor>a6910edce78abbe9533f223b3fc5cfb5b</anchor>
      <arglist>(const std::string &amp;topic_name, const std::string &amp;reason)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>email::UserInfo</name>
    <filename>structemail_1_1UserInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>UserInfo</name>
      <anchorfile>structemail_1_1UserInfo.html</anchorfile>
      <anchor>a079c1b6f41d419aac969bf43a9ca81f8</anchor>
      <arglist>(const std::string &amp;host_smtp_, const std::string &amp;host_imap_, const std::string &amp;username_, const std::string &amp;password_)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UserInfo</name>
      <anchorfile>structemail_1_1UserInfo.html</anchorfile>
      <anchor>a6cdf509b065f465665368ea9c595302c</anchor>
      <arglist>(const UserInfo &amp;)=default</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>host_smtp</name>
      <anchorfile>structemail_1_1UserInfo.html</anchorfile>
      <anchor>a9a7c93eb5a5fad244eb3699f361ae666</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>host_imap</name>
      <anchorfile>structemail_1_1UserInfo.html</anchorfile>
      <anchor>aa810688adcf8ce581af198d138b1a3f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>username</name>
      <anchorfile>structemail_1_1UserInfo.html</anchorfile>
      <anchor>abe9be20a65e424a216f61fae0cf50078</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>password</name>
      <anchorfile>structemail_1_1UserInfo.html</anchorfile>
      <anchor>adb5cc631ca7e5c0669685b5faf9fcef9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>email::WaitSet</name>
    <filename>classemail_1_1WaitSet.html</filename>
    <member kind="function">
      <type></type>
      <name>WaitSet</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a1f9b0ab4f1191682198dcfd2746ee1eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WaitSet</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a6a5385e7a140e0af8f2cde7676336605</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wait</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>aa2d887c4b7475b0540ceb4fa037e0b7a</anchor>
      <arglist>(const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_subscription</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a742c95db4b8aaec2ac56731fc77f490f</anchor>
      <arglist>(Subscription *subscription)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_client</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a689f385df30394ae47663cb848dcf288</anchor>
      <arglist>(ServiceClient *client)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_server</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>abdce7e3034e0f5d2bdff3d7870afebca</anchor>
      <arglist>(ServiceServer *server)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_guard_condition</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a61e5475463ef2475e8a37bdd54eab047</anchor>
      <arglist>(GuardCondition *guard_condition)</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; Subscription * &gt; &amp;</type>
      <name>get_subscriptions</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a14e663661e0c5667a7ede299a0b3552d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; ServiceClient * &gt; &amp;</type>
      <name>get_clients</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a290d51b59a3929a55f57082628456942</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; ServiceServer * &gt; &amp;</type>
      <name>get_servers</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>adb793cb528d1c21a889f247ee64deef8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; GuardCondition * &gt; &amp;</type>
      <name>get_guard_conditions</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>afb3e6df1fbaad0de2ac18dc3c20afd9a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>classemail_1_1WaitSet.html</anchorfile>
      <anchor>a7fa89429ff3e7928dd747c75e7ba2e58</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>email</name>
    <filename>namespaceemail.html</filename>
    <namespace>email::log</namespace>
    <namespace>email::utils</namespace>
    <class kind="class">email::CommunicationInfo</class>
    <class kind="class">email::ContextError</class>
    <class kind="class">email::ContextNotInitializedError</class>
    <class kind="class">email::ContextAlreadyInitializedError</class>
    <class kind="class">email::ContextInitFailedError</class>
    <class kind="class">email::Context</class>
    <class kind="class">email::CurlContext</class>
    <class kind="class">email::CurlExecutor</class>
    <class kind="struct">email::ConnectionInfo</class>
    <class kind="struct">email::ProtocolInfo</class>
    <class kind="class">email::CurlEmailReceiver</class>
    <class kind="class">email::CurlEmailSender</class>
    <class kind="class">email::EmailHandler</class>
    <class kind="struct">email::UserInfo</class>
    <class kind="struct">email::EmailRecipients</class>
    <class kind="struct">email::EmailContent</class>
    <class kind="struct">email::EmailData</class>
    <class kind="class">email::IntraEmailReceiver</class>
    <class kind="class">email::IntraEmailSender</class>
    <class kind="class">email::PollingManager</class>
    <class kind="class">email::EmailReceiver</class>
    <class kind="class">email::EmailSender</class>
    <class kind="class">email::Gid</class>
    <class kind="class">email::GidObject</class>
    <class kind="class">email::GuardConditionAlreadyInUseError</class>
    <class kind="class">email::GuardCondition</class>
    <class kind="class">email::MessageInfo</class>
    <class kind="class">email::ObjectNameInvalidError</class>
    <class kind="class">email::NamedObject</class>
    <class kind="class">email::Options</class>
    <class kind="class">email::TopicNameInvalidError</class>
    <class kind="class">email::PubSubObject</class>
    <class kind="class">email::Publisher</class>
    <class kind="class">email::SafeMap</class>
    <class kind="class">email::SafeQueue</class>
    <class kind="class">email::ServiceNameInvalidError</class>
    <class kind="class">email::ServiceObject</class>
    <class kind="class">email::ServiceClient</class>
    <class kind="class">email::ServiceHandler</class>
    <class kind="class">email::ServiceInfo</class>
    <class kind="struct">email::ServiceRequestId</class>
    <class kind="struct">email::ServiceRequest</class>
    <class kind="class">email::ServiceServer</class>
    <class kind="class">email::Subscription</class>
    <class kind="class">email::SubscriptionHandler</class>
    <class kind="class">email::Timestamp</class>
    <class kind="class">email::WaitSet</class>
    <member kind="typedef">
      <type>std::map&lt; std::string, std::string &gt;</type>
      <name>EmailHeaders</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ae41e6fb7cb5a3b87ee3effdc2aa2065f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>EmailHeaders::value_type</type>
      <name>EmailHeader</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a79f0f6247c3270688400eb20c9564c96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>GidValue</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a75eac80413e3a15a1adff727b822a70c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>spdlog::logger</type>
      <name>Logger</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a8d76c558a86ae3983f1b8f138c036e61</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int64_t</type>
      <name>SequenceNumber</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a0de800b4ba159d6e3892ce756a690103</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; Context &gt;</type>
      <name>get_global_context</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a32664596f7a3d0177434519dc03ea38d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a3d225be7f22f802190fb1f2e49f5b1d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a31064318c3c135912c70c384f25d3305</anchor>
      <arglist>(int argc, char const *const argv[])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>shutdown</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a7a0e2779940792a4753a9b163fd1bbc4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, MessageInfo &gt;</type>
      <name>wait_for_message_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>aa59c37dd2056e5079d933232a16a3396</anchor>
      <arglist>(Subscription *subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, MessageInfo &gt;</type>
      <name>wait_for_message_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a03feb199db737e274a1e6f0750d203a6</anchor>
      <arglist>(std::shared_ptr&lt; Subscription &gt; subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_message</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ab5721e49aa88b793a84361690e62cff6</anchor>
      <arglist>(Subscription *subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_message</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ae337962e644aa83d44bb241471fcb5a2</anchor>
      <arglist>(std::shared_ptr&lt; Subscription &gt; subscription, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, ServiceInfo &gt;</type>
      <name>wait_for_response_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a79fde927095f94957025da12c6283edb</anchor>
      <arglist>(const SequenceNumber sequence_number, ServiceClient *client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; std::string, ServiceInfo &gt;</type>
      <name>wait_for_response_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a2cdbe450415e49215d4a2d869eb577e7</anchor>
      <arglist>(const SequenceNumber sequence_number, std::shared_ptr&lt; ServiceClient &gt; client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_response</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a5f80f51854175a635e2ce28ec401e8a9</anchor>
      <arglist>(const SequenceNumber sequence_number, ServiceClient *client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>wait_for_response</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a81ce8fcb498eb5e3074e69043bccbff0</anchor>
      <arglist>(const SequenceNumber sequence_number, std::shared_ptr&lt; ServiceClient &gt; client, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; struct ServiceRequest, ServiceInfo &gt;</type>
      <name>wait_for_request_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ad5dd2091a29213c9aa3859d817376d10</anchor>
      <arglist>(ServiceServer *server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; struct ServiceRequest, ServiceInfo &gt;</type>
      <name>wait_for_request_with_info</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>afdc469e72e9b1ab69445fdb82082f050</anchor>
      <arglist>(std::shared_ptr&lt; ServiceServer &gt; server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>struct ServiceRequest</type>
      <name>wait_for_request</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>ad0a6b760f7e08068416acceebb60a199</anchor>
      <arglist>(ServiceServer *server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
    <member kind="function">
      <type>struct ServiceRequest</type>
      <name>wait_for_request</name>
      <anchorfile>namespaceemail.html</anchorfile>
      <anchor>a7dfbb8a3972445ace7e5b33b3b8cf18e</anchor>
      <arglist>(std::shared_ptr&lt; ServiceServer &gt; server, const std::chrono::milliseconds timeout=std::chrono::milliseconds(-1))</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>email::log</name>
    <filename>namespaceemail_1_1log.html</filename>
    <class kind="class">email::log::LoggingError</class>
    <class kind="class">email::log::LoggingNotInitializedError</class>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>debug</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fab854c88759c3923a679b84586ca1197c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>info</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8faa7c9183950be07c0f6e85a5b10a45087</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>warn</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fa3e9bbe69f71687a336604c2482f4366c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>error</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8faba726552e49985a6cc8f897f16e99793</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>fatal</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fa6df5a6c39d2a59dd7477e58e07c0bffa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>off</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a76b9f7af528d9d5b684c7dd13770eb8fa0d42315cc89e99a312b0445743128878</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a70e2c4b9640f8b10a086f14269d4681d</anchor>
      <arglist>(const Level &amp;level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_from_env</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>aba50b69230431fca149b16fe3fbcaa9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; Logger &gt;</type>
      <name>create</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>a82cb3ebe95d6b4e4bc16fd417bf65b8e</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; Logger &gt;</type>
      <name>get_or_create</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>ab5f6effef314d9faef6dee3b4d78f4ce</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>remove</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>aae637767284f0246349f0c09c4a7b30f</anchor>
      <arglist>(const std::shared_ptr&lt; Logger &gt; &amp;logger)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shutdown</name>
      <anchorfile>namespaceemail_1_1log.html</anchorfile>
      <anchor>ab7f5f3d63616c0073e304d2b20f86841</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>email::utils</name>
    <filename>namespaceemail_1_1utils.html</filename>
    <namespace>email::utils::payload</namespace>
    <namespace>email::utils::response</namespace>
    <member kind="function">
      <type>std::string</type>
      <name>string_format</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a36d04ae0600a820016e9a547222bad1a</anchor>
      <arglist>(const std::string &amp;format, Args... args)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_env_var</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a48891b8793ba17bf280aef8d8c62f392</anchor>
      <arglist>(const std::string &amp;env_var)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_env_var_or_default</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>ae02d06fc8aab9fc0e6c0e2f08e4bb976</anchor>
      <arglist>(const std::string &amp;env_var, const std::string &amp;default_value)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::string &gt;</type>
      <name>read_file</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a88a5169377c5fdee4455ee6b38723745</anchor>
      <arglist>(const std::string &amp;path)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>split_email_list</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a45df7fc739ac9b6a5f5f8dd28eec92e1</anchor>
      <arglist>(const std::string &amp;list, const bool has_space_after_comma=false)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; std::string &gt;</type>
      <name>split_email_list</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>aef6154f77c351ae81abb1544e8a5f3fd</anchor>
      <arglist>(const YAML::Node &amp;node)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>yaml_to_string</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a82ee838f6167a4af1146f59b82a26933</anchor>
      <arglist>(const YAML::Node &amp;node)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>full_url</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a40a0b74a4dfabc0575e10367ff64f14f</anchor>
      <arglist>(const std::string &amp;protocol, const std::string &amp;host, const int port)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; uint32_t &gt;</type>
      <name>optional_stoul</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a1426a6b72c22a41e717f2dddb9fe6f47</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; int &gt;</type>
      <name>optional_stoi</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a2a5c92f770d0c27fefe339dd2ba426a1</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; int64_t &gt;</type>
      <name>optional_stoll</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a205d62958aa3a9111c4c17da561743fc</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>thread_get_name</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a3f1ec15b0fb2fe7708248d9144068e69</anchor>
      <arglist>(char *name, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>thread_set_name</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>abb5cc15dac76b938b897a32a94d29387</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>thread_append_name</name>
      <anchorfile>namespaceemail_1_1utils.html</anchorfile>
      <anchor>a6de7445821178c24df09d19ede5b3700</anchor>
      <arglist>(const char *suffix)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>email::utils::payload</name>
    <filename>namespaceemail_1_1utils_1_1payload.html</filename>
    <member kind="function">
      <type>const std::string</type>
      <name>build_payload</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>ad30b9776687e2e98638b32759ad2bc3d</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;to, const std::vector&lt; std::string &gt; &amp;cc, const std::vector&lt; std::string &gt; &amp;bcc, const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt, std::optional&lt; std::string &gt; reply_ref=std::nullopt)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>build_payload</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>ac522857948a8c609ea73e96600cb8e2a</anchor>
      <arglist>(EmailRecipients::SharedPtrConst recipients, const struct EmailContent &amp;content, std::optional&lt; EmailHeaders &gt; additional_headers=std::nullopt, std::optional&lt; std::string &gt; reply_ref=std::nullopt)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>join_list</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>ae288cd99e7a54273aea6372c959f76c9</anchor>
      <arglist>(const std::vector&lt; std::string &gt; &amp;list)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>cut_string_if_newline</name>
      <anchorfile>namespaceemail_1_1utils_1_1payload.html</anchorfile>
      <anchor>a455c37a8a129ddcf90c1835f001c0579</anchor>
      <arglist>(const std::string &amp;string)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>email::utils::response</name>
    <filename>namespaceemail_1_1utils_1_1response.html</filename>
    <member kind="function">
      <type>std::optional&lt; int &gt;</type>
      <name>get_nextuid_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a86761af16b95987441640bea6861132a</anchor>
      <arglist>(const std::string &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>EmailHeaders</type>
      <name>get_email_headers_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a5a53dc0d1ceb86baec63678cc7dc060b</anchor>
      <arglist>(const std::string &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; struct EmailContent &gt;</type>
      <name>get_email_content_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a6b5d710f645d106f79a0c1d15c7f9d75</anchor>
      <arglist>(const std::string &amp;response, EmailHeaders &amp;headers)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; struct EmailData &gt;</type>
      <name>get_email_data_from_response</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a653d46e023a23fecac67b8b95e32ff6b</anchor>
      <arglist>(const std::string &amp;response)</arglist>
    </member>
    <member kind="function">
      <type>std::optional&lt; std::string &gt;</type>
      <name>get_header_value</name>
      <anchorfile>namespaceemail_1_1utils_1_1response.html</anchorfile>
      <anchor>a30fbb8f3e4152b10b3998d176b5212d0</anchor>
      <arglist>(const std::string &amp;header_name, const EmailHeaders &amp;headers)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>&lt;tt&gt;email&lt;/tt&gt;: email-based middleware</title>
    <filename>index.html</filename>
  </compound>
</tagfile>
