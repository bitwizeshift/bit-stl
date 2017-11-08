/**
 * \file platform/linux.hpp
 *
 * \brief This header detects features for generic Linux platforms.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

/*
 * Symbols Defined:
 *
 * BIT_PLATFORM_LINUX         : Defined since platform is Linux
 * BIT_PLATFORM_STRING        : String representing the platform type
 * BIT_PLATFORM_HAS_STDINT_H  : Defined if <stdint.h> exists in the platform
 * BIT_PLATFORM_HAS_NANOSLEEP : Defined if the platform supports nanosleep
 * BIT_PLATFORM_HAS_UNISTD_H  : Defined if <unistd.h> exists in the platform
 */
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_LINUX_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_LINUX_HPP

//-----------------------------------------------------------------------------
// Platform Detection
//-----------------------------------------------------------------------------

#define BIT_PLATFORM_LINUX  1
#define BIT_PLATFORM_STRING "Linux"

//-----------------------------------------------------------------------------
// Platform Specifics Detection
//-----------------------------------------------------------------------------

// In order for int64_t to properly be defined in <sys/types>, __GLIBC__ needs
// to be defined
#if defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1)))
# if defined(__GNUC__)
#  define BIT_PLATFORM_HAS_STDINT_H 1
# endif
#endif

#ifdef __USE_POSIX199309
#  define BIT_PLATFORM_HAS_NANOSLEEP  1
#endif

// Always assume unistd.h
#define BIT_PLATFORM_HAS_UNISTD_H    1

#include "generic_posix.hpp"

// Determine API from defined compiler args
#ifdef BIT_USE_VULKAN_API
# define VK_USE_PLATFORM_XLIB_KHR 1
#elif !defined(BIT_USE_OGL_API)
# define BIT_USE_OGL_API 1
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_PLATFORM_LINUX_HPP */
