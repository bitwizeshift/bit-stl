/*****************************************************************************
 * \file
 * \brief This header detects compiler-specific features for GCC
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 *****************************************************************************/

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
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_GCC_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_GCC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

//-----------------------------------------------------------------------------
// Compiler Detection
//-----------------------------------------------------------------------------

#define BIT_COMPILER_GNUC    1
#define BIT_COMPILER_NAME    "GCC"
#define BIT_COMPILER_STRING  BIT_COMPILER_NAME " " BIT_STRINGIZE(__GNUC__) "." BIT_STRINGIZE(__GNUC_MINOR__)
#define BIT_COMPILER_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#define BIT_COMPILER_GNUC_VERSION BIT_COMPILER_VERSION

//-----------------------------------------------------------------------------
// C++ Standards Detection
//
// Version numbers for detecting the various features were taken from the
// following resources:
//
// - https://gcc.gnu.org/projects/cxx0x.html
// - https://gcc.gnu.org/projects/cxx1y.html
// - https://gcc.gnu.org/projects/cxx1z.html
//
// The constants are not defined if the compiler isn't compiling for
// the specified standard in order to avoid conflict
//-----------------------------------------------------------------------------

#define BIT_COMPILER_HAS_INCLASS_MEMBER_INITIALIZATION 1

//-----------------------------------------------------------------------------

// C++11 checks

#if defined(__cplusplus) && (__cplusplus >= 201103L) || defined(__GXX_EXPERIMENTAL_CXX0X__ )
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#    define BIT_COMPILER_HAS_CPP11_RVALUE            1
#    define BIT_COMPILER_HAS_CPP11_STATIC_ASSERT     1
#    define BIT_COMPILER_HAS_CPP11_VA_TEMPLATE       1
#  endif
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4))
#    define BIT_COMPILER_HAS_CPP11_DEFAULT_FUNCTIONS 1
#    define BIT_COMPILER_HAS_CPP11_DELETED_FUNCTIONS 1
#    define BIT_COMPILER_HAS_CPP11_INLINE_NAMESPACE  1
#    define BIT_COMPILER_HAS_CPP11_CHAR16_T          1
#    define BIT_COMPILER_HAS_CPP11_CHAR32_T          1
#    define BIT_COMPILER_HAS_CPP11_SMART_POINTERS    1
#  endif
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#    define BIT_COMPILER_HAS_CPP11_EXPLICIT_CAST     1
#  endif
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#    define BIT_COMPILER_HAS_CPP11_CONSTEXPR         1
#    define BIT_COMPILER_HAS_CPP11_NOEXCEPT          1
#    define BIT_COMPILER_HAS_CPP11_NULLPTR           1
#    define BIT_COMPILER_HAS_CPP11_ENUM_CLASS        1
#  endif
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#    define BIT_COMPILER_HAS_CPP11_OVERRIDE          1
#    define BIT_COMPILER_HAS_CPP11_FINAL             1
#    define BIT_COMPILER_HAS_CPP11_TEMPLATE_ALIAS    1
#  endif
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
#    define BIT_COMPILER_HAS_CPP11_ATTRIBUTES        1
#    define BIT_COMPILER_HAS_CPP11_ALIGNAS           1
#    define BIT_COMPILER_HAS_CPP11_ALIGNOF           1
#    define BIT_COMPILER_HAS_CPP11_THREAD_LOCAL      1
#    define BIT_COMPILER_HAS_CPP11_DECLTYPE          1
#  endif
#endif


//-----------------------------------------------------------------------------

// C++14 checks

#if defined(__cplusplus) && (__cplusplus >= 201402L) || defined(__GXX_EXPERIMENTAL_CXX0Y__)
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
#    define BIT_COMPILER_HAS_CPP14_BINARY_LITERALS      1
#    define BIT_COMPILER_HAS_CPP14_ATTRIBUTE_DEPRECATED 1
#  endif
#endif

//-----------------------------------------------------------------------------

// C++17 checks

#if defined(__cplusplus) && (__cplusplus >= 201702L) || defined(__GXX_EXPERIMENTAL_CXX1Z__)
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
#    defined BIT_COMPILER_HAS_CPP17_NAMESPACE_ATTRIBUTES 1
#  endif
#  if (__GNUC__ >= 6)
#    define BIT_COMPILER_HAS_CPP17_U8_LITERALS            1
#    define BIT_COMPILER_HAS_CPP17_ENUMERATOR_ATTRIBUTES  1
#    define BIT_COMPILER_HAS_NESTED_NAMESPACE_DEFINITIONS 1
#    define BIT_COMPILER_HAS_FOLDING_EXPRESSIONS          1
#  endif
#endif

//-----------------------------------------------------------------------------
// C++ Type Traits Intrinsics Detection
//-----------------------------------------------------------------------------

#if ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
#  define BIT_IS_UNION(T)                 __is_union(T)
#  define BIT_IS_POD(T)                   __is_pod(T)
#  define BIT_IS_EMPTY(T)                 __is_empty(T)
#  define BIT_HAS_TRIVIAL_CONSTRUCTOR(T)  __has_trivial_constructor(T)
#  define BIT_HAS_TRIVIAL_COPY(T)         __has_trivial_copy(T)
#  define BIT_HAS_TRIVIAL_ASSIGN(T)       __has_trivial_assign(T)
#  define BIT_HAS_TRIVIAL_DESTRUCTOR(T)   __has_trivial_destructor(T)
#  define BIT_HAS_NOTHROW_CONSTRUCTOR(T)  __has_nothrow_constructor(T)
#  define BIT_HAS_NOTHROW_COPY(T)         __has_nothrow_copy(T)
#  define BIT_HAS_NOTHROW_ASSIGN(T)       __has_nothrow_assign(T)
#  define BIT_HAS_VIRTUAL_DESTRUCTOR(T)   __has_virtual_destructor(T)

#  define BIT_IS_ABSTRACT(T)              __is_abstract(T)
#  define BIT_IS_BASE_OF(T,U)            (__is_base_of(T,U) && (!::bit::is_same<T,U>::value))
#  define BIT_IS_CLASS(T)                 __is_class(T)
#  define BIT_IS_ENUM(T)                  __is_enum(T)
#  define BIT_IS_POLYMORPHIC(T)           __is_polymorphic(T)
// For some reason, __is_final wasn't added until GCC 4.7
#  if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))
#    define BIT_IS_FINAL(T) __is_final(T)
#  endif
#  define BIT_COMPILER_HAS_TYPE_TRAITS_INTRINSICS 1
#endif

//-----------------------------------------------------------------------------
// C++ Extensions Detections
//-----------------------------------------------------------------------------

#define BIT_COMPILER_ASM_STYLE_ATT   1

#if defined(__AVX__)
#  define BIT_PLATFORM_HAS_AVX    1
#endif
#if defined(__AVX2__)
#  define BIT_PLATFORM_HAS_AVX2   1
#endif
#if (defined(__SSE__) && __SSE__) || defined(__SSE_MATH__ )
#  define BIT_PLATFORM_HAS_SSE    1
#endif
#if defined(__SSE2__) || defined(__SSE2_MATH__ )
#  define BIT_PLATFORM_HAS_SSE2   1
#endif
#if defined(__SSE3__)
#  define BIT_PLATFORM_HAS_SSE3   1
#endif
#if defined(__SSE4_1__)
#  define BIT_PLATFORM_HAS_SSE4_1 1
#endif
#if defined(__SSE4_2__)
#  define BIT_PLATFORM_HAS_SSE4_2 1
#endif

#define BIT_PRAGMA(x)   _Pragma(#x)

#define BIT_WEAK __attribute__((weak))
#define BIT_COMPILER_HAS_WEAK_ALIAS 1

#if defined(__EXCEPTIONS)
# define BIT_COMPILER_EXCEPTIONS_ENABLED 1
#else
# define BIT_COMPILER_EXCEPTIONS_ENABLED 0
#endif

#if defined(__WCHAR_TYPE__)
# define BIT_COMPILER_HAS_WCHAR_T   1
#endif

// Apple provides an easy macro to detect if no long-long exists
#if !defined(__DARWIN_NO_LONG_LONG)
# define BIT_COMPILER_HAS_LONG_LONG 1
#endif

// Make sure GNUC isn't NVidea's CudaCC so that int128 will be properly defined
#if defined(__SIZEOF_INT128__) && !defined(__CUDACC__)
#  define BIT_COMPILER_HAS_INT128    1
#endif

#ifdef __EXCEPTIONS
# define BIT_COMPILER_EXCEPTIONS_ENABLED 1
#else
# define BIT_COMPILER_EXCEPTIONS_ENABLED 0
#endif

//----------------------------------------------------------------------------
// Symbol Import/Export (DLL/shared library)
//----------------------------------------------------------------------------

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
#  define BIT_COMPILER_HAS_DECLSPEC   1
#  define BIT_COMPILER_SYMBOL_EXPORT  __declspec((dllexport))
#  define BIT_COMPILER_SYMBOL_IMPORT  __declspec((dllimport))
#  define BIT_COMPILER_SYMBOL_VISIBLE
#  define BIT_COMPILER_SYMBOL_LOCAL
#elif (__GNUC__ >= 4) // gcc 4.0+ allows visibility("hidden")
#  define BIT_COMPILER_SYMBOL_EXPORT  __attribute__((visibility("default")))
#  define BIT_COMPILER_SYMBOL_IMPORT
#  define BIT_COMPILER_SYMBOL_VISIBLE __attribute__((visibility("default")))
#  define BIT_COMPILER_SYMBOL_LOCAL   __attribute__((visibility("hidden")))
#else
#  define BIT_COMPILER_SYMBOL_EXPORT  __attribute__((dllexport))
#  define BIT_COMPILER_SYMBOL_IMPORT  __attribute__((dllimport))
#  define BIT_COMPILER_SYMBOL_VISIBLE
#  define BIT_COMPILER_SYMBOL_LOCAL
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_GCC_HPP */
