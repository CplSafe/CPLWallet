#pragma once

#include <ohl/blockchain/feed_record.hpp>
#include <ohl/blockchain/operations.hpp>
#include <ohl/blockchain/types.hpp>

namespace ohl { namespace blockchain {

  struct update_feed_operation
  {
      static const operation_type_enum type;
      feed_index   index;
      fc::variant  value;

      void evaluate( transaction_evaluation_state& eval_state )const;
      void evaluate_v1( transaction_evaluation_state& eval_state )const;
  };

} } // ohl::blockchain

FC_REFLECT( ohl::blockchain::update_feed_operation, (index)(value) )
