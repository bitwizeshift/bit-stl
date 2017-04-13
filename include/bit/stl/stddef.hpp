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

// std libraries
#include <cstdlib>


//! \def BIT_DEBUG
//! \brief Debug build
//!
//! \def BIT_UNIT_TEST
//! \brief Unit Test Build
#if !defined(BIT_DEBUG) && (defined(DEBUG) || defined(_DEBUG))
#  define BIT_DEBUG     1
#endif

#if !defined(BIT_UNIT_TEST) && (defined(UNIT_TEST) || defined(_UNIT_TEST))
#  define BIT_UNIT_TEST 1
#endif

//! \def BIT_NOOP()
//! \brief Macro function indicating no operation will occur
#ifndef BIT_NOOP
# define BIT_NOOP() ((void)0)
#endif

//! \def BIT_UNUSED
//!
//! \brief Explicitly marks a variable \p var as being unused within a given function.
//!
//! This is used to silence compiler warnings
//!
//! \param var the variable to explicitly mark as unused
#define BIT_UNUSED(var) do { (void)(var); } while (0)

// bit::stl types
// IWYU pragma: begin_exports
#include "detail/stddef/types/integral_types.hpp"
#include "detail/stddef/types/char_types.hpp"
#include "detail/stddef/types/float_types.hpp"
#include "detail/stddef/types/byte.hpp"
#include "detail/stddef/macros.hpp"
#include "detail/stddef/platform.hpp"
#include "detail/stddef/compiler.hpp"
#include "detail/stddef/compiler_traits.hpp"
#include "detail/stddef/library_export.hpp"
#include "detail/stddef/breakpoint.hpp"
#include "detail/stddef/protect_functions.hpp"
// IWYU pragma: end_exports

//! \def BIT_STL_DEFINE_ENUM_BITWISE_OPERATORS( Type )
//!
//! \brief Defines all bitwise operators globally so that enums of type \a Type
//!        can be used as flags without violating restrictions of enums
#define BIT_STL_DEFINE_ENUM_BITWISE_OPERATORS( Type ) \
  inline Type  operator|  ( Type  lhs, Type rhs ) { return Type( int( lhs ) | int( rhs ) ); } \
  inline Type  operator&  ( Type  lhs, Type rhs ) { return Type( int( lhs ) & int( rhs ) ); } \
  inline Type  operator^  ( Type  lhs, Type rhs ) { return Type( int( lhs ) ^ int( rhs ) ); } \
  inline Type  operator<< ( Type  lhs, int  rhs ) { return Type( int( lhs ) << rhs ); } \
  inline Type  operator>> ( Type  lhs, int  rhs ) { return Type( int( lhs ) >> rhs ); } \
  inline Type& operator|= ( Type& lhs, Type rhs ) { return lhs = lhs |  rhs; } \
  inline Type& operator&= ( Type& lhs, Type rhs ) { return lhs = lhs &  rhs; } \
  inline Type& operator^= ( Type& lhs, Type rhs ) { return lhs = lhs ^  rhs; } \
  inline Type& operator<<=( Type& lhs, int  rhs ) { return lhs = lhs << rhs; } \
  inline Type& operator>>=( Type& lhs, int  rhs ) { return lhs = lhs >> rhs; } \
  inline Type  operator~  ( Type  lhs )           { return Type( ~int( lhs ) ); }

//! \def BIT_STL_DEFINE_ENUM_ARITHMETIC_OPERATORS( Type )
//!
//! \brief Defines all bitwise operators globally so that enums of type \a Type
//!        can be used as flags without violating restrictions of enums
#define BIT_STL_DEFINE_ENUM_ARITHMETIC_OPERATORS( Type ) \
  inline Type  operator+ ( Type  lhs, Type rhs ) { return Type( int( lhs ) + int( rhs ) ); } \
  inline Type  operator- ( Type  lhs, Type rhs ) { return Type( int( lhs ) - int( rhs ) ); } \
  inline Type  operator* ( Type  lhs, Type rhs ) { return Type( int( lhs ) * int( rhs ) ); } \
  inline Type  operator/ ( Type  lhs, Type rhs ) { return Type( int( lhs ) / int( rhs ) ); } \
  inline Type  operator% ( Type  lhs, Type rhs ) { return Type( int( lhs ) % int( rhs ) ); } \
  inline Type& operator+=( Type& lhs, Type rhs ) { return lhs = lhs + rhs;   } \
  inline Type& operator-=( Type& lhs, Type rhs ) { return lhs = lhs - rhs;   } \
  inline Type& operator*=( Type& lhs, Type rhs ) { return lhs = lhs * rhs;   } \
  inline Type& operator/=( Type& lhs, Type rhs ) { return lhs = lhs / rhs;   } \
  inline Type& operator%=( Type& lhs, Type rhs ) { return lhs = lhs % rhs;   } \
  inline Type  operator+ ( Type  lhs )           { return lhs;               } \
  inline Type  operator- ( Type  lhs )           { return Type(- int(lhs) ); }

//! \def BIT_STL_DEFINE_ENUM_INCREMENT_OPERATORS( Type )
//!
//! \brief Defines all bitwise operators globally so that enums of type \a Type
//!        can easily be incremented and decremented while still being enums
#define BIT_STL_DEFINE_ENUM_INCREMENT_OPERATORS( Type ) \
  inline Type &operator++( Type &a      ) { return a = Type( int( a ) + 1 ); } \
  inline Type &operator--( Type &a      ) { return a = Type( int( a ) - 1 ); } \
  inline Type  operator++( Type &a, int ) { Type t = a; ++a; return t; } \
  inline Type  operator--( Type &a, int ) { Type t = a; --a; return t; }


namespace bit {
  namespace stl {

//! \addtogroup stl
//! \{

    /// \brief An alias for lvalue-references to an array of N entries
    template<typename T, std::size_t N>
    using array_ref_t = T (&)[N];

    /// \brief An alias for rvalue-references to an array of N entries
    template<typename T, std::size_t N>
    using array_rref_t = T (&&)[N];

    namespace detail {

      template<typename Fn>
      struct function_t;

      template<typename R, typename...Args>
      struct function_t<R(Args...)> {
        using type = R(*)(Args...);
      };

#if __cplusplus >= 201703L
      template<typename R, typename...Args>
      struct function_t<R(Args...) noexcept> {
        using type = R(*)(Args...) noexcept;
      }
#endif

      //----------------------------------------------------------------------

      template<typename T, typename R>
      struct member_function_t;

      template<typename T, typename R, typename...Args>
      struct member_function_t<T,R(Args...)> {
        using type = R(T::*)(Args...);
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const T,R(Args...)> {
        using type = R(T::*)(Args...) const;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<volatile T,R(Args...)> {
        using type = R(T::*)(Args...) volatile;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const volatile T,R(Args...)> {
        using type = R(T::*)(Args...) const volatile;
      };

#if __cplusplus >= 201703L
      template<typename T, typename R, typename...Args>
      struct member_function_t<T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) noexcept;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) const noexcept;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<volatile T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) volatile noexcept;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const volatile T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) const volatile noexcept;
      };
#endif
    } // namespace detail

    template<typename T, typename R>
    using member_t = R T::*;

    /// \brief A type alias for member function pointers to make it more
    ///        readable.
    template<typename T, typename R>
    using member_function_t = typename detail::member_function_t<T,R>::type;

    /// \brief A type alias for function pointers to make it more readable
    template<typename Fn>
    using function_t = typename detail::function_t<Fn>::type;

    //--------------------------------------------------------------------------
    // System-Specific Lexical Types
    //--------------------------------------------------------------------------

    using word  = int;          ///< Signed instruction-sized integer (Word)
    using uword = unsigned int; ///< Unsigned instruction-sized integer (Word)

    //---------------------------------------------------------------------------

    using uchar     = unsigned char;  ///< Unsigned char type
    using ushort    = unsigned short; ///< Unsigned short type
    using uint      = unsigned int;   ///< Unsigned int type
    using ulong     = unsigned long;  ///< Unsigned long type
    using ulonglong = unsigned long long;

    //--------------------------------------------------------------------------

    using size_t  = std::size_t;    ///< Type representing size of objects
    using align_t = std::size_t;    ///< Type representing alignment of an object
    using index_t = std::ptrdiff_t; ///< Type representing index of objects
    using hash_t  = std::size_t;    ///< Type used for hashes

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
    template<typename CharT>
    struct const_type_wrapper final
    {
      constexpr const_type_wrapper( const CharT* ptr ) : ptr(ptr){}
      const CharT* ptr;
    };

    using const_char_wrapper   = const_type_wrapper<char>;     /// For ansi strings
    using const_wchar_wrapper  = const_type_wrapper<wchar_t>;  /// For wide strings
    using const_char16_wrapper = const_type_wrapper<char16_t>; /// For UTF16 strings
    using const_char32_wrapper = const_type_wrapper<char32_t>; /// For UTF32 strings
    using const_tchar_wrapper  = const_type_wrapper<tchar>;    /// For specified string types

    /// \brief Constructor tag used to zero out the entire class
    struct ctor_zero_out_tag{};

    /// \brief Constructor tag used to disable automatic internal conversion
    struct ctor_do_not_convert_tag{};

    /// \brief Constructor tag used as a placeholder to not conflict with
    ///        variadic constructors
    struct ctor_va_args_tag{};

    //--------------------------------------------------------------------------
    // Predefined Tags
    //--------------------------------------------------------------------------

    /// Predefined constant for zeroing out a constructor
    constexpr ctor_zero_out_tag ctor_zero_out = {};

    /// Predefined constant for disabling internal conversion
    constexpr ctor_do_not_convert_tag ctor_dnc = {};

//! \}

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_STDDEF_HPP */
