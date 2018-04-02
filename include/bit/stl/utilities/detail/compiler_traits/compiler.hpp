/*****************************************************************************
 * \file
 * \brief This header detects the appropriate compiler configuration based on
 *        the compiler's default defined macros
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
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

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

#include BIT_COMPILER_CONFIG_FILE // IWYU pragma: export

#if 0 // Used for dependency scanners to detect possible inclusions
#  include "compiler/intel.hpp"
#  include "compiler/clang.hpp"
#  include "compiler/msvc.hpp"
#  include "compiler/gcc.hpp"
#  include "compiler/generic.hpp"
#endif

#undef BIT_COMPILER_CONFIG_FILE

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_COMPILER_HPP */
