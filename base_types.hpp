/**
 * \file base_types.hpp
 *
 * \brief This header defines a standard set of both lexical and fixed-sized
 *        types.
 */

#ifndef BIT_BASE_TYPES_HPP
#define BIT_BASE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// std libraries
#include <cstdlib> // Used for size_t
#include <climits> // Used for integer limits

// bit::core local libraries
#include "config.hpp"

namespace bit {

//! \addtogroup core
//! \{

  //--------------------------------------------------------------------------
  // System-Specific Lexical Types
  //--------------------------------------------------------------------------

  typedef int            word;       ///< Signed instruction-sized integer (Word)
  typedef unsigned int   uword;      ///< Unsigned instruction-sized integer (Word)

  //---------------------------------------------------------------------------

  typedef unsigned char  uchar;      ///< Unsigned char type
  typedef unsigned short ushort;     ///< Unsigned short type
  typedef unsigned int   uint;       ///< Unsigned int type
  typedef unsigned long  ulong;      ///< Unsigned long type

#ifdef BIT_COMPILER_HAS_LONG_LONG
  typedef unsigned long long ulonglong;
#endif

  //--------------------------------------------------------------------------
  // Generic Structures
  //--------------------------------------------------------------------------

  typedef std::size_t  size_t;  ///< Type representing size of objects

  typedef bit::size_t align_t; ///< Type representing alignment of an object
  typedef bit::size_t index_t; ///< Type representing index of objects

//! \}

} // namespace bit

#include "internal/types/integral_types.hpp"
#include "internal/types/char_types.hpp"
#include "internal/types/float_types.hpp"
#include "internal/types/byte.hpp"

namespace bit{

//! \addtogroup core
//! \{

  //--------------------------------------------------------------------------
  // Tag-Based Dispatching
  //--------------------------------------------------------------------------

  /// \struct bit::const_type_wrapper
  ///
  /// \brief Constructor tag used to differentiate const type pointers from
  /// fixed known type arrays at compile time.
  /// (e.g. "const T* p" from "const T (&p)[N]")
  ///
  /// This is used primarily for methods that need to differentiate
  /// known string sizes from pointers at compile time -- but can be extended
  /// to any generic form of array/pointer
  template<typename T>
  struct const_type_wrapper final
  {
    constexpr const_type_wrapper( const T* ptr ) : ptr(ptr){}
    const T* ptr;
  };

  typedef const_type_wrapper<char>     const_char_wrapper;   /// For ansi strings
  typedef const_type_wrapper<wchar_t>  const_wchar_wrapper;  /// For wide strings
  typedef const_type_wrapper<char16_t> const_char16_wrapper; /// For UTF16 strings
  typedef const_type_wrapper<char32_t> const_char32_wrapper; /// For UTF32 strings
  typedef const_type_wrapper<tchar>    const_tchar_wrapper;  /// For specified string types

  /// \struct bit::ctor_do_not_initialize
  ///
  /// \brief Constructor tag used to disable ctor value initialization
  struct ctor_do_not_initialize_tag{};

  /// \struct bit::ctor_zero_out
  ///
  /// \brief Constructor tag used to zero out the entire class
  struct ctor_zero_out_tag{};

  /// \struct bit::ctor_do_not_convert_tag
  ///
  /// \brief Constructor tag used to disable automatic internal conversion
  struct ctor_do_not_convert_tag{};

  /// \struct bit::ctor_va_args
  ///
  /// \brief Constructor tag used as a placeholder to not conflict with
  ///        variadic constructors
  struct ctor_va_args_tag{};

  /// \struct bit::aligned_tag
  ///
  /// \brief Tag used for tag-based dispatching to correctly call aligned
  ///        operator new and delete
  struct aligned_tag{};

  /// \struct bit::offset_tag
  ///
  /// \brief Tag used for tag-based dispatching to correctly call offset
  ///        operator new and delete
  struct offset_tag{};

  /// \struct bit::aligned_offset_tag
  ///
  /// \brief Tag used for tag-base dispatching to correctly call aligned/offset
  ///        operator new and delete
  struct aligned_offset_tag : aligned_tag, offset_tag{};

  //--------------------------------------------------------------------------
  // Predefined Tags
  //--------------------------------------------------------------------------

  /// Predefined constant for disabling initialization
  constexpr ctor_do_not_initialize_tag ctor_dni = {};

  /// Predefined constant for zeroing out a constructor
  constexpr ctor_zero_out_tag ctor_zero_out = {};

  /// Predefined constant for disabling internal conversion
  constexpr ctor_do_not_convert_tag ctor_dnc = {};

  /// Predefined constant for aligned tag
  constexpr aligned_tag aligned = {};

  /// Predefined constant for offset tag
  constexpr offset_tag  offset = {};

  /// Predefined constant for aligned offset tag
  constexpr aligned_offset_tag aligned_offset = {};

//! \}

} // namespace bit

#endif /* BIT_BASE_TYPES_HPP */
