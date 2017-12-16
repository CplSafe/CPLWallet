file(GLOB HEADERS "include/ohl/keyhotee/*.hpp")

add_library( ohl_keyhotee
             import_keyhotee_id.cpp
             ${HEADERS}
           )

target_link_libraries( ohl_keyhotee fc ohl_db ohl_blockchain leveldb bitcoin)
target_include_directories( ohl_keyhotee 
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
