file(GLOB HEADERS "include/ohl/client/*.hpp")
file(GLOB APIS "*_api.cpp")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/ohl/client/build_info.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/include/ohl/client/build_info.hpp" @ONLY)

add_definitions( -DOHL_GLOBAL_API_LOG=1 )

add_library( ohl_client
             client.cpp
             messages.cpp
             notifier.cpp
             api_logger.cpp
             ${APIS}
             ${HEADERS}
             "${CMAKE_CURRENT_BINARY_DIR}/include/ohl/client/build_info.hpp" )

if(MSVC)
  set_source_files_properties(client.cpp PROPERTIES COMPILE_FLAGS "/bigobj")
endif(MSVC)

target_link_libraries( ohl_client
                       PRIVATE ohl_db ohl_blockchain bitcoin fc leveldb
                       PUBLIC ohl_api ohl_net ohl_wallet ohl_cli ohl_rpc ohl_rpc_stubs )
target_include_directories( ohl_client
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
                            PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include" )
