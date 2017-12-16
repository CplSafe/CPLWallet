The BitSharesXT GUI wallet supports handling URLs with the custom xts: scheme. URLs of this scheme can be used to access certain information within the BitShares UI, such as an account page; or to perform an action within the BitShares network, such as voting for a delegate or making a transfer. Note that URLs which perform actions visible to the network will not be processed without confirmation from the owner of the wallet, so a URL which makes a transfer will automatically fill out the transfer form, but the user is still required to unlock his wallet and confirm the action.

The URL types currently supported are documented below. Unformatted text is to be interpreted as literal characters of a valid URL. _Italicized_ text is a placeholder for some other value, so _profile-name_ should be replaced with the name of a profile. Text in [square brackets] is a placeholder for an optional value. Pipe-delimited text in {curly|braces} represents values where only one of the values may appear at a time in a valid URL.

* Go to profile
 * xts:_profile-name_
* Add new contact with name
 * xts:_name_:_XTSaccountkey_
* Request Payment
 * xts:_name_/transfer/[amount/_amount_/]\[memo/_memo text_/]\[from/_sender name_/]\[asset/_asset name_]   (registered accounts)
 * xts:_name_:_XTSaccountkey_/transfer/[amount/_amount_/]\[memo/_memo text_/]\[from/_sender name_/]\[asset/_asset name_]  (unregistered accounts) (Not Yet Implemented)
 * The ordering of the amount, memo, from and asset fields is unimportant.
 * _name_, located at the beginning of the URL, is the name of the *receiving* account, and is required. In the general case, the sender may or may not be known, thus the _from_ field is optional.
* Vote for delegate
 * xts:_delegate-name_/{approve|disapprove}
* Go to block
 * xts:Block/num/_block-number_
 * xts:Block/_block-id_
* Go to transaction
 * xts:Trx/_transaction-id_
 * Note that _transaction-id_ above may be a prefix, as long as at least 8 characters are present
* Login to website
 * xts:Login/_server-one-time-public-key_/_signature-of-one-time-public-key-with-account-key_/www.server.com:port/path/to/login.php
 * For more information on the BitShares XT Login protocol, see [[here|BitShares XT Login]].