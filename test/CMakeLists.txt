cmake_minimum_required(VERSION 3.1)

include(AddTestExecutable)

find_package(Catch)

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
)

add_test_executable(bit_stl_test ${sources})

target_link_libraries(bit_stl_test PRIVATE bit_stl "philsquared::Catch")
