/**
 * \file platform/generic_posix.hpp
 *
 * \brief This header detects features of generic Posix systems.
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
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_GENERIC_POSIX_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_GENERIC_POSIX_HPP

#ifdef BIT_PLATFORM_HAS_UNISTD_H
# include <unistd.h>

// Detect POSIX compliance versions
# if defined(_POSIX_VERSION)
#  if (_POSIX_VERSION >= 198808L)
#   define BIT_STANDARD_POSIX_1_1988 1
#  endif
#  if (defined(_POSIX2_C_VERSION ) && (_POSIX2_C_VERSION >= 199209L))
#   define BIT_STANDARD_POSIX_2_1993 1
#  endif
#  if (_POSIX_VERSION >= 199009L)
#   define BIT_STANDARD_POSIX_1_1990 1
#  endif
#  if (_POSIX_VERSION >= 199309L)
#   define BIT_STANDARD_POSIX_1_1993 1
#  endif
#  if (_POSIX_VERSION >= 199506L)
#   define BIT_STANDARD_POSIX_1_1996 1
#  endif
#  if (_POSIX_VERSION >= 200112L)
#   define BIT_STANDARD_POSIX_1_2001 1
#  endif
#  if (_POSIX_VERSION >= 200809L)
#   define BIT_STANDARD_POSIX_1_2008 1
#  endif
# endif

// Detect X-Open Standard Compliance
# if defined(_XOPEN_VERSION)
#  if ((_XOPEN_VERSION + 0) >= 3)
#   define BIT_STANDARD_XOPEN_1989 1
#  endif
#  if ((_XOPEN_VERSION + 0) >= 4)
#   define BIT_STANDARD_XOPEN_1992 1
#  endif
#  if ((_XOPEN_VERSION + 0) >= 4) && defined(_XOPEN_UNIX)
#   define BIT_STANDARD_XOPEN_1995 1
#  endif
#  if ((_XOPEN_VERSION + 0) >= 500)
#   define BIT_STANDARD_XOPEN_1998 1
#  endif
#  if ((_XOPEN_VERSION + 0) >= 600)
#   define BIT_STANDARD_XOPEN_2003 1
#  endif
#  if ((_XOPEN_VERSION + 0) >= 700)
#   define BIT_STANDARD_XOPEN_2008 1
#  endif
# endif

//-----------------------------------------------------------------------------

// POSIX version 2 requires <dirent.h>
# if !defined(BIT_PLATFORM_HAS_DIRENT_H) && defined(BIT_STANDARD_POSIX_1_1990)
#  define BIT_PLATFORM_HAS_DIRENT_H 1
# endif

// POSIX version 6 requires <stdint.h>
# if !defined(BIT_PLATFORM_HAS_STDINT_H) && defined(BIT_STANDARD_POSIX_1_2001) // (_POSIX_VERSION >= 200100))
#  define BIT_PLATFORM_HAS_STDINT_H 1
# endif

// POSIX version 6 requires <sys/socket.h>, <sys/inet.h>, etc.
# if !defined(BIT_PLATFORM_HAS_POSIX_SOCKETS) && defined(BIT_STANDARD_POSIX_1_2001) // (defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L))
#  define BIT_PLATFORM_HAS_POSIX_SOCKETS 1
# endif

// POSIX Thread detection
# if !(defined(BIT_PLATFORM_HAS_WINTHREADS) || defined(BIT_PLATFORM_HAS_PTHREADS)) && \
   ((defined(_POSIX_THREADS) && ((_POSIX_THREADS + 0) >= 0)) || \
    (defined(BIT_STANDARD_POSIX_1_2001)))
#  define BIT_PLATFORM_HAS_PTHREADS 1
# endif

// POSIX nanosleep timer detection
# if !defined(BIT_PLATFORM_HAS_NANOSLEEP) && \
   ((defined(_POSIX_TIMERS) && ((_POSIX_TIMERS + 0) >= 0)) || \
   (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)))
#  define BIT_PLATFORM_HAS_NANOSLEEP 1
# endif

// POSIX has posix_memalign method
# if (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L)) || \
   (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))
#  define BIT_PLAFORM_HAS_POSIX_MEMALIGN 1
# endif

// POSIX has aligned_alloc method
# ifdef _ISOC11_SOURCE
#  define BIT_PLATFORM_HAS_ALIGNED_ALLOC 1
# endif

#endif // BIT_PLATFORM_HAS_UNISTD_H

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_GENERIC_POSIX_HPP */
