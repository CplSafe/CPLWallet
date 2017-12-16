#include <ohl/blockchain/address.hpp>
#include <ohl/blockchain/pts_address.hpp>
#include <ohl/blockchain/types.hpp>
//#include <ohl/utilities/deterministic_openssl_rand.hpp>
#include <ohl/utilities/key_conversion.hpp>


#include <fc/crypto/elliptic.hpp>
#include <fc/io/json.hpp>
#include <fc/reflect/variant.hpp>
#include <fc/filesystem.hpp>
#include <fc/variant_object.hpp>

#include <iostream>

using namespace ohl::blockchain;

int main( int argc, char** argv )
{ try {
    // btc and pts addresses
    if( argc < 3 )
    {
        std::cout << "Usage: ohl_convert_addresses <snapshot_file> <output_file>\n";
        exit(1);
    }
    auto pts_snapshot = fc::json::from_file( argv[1] ).as<std::map<string, share_type>>();
    std::map<address, share_type> snapshot;
    for( auto pair : pts_snapshot )
    {
        auto addr = address( pts_address( pair.first ) );
        if( snapshot.find( addr ) == snapshot.end() )
            snapshot[addr] = pair.second;
        else
            FC_ASSERT(!"Duplicate address!");
    }
    fc::json::save_to_file( snapshot, string(argv[2]) );
} FC_CAPTURE_AND_RETHROW() }
