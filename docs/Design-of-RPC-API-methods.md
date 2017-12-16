# RPC implementation internals
============================

## Code Generation Overview
------------------------
The RPC API is defined by a set of JSON files in `libraries/api`

- `blockchain_api.json`
- `wallet_api.json`
- `network_api.json`

These files describe each RPC method, providing enough information to generate help,
the C++ method signature, a C++ RPC client, and a C++ RPC server.

From those files, it generates:
- `bts/api/common_api.hpp`: the pure virtual interface listing each of the methods listed in the
  JSON files.
- `bts/rpc_stubs/common_api_client.hpp` and `bts/rpc_stubs/common_api_client.hpp`:  a C++
  implementation of the client-side RPC API.  This code implements the common_api interface
  for talking to an out-of-process bitshares_client.  This code is used by `bts::rpc::rpc_client`,
  which derives from the client stub class and adds a few functions to establish the RPC
  network connection.
- `bts/rpc_stubs/common_api_server.hpp` and `bts/rpc_stubs/common_api_server.hpp`:  implements
  the server side of the RPC interface.  The generated code takes care of converting the
  method arguments from JSON to the native C++ types, validating the parameters, dispatching
  to native method in `bts::client::client`, and then converting the result back to JSON.
  This code is used by `bts::rpc::rpc_server`, which derives from the server stub class
  and adds methods to accept RPC and HTTP-RPC connections.

Implementing a new method
-------------------------
To add a new function to the JSON-RPC API.  I'll walk through the call I'm working on now,
`network_set_allowed_peers`.  The logic is already implemented in `bts::net::node` as
`void set_allowed_peers(const std::vector<node_id_t>& allowed_peers)`.

1. Implement the C++ call in `bts::client::client`.  All RPC methods must be implemented in
   client with the same name as they have in JSON-RPC, so this method will add the
   `network_` prefix and delegate the call to the node.  You only need to add the
   implementation in the .cpp file.  The method prototype in the header will be generated
   from the JSON.
```{.cpp}
void client::network_set_allowed_peers(const std::vector<bts::net::node_id_t>& allowed_peers)
{
  my->_p2p_node->set_allowed_peers(allowed_peers);
}
```
2. Add the function to the appropriate JSON file.  Since this is a network function, it goes
   in `network_api.json`.  Down in the `methods` section, add a method description:
```{.json}
{
  "method_name": "network_set_allowed_peers",
  "description": "Sets the list of peers this node is allowed to connect to",
  "return_type": "void",
  "parameters" :
    [
      {
        "name" : "allowed_peers",
        "type" : "node_id_list",
        "description" : "the list of allowable peers"
      }
    ],
  "prerequisites" : ["json_authenticated"],
  "detailed_description" : "This function sets the list of peers we're allowed to connect to. It is used during testing to force network splits or other weird topologies."
}
```
Some notes on the method description:
   - `description` should be a short one-liner, `detailed_description` (if present) should be a
     longer description that will be appended to the short `description` when we generate
     long-form help messages.
   - types like `return_type` and the `type` field for each parameter can be one of the predefined types
     the generator knows about, or one of the types defined in the `types` section of the json file.
     The default types are:
     - `void` (only used for return values, a method that takes no parameters just has an empty parameter list)
     - `int16_t`
     - `uint16_t`
     - `int32_t`
     - `uint32_t`
     - `int64_t`
     - `uint64_t`
     - `std::string`
     - `json_variant`, which maps to `fc::variant`
     - `json_object`, which maps to `fc::variant_object`
     - `json_variant_list`, which maps to `fc::variants`
     - `json_object_list`, which maps to `std::vector<fc::variant_object>`
   - `prerequisites` can be a list containing one or more of:
     - `"no_prerequisites"`
     - `"json_authenticated"`
     - `"wallet_open"` (implies `"json_authenticated"`)
     - `"wallet_unlocked"` (implies `"wallet_open"`)
     - `"connected_to_network"`
   - Since this is the first method to need the type `node_id_list`, we need to define it.  In C++, it's
     a vector of `bts::net::node_id_t`, and we don't know anything about those either.  So first, let's
     define a `node_id` type to the JSON generator.
~~~~~~~~~~~~~~~~~~~~~{.json}
{
  "type_name" : "node_id",
  "cpp_parameter_type" : "const bts::net::node_id_t&",
  "cpp_return_type" : "bts::net::node_id_t",
  "cpp_include_file" : "bts/net/node.hpp",
  "default_example" : "TODO"
}
~~~~~~~~~~~~~~~~~~~~~
     A few notes on this:
     - the `type_name` should be something that makes sense to display in our API help.  So prefer
       names like `node_id_list` to `std::vector<bts::net::node_id_t>`.
     - `cpp_parameter_type` is how objects of this type are passed as a parameter to functions.
       usually this is by const reference to larger objects, or by value for integer types.
     - `cpp_return_type` is the type as it appers as a return value, or for instantiating on
       the stack.  Usually just the type name.
     - `cpp_include_file` - if you provide this, it will make sure this file is included in any
       generated files that reference this type.
     - `default_example` is an object of that type, in JSON form, that will be used in generating
       example calls in the documentation.

     Now that the base type is defined, I need to define what a list of that type looks like:
~~~~~~~~~~~~~~~~~~~~~{.json}
{
  "type_name" : "node_id_list",
  "container_type" : "array",
  "contained_type" : "node_id",
  "default_example" : "TODO"
}
~~~~~~~~~~~~~~~~~~~~~
A few notes on this:
     - `container_type` can be `"array"` or `"dictionary"`.
       - `array` maps to `std::vector` and requires a `contained_type`
       - `dictionary` maps to `std::map`, and requires a `key_type` and `value_type`
2. Build.

## Command-Line Interface Prompting and Special Parameter Types
------------------------------------------------------------
The command line interface (CLI) will automatically prompt for missing required parameters. For example, if the user
types the command "unlock", the CLI will prompt the user to enter the required parameters "timeout" and "passphrase".
A CLI command can be aborted during prompted entry by pressing <ENTER> without entering any data.

Currently the command-line interface recoognizes these special types when prompting for parameters:

- passphrase: this type should be used for any password that shouldn't be echoed to the console during prompted entry.
- new_passphrase: this type should be used for any command that requires the user to specify a "new" password. In this case,
                  the CLI will not echo the password AND it will prompt for the password twice to verify it's accurate entry.
