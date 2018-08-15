cmake_minimum_required(VERSION 3.1)

include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

find_package(BitStl 2.0.0 REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(source_files
  src/main.cpp
)

add_executable(BitStl.TestPackage ${source_files})
target_link_libraries(BitStl.TestPackage PRIVATE Bit::stl)
