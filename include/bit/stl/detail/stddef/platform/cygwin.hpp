/**
 * \brief This header detects features for the Cygwin platform
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
/*
 * Symbols Defined:
 *
 * BIT_PLATFORM_CYGWIN            : Defined since platform is Cygwin
 * BIT_PLATFORM_STRING            : String representing the platform type
 * BIT_PLATFORM_HAS_UNISTD_H      : Defined if <unistd.h> exists in the platform
 * BIT_PLATFORM_HAS_POSIX_SOCKETS : Defined if platform supports posix (BSD) Sockets
 * BIT_PLATFORM_HAS_PTHREADS      : Defined if platform supports pthreads
 * BIT_PLATFORM_HAS_WINTHREADS    : Defined if platform supports winthreads
 * BIT_PLATFORM_HAS_STDINT_H      : Defined if <stdint.h> exists in the platform
 */
#ifndef BIT_STL_DETAIL_STDDEF_PLATFORM_CYGWIN_HPP
#define BIT_STL_DETAIL_STDDEF_PLATFORM_CYGWIN_HPP

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

#endif /* BIT_STL_DETAIL_STDDEF_PLATFORM_CYGWIN_HPP */
