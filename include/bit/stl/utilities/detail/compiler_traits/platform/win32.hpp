/*****************************************************************************
 * \file
 * \brief This header detects features for Windows platforms
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
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_WIN32_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_WIN32_HPP

//-----------------------------------------------------------------------------
// Platform Detection
//-----------------------------------------------------------------------------

#define BIT_PLATFORM_WINDOWS 1

#if defined(__MINGW32__) || defined(__MINGW64__)
# include <_mingw.h> // Include for version information
# define BIT_PLATFORM_MINGW  1
#endif

#if defined(_WIN64)
# define BIT_PLATFORM_WIN64  1
# define BIT_PLATFORM_STRING "Windows (64-bit)"
#else
# define BIT_PLATFORM_WIN32  1
# define BIT_PLATFORM_STRING "Windows (32-bit)"
#endif

//-----------------------------------------------------------------------------
// Platform Specifics Detection
//-----------------------------------------------------------------------------

// MinGW has some added headers not present in MSVC
#if defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 2) || ((__MINGW32_MAJOR_VERSION == 2) && (__MINGW32_MINOR_VERSION >= 0)))
# ifndef BIT_PLATFORM_HAS_STDINT_H
#   define BIT_PLATFORM_HAS_STDINT_H  1
# endif
# ifndef BIT_PLATFORM_HAS_DIRENT_H
#   define BIT_PLATFORM_HAS_DIRENT_H  1
# endif
# ifndef BIT_PLATFORM_HAS_UNISTD_H
#   define BIT_PLATFORM_HAS_UNISTD_H  1
# endif
#endif

// Mingw configuration specific
#if !defined(BIT_PLATFORM_HAS_PTHREADS)
# define BIT_PLATFORM_HAS_WINTHREADS 1
#endif

#define BIT_PLATFORM_HAS_WINSOCKS              1

#define BIT_PLATFORM_HAS_ALIGNED_MALLOC        1
#define BIT_PLATFORM_HAS_ALIGNED_OFFSET_MALLOC 1

// Determine API from defined compiler args
#ifdef BIT_USE_VULKAN_API
# define VK_USE_PLATFORM_WIN32_KHR 1
#elif !defined(BIT_USE_OGL_API)
# define BIT_USE_OGL_API 1
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_WIN32_HPP */
