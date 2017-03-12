/**
 * \brief This header detects the appropriate platform configuration based on
 *        the compiling operating system
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_DETAIL_STDDEF_PLATFORM_HPP
#define BIT_STL_DETAIL_STDDEF_PLATFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

//! \def BIT_PLATFORM_CONFIG_FILE
//!
//! The file path to the platform configuration file used by this configuration
#if (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__))
# define BIT_PLATFORM_CONFIG_FILE "platform/linux.hpp"
#elif defined(__CYGWIN__)
# define BIT_PLATFORM_CONFIG_FILE "platform/cygwin.hpp"
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define BIT_PLATFORM_CONFIG_FILE "platform/win32.hpp"
#elif defined(__APPLE__) || defined(__APPLE_CC__) || defined(__MACH__)
# define BIT_PLATFORM_CONFIG_FILE "platform/macosx.hpp"
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
# define BIT_PLATFORM_CONFIG_FILE "platform/generic_posix.hpp"
#else
# error "Platform not recognized!"
#endif

#include BIT_PLATFORM_CONFIG_FILE

#if 0 // Used for dependency scanners to detect possible inclusions
# include "platform/linux.hpp"
# include "platform/cygwin.hpp"
# include "platform/win32.hpp"
# include "platform/macosx.hpp"
# include "platform/generic_posix.hpp"
#endif


//-----------------------------------------------------------------------------
// Detect Processor architecture
//
// Symbols Defined:
//    BIT_PROCESSOR_X86        : x86 processor
//    BIT_PROCESSOR_X86_64     : x86-64 processor
//    BIT_PROCESSOR_IA64       : IA64 processor
//    BIT_PROCESSOR_POWERPC    : Power-pc processor
//    BIT_PROCESSOR_POWERPC_32 : Power-PC 32-bit processor
//    BIT_PROCESSOR_POWERPC_64 : Power-PC 64-bit processor
//    BIT_ARCHITECTURE         : Expands to instruction length (32 or 64)
//    BIT_ARCHITECTURE_32      : Architecture is 32 bit
//    BIT_ARCHITECTURE_64      : Architecture is 64 bit
//-----------------------------------------------------------------------------
#if defined(__x86_64__) || defined(_M_X64) || defined(__ia64__) || defined(_M_AMD64) || \
      defined(_AMD64_) || defined(_M_IA64) || defined(_IA64_)
# define BIT_PROCESSOR_X86_64      1
# define BIT_ARCHITECTURE_64       1
# define BIT_ARCHITECTURE          64
# define BIT_PROCESSOR_STRING      "x86_64"
#elif defined(_M_IX86) || defined(_X86_) || defined(__i386__) || defined(__intel__) || defined(_M_IX86) \
    || defined(__i486__ )|| defined(__pentium__)        \
    || defined(__pentiumpro__) || defined(__pentium4__) \
    || defined(__k8__) || defined(__athlon__)  || defined(__k6__)
# define BIT_PROCESSOR_X86         1
# define BIT_ARCHITECTURE_32       1
# define BIT_ARCHITECTURE          32
# define BIT_PROCESSOR_STRING      "x86"
#elif  defined(__POWERPC__) || defined(__powerpc__)
# define BIT_PROCESSOR_POWERPC     1
# define BIT_PROCESSOR_POWERPC_32  1
# define BIT_ARCHITECTURE_32       1
# define BIT_ARCHITECTURE          32
# define BIT_PROCESSOR_STRING      "powerpc"
#elif defined(__POWERPC64__) || defined(__powerpc64__)
# define BIT_PROCESSOR_POWERPC     1
# define BIT_PROCESSOR_POWERPC_64  1
# define BIT_ARCHITECTURE_64       1
# define BIT_ARCHITECTURE          64
# define BIT_PROCESSOR_STRING      "powerpc64"
#endif

///!
///! \def BIT_BYTE_ORDER
///! The order bytes are stored (decimal number 1234 or 4321)
///!
///! \def BIT_BIG_ENDIAN
///! Defined as 1 if the target machine is big-endian
///!
///! \def BIT_LITTLE_ENDIAN
///! Defined as 1 if the target is little-endian
///!
#if defined (__GLIBC__)
# include <endian.h>
#   define BIT_BYTE_ORDER __BYTE_ORDER
# if(__BYTE_ORDER == __LITTLE_ENDIAN)
#   define BIT_LITTLE_ENDIAN 1
# elif(__BYTE_ORDER == __BIG_ENDIAN)
#   define BIT_BIG_ENDIAN    1
# endif
#elif defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN) || \
      defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__) || \
      defined(_STLP_BIG_ENDIAN) && !defined(_STLP_LITTLE_ENDIAN)
# define BIT_BIG_ENDIAN 1
# define BIT_BYTE_ORDER 4321
#elif defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN) || \
      defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) || \
      defined(_STLP_LITTLE_ENDIAN) && !defined(_STLP_BIG_ENDIAN)
# define BIT_LITTLE_ENDIAN 1
# define BIT_BYTE_ORDER 1234
#elif defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hpux) || defined(__hppa) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__)
# define BIT_BIG_ENDIAN 1
# define BIT_BYTE_ORDER 4321
#elif defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(__amd64) \
   || defined(__amd64__) || defined(_M_AMD64) \
   || defined(__x86_64) || defined(__x86_64__) \
   || defined(_M_X64) || defined(__bfin__)
# define BIT_LITTLE_ENDIAN 1
# define BIT_BYTE_ORDER    1234
#endif
#if !defined(BIT_BYTE_ORDER) || !(defined(BIT_BIG_ENDIAN) || defined(BIT_LITTLE_ENDIAN)) // Error if endian not detected
# error "Unknown machine endianness"
#endif

//-----------------------------------------------------------------------------
// Platform pointer size (may be different than word size)
//-----------------------------------------------------------------------------

//! \def BIT_PLATFORM_PTR_SIZE
//!
//! The size of the platform pointer size (assumed to be the pointer size)
#ifndef BIT_PLATFORM_PTR_SIZE
# if defined(__SIZEOF_POINTER__)
#   define BIT_PLATFORM_PTR_SIZE __SIZEOF_POINTER__
# elif defined(__WORDSIZE) // Some GCC versions define the size of a word
#   define BIT_PLATFORM_PTR_SIZE ((__WORDSIZE) / 8)
# elif defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(_M_IA64) || defined(__ia64__) || defined(__arch64__) || defined(__mips64__) || defined(__64BIT__)
#   define BIT_PLATFORM_PTR_SIZE 8
# elif defined(__CC_ARM) && (__sizeof_ptr == 8)
#   define BIT_PLATFORM_PTR_SIZE 8
# else // Assume 32-bit pointers
#   if defined(BIT_COMPILER_HAS_PREPROCESSOR_WARNING)
#     warning "Pointer size undefined, assumed to be 4 bytes."
#     warning "If this is not correct, please define BIT_PLATFORM_PTR_SIZE manually"
#   elif defined(BIT_COMPILER_HAS_PRAGMA_MESSAGE)
#     pragma message("Pointer size undefined, assumed to be 4 bytes.")
#     pragma message("If this is not correct, please define BIT_PLATFORM_PTR_SIZE manually.")
#   endif
#   define BIT_PLATFORM_PTR_SIZE 4
# endif
#endif

//-----------------------------------------------------------------------------
// Platform word size
//-----------------------------------------------------------------------------

//! \def BIT_PLATFORM_WORD_SIZE
//!
//! The size of the platform word size (assumed to be the pointer size)
#ifndef BIT_PLATFORM_WORD_SIZE
# define BIT_PLATFORM_WORD_SIZE BIT_PLATFORM_PTR_SIZE
#endif

#endif /* BIT_STL_DETAIL_STDDEF_PLATFORM_HPP */
