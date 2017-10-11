cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(AddIndependenceCheck)
include(MakeVersionHeader)
include(EnableCCache)

#-----------------------------------------------------------------------------
# Project Setup
#-----------------------------------------------------------------------------

# enable cacche to speed up compilations
enable_ccache()

option(BIT_STL_COMPILE_INDEPENDENCE_TESTS "Include each header independently in a .cpp file to determine header independence" on)
option(BIT_STL_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" on)

project("BitStl")

if( CMAKE_BUILD_TYPE STREQUAL "" )
  message(STATUS "CMAKE_BUILD_TYPE not set; defaulting to 'Debug'")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

set(BIT_STL_VERSION_MAJOR 1 CACHE STRING "major version of bit::stl" FORCE)
set(BIT_STL_VERSION_MINOR 1 CACHE STRING "minor version of bit::stl" FORCE)
set(BIT_STL_VERSION_PATCH 166 CACHE STRING "patch version of bit::stl" FORCE)

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
      include/bit/stl/array.hpp
      include/bit/stl/array_view.hpp
      include/bit/stl/assert.hpp
      include/bit/stl/casts.hpp
      include/bit/stl/checked.hpp
      include/bit/stl/circular_array.hpp
      include/bit/stl/circular_buffer.hpp
      include/bit/stl/circular_deque.hpp
      include/bit/stl/circular_queue.hpp
      include/bit/stl/data_watcher.hpp
      include/bit/stl/delegate.hpp
      include/bit/stl/enum.hpp
      include/bit/stl/expected.hpp
      include/bit/stl/functional.hpp
      include/bit/stl/hashed_string.hpp
      include/bit/stl/hashed_string_view.hpp
      include/bit/stl/iterator.hpp
      include/bit/stl/lazy.hpp
      include/bit/stl/map_view.hpp
      include/bit/stl/memory.hpp
      include/bit/stl/numeric.hpp
      include/bit/stl/optional.hpp
      include/bit/stl/pointer_wrapper.hpp
      include/bit/stl/range.hpp
      include/bit/stl/set_view.hpp
      include/bit/stl/source_location.hpp
      include/bit/stl/span.hpp
      include/bit/stl/stddef.hpp
      include/bit/stl/string.hpp
      include/bit/stl/string_span.hpp
      include/bit/stl/string_tokenizer.hpp
      include/bit/stl/string_view.hpp
      include/bit/stl/tribool.hpp
      include/bit/stl/tuple.hpp
      include/bit/stl/type_traits.hpp
      include/bit/stl/utility.hpp
      include/bit/stl/uuid.hpp
)

add_library(stl INTERFACE)
add_library(bit::stl ALIAS stl)

target_include_directories(stl INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                                         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)
target_compile_definitions(stl INTERFACE
  $<$<CONFIG:DEBUG>:DEBUG>
  $<$<CONFIG:RELEASE>:DEBUG RELEASE>
)

#-----------------------------------------------------------------------------
# bit::stl : Independence Tests
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_INDEPENDENCE_TESTS )

  add_independence_check(stl_independence ${headers})

  target_compile_definitions(stl_independence PRIVATE
    $<$<CONFIG:DEBUG>:DEBUG>
    $<$<CONFIG:RELEASE>:DEBUG RELEASE>
  )

  if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(stl_independence PRIVATE -Wall -pedantic)
  elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options(stl_independence PRIVATE -Wall -pedantic)
  elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    # TODO: Determine MSVC necessary compiler flags
  endif()

  add_library(bit::stl::independence ALIAS stl_independence)

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

include(ExportLibrary)

if( EXISTS "$ENV{BIT_HOME}" )
  set(CMAKE_INSTALL_PREFIX "$ENV{BIT_HOME}")
endif()

export_library( TARGETS stl
                PACKAGE Stl
                VERSION ${BIT_STL_VERSION}
                MAJOR_VERSION ${BIT_STL_VERSION_MAJOR}
                MINOR_VERSION ${BIT_STL_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
