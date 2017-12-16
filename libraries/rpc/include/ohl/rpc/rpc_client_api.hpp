#pragma once

#include <ohl/net/node.hpp>
#include <ohl/wallet/wallet.hpp>

#include <fc/filesystem.hpp>
#include <fc/network/ip.hpp>

#include <memory>

namespace ohl { namespace rpc {
  namespace detail { class rpc_client_impl; }

    using namespace ohl::blockchain;
    using namespace ohl::wallet;

    typedef vector<std::pair<share_type,string> > balances;

    enum generate_transaction_flag
    {
      sign_and_broadcast    = 0,
      do_not_broadcast      = 1,
      do_not_sign           = 2
    };

} } // ohl::rpc
FC_REFLECT_ENUM( ohl::rpc::generate_transaction_flag, (do_not_broadcast)(do_not_sign)(sign_and_broadcast) )
