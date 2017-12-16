**Note: The latest code runs out of file descriptors on multi-client tests on OSX due to the number of databases we are using. You will need to increase your process file descriptor limit to prevent these tests from crashing. Note that the `run_regression_tests.sh` script will automatically increase this limit.**

The regression testing system allows the recording and playback of command-line
interface (CLI-based) tests. These tests are aimed at detecting regressions in
bitshares clients at the functional level. 

Verification is performed by comparing the results of the command-line
interface log session for each client against a golden-reference log session.
Input for each client from the testcomes from these same golden reference log
files.

The tests are stored in bitshares_toolkit\test as follows:

```
regression_tests\
  one_client_test\
    test.config
    client.log
  two_client_test\
    test.config
    client1.log
	client2.log
  ...
```

In the above example, two_client_test consists of a single test run that
launches two clients. The test.config file tells the test how to configure the
two clients, and in this example contains:

```
client1 --input-log=client1.log --upnp=false
client2 --input-log=client2.log --upnp=false
```

The `--input-log` says to create one client named client1 and send it CLI input
commands from client1.log and create a second client named client2 and send
it CLI input commands from client2.log. Each client can also be configured
with other bitshares command line arguments as desired (e.g. --unpn=false).
Multiple --input-logs args can be passed to a client.

## Regression Test Results Directories
-----------------------------------

If no data-dir is supplied as a command-line argument (this is the preferred
operation for regression tests except for tests that are testing this specific functionality),
the regression test run will be recorded in an output directory parallel to the
bitshares_toolkit source directory. For example, if your source is located in:

```
\gh\bitshare_toolkit
```

then the regression tests output will be stored as:

```
\gh\regression_tests_output\
  one_client_test\
    client.log
  two_client_test\
    client1.log
	client2.log
```

The CLI output logs in these directories can be visually diffed for changes whenever
there is a mismatch between an input log file located under the `regression_tests` directory and
the corresponding output log file located under the `regression_tests_output` directory.

The test generates an "expected_output" file for each client in the test. This expected_output
file is a concatenation of all the files fed to the client via --input-log. After all
clients have completed (due to each receiving a "quit" command), the test system does
a binary comparison between each expected_output file and the corresponding client's
console.log. The expected_output files are in `regression_tests_output` under the given
test directory. The console.log files are located in the data dirs (under the test
directory in regression_tests_output). For example, if you run a test called `wallet_asset_test`
with two clients called `blockmaker` and `transactor`, four result files will be created when you run the test:

```
regression_tests_output\regression_tests\wallet_asset\expected_output_blockmaker.log
regression_tests_output\regression_tests\wallet_asset\blockmaker\console.log

regression_tests_output\regression_tests\wallet_asset\expected_output_transactor.log
regression_tests_output\regression_tests\wallet_asset\transactor\console.log
```
These two pairs of files are binary diffed by the test platform to detect any errors.

In the event that a test fails due to a binary mismatch, you can diff the expected_output file
and the failing console.log to see what caused the test failure. If an output formatting
change caused the test to fail, you only need to cut/paste the appropriate lines
from the console.log file to the test files located in regression_tests directory
in the git repository. On windows, you can keep a kdiff session running that compares the actual output
and the expected output and refresh to see the differences each time you make a change and re-run a
test.

## Launching the Regression Tests
------------------------------
Currently, regression tests are inappropriately located in "wallet_test".
To run the tests, run:

```
cd bitshares_toolkit\tests
./wallet_tests -t regression_tests_without_network
```

Developing and Testing a Single Test
------------------------------------
The above command runs all the tests in the regresssion_tests directory. 
While developing a test, you will often only want to run your test. 
The easiest way to do this right now is to name it on the command line:
```
./wallet_tests -t regression_tests_without_network/transfer_test
```

Creating a Regression Test
--------------------------
To create a regression test, you need to perform the following steps:

1. Create a new test directory under `test\regression_tests` (e.g. my_test)
2. Record a log session using the bitshares client for each client that will
   be involved in your test, and copy the console.log for that client to your
   test directory, renaming the log files so that they don't conflict with each other.
   You can add delays between the execution of commands in your script
   using the "wait" command (e.g. `wait 60` to wait 60 seconds before executing the next command).
   There are also commands that delay in terms of block intervals that can be used when
   you need to wait for a transaction to be included into a block.
   To record a session, you should be running a client that is configured to use the "test genesis
   block" and that will just connect up to your other "test clients". The test genesis block is
   located in `bitshares_toolkit\tests\test_genesis.json`. The public/private key pairs for
   the delegates in this test genesis block are stored in 
   `bitshares_toolkit\tests\test_genesis.json.keypairs`. These two files were originally created
   by running `wallet_tests.exe --t make_test_genesis_block`. 
3. To record a test log session with  one or more clients, you can run these batch scripts: 
   `client0.bat`, `client1.bat`, `client2.bat`.
   These scripts will spawn clients that just run locally and connect to each other as an isolated
   network. They store their datadirs in `bitshares_toolkit\regression_tests\_new_test`, so be sure
   you delete this directory before you commit.
4. You can execute an input-log script directly from the CLI so that you don't have to manually
   type all the commands of commonly used setup scripts. For example, to create a wallet, you
   can type:
   `execute_script regression_tests/_common_logs/create_and_unlock_wallet.log`
5. Generally, you should type "quit" as the last line in your script to avoid the test
   stopping at a command prompt and prompting for console input after the script finishes.
   However, you may want to temporarily remove the quit from a test when you'd like to
   type commands to a client after it's finished executing the script to check the client's
   status, just don't forget to add the quit back to the script afterwards.
6. Create a test.config in your test directory that specifies on each line the
   command-line arguments for a single client. The first parameter on the line
   should be used to name each client. Try to use useful client names when possible.
   For example, if your test is performing a transfer from one client to another,
   you could name the first client "sender" and the second client "receiver".
7. By convention, scripts that are useful in many tests should be stored in this directory:
   `regresssion_tests\_common_logs`
   
## Configuring Delegates for a Test
--------------------------------
The DPOS blockchain used by bitshares_toolkit requires that "delegate" accounts are created that can
produce the blocks every block interval. These delegate accounts are already registered in the genesis
block for the tests (genesis.json file). 

Any test that requires a blockchain (in other words, most tests) will need to configure at least
one or two clients with delegate accounts so that blocks can be produced (otherwise, no transactions
will be included into blocks). The existing tests use one of two methods
for this: 

1. a single client imports the keys for all the delegates and this client is responsible for generating all the blocks
2. two clients each import 1/2 of the delegate keys and each produces blocks

Single client tests are simplest because they don't require synchronization between clients. There
are however two drawbacks to this technique:

1. it doesn't test broadcast operations across clients, so it's not suitable for network testing
2. you have to enable and disable block production in the delegate accounts before your client will
scan the blockchain for transactions pertinent to your wallet (this is a restriction on clients
that was implemented to avoid causing wallet scanning to slow down delegates too much causing them
to fail to produce a block during their time slot which in turn could increase the chance for
blockchain forks).

Despite these restrictions, simple API tests should probably use the single client approach.

When you do need to use multiple clients for a test, the current recommended practice is to create
one client that has all the delegates (the "block-maker" client) and another client that will act
will generate transactions and scans the blockchain to ensure that they get incorporated into blocks 
in the future (the "transactor" client).  The transactor client may import a few
delegate accounts in order to access their initial balances, but the transactor should leave 
block production disabled for all delegate accounts so that it can perform blockchain scanning, 
and should have at most 5 accounts (scanning time increases as the number of accounts increases)
   
   
## Using Simulated Time in Tests
-----------------------------
To make the tests run faster and also to ensure repeatability of timestamps in the test, the tests 
are generally written to use simulated time instead of actual time. The simulated time system is 
less than perfect at the moment when creating a multiple client test, because it can be tricky to 
get the clients properly synchronized. 

Simulated time is first initialized by the `debug_start_simulated_time` 
command, then then advanced by using `debug_advance_time` commands. Time 
is shared by all clients in the test, so if one client advances the 
time, all clients will see the time advance. In simulated time tests, 
clients will usually avoid waiting for specific amounts of time, instead 
wait for blocks to be produced using `debug_wait_for_block`. There's 
three methodologies that work right now for simulated time: 

1. one client test is the simplest as it requires no cross-client time synchronization
2. two client test where one client is block-maker and simulated time is advanced by whichever client is generating the transaction (other client waits for the block). This approach is used in `titan_test`.
3. three or more client tests where the block-maker advances time and the transactor clients wait for 
blocks generated by the block-maker (so far this method has only been tested with 2 clients and only 
in create_asset test). 

## Using Real Time in Tests
------------------------
Wall-time can also be used for a test, although it's not recommended for any test that generates 
more than one or two blocks. An example of such a test is transfer_test.  It uses `debug_wait_block_interval` to wait long enough to guarantee that a block is produced.

   
## Common Scripts Needed for a Test
--------------------------------
The directory `regression_tests\_common_logs` contains a number of re-usable scripts, and several of 
these scripts will be needed by most tests. Below is a short summary of the purpose of some of these 
scripts: 

```
initialize_simulated_time.log: initializes a client to use simulated time instead of actual wall-time. 
create_and_unlock_wallet: this creates a wallet named default in the client. Most all clients will need this script.
import_delegate_keys: imports all delegate keys into a client. Delegates are the block producers, so you must have at least one client that imports delegate keys if you need to test any operations that involve block creation.
advance_5_blocks: advances simulated time for 5 blocks. This script is intended for use by a block-maker client.
```