if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/bitcoin/include )

add_executable( btc_wallet_dump bitcoin_recovery.cpp )
target_link_libraries( btc_wallet_dump fc ohl_blockchain ohl_utilities bitcoin )

add_executable( ohl_create_key ohl_create_key.cpp )
target_link_libraries( ohl_create_key fc ohl_blockchain ohl_utilities deterministic_openssl_rand )

add_executable( ohl_create_genesis ohl_create_genesis.cpp )
target_link_libraries( ohl_create_genesis fc ohl_blockchain ohl_utilities)

add_executable( key_to_wif key_to_wif.cpp )
target_link_libraries( key_to_wif fc ohl_blockchain ohl_utilities)

add_executable( ohl_key_info ohl_key_info.cpp )
target_link_libraries( ohl_key_info fc ohl_blockchain ohl_utilities)

add_executable( ohl_convert_addresses ohl_convert_addresses.cpp )
target_link_libraries( ohl_convert_addresses fc ohl_blockchain ohl_utilities)

# I've added two small files here that are also compiled in ohl_blockchain
# to avoid a circular dependency.  The circular dependency could be broken more cleanly
# by splitting ohl_blockchain, but it doesn't seem worth it just for this
add_executable( ohl_genesis_to_bin ohl_genesis_to_bin.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/blockchain/types.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/blockchain/pts_address.cpp )
target_link_libraries( ohl_genesis_to_bin fc )
target_include_directories( ohl_genesis_to_bin PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/blockchain/include" )

add_executable( ohl_json_to_cpp ohl_json_to_cpp.cpp )
target_link_libraries( ohl_json_to_cpp fc ohl_utilities)

add_executable( map_ohl_network map_ohl_network.cpp )
target_link_libraries( map_ohl_network fc ohl_net ohl_client)

add_executable( pack_web pack_web.cpp )
target_link_libraries( pack_web fc )

add_executable( compute_item_hashes compute_item_hashes.cpp )
target_link_libraries( compute_item_hashes fc ohl_net ohl_client)

if( ${INCLUDE_QT_WALLET} )
  add_subdirectory( web_update_utility )
endif()
