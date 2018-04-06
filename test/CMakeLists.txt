cmake_minimum_required(VERSION 3.1)

#-----------------------------------------------------------------------------
# Test Options
#-----------------------------------------------------------------------------

option(BIT_STL_COMPILE_ASAN "Compile and run the address sanetizer" off)
option(BIT_STL_COMPILE_UBSAN "Compile and run the undefined behavior sanitizer" off)
option(BIT_STL_COMPILE_TSAN "Compile and run the thread sanitizer" off)
option(BIT_STL_COMPILE_COVERAGE "Compile and run code coverage" off)

#-----------------------------------------------------------------------------
# Unit Tests
#-----------------------------------------------------------------------------

find_package(Catch REQUIRED)

set(sources
      # utilities
      bit/stl/utilities/compressed_pair.test.cpp
      bit/stl/utilities/delegate.test.cpp
      bit/stl/utilities/lazy.test.cpp
      bit/stl/utilities/tribool.test.cpp
      bit/stl/utilities/expected.test.cpp
      bit/stl/utilities/scope_guard.test.cpp

      # containers
      bit/stl/containers/array_view.test.cpp
      bit/stl/containers/hashed_string_view.test.cpp
      bit/stl/containers/set_view.test.cpp
      bit/stl/containers/span.test.cpp
      bit/stl/containers/string_view.test.cpp
      bit/stl/containers/circular_queue.test.cpp
      bit/stl/containers/circular_deque.test.cpp
      bit/stl/containers/circular_buffer.test.cpp

      # memory
      bit/stl/memory/exclusive_ptr.test.cpp

      main.test.cpp
)

add_executable(bit_stl_test ${sources})

target_link_libraries(bit_stl_test PRIVATE "bit::stl" "philsquared::Catch")

#-----------------------------------------------------------------------------

add_test( NAME "bit_stl_test_default"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:bit_stl_test>" )

add_test( NAME "bit_stl_test_all"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:bit_stl_test>" "*" )

if( BIT_STL_COMPILE_TSAN AND BIT_STL_COMPILE_UBSAN OR
    BIT_STL_COMPILE_UBSAN AND BIT_STL_COMPILE_ASAN OR
    BIT_STL_COMPILE_ASAN AND BIT_STL_COMPILE_TSAN )
  message(FATAL_ERROR "TSAN, UBSAN, and ASAN can only be enabled independently")
endif()

#-----------------------------------------------------------------------------
# Address Sanitizer
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_ASAN )

  if( NOT UNIX )
    message(FATAL_ERROR "UBSAN only available posix platforms")
  endif()

  target_link_libraries(bit_stl_test PRIVATE -fsanitize=address
                                             -fsanitize=leak)
  target_compile_options(bit_stl_test PRIVATE -fsanitize=address
                                              -fsanitize=leak
                                              -g
                                              -O1
                                              -fno-omit-frame-pointer)

endif()

#-----------------------------------------------------------------------------
# Undefined Behavior Sanitizer
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_UBSAN )

  if( NOT UNIX )
    message(FATAL_ERROR "UBSAN only available posix platforms")
  endif()

  target_compile_options(bit_stl_test PRIVATE -fsanitize=undefined)
  target_link_libraries(bit_stl_test PRIVATE -fsanitize=undefined)

endif()

#-----------------------------------------------------------------------------
# Thread Sanitizer
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_TSAN )

  if( NOT UNIX )
    message(FATAL_ERROR "UBSAN only available posix platforms")
  endif()

  target_compile_options(bit_stl_test PRIVATE -fsanitize=thread)
  target_link_libraries(bit_stl_test PRIVATE -fsanitize=thread)

endif()

#-----------------------------------------------------------------------------
# Code Coverage
#-----------------------------------------------------------------------------

if( BIT_STL_COMPILE_COVERAGE )

  if( NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND
      NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    message(FATAL_ERROR "Coverage only available for GNUC compilers")
  endif()

  target_link_libraries(bit_stl_test PRIVATE --coverage)
  target_compile_options(bit_stl_test PRIVATE
    -g
    -O0
    -fprofile-arcs
    -ftest-coverage
  )

endif()
