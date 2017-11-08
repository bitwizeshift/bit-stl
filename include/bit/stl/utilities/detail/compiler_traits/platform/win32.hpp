/**
 * \file platform/win32.hpp
 *
 * \brief This header detects features for Windows platforms
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

/*
 * Symbols Defined:
 *
 * BIT_PLATFORM_WINDOWS         : Defined since platform is Windows
 * BIT_PLATFORM_MINGW           : Defined if platform is windows with MinGW
 * BIT_PLATFORM_WIN32           : Defined if platform is 32 bit
 * BIT_PLATFORM_WIN64           : Defined if platform is 64 bit
 * BIT_PLATFORM_STRING          : String representing the platform type
 * BIT_PLATFORM_HAS_STDINT_H    : Defined if stdint.h exists in the platform
 * BIT_PLATFORM_HAS_DIRENT_H    : Defined if dirent.h exists in the platform
 * BIT_PLATFORM_HAS_UNISTD_H    : Defined if unistd.h exists in the platform
 * BIT_PLATFORM_HAS_PTHREADS    : Defined if platform uses pthreads
 * BIT_PLATFORM_HAS_WINTHREADS  : Defined if platform uses winthreads (default)
 * BIT_PLATFORM_HAS_WINSOCKS    : Defined since platform uses winsocks
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
