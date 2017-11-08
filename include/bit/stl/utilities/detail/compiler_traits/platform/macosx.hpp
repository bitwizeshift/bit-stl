/**
 * \file platform/macosx.hpp
 *
 * \brief This header detects features for Mac OSX Platform
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

/*
 * Symbols Defined:
 *
 * BIT_PLATFORM_MACOSX            : Defined since platform is Mac OSX
 * BIT_PLATFORM_STRING            : String representing the platform type
 * BIT_PLATFORM_HAS_UNISTD_H      : Defined if <unistd.h> exists in the platform
 * BIT_PLATFORM_HAS_STDINT_H      : Defined if <stdint.h> exists in the platform
 * BIT_PLATFORM_HAS_PTHREADS      : Defined if the platform supports pthreads
 * BIT_PLATFORM_HAS_POSIX_SOCKETS : Defined if the platform supports posix (bsd) sockets
 */
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_MACOSX_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_MACOSX_HPP

//-----------------------------------------------------------------------------
// Platform Detection
//-----------------------------------------------------------------------------

#define BIT_PLATFORM_MACOSX 1
#define BIT_PLATFORM_STRING "Mac OSX"

//-----------------------------------------------------------------------------
// Platform Specifics Detection
//-----------------------------------------------------------------------------

#ifndef BIT_PLATFORM_HAS_UNISTD_H
# define BIT_PLATFORM_HAS_UNISTD_H  1
#endif

#include "generic_posix.hpp"

#ifndef BIT_PLATFORM_HAS_STDINT_H
# define BIT_PLATFORM_HAS_STDINT_H  1
#endif

#ifndef BIT_PLATFORM_HAS_PTHREADS
# define BIT_PLATFORM_HAS_PTHREADS  1
#endif

#ifndef BIT_PLATFORM_HAS_POSIX_SOCKETS
# define BIT_PLATFORM_HAS_POSIX_SOCKETS 1
#endif

// Determine API from defined compiler args
#ifdef BIT_USE_VULKAN_API
# error "Vulkan doesn't work with Mac OSX"
#elif !defined(BIT_USE_OGL_API)
# define BIT_USE_OGL_API 1
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_MACOSX_HPP */
