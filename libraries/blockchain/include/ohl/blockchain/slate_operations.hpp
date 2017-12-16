#pragma once

#include <ohl/blockchain/operations.hpp>

namespace ohl { namespace blockchain {

struct define_slate_operation
{
    static const operation_type_enum type;

    vector<signed_int> slate;

    void evaluate( transaction_evaluation_state& eval_state )const;
};

} } // ohl::blockchain

FC_REFLECT( ohl::blockchain::define_slate_operation, (slate) )
