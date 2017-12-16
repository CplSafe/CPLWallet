BitShares supports a system of account hierarchies, where one parent account may have many children, grandchildren, etc. and that parent can update children or grandchildren at will. Subaccounts are denoted by dots in their names, similar to subdomains, so if a user registers an account ``bob``, he may register the subaccount ``child.bob`` using ``bob``'s private key. This means that only ``bob`` may register ``child.bob``, and ``bob`` can update ``child.bob`` at any time.

Subaccounts can be recursive, so ``child.bob`` could authorize the creation of ``grand.child.bob`` if he desired. It is useful to note that ``bob`` is not able to create ``grand.child.bob`` as it is not a direct descendent; however, ``bob`` can later update a grandchild after its registration if he desires.

## Creating Subaccounts

Subaccounts are created just like any other account. The user first creates a local account with the full subaccount name, i.e. ``child.parent``, and then registers it. The only caveat is that the wallet which registers the subaccount must have the private key of the parent account, i.e. ``parent``. This does not necessitate the same wallet to have both keys; if a user Alice wishes to register a subaccount as a child of an account owned by another user, Bob, then Alice may create a local account named ``alice.bob`` and send Bob the public key. Bob then creates a contact account named ``alice.bob`` with the public key he received from Alice and registers the account for Alice. This way neither Alice nor Bob disclosed their private keys to anyone.

At the time of this writing, the wallet GUI does not allow periods in account names. In order to create the local subaccount, the command line interface must be used, either by running bitshares_client or by using the Console tab in the GUI.

## Naming Rules
Each component of a subaccount name must be a valid name, so in the subaccount ``delegate1.delegates.delegated-proof-of-steak``, all of ``delegate1.delegates.delegated-proof-of-steak``, ``delegates.delegated-proof-of-steak``, and ``delegated-proof-of-steak`` must be valid accounts as well. This means that ``1.delegates.delegated-proof-of-steak`` is not a valid account name, because ``1`` is not a valid account name. Names cannot have consecutive dots, i.e. ``a..b`` is not a valid account name.

Subaccount rules only apply in one direction, i.e. ``child.parent`` and ``child`` have no relationship, and both of these accounts may exist.

## Updating Rules
A parent may perform a wallet_account_update_registration on any of its descendents, so ``grand.child.parent`` may be updated by ``child.parent`` or ``parent``, and ``child.parent`` may be updated by ``parent``. The parent may authorize such an update using either its active key or its owner key.