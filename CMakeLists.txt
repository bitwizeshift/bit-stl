cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(AddHeaderSelfContainmentTest)
include(MakeVersionHeader)
include(EnableCCache)

#-----------------------------------------------------------------------------
# Project Setup
#-----------------------------------------------------------------------------

# enable cacche to speed up compilations
enable_ccache()

option(BIT_STL_COMPILE_HEADER_SELF_CONTAINMENT_TESTS "Include each header independently in a .cpp file to determine header self-containment" off)
option(BIT_STL_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" off)
option(BIT_STL_GENERATE_DOCUMENTATION "Generates doxygen documentation" off)

project("BitStl")

if( CMAKE_BUILD_TYPE STREQUAL "" )
  message(STATUS "CMAKE_BUILD_TYPE not set; defaulting to 'Debug'")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

set(BIT_STL_VERSION_MAJOR 2 CACHE STRING "major version of bit::stl" FORCE)
set(BIT_STL_VERSION_MINOR 0 CACHE STRING "minor version of bit::stl" FORCE)
set(BIT_STL_VERSION_PATCH 0 CACHE STRING "patch version of bit::stl" FORCE)

set(BIT_STL_VERSION "${BIT_STL_VERSION_MAJOR}.${BIT_STL_VERSION_MINOR}.${BIT_STL_VERSION_PATCH}" CACHE STRING "version of bit::stl" FORCE)

message(STATUS "bit::stl ${BIT_STL_VERSION}")

#-----------------------------------------------------------------------------
# bit::stl
#-----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

make_version_header("${CMAKE_CURRENT_BINARY_DIR}/include/bit/stl/version.hpp"
  MAJOR ${BIT_STL_VERSION_MAJOR}
  MINOR ${BIT_STL_VERSION_MINOR}
  PATCH ${BIT_STL_VERSION_PATCH}
  PREFIX BIT_STL
  SUFFIX "a"
)

set(headers
  # utilities
  include/bit/stl/utilities/assert.hpp
  include/bit/stl/utilities/casts.hpp
  include/bit/stl/utilities/compressed_pair.hpp
  include/bit/stl/utilities/compressed_tuple.hpp
  include/bit/stl/utilities/checked.hpp
  include/bit/stl/utilities/delegate.hpp
  include/bit/stl/utilities/enum.hpp
  include/bit/stl/utilities/expected.hpp
  include/bit/stl/utilities/functional.hpp
  include/bit/stl/utilities/lazy.hpp
  include/bit/stl/utilities/optional.hpp
  include/bit/stl/utilities/pointer_wrapper.hpp
  include/bit/stl/utilities/source_location.hpp
  include/bit/stl/utilities/stddef.hpp
  include/bit/stl/utilities/tribool.hpp
  include/bit/stl/utilities/tuple.hpp
  include/bit/stl/utilities/type_traits.hpp
  include/bit/stl/utilities/utility.hpp
  include/bit/stl/utilities/uuid.hpp

  # containers
  include/bit/stl/containers/array.hpp
  include/bit/stl/containers/array_view.hpp
  include/bit/stl/containers/circular_array.hpp
  include/bit/stl/containers/circular_buffer.hpp
  include/bit/stl/containers/circular_deque.hpp
  include/bit/stl/containers/circular_queue.hpp
  include/bit/stl/containers/hashed_string.hpp
  include/bit/stl/containers/hashed_string_view.hpp
  include/bit/stl/containers/map_view.hpp
  include/bit/stl/containers/set_view.hpp
  include/bit/stl/containers/span.hpp
  include/bit/stl/containers/string.hpp
  include/bit/stl/containers/string_span.hpp
  include/bit/stl/containers/string_view.hpp

  # iterators
  include/bit/stl/iterators/tagged_iterator.hpp
  include/bit/stl/iterators/tuple_element_iterator.hpp
  include/bit/stl/iterators/zip_iterator.hpp

  # ranges
  include/bit/stl/ranges/move_range.hpp
  include/bit/stl/ranges/range.hpp
  include/bit/stl/ranges/reverse_range.hpp
  include/bit/stl/ranges/tuple_element_range.hpp
  include/bit/stl/ranges/zip_range.hpp

  # memory
  include/bit/stl/memory/memory.hpp

  # numeric
  include/bit/stl/numeric/numeric.hpp

  # not sure where this goes yet
  include/bit/stl/string_tokenizer.hpp
)

add_library(bit_stl INTERFACE)
add_library(bit::stl ALIAS bit_stl)

target_include_directories(bit_stl INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)
target_compile_definitions(bit_stl INTERFACE
  $<$<CONFIG:DEBUG>:DEBUG>
  $<$<CONFIG:RELEASE>:DEBUG RELEASE>
)

#-----------------------------------------------------------------------------
# bit::stl : Independence Tests
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_HEADER_SELF_CONTAINMENT_TESTS )

  # Add containment test and alias as 'bit::stl::header_self_containment_test'
  add_header_self_containment_test(bit_stl_header_self_containment_test ${headers})
  add_library(bit::stl::header_self_containment_test ALIAS bit_stl_header_self_containment_test)

  target_compile_definitions(bit_stl_header_self_containment_test PRIVATE
    $<$<CONFIG:DEBUG>:DEBUG>
    $<$<CONFIG:RELEASE>:NDEBUG RELEASE>
  )

  if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(bit_stl_header_self_containment_test PRIVATE -Wall -pedantic)
  elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options(bit_stl_header_self_containment_test PRIVATE -Wall -pedantic)
  elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    # TODO: Determine MSVC necessary compiler flags
  endif()

endif()

#-----------------------------------------------------------------------------
# bit::stl : Unit Tests
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_UNIT_TESTS )
  add_subdirectory(test)
endif()

#-----------------------------------------------------------------------------
# bit::stl : Documentation
#-----------------------------------------------------------------------------

if( BIT_STL_GENERATE_DOCUMENTATION )
  add_subdirectory(doc)
endif()

#-----------------------------------------------------------------------------
# bit::stl : Export
#-----------------------------------------------------------------------------

include(ExportLibrary)

if( EXISTS "$ENV{BIT_HOME}" )
  set(CMAKE_INSTALL_PREFIX "$ENV{BIT_HOME}")
endif()

export_library( TARGETS bit_stl
                PACKAGE Stl
                VERSION ${BIT_STL_VERSION}
                MAJOR_VERSION ${BIT_STL_VERSION_MAJOR}
                MINOR_VERSION ${BIT_STL_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
