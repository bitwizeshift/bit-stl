/*****************************************************************************
 * \file
 * \brief This header detects features for the Cygwin platform
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
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_CYGWIN_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_CYGWIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

//-----------------------------------------------------------------------------
// Platform Detection
//-----------------------------------------------------------------------------

#define BIT_PLATFORM_CYGWIN 1
#define BIT_PLATFORM_STRING "Cygwin"

//-----------------------------------------------------------------------------
// Platform Specifics Detection
//-----------------------------------------------------------------------------

// cygwin never comes without <unistd.h>
#define BIT_PLATFORM_HAS_UNISTD_H      1

#include <unistd.h>

// Cygwin can be implemented with either pthreads or winthreads
#if (defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0)) && \
    (!defined(BIT_PLATFORM_HAS_WINTHREADS))
# define BIT_PLATFORM_HAS_PTHREADS     1
#elif !defined(BIT_PLATFORM_HAS_WINTHREADS)
# define BIT_PLATFORM_HAS_WINTHREADS 1
#endif

#if !defined(BIT_PLATFORM_HAS_WINSOCK)
# define BIT_PLATFORM_HAS_POSIX_SOCKETS 1
#endif

// Include <sys/types.h> to check for _STDINT_H
#include <sys/types.h>

#if defined(_STDINT_H)
# define BIT_PLATFORM_HAS_STDINT_H     1
#endif

// Determine API from defined compiler args
#ifdef BIT_USE_VULKAN_API
# define VK_USE_PLATFORM_WIN32_KHR 1
#endif

// Cygwin is a Posix system on Windows
#include "generic_posix.hpp"

// Determine API from defined compiler args
#ifdef BIT_USE_VULKAN_API
# define VK_USE_PLATFORM_WIN32_KHR 1
#elif !defined(BIT_USE_OGL_API)
# define BIT_USE_OGL_API 1
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_CYGWIN_HPP */
