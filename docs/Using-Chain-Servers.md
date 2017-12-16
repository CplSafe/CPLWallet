The BitShares toolkit supports an alternative method of syncing long, continuous segments of blockchain via a feature called Chain Servers. The Chain Servers, unlike the normal P2P network, exist only to provide long sequences of blocks from the official chain. This allows for a more efficient initial sync. **After** syncing from a Chain Server, the client will connect to the P2P network as usual to keep in sync with the network. This means that while the client syncs from the Chain Server, it will have no connections to the P2P network. The status of the sync can be queried by running `get_info` in the console and noting the current head block number.

## Using a Chain Server to Sync with BitShares X
A future release of BitShares X will include a set of seed servers, which will allow clients to connect and sync from a chain server automatically. At the time of this writing, clients which wish to sync from a chain server must add one manually to their `config.json` file. A chain server for the BitShares X network is maintained by BitShares X user delegate.nathanhourt.com at `69.90.132.209`.

To sync from this chain server, first locate your `config.json` file. This file will be located in the BitShares X data directory, which is placed in these locations by default:

 - Windows: `%APPDATA%/BitShares X` (Try going to Start->Run and opening %APPDATA%, then open the BitShares X folder)
 - Mac: `~/Library/Application Support/BitShares X` (Open a Finder window and press Command-Shift-G, then paste in the path)
 - Linux: `~/.BitSharesX`

In this folder, find the config.json file and open it with your preferred text editor (Mac users may use TextEdit and Windows users may use Notepad). In this file, find the `chain_servers` list, which is located by default immediately after the `default_peers` list. If you do not see `chain_servers` in your `config.json`, your `config.json` was created by an old version of BitShares X. Delete `config.json` and restart your client, then open it again. If there is still not a `chain_servers` section, update your BitShares X client.

When you have found the `chain_servers` section in your config.json, modify that section to add delegate.nathanhourt.com's chain server as follows:

```"chain_servers": ["69.90.132.209:1375"],```

When finished, there should only be one `chain_servers` line (ignore the `chain_server` section) and make sure that this line looks like the one above and ends with a comma. Save your changes and close `config.json`. The next time you start your client, it should sync from the new chain server before connecting to the P2P network.

## Running Your Own Chain Server
To run a chain server of your own, open `config.json` as described above, and edit the `chain_server` section (not the `chain_servers` section as above). If this section does not exist, follow the instructions above to recreate your `config.json`.

In the `chain_server` config, set the `enabled` property to true, and set a `listen_port` for your chain server. Save your changes and restart your BitShares X client. If the chain server is configured correctly, part of the startup output of the client will say

```Starting a chain server on port ####```

where `####` is the port you specified in your config file. Note that only command line clients may run a chain server; the GUI client cannot run a chain server.