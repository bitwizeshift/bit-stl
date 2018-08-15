set(temp_state ${CMAKE_FIND_APPBUNDLE})
set(CMAKE_FIND_APPBUNDLE "NEVER")

find_program(CMAKE_DOXYGEN_PROGRAM doxygen)

set(CMAKE_FIND_APPBUNDLE ${temp_state})

if( NOT CMAKE_DOXYGEN_PROGRAM )
  message(FATAL_ERROR "'Doxygen' program not found.")
endif()

# Generate Doxyfile
set(root_source_path "${CMAKE_CURRENT_LIST_DIR}")
set(root_build_path "${CMAKE_CURRENT_BINARY_DIR}")
get_filename_component(root_source_path "${root_source_path}" DIRECTORY)
get_filename_component(root_build_path "${root_build_path}" DIRECTORY)

set(README_FILEPATH "${root_source_path}/Readme.md")
set(INCLUDE_FILEPATH "${root_source_path}/include")
set(GENERATED_INCLUDE_FILEPATH "${root_build_path}/include")

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
  @ONLY
)

# Add target for generating doxygen
file(MAKE_DIRECTORY "${BIT_STL_DOXYGEN_OUTPUT_PATH}")
add_custom_target(
  stl_docs
  COMMAND "${CMAKE_DOXYGEN_PROGRAM}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
  WORKING_DIRECTORY "${BIT_STL_DOXYGEN_OUTPUT_PATH}"
  COMMENT "Generating Doxygen documentation for Bit::stl"
  VERBATIM
)
