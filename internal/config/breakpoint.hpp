/**
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_INTERNAL_CONFIG_BREAKPOINT_HPP
#define BIT_STL_INTERNAL_CONFIG_BREAKPOINT_HPP

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

#endif /* BIT_STL_INTERNAL_CONFIG_BREAKPOINT_HPP */
