# `email` design

**Note**: for a rendered version of this document, see: https://christophebedard.com/rmw_email/design/email/

1. [Use of emails](#use-of-emails)
   1. [As a message container](#as-a-message-container)
   1. [Headers](#headers)
   1. [Polling](#polling)
1. [Overall architecture](#overall-architecture)
1. [Waiting on messages](#waiting-on-messages)
1. [Data containers](#data-containers)
   1. [Email](#email)
   1. [Messages](#messages)

## Use of emails

### As a message container

Emails are used as a container to send and receive string messages.

The email subject is used for the topic name or service name.
The email body contains the string message.

### Headers

Emails include both standard and non-standard (i.e., custom) headers.
Email headers are used to include metadata about each communication instance in a structured way without polluting the content itself (i.e., email body).
See [*Data containers*](#data-containers).
These custom headers do not have a `X-` prefix as per [RFC 6648](https://datatracker.ietf.org/doc/html/rfc6648).

This metadata is thus also used to be able to differentiate between publisher/subscription messages and service requests/responses.
See [*Overall architecture*](#overall-architecture).

The headers of the service response emails are set so that the email is a reply to the original service request email.
This is done by setting the values of the `In-Reply-To` and `References` headers of the response email to the value of the `Message-ID` header of the request email.
See [page 26 of RFC 5322](https://datatracker.ietf.org/doc/html/rfc5322#page-26).

The use of these headers also helps differentiate between a service request and a service response.

### Polling

To poll for new emails using the IMAP protocol commands, we can:

* first run an `EXAMINE INBOX` command to get the UID value of the next email
   * a UID is simply a unique identifier for each email
      * see [RFC 3501 section 2.3.1.1](https://datatracker.ietf.org/doc/html/rfc3501#section-2.3.1.1)
   * the next UID value is called `UIDNEXT` in the command response
   * see [RFC 3501 section 6.3.2](https://datatracker.ietf.org/doc/html/rfc3501#section-6.3.2) for the `EXAMINE` command and response
* then periodically try to fetch en email using that UID
   * if there is no new email, the command will fail
      * keep trying
   * if there is a new email, we increment an internal UID counter
   * then we repeat this step with this new value

## Overall architecture

There are three main layers to send and receive messages:

1. `curl`: context, executor
   * does basic `libcurl` initialization
   * connects to remote server
1. email: sender, receiver
   * uses the first layer with `libcurl` to execute commands to:
      * send emails through `smtps` (secure SMTP)
      * poll for emails through `imaps` (secure IMAP)
   * email senders can send an email that is a reply to an email received by an email receiver
   * see [*Use of emails*](#use-of-emails)
1. publisher/subscription and service client/server
   * publishers are simply email senders
   * subscriptions indirectly use email receivers
   * service clients use publishers to send requests and indirectly use email receivers to receive responses
   * service servers indirectly use email receivers to receive requests and use email senders to send responses by replying to the request email

Internal handling of emails/mesages is done as follows:

1. polling manager
   * uses an email receiver to poll for new emails on a thread
   * calls all registered handlers when a new email is received
1. handlers: subscription, service client/server
   * all handlers register with the polling manager
   * handlers check whether the new email applies to them
      * see [*Use of emails*](#use-of-emails)
   * if so, they pass it on to the right object(s) that registered with them
      * according to topic name or service name
1. subscriptions, service clients/servers
   * all subscriptions register with the subscription handler
   * all service clients and servers register with the service handler
   * new messages, service requests or service responses are added to the corresponding queues or maps
      * subscriptions have a message queue
      * service clients have a response map
      * service servers have a request queue
   * users can either poll the subscription/client/server directly for new messages/requests/responses or wait on it
      * see [*Waiting on messages*](#waiting-on-messages)

```plantuml
@startuml

class CurlContext {
   +init()
   +fini()
   +get_handle(): CURL *
   +execute()
}
hide CurlContext fields
hide CurlContext circle

class CurlExecutor {
   +init()
   #init_options() {abstract}
   #context: CurlContext
}
hide CurlExecutor fields
hide CurlExecutor circle
CurlContext *-- CurlExecutor


class EmailSender {
   +send(EmailContent, optional<EmailHeaders>)
   +reply(EmailContent, EmailData, optional<EmailHeaders>)
   #init_options() {abstract}
}
hide EmailSender fields
hide EmailSender circle
CurlExecutor <|-- EmailSender

class EmailReceiver {
   +get_email(): optional<EmailData>
   #init_options() {abstract}
   -get_nextuid(): optional<int>
   -get_email_from_uid(int): optional<EmailData>
   -execute(optional<string>, url_options, optional<string> custom_request): optional<string>
}
hide EmailReceiver fields
hide EmailReceiver circle
CurlExecutor <|-- EmailReceiver


class PollingManager {
   -thread
   -handlers: vector<function<void (EmailData)>>
   -poll_thread()
   +start()
   +shutdown()
   +register_handler(function<void (EmailData)>)
}
EmailReceiver o-- PollingManager
hide PollingManager circle

abstract class EmailHandler {
   +handle(EmailData) {abstract}
}
hide EmailHandler fields
hide EmailHandler circle


class SubscriptionHandler {
   -subscriptions
   +register_subscription(string topic_name, queue<pair<string, MessageInfo>> message_queue)
   +handle(EmailData) {abstract}
}
hide SubscriptionHandler fields
hide SubscriptionHandler circle
EmailHandler <|-- SubscriptionHandler
PollingManager "registers with" <-- SubscriptionHandler

class ServiceHandler {
   -clients
   -servers
   +register_service_client(Gid, map<SequenceNumber, pair<EmailData, ServiceInfo>> response_map)
   +register_service_server(string service_name, queue<pair<EmailData, ServiceInfo>> request_queue)
   +handle(EmailData) {abstract}
}
hide ServiceHandler fields
hide ServiceHandler circle
EmailHandler <|-- ServiceHandler
PollingManager "registers with" <-- ServiceHandler


class GidObject {
   -gid: Gid
   +get_gid(): Gid
}
hide GidObject circle
class NamedObject {
   -object_name: string
   #get_object_name(): string
   #validate_name() {abstract}
}
hide NamedObject circle

class PubSubObject {
   +get_topic_name(): string
   -validate_name() {abstract}
}
hide PubSubObject fields
hide PubSubObject circle
GidObject <|-- PubSubObject
NamedObject <|-- PubSubObject

class ServiceObject {
   +get_service_name(): string
   -validate_name() {abstract}
}
hide ServiceObject fields
hide ServiceObject circle
GidObject <|-- ServiceObject
NamedObject <|-- ServiceObject


class Publisher {
   +publish(string message, optional<EmailHeaders> additional_headers)
}
hide Publisher fields
hide Publisher circle
PubSubObject <|-- Publisher
EmailSender o-- Publisher

class Subscription {
   -messages: queue<pair<string, MessageInfo>>
   +has_message(): bool
   +get_message(): optional<string>
   +get_message_with_info(): optional<pair<string, MessageInfo>>
}
hide Subscription circle
PubSubObject <|-- Subscription
SubscriptionHandler "registers with" <-- Subscription


class ServiceClient {
   -responses: map<SequenceNumber, pair<EmailData, ServiceInfo>>
   +send_request(string request, SequenceNumber seq)
   +send_request(request): SequenceNumber
   +has_response(SequenceNumber seq): bool
   +has_response(): bool
   +get_response(SequenceNumber seq): optional<string>
   +get_response_with_info(SequenceNumber seq): optional<pair<string, ServiceInfo>>
   +get_response_with_info(): optional<pair<string, ServiceInfo>>
}
hide ServiceClient circle
ServiceObject <|-- ServiceClient
Publisher *-- ServiceClient
ServiceHandler "registers with" <-- ServiceClient

class ServiceServer {
   -requests: queue<pair<EmailData, ServiceInfo>>
   +has_request(): bool
   +get_request(): optional<ServiceRequest>
   +get_request_with_info(): optional<pair<ServiceRequest, ServiceInfo>>
   +send_response(ServiceRequestId request_id, string response)
}
hide ServiceServer circle
ServiceObject <|-- ServiceServer
EmailSender *-- ServiceServer
ServiceHandler "registers with" <-- ServiceServer

@enduml
```

## Waiting on messages

Subscriptions and service clients/servers must be waited on through polling.
Wait sets can be used to wait on new messages, service requests or service responses.
Some utility functions can be used to wait on a specific object using a wait set.

Wait sets also support guard conditions as another way to control waiting.

```plantuml
@startuml

class GuardCondition {
   +trigger()
   +triggered(): bool
   +exchange_in_use(bool in_use): bool
   +reset()
}
hide GuardCondition fields
hide GuardCondition circle

class WaitSet {
   -subscriptions: vector<Subscription *>
   -clients: vector<ServiceClient *>
   -servers: vector<ServiceServer *>
   -guard_conditions: vector<Subscription *>
   +add_subscription(Subscription *)
   +add_client(ServiceClient *)
   +add_server(ServiceServer *)
   +add_guard_condition(GuardCondition *)
   +get_subscriptions(): vector<Subscription *>
   +get_clients(): vector<ServiceClient *>
   +get_servers(): vector<ServiceServer *>
   +get_guard_conditions(): vector<GuardCondition *>
   +wait(milliseconds timeout): bool
   +clear()
}
hide WaitSet circle

class wait. {
   .. Subscription ..
   +wait_for_message(Subscription * subscription, milliseconds timeout): string
   +wait_for_message_with_info(Subscription * subscription, milliseconds timeout): pair<string, MessageInfo>
   .. Service client ..
   +wait_for_response(SequenceNumber seq, ServiceClient * client, milliseconds timeout): string
   +wait_for_response_with_info(SequenceNumber seq, ServiceClient * client, milliseconds timeout): pair<string, ServiceInfo>
   .. Service server ..
   +wait_for_request(ServiceServer * server, milliseconds timeout): ServiceRequest
   +wait_for_request_with_info(ServiceServer * server, milliseconds timeout): pair<ServiceRequest, ServiceInfo>
}
hide wait. circle
hide wait. fields
WaitSet <-- wait

@enduml
```

## Data containers

### Email

Emails contain:

* recipients
* subject
* body
* headers (metadata)

```plantuml
@startuml

/'
class ConnectionInfo {
   +host: string
   +username: string
   +password: string
}
hide ConnectionInfo circle
hide ConnectionInfo methods

class ProtocolInfo {
   +protocol: string
   +port: int
}
hide ProtocolInfo circle
hide ProtocolInfo methods

class UserInfo {
   +host_smtp: string
   +host_imap: string
   +username: string
   +password: string
}
'/

class EmailRecipients {
   +to: vector<string>
   +cc: vector<string>
   +bcc: vector<string>
}
hide EmailRecipients circle
hide EmailRecipients methods

class EmailHeaders <<typedef>> {
   map<string, string>
}
hide EmailHeaders circle
hide EmailHeaders methods

class EmailContent {
   +subject: string
   +body: string
}
hide EmailContent circle
hide EmailContent methods

class EmailData {
   +message_id: string
   +in_reply_to: string
   +from: string
   +recipients: EmailRecipients
   +content: EmailContent
   +additional_headers: EmailHeaders
}
hide EmailData circle
hide EmailData methods
EmailRecipients *-- EmailData
EmailContent *-- EmailData
EmailHeaders *-- EmailData

@enduml
```

### Messages

Basic metadata is provided for all communication instances (i.e., messages, service requests or service responses):

* source timestamp
* reception timestamp
* GID of the source object (i.e., publisher, service client or service server)
   * a GID is just a unique identifier

Additionally, for service requests/responses:

* sequence number of the request
   * for service responses, this is the sequence number of the original request

```plantuml
@startuml

class Timestamp {
   +nanoseconds(): int64_t
   +to_string(): string
   +from_string(string timestamp): optional<Timestamp> {static}
   +now(): Timestamp {static}
}
hide Timestamp fields
hide Timestamp circle

class GidValue <<typedef>> {
   uint32_t
}
hide GidValue circle
hide GidValue methods
class Gid {
   +value(): GidValue
   +to_string(): string
   +from_string(string gid): optional<Gid> {static}
   +new_gid(): Gid {static}
}
hide Gid fields
hide Gid circle
GidValue *-- Gid

class SequenceNumber <<typedef>> {
   int64_t
}
hide SequenceNumber circle
hide SequenceNumber methods


class CommunicationInfo {
   +source_timestamp(): Timestamp
   +received_timestamp(): Timestamp
   +source_gid(): Gid
   +from_headers(EmailHeaders headers, string source_gid_header): optional<CommunicationInfo> {static}
}
hide CommunicationInfo fields
hide CommunicationInfo circle
Timestamp "2" *-- CommunicationInfo
Gid *-- CommunicationInfo

class MessageInfo {
   +source_timestamp(): Timestamp
   +received_timestamp(): Timestamp
   +publisher_gid(): Gid
   +from_headers(EmailHeaders headers): optional<MessageInfo> {static}
}
hide MessageInfo fields
hide MessageInfo circle
CommunicationInfo *-- MessageInfo

class ServiceInfo {
   +source_timestamp(): Timestamp
   +received_timestamp(): Timestamp
   +client_gid(): Gid
   +sequence_number(): SequenceNumber
   +from_headers(EmailHeaders headers): optional<ServiceInfo> {static}
}
hide ServiceInfo fields
hide ServiceInfo circle
CommunicationInfo *-- ServiceInfo
SequenceNumber *-- ServiceInfo

class ServiceRequestId {
   +sequence_number: SequenceNumber
   +client_gid: Gid
}
hide ServiceRequestId circle
hide ServiceRequestId methods
SequenceNumber *-- ServiceRequestId
Gid *-- ServiceRequestId

class ServiceRequest {
   +id: ServiceRequestId
   +content: string
}
hide ServiceRequest circle
hide ServiceRequest methods
ServiceRequestId *-- ServiceRequest

@enduml
```
