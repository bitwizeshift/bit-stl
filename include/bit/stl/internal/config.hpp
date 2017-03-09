/**
 * \file config.hpp
 *
 * \brief This header contains important configuration information for setting
 *        up the compilation environment.
 *
 * This header is included stddef and is necessary for detecting
 * compiler/platform-specific features, such as available libraries
 * and intrinsic methods.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_INTERNAL_CONFIG_HPP
#define BIT_STL_INTERNAL_CONFIG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// Prevent normal errors from being warned
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

//! \def BIT_DEBUG
//! \brief Debug build
//!
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

#include "config/macros.hpp"
#include "config/platform.hpp"
#include "config/compiler.hpp"
#include "config/compiler_traits.hpp"
#include "config/library_export.hpp"
#include "config/breakpoint.hpp"
#include "config/protect_functions.hpp"

//! \def BIT_DEFINE_ENUM_BITWISE_OPERATORS( Type )
//!
//! \brief Defines all bitwise operators globally so that enums of type \a Type
//!        can be used as flags without violating restrictions of enums
#define BIT_DEFINE_ENUM_BITWISE_OPERATORS( Type ) \
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

//! \def BIT_DEFINE_ENUM_ARITHMETIC_OPERATORS( Type )
//!
//! \brief Defines all bitwise operators globally so that enums of type \a Type
//!        can be used as flags without violating restrictions of enums
#define BIT_DEFINE_ENUM_ARITHMETIC_OPERATORS( Type ) \
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

//! \def BIT_DEFINE_ENUM_INCREMENT_OPERATORS( Type )
//!
//! \brief Defines all bitwise operators globally so that enums of type \a Type
//!        can easily be incremented and decremented while still being enums
#define BIT_DEFINE_ENUM_INCREMENT_OPERATORS( Type ) \
  inline Type &operator++( Type &a      ) { return a = Type( int( a ) + 1 ); } \
  inline Type &operator--( Type &a      ) { return a = Type( int( a ) - 1 ); } \
  inline Type  operator++( Type &a, int ) { Type t = a; ++a; return t; } \
  inline Type  operator--( Type &a, int ) { Type t = a; --a; return t; }

#endif /* BIT_STL_INTERNAL_CONFIG_HPP */
