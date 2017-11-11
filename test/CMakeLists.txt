cmake_minimum_required(VERSION 3.1)

find_package(Catch REQUIRED)

set(sources
      # utilities
      bit/stl/utilities/compressed_pair.test.cpp
      bit/stl/utilities/delegate.test.cpp
      bit/stl/utilities/lazy.test.cpp
      bit/stl/utilities/tribool.test.cpp

      # containers
      bit/stl/containers/array_view.test.cpp
      bit/stl/containers/hashed_string_view.test.cpp
      bit/stl/containers/set_view.test.cpp
      bit/stl/containers/span.test.cpp
      bit/stl/containers/string_view.test.cpp
      bit/stl/containers/circular_queue.test.cpp

      main.test.cpp
)

add_executable(bit_stl_test ${sources})

target_link_libraries(bit_stl_test PRIVATE "bit::stl" "philsquared::Catch")

#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------

add_test( NAME "bit_stl_test_default"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:bit_stl_test>" )

#-----------------------------------------------------------------------------

add_test( NAME "bit_stl_test_all"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:bit_stl_test>" "*" )
