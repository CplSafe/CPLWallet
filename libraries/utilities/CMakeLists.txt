list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libraries/fc/GitVersionGen" )
include( GetGitRevisionDescription )
get_git_head_revision(GIT_REFSPEC OHLSHARES_GIT_REVISION_SHA)
get_git_unix_timestamp(OHLSHARES_GIT_REVISION_UNIX_TIMESTAMP)
git_describe(OHLSHARES_GIT_REVISION_DESCRIPTION --tags)
if(NOT OHLSHARES_GIT_REVISION_DESCRIPTION)
    set(OHLSHARES_GIT_REVISION_DESCRIPTION "unknown")
endif(NOT OHLSHARES_GIT_REVISION_DESCRIPTION)

file(GLOB headers "include/ohl/utilities/*.hpp")

set(sources key_conversion.cpp string_escape.cpp
            words.cpp
            ${headers})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/git_revision.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp" @ONLY)
list(APPEND sources "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp")

add_library( ohl_utilities
             ${sources}
             ${HEADERS} )
target_link_libraries( ohl_utilities fc )
target_include_directories( ohl_utilities
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
if (USE_PCH)
  set_target_properties(ohl_utilities PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(ohl_utilities)
endif(USE_PCH)
