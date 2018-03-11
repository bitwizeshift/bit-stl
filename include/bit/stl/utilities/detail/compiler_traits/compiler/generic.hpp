/**
 * \file compiler/generic.hpp
 *
 * \brief This header attempts to detect a feature set from a generic
 *        (non-detected) c++ compiler.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_GENERIC_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_GENERIC_HPP

//-----------------------------------------------------------------------------
// Compiler Detection
//-----------------------------------------------------------------------------

#define BIT_COMPILER_UNKNOWN 1
#define BIT_COMPILER_VERSION 0
#define BIT_COMPILER_NAME    "Unknown Compiler"
#define BIT_COMPILER_STRING  "Unknown Compiler (unknown version)"

//-----------------------------------------------------------------------------
// C++ Standards Detection
//   Best we can do for a unknown compiler is make assumptions based on the
//   required standards -- After all, what are standards for?
//-----------------------------------------------------------------------------

#define BIT_COMPILER_HAS_INCLASS_MEMBER_INITIALIZATION 1

// If compiling for C++11, assume all features exist since compiler is unknown
#if __cplusplus >= 201103L
#  define BIT_COMPILER_HAS_CPP11_RVALUE            1
#  define BIT_COMPILER_HAS_CPP11_STATIC_ASSERT     1
#  define BIT_COMPILER_HAS_CPP11_VA_TEMPLATE       1
#  define BIT_COMPILER_HAS_CPP11_TEMPLATE_ALIAS    1
#  define BIT_COMPILER_HAS_CPP11_DEFAULT_FUNCTIONS 1
#  define BIT_COMPILER_HAS_CPP11_DELETED_FUNCTIONS 1
#  define BIT_COMPILER_HAS_CPP11_INLINE_NAMESPACE  1
#  define BIT_COMPILER_HAS_CPP11_CHAR16_T          1
#  define BIT_COMPILER_HAS_CPP11_CHAR32_T          1
#  define BIT_COMPILER_HAS_CPP11_EXPLICIT_CAST     1
#  define BIT_COMPILER_HAS_CPP11_CONSTEXPR         1
#  define BIT_COMPILER_HAS_CPP11_NOEXCEPT          1
#  define BIT_COMPILER_HAS_CPP11_NULLPTR           1
#  define BIT_COMPILER_HAS_CPP11_ENUM_CLASS        1
#  define BIT_COMPILER_HAS_CPP11_OVERRIDE          1
#  define BIT_COMPILER_HAS_CPP11_FINAL             1
#  define BIT_COMPILER_HAS_CPP11_ATTRIBUTES        1
#  define BIT_COMPILER_HAS_CPP11_ALIGNAS           1
#  define BIT_COMPILER_HAS_CPP11_ALIGNOF           1
#  define BIT_COMPILER_HAS_CPP11_THREAD_LOCAL      1
#  define BIT_COMPILER_HAS_CPP11_STD_THREADS       1
#  define BIT_COMPILER_HAS_CPP11_DECLTYPE          1
#  define BIT_COMPILER_HAS_LONG_LONG               1
#endif

// If compiling for C++14, assume all features exist since compiler is unknown
#if __cplusplus >= 201402L
#  define BIT_COMPILER_CPP14 1
#  define BIT_COMPILER_HAS_CPP14_BINARY_LITERALS      1
#  define BIT_COMPILER_HAS_CPP14_ATTRIBUTE_DEPRECATED 1
#endif

//-----------------------------------------------------------------------------
// C++ Extensions Detections
//-----------------------------------------------------------------------------

#define BIT_COMPILER_ASM_STYLE_UNKNOWN 1

#define BIT_PRAGMA(x)

// Assume weak alias doesn't exist
#define BIT_WEAK

// Assume C++ conformance that wchar_t is defined as a system type
#define BIT_COMPILER_HAS_WCHAR_T 1

//----------------------------------------------------------------------------
// Symbol Import/Export (DLL/shared library)
//----------------------------------------------------------------------------

#if !(defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
#  define BIT_COMPILER_SYMBOL_EXPORT  __declspec((dllexport))
#  define BIT_COMPILER_SYMBOL_IMPORT  __declspec((dllimport))
#  define BIT_COMPILER_SYMBOL_VISIBLE
#  define BIT_COMPILER_SYMBOL_LOCAL
#else // Assume -- if not windows -- that compiler uses __attribute__ style syntax
#  define BIT_COMPILER_SYMBOL_EXPORT  __attribute__((visibility("default")))
#  define BIT_COMPILER_SYMBOL_IMPORT
#  define BIT_COMPILER_SYMBOL_VISIBLE __attribute__((visibility("default")))
#  define BIT_COMPILER_SYMBOL_LOCAL   __attribute__((visibility("hidden")))
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_GENERIC_HPP */
