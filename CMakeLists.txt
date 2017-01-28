cmake_minimum_required(VERSION 3.1)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/add_header_library.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/add_test_executable.cmake")

project("bit::stl")

set(CMAKE_CXX_VERSION 14)

#-----------------------------------------------------------------------------
# bit::stl : Interface
#-----------------------------------------------------------------------------

set(BIT_STL_VERSION_MAJOR 0 CACHE STRING "major version of bit::stl" FORCE)
set(BIT_STL_VERSION_MINOR 1 CACHE STRING "minor version of bit::stl" FORCE)
set(BIT_STL_VERSION "${BIT_STL_VERSION_MAJOR}.${BIT_STL_VERSION_MINOR}" CACHE STRING "version of bit::stl" FORCE)

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

add_header_library(bit_stl ${headers} INCLUDE_DIRECTORIES "include")
add_library("bit::stl" ALIAS bit_stl)
target_compile_options(bit_stl INTERFACE -std=c++14 -DDEBUG)

#-----------------------------------------------------------------------------
# bit::stl : Tests
#-----------------------------------------------------------------------------

if( BIT_BUILD_TESTS )

  set(test_sources
        test/main.test.cpp
        test/bit/stl/array_view.test.cpp
        test/bit/stl/delegate.test.cpp
        test/bit/stl/expected.test.cpp
        test/bit/stl/hashed_string_view.test.cpp
        test/bit/stl/lazy.test.cpp
        test/bit/stl/set_view.test.cpp
        test/bit/stl/span.test.cpp
        test/bit/stl/string_tokenizer.test.cpp
        test/bit/stl/string_view.test.cpp
        test/bit/stl/tribool.test.cpp
        test/bit/stl/type_traits.test.cpp
  )

  add_test_executable(bit_stl_test ${test_sources})
  target_link_libraries(bit_stl_test "bit::stl")

endif()

#-----------------------------------------------------------------------------
# bit::stl : Export
#-----------------------------------------------------------------------------

set(PACKAGE_VERSION_MAJOR "${BIT_STL_VERSION_MAJOR}")
set(PACKAGE_VERSION_MINOR "${BIT_STL_VERSION_MINOR}")
set(PACKAGE_VERSION "${BIT_STL_VERSION}")

configure_file("cmake/package/package-config-version.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config-version.cmake"
               @ONLY)

set(PACKAGE_VERSION_MAJOR)
set(PACKAGE_VERSION_MINOR)
set(PACKAGE_VERSION)

#-----------------------------------------------------------------------------

set(PACKAGE_TARGET "bit_stl")
configure_file("cmake/package/package-config.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config.cmake"
               @ONLY)
set(PACKAGE_TARGET)

set(lib_dir "lib/bit-stl-${BIT_STL_VERSION}")
set(lib_config_dir "${lib_dir}/${CMAKE_BUILD_TYPE}")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config-version.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/bit_stl-config.cmake"
        DESTINATION
               ${lib_dir})

#install(EXPORT bit_stl DESTINATION "${lib_config_dir}")
