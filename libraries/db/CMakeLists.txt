file(GLOB HEADERS "include/ohl/db/*.hpp")
add_library( ohl_db upgrade_leveldb.cpp ${HEADERS} )
target_link_libraries( ohl_db fc leveldb )
target_include_directories( ohl_db PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
