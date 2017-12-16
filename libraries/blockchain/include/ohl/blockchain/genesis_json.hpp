#pragma once
#include <ohl/blockchain/genesis_state.hpp>
#include <sstream>

namespace ohl { namespace blockchain {

  genesis_state get_builtin_genesis_block_config();
  fc::sha256 get_builtin_genesis_block_state_hash();

} } // ohl::blockchain
