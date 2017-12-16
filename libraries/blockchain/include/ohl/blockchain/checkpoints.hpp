#pragma once
#include <ohl/blockchain/types.hpp>

namespace ohl { namespace blockchain {

static std::map<uint32_t, ohl::blockchain::block_id_type> CHECKPOINT_BLOCKS
{
    
};

// Initialized in load_checkpoints()
static uint32_t LAST_CHECKPOINT_BLOCK_NUM = 0;

} } // ohl::blockchain
