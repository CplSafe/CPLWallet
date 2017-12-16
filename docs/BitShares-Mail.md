The BitShares Toolkit supplies a mail subsystem, which supports basic encrypted and signed email functionality, and also serves as the foundation of transaction notifications. Arbitrary nodes on the network can be mail servers, which expose a public JSON-RPC API port to which mail clients can connect to post and retrieve mail. Users may publish a list of preferred mail servers in their public data, in which case senders must send mail to those servers. If the user does not publish a list of mail servers, a default set of mail servers is used instead. In this fashion, users can host their own private mail servers.

All BitShares Mail messages are encrypted, and the server sees only an encrypted blob and a recipient address. The recipient address is the owner address of the intended recipient's account on the blockchain. This means that recipients are identified by the mail, but the content of the message is unknown. In particular, the mail server (or an eavesdropper) does not know whether the mail is an email or transaction notification. The only information given by an encrypted message is the recipient address.

## Using BitShares Mail
To set your mail servers:
`wallet_set_preferred_mail_servers <account name> <list of server accounts> [paying account]`
Sets `account name`'s preferred mail servers to the ones managed by the accounts in `list of server accounts`. Each account in `list of server accounts` should have published a `mail_server_endpoint` field in their public data formatted as `IPv4 address:port number` which is the endpoint of a JSON-RPC server with the mail server enabled. If any account in `list of server accounts` has not published this field, `wallet_set_preferred_mail_servers` will return an error stating which one has not published his field. Presently, the default mail server on BitShares X is `nathanhourt.com`.

To send mail:
`mail_send <from account name> <to account name> <subject> <body> [in-reply-to ID]`
This returns a temporary message ID which identifies the message as it proceeds through the sending process. To see the status of outgoing messages in processing, use `mail_get_processing_messages`. If a message has failed to send, use `mail_get_message <ID>` to see why the message failed. To retry sending a message, use `mail_retry_send <ID>`.

To receive mail:
`mail_check_new_messages`
This fetches new messages from the recipients' mail servers, stores them in the archive, and returns the number of new messages. Use `mail_inbox` to see the newly retrieved messages and their ID's. Use `mail_get_message <ID>` to see the entire email. Use `mail_archive_message <ID>` to remove the message from the inbox, and `mail_get_archive_messages` to view the entire archive. To fetch all mail from the servers, regardless of whether it's new or not, use `mail_check_new_messages true`.

The mail client supports searching the archive by sender and receiver. Use `mail_get_messages_from <sender>`, `mail_get_messages_to <recipient>`, and `mail_get_messages_in_conversation <account one> <account two>`.

To delete mail in the archive:
`mail_remove_message <ID>`
This permanently deletes the message from the local archive. The message may still be on mail servers.

To see a complete listing of mail calls and their documentation:
`help mail` or `mail?`

### Mail Server Calls
The `mail_fetch_inventory`, `mail_fetch_message` and `mail_store_message` calls are only valid on mail servers. These calls are not intended to be used by humans, and can safely be ignored.