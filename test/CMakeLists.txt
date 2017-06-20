cmake_minimum_required(VERSION 3.1)

find_package(Catch REQUIRED)

set(sources
      main.test.cpp
      bit/stl/array_view.test.cpp
      bit/stl/delegate.test.cpp
      bit/stl/expected.test.cpp
      bit/stl/hashed_string_view.test.cpp
      bit/stl/lazy.test.cpp
      bit/stl/set_view.test.cpp
      bit/stl/span.test.cpp
      bit/stl/string_tokenizer.test.cpp
      bit/stl/string_view.test.cpp
      bit/stl/tribool.test.cpp
      bit/stl/type_traits.test.cpp
      bit/stl/utility.compressed_pair.test.cpp
)

add_executable(stl_test ${sources})

target_link_libraries(stl_test PRIVATE "bit::stl" "philsquared::Catch")

#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------

add_test( NAME "stl_test_default"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:stl_test>" )

#-----------------------------------------------------------------------------

add_test( NAME "stl_test_all"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:stl_test>" "*" )
