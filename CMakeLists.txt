cmake_minimum_required(VERSION 2.6)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/add_header_library.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/add_test_executable.cmake")

project("bit::stl")

set(CMAKE_CXX_VERSION 14)

#-----------------------------------------------------------------------------
# bit::stl
#-----------------------------------------------------------------------------

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
target_compile_options(bit_stl INTERFACE -std=c++14 -DDEBUG)

add_library("bit::stl" ALIAS bit_stl)

if( BIT_BUILD_TESTS )

  set(test_sources
    tests/main.test.cpp
    tests/bit/stl/array_view.test.cpp
    tests/bit/stl/delegate.test.cpp
    tests/bit/stl/expected.test.cpp
    tests/bit/stl/hashed_string_view.test.cpp
    tests/bit/stl/lazy.test.cpp
    tests/bit/stl/set_view.test.cpp
    tests/bit/stl/span.test.cpp
    tests/bit/stl/string_tokenizer.test.cpp
    tests/bit/stl/string_view.test.cpp
    tests/bit/stl/tribool.test.cpp
    tests/bit/stl/type_traits.test.cpp
  )

  add_test_executable(bit_stl_test ${test_sources})
  target_link_libraries(bit_stl_test "bit::stl")

endif()
