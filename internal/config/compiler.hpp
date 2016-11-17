/**
 * This header detects the appropriate compiler configuration based on the
 * compiler's default defined macros
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_INTERNAL_CONFIG_COMPILER_HPP
#define BIT_INTERNAL_CONFIG_COMPILER_HPP

//----------------------------------------------------------------------------
// Compiler Detection
//
//   Detects the compiler based on known predefined macros. It then defines
//   macros accordingly.
//----------------------------------------------------------------------------

#if defined(__ICL) || defined(__ICL) || defined(__ECC)
#  define BIT_COMPILER_CONFIG_FILE "compiler/intel.hpp"
#elif defined(__clang__)
#  define BIT_COMPILER_CONFIG_FILE "compiler/clang.hpp"
#elif defined(_MSVC_VER)
#  define BIT_COMPILER_CONFIG_FILE "compiler/msvc.hpp"
#elif defined(__GNUC__)
#  define BIT_COMPILER_CONFIG_FILE "compiler/gcc.hpp"
#elif defined(__BORLANDC__)
#  error "Borland C++ compiler is not supported due to incorrect handling of templates."
#else
#  define BIT_COMPILER_CONFIG_FILE "compiler/generic.hpp"
#endif

#include BIT_COMPILER_CONFIG_FILE

#if 0 // Used for dependency scanners to detect possible inclusions
#  include "compiler/intel.hpp"
#  include "compiler/clang.hpp"
#  include "compiler/msvc.hpp"
#  include "compiler/gcc.hpp"
#  include "compiler/generic.hpp"
#endif

#undef BIT_COMPILER_CONFIG_FILE

#endif /* BIT_INTERNAL_CONFIG_COMPILER_HPP */
