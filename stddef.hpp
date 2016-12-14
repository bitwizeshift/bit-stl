/**
 * \file stddef.hpp
 *
 * \brief This header defines a standard set of both lexical and fixed-sized
 *        types.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_STDDEF_HPP
#define BIT_STL_STDDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl internal configuration library
#include "internal/config.hpp"

// std libraries
#include <cstdlib> // Used for size_t

namespace bit {
  namespace stl {

//! \addtogroup stl
//! \{

    //--------------------------------------------------------------------------
    // System-Specific Lexical Types
    //--------------------------------------------------------------------------

    using word  = int;          ///< Signed instruction-sized integer (Word)
    using uword = unsigned int; ///< Unsigned instruction-sized integer (Word)

    //---------------------------------------------------------------------------

    using uchar  = unsigned char;  ///< Unsigned char type
    using ushort = unsigned short; ///< Unsigned short type
    using uint   = unsigned int;   ///< Unsigned int type
    using ulong  = unsigned long;  ///< Unsigned long type

#ifdef BIT_COMPILER_HAS_LONG_LONG
    using ulonglong = unsigned long long;
#endif

    //--------------------------------------------------------------------------
    // Generic Structures
    //--------------------------------------------------------------------------

    using size_t  = std::size_t; ///< Type representing size of objects
    using align_t = std::size_t; ///< Type representing alignment of an object
    using index_t = std::size_t; ///< Type representing index of objects

//! \}
  } // namespace stl
} // namespace bit

#include "internal/types/integral_types.hpp"
#include "internal/types/char_types.hpp"
#include "internal/types/float_types.hpp"
#include "internal/types/byte.hpp"

namespace bit {
  namespace stl {

//! \addtogroup stl
//! \{

    //------------------------------------------------------------------------
    // Tag-Based Dispatching
    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief Constructor tag used to differentiate const type pointers from
    ///        fixed known type arrays at compile time.
    ///        (e.g. "const T* p" from "const T (&p)[N]")
    ///
    /// This is used primarily for methods that need to differentiate
    /// known string sizes from pointers at compile time -- but can be
    /// extended to any generic form of array/pointer
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct const_type_wrapper final
    {
      constexpr const_type_wrapper( const T* ptr ) : ptr(ptr){}
      const T* ptr;
    };

    using const_char_wrapper   = const_type_wrapper<char>;     /// For ansi strings
    using const_wchar_wrapper  = const_type_wrapper<wchar_t>;  /// For wide strings
    using const_char16_wrapper = const_type_wrapper<char16_t>; /// For UTF16 strings
    using const_char32_wrapper = const_type_wrapper<char32_t>; /// For UTF32 strings
    using const_tchar_wrapper  = const_type_wrapper<tchar>;    /// For specified string types

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
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_STDDEF_HPP */
