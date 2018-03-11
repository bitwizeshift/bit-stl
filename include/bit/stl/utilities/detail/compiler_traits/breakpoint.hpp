/**
 * \file breakpoint.hpp
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
#ifndef BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_BREAKPOINT_HPP
#define BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_BREAKPOINT_HPP

//! \def BIT_BREAKPOINT
//!
//! \brief Create breakpoint to halt code execution.
//!
//! This symbol can be redefined by the user by defining it before including any
//! library functions. This allows breakpoints to function differently if a user
//! specifies it to, and provides easier portability to other systems.
#ifndef BIT_BREAKPOINT
#  if !defined(BIT_DEBUG)
#    define BIT_BREAKPOINT() BIT_NOOP()      // Breakpoints only exist in debug
#  elif defined(_MSC_VER) && (_MSC_VER >= 1300)
#    define BIT_BREAKPOINT() __debugbreak()   // MSVC-specific breakpoint
#  elif (defined(__clang__) || defined(__GNUC__)) // && (defined(BIT_PLATFORM_POSIX) || defined(BIT_PLATFORM_APPLE))
#    define BIT_BREAKPOINT() __builtin_trap() // __builtin_trap for compilers that support it
#  elif (BIT_PROCESSOR_X86 || BIT_PROCESSOR_X86_64) && defined(BIT_COMPILER_ASM_STYLE_ATT)
#    define BIT_BREAKPOINT() asm("int3")      // int3 is breakpoint for x86 processors
#  elif (BIT_PROCESSOR_X86 || BIT_PROCESSOR_X86_64) && defined(BIT_COMPILER_ASM_STYLE_INTEL)
#    define BIT_BREAKPOINT() { __asm int 3 }  // int3 is breakpoint for x86 processors
#  elif defined(BIT_PROCESSOR_POWERPC)
#    define BIT_BREAKPOINT() asm(".long 0")   // Triggers exception on PowerPC
#  else // Backup option for breakpoint creation
#    include <signal.h>
#    if defined(BIT_PLATFORM_WINDOWS)
#      define BIT_BREAKPOINT() raise(SIGABRT) // Windows signal doesn't support SIGTRAP, so best to abort
#    else
#      define BIT_BREAKPOINT() raise(SIGTRAP) // Resort to sigtrap in all other cases
#    endif
#  endif
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_COMPILER_TRAITS_BREAKPOINT_HPP */
