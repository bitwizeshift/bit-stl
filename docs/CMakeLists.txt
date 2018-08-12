set(temp_state ${CMAKE_FIND_APPBUNDLE})
set(CMAKE_FIND_APPBUNDLE "NEVER")

find_program(CMAKE_DOXYGEN_PROGRAM doxygen)

set(CMAKE_FIND_APPBUNDLE ${temp_state})

if( NOT CMAKE_DOXYGEN_PROGRAM )
  message(FATAL_ERROR "'Doxygen' program not found.")
endif()

# Add target for generating doxygen
add_custom_target("bit_stl_doxygen" ALL
                  COMMAND "${CMAKE_DOXYGEN_PROGRAM}" "Doxyfile"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                  COMMENT "Generating Doxygen documentation for 'bit::stl'"
                  VERBATIM )
