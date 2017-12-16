file(GLOB HEADERS "include/ohl/light_wallet/*.hpp")

add_library( ohl_light_wallet
             light_wallet.cpp
             ${HEADERS}
           )

target_link_libraries( ohl_light_wallet fc ohl_utilities ohl_blockchain ohl_rpc_stubs )
target_include_directories( ohl_light_wallet
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

if (USE_PCH)
  set_target_properties(ohl_light_wallet PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(ohl_light_wallet)
endif(USE_PCH)
