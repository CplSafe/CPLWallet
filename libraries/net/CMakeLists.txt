file(GLOB HEADERS "include/ohl/net/*.hpp")

set(SOURCES node.cpp
            stcp_socket.cpp
            core_messages.cpp
            peer_database.cpp
            peer_connection.cpp
            upnp.cpp
            message_oriented_connection.cpp
            chain_downloader.cpp
            chain_server.cpp)

add_library( ohl_net ${SOURCES} ${HEADERS} )

target_link_libraries( ohl_net 
  PUBLIC fc ohl_wallet ohl_db ohl_utilities leveldb ohl_api ohl_rpc_stubs upnpc-static)
target_include_directories( ohl_net 
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
# currently depends on client for definitions, remove this
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../client/include"
# Looks like ohl_net and ohl_rpc also have cycle deps
          "${CMAKE_CURRENT_SOURCE_DIR}/../rpc/include"
# later, move upnp include into target_include_directories for upnp
"${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/miniupnp"
)

if (USE_PCH)
  set_target_properties(ohl_net PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(ohl_net)
endif(USE_PCH)
