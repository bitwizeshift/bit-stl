cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(AddIndependenceCheck)
include(GitBuildInformation)
include(MakeVersionHeader)

project("bit::stl")

if( CMAKE_BUILD_TYPE STREQUAL "" )
  message(STATUS "CMAKE_BUILD_TYPE not set; defaulting to 'Debug'")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

#-----------------------------------------------------------------------------
# Options
#-----------------------------------------------------------------------------

option(BIT_STL_COMPILE_INDEPENDENCE_TESTS "Include each header independently in a .cpp file to determine header independence" on)
option(BIT_STL_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" on)

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

git_build_information( MINOR_VARIABLE BIT_STL_VERSION_MINOR
                       PATCH_VARIABLE BIT_STL_VERSION_PATCH
                       BUILD_VARIABLE BIT_STL_BUILD_NUMBER
                       BRANCH_VARIABLE BIT_STL_BRANCH
                       HASH 830231538303f1b6e166a2ee6761fe8c23b4eb69
)

set(BIT_STL_VERSION_MAJOR 0 CACHE STRING "major version of bit::stl" FORCE)
set(BIT_STL_VERSION_MINOR ${BIT_STL_VERSION_MINOR} CACHE STRING "minor version of bit::stl" FORCE)
set(BIT_STL_VERSION_PATCH ${BIT_STL_VERSION_PATCH} CACHE STRING "patch version of bit::stl" FORCE)
set(BIT_STL_VERSION "${BIT_STL_VERSION_MAJOR}.${BIT_STL_VERSION_MINOR}.${BIT_STL_VERSION_PATCH}" CACHE STRING "version of bit::stl" FORCE)
set(BIT_STL_BUILD_NUMBER "${BIT_STL_BUILD_NUMBER}" CACHE STRING "build number of bit::stl" FORCE)

message(STATUS "bit::stl ${BIT_STL_VERSION} (${BIT_STL_BRANCH} ${BIT_STL_BUILD_NUMBER})")

#-----------------------------------------------------------------------------
# bit::stl
#-----------------------------------------------------------------------------

set(CMAKE_CXX_VERSION 14)

make_version_header("${CMAKE_CURRENT_BINARY_DIR}/include/bit/stl/version.hpp"
  MAJOR ${BIT_STL_VERSION_MAJOR}
  MINOR ${BIT_STL_VERSION_MINOR}
  PATCH ${BIT_STL_VERSION_PATCH}
  BUILD ${BIT_STL_BUILD_NUMBER}
  PREFIX BIT_STL
  SUFFIX "a"
  TAG ${BIT_STL_BRANCH}
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

set(headers
      "include/bit/stl/array_view.hpp"
      "include/bit/stl/assert.hpp"
      "include/bit/stl/casts.hpp"
      "include/bit/stl/checked.hpp"
      "include/bit/stl/data_watcher.hpp"
      "include/bit/stl/delegate.hpp"
      "include/bit/stl/expected.hpp"
      "include/bit/stl/functional.hpp"
      "include/bit/stl/hashed_string_view.hpp"
      "include/bit/stl/iterator.hpp"
      "include/bit/stl/lazy.hpp"
      "include/bit/stl/map_view.hpp"
      "include/bit/stl/memory.hpp"
      "include/bit/stl/numeric.hpp"
      "include/bit/stl/optional.hpp"
      "include/bit/stl/pointer_iterator.hpp"
      "include/bit/stl/safe_enum.hpp"
      "include/bit/stl/set_view.hpp"
      "include/bit/stl/source_location.hpp"
      "include/bit/stl/span.hpp"
      "include/bit/stl/stddef.hpp"
      "include/bit/stl/string_span.hpp"
      "include/bit/stl/string_tokenizer.hpp"
      "include/bit/stl/string_view.hpp"
      "include/bit/stl/tribool.hpp"
      "include/bit/stl/tuple.hpp"
      "include/bit/stl/type_traits.hpp"
      "include/bit/stl/utility.hpp"
)

add_library(bit_stl INTERFACE)
target_include_directories(bit_stl INTERFACE include)
target_compile_options(bit_stl INTERFACE -std=c++14 $<$<CONFIG:DEBUG>:-DDEBUG>)

#-----------------------------------------------------------------------------
# bit::stl : Independence Tests
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_INDEPENDENCE_TESTS )

  add_independence_check(bit_stl_independence ${headers})
  target_compile_options(bit_stl_independence PRIVATE -std=c++14 $<$<CONFIG:DEBUG>:-DDEBUG>)

endif()

#-----------------------------------------------------------------------------
# bit::stl : Unit Tests
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_UNIT_TESTS )

  add_subdirectory(test)

endif()

#-----------------------------------------------------------------------------
# bit::stl : Export
#-----------------------------------------------------------------------------

set(PACKAGE_VERSION_MAJOR "${BIT_STL_VERSION_MAJOR}")
set(PACKAGE_VERSION_MINOR "${BIT_STL_VERSION_MINOR}")
set(PACKAGE_VERSION       "${BIT_STL_VERSION}")

configure_file("cmake/package/package-config-version.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config-version.cmake"
               @ONLY)

set(PACKAGE_VERSION_MAJOR)
set(PACKAGE_VERSION_MINOR)
set(PACKAGE_VERSION)

#-----------------------------------------------------------------------------

# set(PACKAGE_TARGET "bit_stl")
# set(PACKAGE_TARGETS_FILE "BitStlTargets")
# configure_file("cmake/package/package-config.cmake.in"
#                "${CMAKE_CURRENT_BINARY_DIR}/BitStlConfig.cmake"
#                @ONLY)
# set(PACKAGE_TARGET)

# set(lib_dir "lib/bit-stl-${BIT_STL_VERSION}")
# set(lib_config_dir "${lib_dir}/${CMAKE_BUILD_TYPE}")

# install( TARGETS "bit_stl"
#          EXPORT "BitStlTargets"
#          LIBRARY DESTINATION "lib"
#          ARCHIVE DESTINATION "lib"
#          RUNTIME DESTINATION "bin"
#          INCLUDES DESTINATION "include" )

# install( EXPORT "BitStlTargets"
#          DESTINATION "${cmake}"
#          FILE "BitStlTargets.cmake" )

# install( FILES "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config-version.cmake"
#                "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config.cmake"
#          DESTINATION
#                 ${lib_dir} )

#install(EXPORT bit_stl DESTINATION "${lib_config_dir}")
