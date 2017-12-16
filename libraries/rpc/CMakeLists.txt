file(GLOB HEADERS "include/ohl/rpc/*.hpp")

add_library( ohl_rpc 
             rpc_server.cpp
             rpc_client.cpp
             ${HEADERS}
           )

target_link_libraries( ohl_rpc 
                       PUBLIC ohl_blockchain ohl_rpc_stubs ohl_api ohl_wallet ohl_client ohl_net fc 
                       PRIVATE ohl_db ohl_utilities leveldb)
target_include_directories( ohl_rpc 
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
if (USE_PCH)
  set_target_properties(ohl_rpc PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(ohl_rpc)
endif(USE_PCH)
