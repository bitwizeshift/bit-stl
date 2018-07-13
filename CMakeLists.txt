cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

#-----------------------------------------------------------------------------
# Project Setup
#-----------------------------------------------------------------------------

# default to debug when building CMake
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

include(EnableCCache)

# enable cacche to speed up compilations
enable_ccache()

include(CMakeDependentOption)

option(BIT_STL_COMPILE_HEADER_SELF_CONTAINMENT_TESTS "Include each header independently in a .cpp file to determine header self-containment" off)
option(BIT_STL_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" off)
option(BIT_STL_GENERATE_DOCUMENTATION "Generates doxygen documentation" off)
option(BIT_STL_VERBOSE_CONFIGURE "Verbosely configures this library project" off)

project("BitStl" LANGUAGES CXX)

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

set(BIT_STL_VERSION_MAJOR 2 CACHE STRING "major version of bit::stl" FORCE)
set(BIT_STL_VERSION_MINOR 0 CACHE STRING "minor version of bit::stl" FORCE)
set(BIT_STL_VERSION_PATCH 0 CACHE STRING "patch version of bit::stl" FORCE)

set(BIT_STL_VERSION "${BIT_STL_VERSION_MAJOR}.${BIT_STL_VERSION_MINOR}.${BIT_STL_VERSION_PATCH}" CACHE STRING "version of bit::stl" FORCE)

if( BIT_STL_VERBOSE_CONFIGURE )
  message(STATUS "bit::stl ${BIT_STL_VERSION}")
endif()

#-----------------------------------------------------------------------------
# bit::stl
#-----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

include(MakeVersionHeader)

make_version_header("${CMAKE_CURRENT_BINARY_DIR}/include/bit/stl/version.hpp"
  MAJOR ${BIT_STL_VERSION_MAJOR}
  MINOR ${BIT_STL_VERSION_MINOR}
  PATCH ${BIT_STL_VERSION_PATCH}
  PREFIX BIT_STL
  SUFFIX "a"
)

set(headers

  # Type Traits
  include/bit/stl/traits/composition/bool_constant.hpp
  include/bit/stl/traits/composition/conjunction.hpp
  include/bit/stl/traits/composition/detected.hpp
  include/bit/stl/traits/composition/disjunction.hpp
  include/bit/stl/traits/composition/empty.hpp
  include/bit/stl/traits/composition/identity.hpp
  include/bit/stl/traits/composition/integral_constant.hpp
  include/bit/stl/traits/composition/negation.hpp
  include/bit/stl/traits/composition/nonesuch.hpp
  include/bit/stl/traits/composition/sfinae.hpp
  include/bit/stl/traits/composition/size_constant.hpp
  include/bit/stl/traits/composition/type_list.hpp
  include/bit/stl/traits/composition/void_t.hpp
  include/bit/stl/traits/properties/is_assignable.hpp
  include/bit/stl/traits/properties/is_const_member_function_pointer.hpp
  include/bit/stl/traits/properties/is_copy_assignable.hpp
  include/bit/stl/traits/properties/is_copy_constructible.hpp
  include/bit/stl/traits/properties/is_cv_member_function_pointer.hpp
  include/bit/stl/traits/properties/is_default_constructible.hpp
  include/bit/stl/traits/properties/is_destructible.hpp
  include/bit/stl/traits/properties/is_explicitly_constructible.hpp
  include/bit/stl/traits/properties/is_explicitly_convertible.hpp
  include/bit/stl/traits/properties/is_implicitly_constructible.hpp
  include/bit/stl/traits/properties/is_implicitly_convertible.hpp
  include/bit/stl/traits/properties/is_member_function_pointer.hpp
  include/bit/stl/traits/properties/is_member_object_pointer.hpp
  include/bit/stl/traits/properties/is_member_pointer.hpp
  include/bit/stl/traits/properties/is_move_assignable.hpp
  include/bit/stl/traits/properties/is_move_constructible.hpp
  include/bit/stl/traits/properties/is_nothrow_assignable.hpp
  include/bit/stl/traits/properties/is_nothrow_copy_assignable.hpp
  include/bit/stl/traits/properties/is_nothrow_copy_constructible.hpp
  include/bit/stl/traits/properties/is_nothrow_default_constructible.hpp
  include/bit/stl/traits/properties/is_nothrow_destructible.hpp
  include/bit/stl/traits/properties/is_nothrow_move_assignable.hpp
  include/bit/stl/traits/properties/is_nothrow_move_constructible.hpp
  include/bit/stl/traits/properties/is_trivially_copy_assignable.hpp
  include/bit/stl/traits/properties/is_trivially_copy_constructible.hpp
  include/bit/stl/traits/properties/is_trivially_default_constructible.hpp
  include/bit/stl/traits/properties/is_trivially_move_assignable.hpp
  include/bit/stl/traits/properties/is_trivially_move_constructible.hpp
  include/bit/stl/traits/properties/is_trivially_destructible.hpp
  include/bit/stl/traits/properties/is_volatile_member_function_pointer.hpp
  include/bit/stl/traits/relationships/arity.hpp
  include/bit/stl/traits/relationships/function_argument.hpp
  include/bit/stl/traits/relationships/index_of_type.hpp
  include/bit/stl/traits/relationships/is_base_of_all.hpp
  include/bit/stl/traits/relationships/is_base_of_any.hpp
  include/bit/stl/traits/relationships/is_derived_from_all.hpp
  include/bit/stl/traits/relationships/is_derived_from_any.hpp
  include/bit/stl/traits/relationships/is_different.hpp
  include/bit/stl/traits/relationships/is_one_of.hpp
  include/bit/stl/traits/relationships/is_same.hpp
  include/bit/stl/traits/relationships/is_same_constness.hpp
  include/bit/stl/traits/relationships/is_same_cv.hpp
  include/bit/stl/traits/relationships/is_same_decay.hpp
  include/bit/stl/traits/relationships/is_same_sign.hpp
  include/bit/stl/traits/relationships/is_same_volatility.hpp
  include/bit/stl/traits/relationships/nth_type.hpp
  include/bit/stl/traits/relationships/resolves_overload.hpp
  include/bit/stl/traits/relationships/pointer_rank.hpp
  include/bit/stl/traits/transformations/base_type.hpp
  include/bit/stl/traits/transformations/function_signature.hpp
  include/bit/stl/traits/transformations/match_cv_qualifiers.hpp
  include/bit/stl/traits/transformations/match_ref_qualifiers.hpp
  include/bit/stl/traits/transformations/match_sign_qualifiers.hpp
  include/bit/stl/traits/transformations/normalize_char.hpp
  include/bit/stl/traits/transformations/remove_pointers.hpp

  # Functional
  include/bit/stl/functional/arithmetic/divides.hpp
  include/bit/stl/functional/arithmetic/minus.hpp
  include/bit/stl/functional/arithmetic/modulus.hpp
  include/bit/stl/functional/arithmetic/multiplies.hpp
  include/bit/stl/functional/arithmetic/negate.hpp
  include/bit/stl/functional/arithmetic/plus.hpp
  include/bit/stl/functional/bitwise/bit_and.hpp
  include/bit/stl/functional/bitwise/bit_not.hpp
  include/bit/stl/functional/bitwise/bit_or.hpp
  include/bit/stl/functional/bitwise/bit_xor.hpp
  include/bit/stl/functional/comparison/equal_to.hpp
  include/bit/stl/functional/comparison/equivalent_to.hpp
  include/bit/stl/functional/comparison/greater.hpp
  include/bit/stl/functional/comparison/greater_equal.hpp
  include/bit/stl/functional/comparison/less.hpp
  include/bit/stl/functional/comparison/less_equal.hpp
  include/bit/stl/functional/comparison/not_equal_to.hpp
  include/bit/stl/functional/extraction/use_first.hpp
  include/bit/stl/functional/extraction/use_nth_element.hpp
  include/bit/stl/functional/extraction/use_second.hpp
  include/bit/stl/functional/extraction/use_self.hpp
  include/bit/stl/functional/logical/logical_and.hpp
  include/bit/stl/functional/logical/logical_not.hpp
  include/bit/stl/functional/logical/logical_or.hpp

  # Concepts
  include/bit/stl/concepts/AssociativeContainer.hpp
  include/bit/stl/concepts/BidirectionalIterator.hpp
  include/bit/stl/concepts/Container.hpp
  include/bit/stl/concepts/ContiguousContainer.hpp
  include/bit/stl/concepts/Destructible.hpp
  include/bit/stl/concepts/EqualityComparable.hpp
  include/bit/stl/concepts/ForwardIterator.hpp
  include/bit/stl/concepts/InputIterator.hpp
  include/bit/stl/concepts/Iterator.hpp
  include/bit/stl/concepts/NullablePointer.hpp
  include/bit/stl/concepts/RandomAccessIterator.hpp
  include/bit/stl/concepts/Range.hpp
  include/bit/stl/concepts/ReverseRange.hpp
  include/bit/stl/concepts/ReversibleContainer.hpp
  include/bit/stl/concepts/SequenceContainer.hpp

  # utilities
  include/bit/stl/utilities/aligned_storage.hpp
  include/bit/stl/utilities/assert.hpp
  include/bit/stl/utilities/byte.hpp
  include/bit/stl/utilities/casts.hpp
  include/bit/stl/utilities/compressed_pair.hpp
  include/bit/stl/utilities/compressed_tuple.hpp
  include/bit/stl/utilities/compiler_traits.hpp
  include/bit/stl/utilities/delegate.hpp
  include/bit/stl/utilities/dynamic_index_constant.hpp
  include/bit/stl/utilities/dynamic_size_constant.hpp
  include/bit/stl/utilities/enum.hpp
  include/bit/stl/utilities/expected.hpp
  include/bit/stl/utilities/hash.hpp
  include/bit/stl/utilities/in_place.hpp
  include/bit/stl/utilities/integral_type.hpp
  include/bit/stl/utilities/invoke.hpp
  include/bit/stl/utilities/lazy.hpp
  include/bit/stl/utilities/macros.hpp
  include/bit/stl/utilities/monostate.hpp
  include/bit/stl/utilities/optional.hpp
  include/bit/stl/utilities/pointer_wrapper.hpp
  include/bit/stl/utilities/propagate_const.hpp
  include/bit/stl/utilities/scope_guard.hpp
  include/bit/stl/utilities/source_location.hpp
  include/bit/stl/utilities/tribool.hpp
  include/bit/stl/utilities/tuple.hpp
  include/bit/stl/utilities/tuple_utilities.hpp
  include/bit/stl/utilities/types.hpp
  include/bit/stl/utilities/uninitialized_storage.hpp
  include/bit/stl/utilities/utility.hpp
  include/bit/stl/utilities/uuid.hpp
  include/bit/stl/utilities/variant.hpp

  # numeric
  include/bit/stl/numeric/numeric.hpp

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
  include/bit/stl/memory/allocator_deleter.hpp
  include/bit/stl/memory/exclusive_ptr.hpp
  include/bit/stl/memory/clone_ptr.hpp
  include/bit/stl/memory/fat_ptr.hpp
  include/bit/stl/memory/memory.hpp
  include/bit/stl/memory/observer_ptr.hpp
  include/bit/stl/memory/offset_ptr.hpp
  include/bit/stl/memory/owner.hpp
  include/bit/stl/memory/scoped_ptr.hpp
)

set(inline_headers
  # utilities
  include/bit/stl/utilities/detail/assert.inl
  include/bit/stl/utilities/detail/casts.inl
  include/bit/stl/utilities/detail/compressed_pair.inl
  include/bit/stl/utilities/detail/compressed_tuple.inl
  include/bit/stl/utilities/detail/delegate.inl
  include/bit/stl/utilities/detail/dynamic_index_constant.inl
  include/bit/stl/utilities/detail/dynamic_size_constant.inl
  include/bit/stl/utilities/detail/enum.inl
  include/bit/stl/utilities/detail/expected.inl
  include/bit/stl/utilities/detail/hash.inl
  include/bit/stl/utilities/detail/invoke.inl
  include/bit/stl/utilities/detail/integral_type.inl
  include/bit/stl/utilities/detail/lazy.inl
  include/bit/stl/utilities/detail/monostate.inl
  include/bit/stl/utilities/detail/optional.inl
  include/bit/stl/utilities/detail/pointer_wrapper.inl
  include/bit/stl/utilities/detail/propagate_const.inl
  include/bit/stl/utilities/detail/scope_guard.inl
  include/bit/stl/utilities/detail/source_location.inl
  include/bit/stl/utilities/detail/tribool.inl
  include/bit/stl/utilities/detail/tuple_utilities.inl
  include/bit/stl/utilities/detail/uninitialized_storage.inl
  include/bit/stl/utilities/detail/utility.inl
  include/bit/stl/utilities/detail/uuid.inl

  # containers
  include/bit/stl/containers/detail/array.inl
  include/bit/stl/containers/detail/array_view.inl
  include/bit/stl/containers/detail/circular_array.inl
  include/bit/stl/containers/detail/circular_buffer.inl
  include/bit/stl/containers/detail/circular_deque.inl
  include/bit/stl/containers/detail/circular_queue.inl
  include/bit/stl/containers/detail/hashed_string.inl
  include/bit/stl/containers/detail/hashed_string_view.inl
  include/bit/stl/containers/detail/map_view.inl
  include/bit/stl/containers/detail/set_view.inl
  include/bit/stl/containers/detail/span.inl
  include/bit/stl/containers/detail/string.inl
  include/bit/stl/containers/detail/string_span.inl
  include/bit/stl/containers/detail/string_view.inl

  # iterators
  include/bit/stl/iterators/detail/tagged_iterator.inl
  include/bit/stl/iterators/detail/tuple_element_iterator.inl
  include/bit/stl/iterators/detail/zip_iterator.inl

  # ranges
  include/bit/stl/ranges/detail/move_range.inl
  include/bit/stl/ranges/detail/range.inl
  include/bit/stl/ranges/detail/reverse_range.inl
  include/bit/stl/ranges/detail/tuple_element_range.inl
  include/bit/stl/ranges/detail/zip_range.inl

  # memory
  include/bit/stl/memory/detail/allocator_deleter.inl
  include/bit/stl/memory/detail/clone_ptr.inl
  include/bit/stl/memory/detail/exclusive_ptr.inl
  include/bit/stl/memory/detail/fat_ptr.inl
  include/bit/stl/memory/detail/memory.inl
  include/bit/stl/memory/detail/observer_ptr.inl
  include/bit/stl/memory/detail/offset_ptr.inl
  include/bit/stl/memory/detail/scoped_ptr.inl
  include/bit/stl/numeric/detail/numeric.inl
)

add_library(stl INTERFACE)
add_library(bit::stl ALIAS stl)

target_include_directories(stl INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

#-----------------------------------------------------------------------------
# bit::stl : Independence Tests
#-----------------------------------------------------------------------------

include(AddHeaderSelfContainmentTest)

if( BIT_STL_COMPILE_HEADER_SELF_CONTAINMENT_TESTS )

  # Add containment test and alias as 'bit::stl::header_self_containment_test'
  add_header_self_containment_test(stl_header_self_containment_test ${headers})
  target_sources(stl_header_self_containment_test PRIVATE ${inline_headers})
  add_library(bit::stl::header_self_containment_test ALIAS stl_header_self_containment_test)

  if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
      "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options(stl_header_self_containment_test PRIVATE -Wall -Werror -pedantic)
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

export_library( TARGETS stl
                PACKAGE Stl
                VERSION ${BIT_STL_VERSION}
                MAJOR_VERSION ${BIT_STL_VERSION_MAJOR}
                MINOR_VERSION ${BIT_STL_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
