#include <ohl/blockchain/operations.hpp>

namespace ohl { namespace blockchain {

    struct data_operation
    {
        static const operation_type_enum  type;
        uint64_t                          tag;
        std::vector<char>                 data;
        void evaluate( transaction_evaluation_state& eval_state )const;
    };

}} // ohl::blockchain

FC_REFLECT( ohl::blockchain::data_operation,
            (tag)
            (data)
            )

