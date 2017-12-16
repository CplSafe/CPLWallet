file(GLOB HEADERS "include/ohl/wallet/*.hpp")

add_library( ohl_wallet
             wallet_records.cpp
             wallet_db.cpp
             bitcoin.cpp
             transaction_builder.cpp
             transaction_ledger.cpp
             transaction_ledger_experimental.cpp
             login.cpp
             wallet.cpp
             ${HEADERS}
           )

target_link_libraries( ohl_wallet fc ohl_db ohl_utilities ohl_blockchain leveldb bitcoin ohl_keyhotee ohl_cli )
target_include_directories( ohl_wallet
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" )

configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/include/ohl/wallet/url.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/include/ohl/wallet/url.hpp" )


if(MSVC)
  set_source_files_properties(wallet.cpp PROPERTIES COMPILE_FLAGS "/bigobj")
endif()

if (USE_PCH)
  set_target_properties(ohl_wallet PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(ohl_wallet)
endif(USE_PCH)
