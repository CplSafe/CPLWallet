#pragma once
#include <ohl/blockchain/block.hpp>
#include <ohl/client/client.hpp>

namespace ohl { namespace client {

   enum message_type_enum
   {
      trx_message_type          = 1000,
      block_message_type        = 1001
   };

   struct trx_message
   {
      static const message_type_enum type;

      ohl::blockchain::signed_transaction trx;
      trx_message() {}
      trx_message(ohl::blockchain::signed_transaction transaction) :
        trx(std::move(transaction))
      {}
   };

   struct block_message
   {
      static const message_type_enum type;

      block_message(){}
      block_message(const ohl::blockchain::full_block& blk )
      :block(blk),block_id(blk.id()){}

      ohl::blockchain::full_block    block;
      ohl::blockchain::block_id_type block_id;

   };

} } // ohl::client

FC_REFLECT_ENUM( ohl::client::message_type_enum, (trx_message_type)(block_message_type) )
FC_REFLECT( ohl::client::trx_message, (trx) )
FC_REFLECT( ohl::client::block_message, (block)(block_id) )
