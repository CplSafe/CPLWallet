list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
find_package(Curses)
find_package(Readline)

file(GLOB HEADERS "include/ohl/cli/*.hpp")

add_library( ohl_cli 
             cli.cpp
             pretty.cpp
             print_result.cpp
             ${HEADERS})

if (READLINE_FOUND)
  target_compile_definitions (ohl_cli PRIVATE HAVE_READLINE)
  set(readline_libraries ${Readline_LIBRARY})
  if (CURSES_FOUND)
    list(APPEND readline_libraries ${CURSES_LIBRARY})
  endif()
  set(readline_includes ${Readline_INCLUDE_DIR})
endif()
target_link_libraries( ohl_cli 
                       PUBLIC ohl_client fc ohl_db ohl_rpc ohl_wallet ohl_blockchain leveldb ${readline_libraries})
target_include_directories( ohl_cli 
                            PRIVATE "${readline_includes}"
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
if(WIN32)
  target_compile_definitions( ohl_cli PRIVATE _CRT_NONSTDC_NO_DEPRECATE )
endif(WIN32)
