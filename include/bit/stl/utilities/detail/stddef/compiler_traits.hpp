/**
 * \file compiler_traits.hpp
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_UTILITIES_DETAIL_STDDEF_COMPILER_TRAITS_HPP
#define BIT_STL_UTILITIES_DETAIL_STDDEF_COMPILER_TRAITS_HPP

//-----------------------------------------------------------------------------
// Clang detection mechanisms
//---------------------------------------------------------------------------==

//! \def __has_attribute
//!
//! \brief provides compatibility with non-clang compilers for the preprocessor
//!        method __has_attribute
#ifndef __has_attribute
# define __has_attribute(x) 0          // Compatibility with non-clang compilers
#endif

//! \def __has_builtin
//!
//! \brief provides compatibility with non-clang compilers for the preprocessor
//!        method __has_builtin
#ifndef __has_builtin
# define __has_builtin(x)   0          // Compatibility with non-clang compilers
#endif

//! \def __has_feature
//!
//! \brief provides compatibility with non-clang compilers for the preprocessor
//!        method __has_feature
#ifndef __has_feature
# define __has_feature(x)   0          // Compatibility with non-clang compilers.
#endif

//! \def __has_extension
//!
//! \brief provides compatibility with pre-3.0 clang compilers for the preprocessor
//!        method __has_extension
#ifndef __has_extension
# define __has_extension __has_feature // Compatibility with pre-3.0 compilers.
#endif

//---------------------------------------------------------------------------
// Standard C compatibility
//---------------------------------------------------------------------------

//! \def BIT_STANDARD_C_ANSI
//! \brief Compiler claims to support ANSI C
//!
//!
//! \def BIT_STANDARD_C94
//! \brief Compiler claims to support C94
//!
//!
//! \def BIT_STANDARD_C99
//! \brief Compiler claims to support C99
//!
//!
//! \def BIT_STANDARD_C11
//! \brief Compiler claims to support C11
#if defined(__STDC__)
# define BIT_STANDARD_C_ANSI 1
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L)
#    define BIT_STANDARD_C94   1
#  endif
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#    define BIT_STANDARD_C99   1
#  endif
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#    define BIT_STANDARD_C11   1
#  endif
#endif

//---------------------------------------------------------------------------
// Standard C++ compatibility
//---------------------------------------------------------------------------

//! \def BIT_STANDARD_CPLUSPLUS
//! \brief Compiler is a C++ compiler
//!
//! \def BIT_STANDARD_CPP97
//! \brief Compiler claims to support C++97 (This should always be true)
//!
//! \def BIT_STANDARD_CPP11
//! \brief Compiler claims to support C++11
//!
//! \def BIT_STANDARD_CPP14
//! \brief Compiler claims to support C++14
//!
//! \def BIT_STANDARD_CPP17
//! \brief Compiler claims to support C++17
#if defined(__cplusplus)
# define BIT_STANDARD_CPLUSPLUS 1
#  if (__cplusplus >= 199711L)
#    define BIT_STANDARD_CPP97   1
#  endif
#  if (__cplusplus >= 201103L)
#    define BIT_STANDARD_CPP11   1
#  endif
#  if (__cplusplus >= 201402L)
#    define BIT_STANDARD_CPP14   1
#  endif
#  if (__cplusplus >= 201703L)
#    define BIT_STANDARD_CPP17   1
#  endif
#endif

//! \def BIT_STANDARD_CPP_CLI
//!
//! \brief Compiler claims to support Microsoft C++ CLI standard
#if defined(__cplusplus_cli)
#  if(__cplusplus_cli >= 200406L)
#    define BIT_STANDARD_CPP_CLI 1
#  endif
#endif

//-----------------------------------------------------------------------------

//! \def BIT_DEPRECATED_FOR(f)
//!
//! \brief A utility macro for displaying a deprecated message, informing the user
//!        of the replacement for a deprecated method or function
//!
//! Example usage:
//! \code
//! BIT_DEPRECATED_FOR("bar") void foo(); // Function foo is deprecated, use "bar" instead
//! \endcode
//!
//!
//! \def BIT_UNAVAILABLE(maj,min)
//! \brief A utility macro fro displaying a deprecated message, with specifications
//!        for before a certain version number of the system
//!
//!
//! Example usage:
//! \code
//! BIT_UNAVAILABLE(1,3) void foo(); // Function foo is not available for version 1.3 of this engine
//! \endcode
#if BIT_COMPILER_HAS_CPP14_DEPRECATED
# define BIT_DEPRECATED_FOR(f)    [[deprecated("Use '" f "' instead")]]
# define BIT_UNAVAILABLE(maj,min) [[deprecated("Not available before " #maj "." #min)]]
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
# define BIT_DEPRECATED_FOR(f)    __attribute__((deprecated("Use '" f "' instead")))
# define BIT_UNAVAILABLE(maj,min) __attribute__((deprecated("Not available before " #maj "." #min)))
#elif _MSC_FULL_VER > 140050320
# define BIT_DEPRECATED_FOR(f)    __declspec(deprecated("is deprecated. Use '" f "' instead"))
# define BIT_UNAVAILABLE(maj,min) __declspec(deprecated("is not available before " #maj "." #min))
#else
# define BIT_DEPRECATED_FOR(f)    BIT_DEPRECATED
# define BIT_UNAVAILABLE(maj,min) BIT_DEPRECATED
#endif


//!
//! \def BIT_NO_RETURN
//! \brief signals to the compiler that execution never finishes in the function
//!
//! Example Usage:
//! \code
//! void BIT_NO_RETURN exit(int code);
//! \endcode
//!
#if BIT_COMPILER_HAS_CPP11_ATTRIBUTES
# define BIT_NO_RETURN [[noreturn]]
#elif defined(__GNUC__)
# define BIT_NO_RETURN __attribute__((__noreturn__))
#elif defined(_MSC_VER)
# define BIT_NO_RETURN __declspec(noreturn)
#else
# define BIT_NO_RETURN
#endif

//! \def BIT_UNREACHABLE()
//!
//! \brief Designates the code section immediately following this call to be
//!        never reached in the execution codepath, allowing for optimizations.
//!
//! This can be particularly useful when used in conjunction with
//! BIT_NO_RETURN, such as the following example:
//!
//! \code
//! void BIT_NO_RETURN no_return_function( /* params */ ){
//!   // Do something
//!   throw std::exception("Some exception");
//!   BIT_UNREACHABLE();
//! }
//! \endcode
#if defined(BIT_COMPILER_CLANG)
# define BIT_UNREACHABLE() __builtin_unreachable()
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)))
# define BIT_UNREACHABLE() __builtin_unreachable()
#elif defined(__MSC_VER)
# define BIT_UNREACHABLE() __assume(0)
#else
# define BIT_UNREACHABLE()
#endif


//! \def BIT_DEFAULT_UNREACHABLE()
//!
//! \brief Hint to the compiler that the default case is not reachable by normal
//!        execution path.
#define BIT_DEFAULT_UNREACHABLE() default: BIT_UNREACHABLE()


//! \def BIT_LIKELY(x)
//!
//! \brief Hint to the compiler that a code path is likely to be taken if the
//!        given condition is true
//!
//! \def BIT_UNLIKELY(x)
//!
//! \brief Hint to the compiler that a code path is unlikely to be taken if the
//!        given condition is true
#if defined(__GNUC__) && (__GNUC__ >= 3) || defined(__clang__)
# define BIT_LIKELY(x)   __builtin_expect(!!(x), 1)
# define BIT_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
# define BIT_LIKELY(x)   (x)
# define BIT_UNLIKELY(x) (x)
#endif


//! \def BIT_RETURN_NONNULL
//!
//! \brief signals to the compiler that the function never returns null
//!
//! Example Usage:
//! \code
//! void* BIT_RETURN_NONNULL safe_malloc( size_t n );
//! \endcode
#if defined(__GNUC__) || defined(__clang__)
# define BIT_RETURN_NONNULL __attribute__((returns_nonnull))
#else
# define BIT_RETURN_NONNULL
#endif


//! \def BIT_NODISCARD
//!
//! \brief Compiler hint to warn when a function's result is not used
//!
//! Example use:
//! \code
//! BIT_NODISCARD int foo();
//! ...
//! foo(); // <-- Generates warning to compiler
//! \endcode
#if __cplusplus >= 201703L
# define BIT_NODISCARD [[nodiscard]]
#elif defined(__GNUC__) || defined(__clang__)
# define BIT_NODISCARD __attribute__((warn_unused_result))
#else
# define BIT_NODISCARD
#endif

//! \def BIT_FORCE_INLINE
//!
//! \brief Forces the compiler to inline the code segment
//!
//! \code
//! BIT_FORCE_INLINE void do_something(){ ... }       // Compiler will inline
//! \endcode
#if defined(__GNUC__) || defined(__clang__)
# define BIT_FORCE_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER) || defined(__INTEL)
# define BIT_FORCE_INLINE __forceinline
#else
# define BIT_FORCE_INLINE inline
#endif


//! \def BIT_NO_INLINE
//!
//! \brief Forces the compiler to not inline a code segment
//!
//! \code
//! BIT_NO_INLINE void do_something_else(){ ... }  // Compiler will not inline
//! \endcode
#if defined(__GNUC__) || defined(__clang__)
# define BIT_NO_INLINE __attribute__((__noinline__))
#elif defined(_MSC_VER) || defined(__INTEL)
# define BIT_NO_INLINE __declspec(noinline)
#else
# define BIT_NO_INLINE
#endif

//! \def BIT_ASSUME(x)
//!
//! \brief Make compiler assume 'x'
//!
//! Implements VC++'s __assume, wrapped in a macro for portability.
//!
//! Example Usage:
//! \code
//! switch(var){
//!   case 1: ...; break;
//!   case 2: ...; break;
//!   default: BIT_ASSUME(0); // Default branch never reached
//! }
//! \endcode
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
# define BIT_ASSUME(x) __assume(x)
#else
# define BIT_ASSUME(x)
#endif


//! \def BIT_INIT_PRIORITY(x)
//!
//! \brief Constrol the construction order of elements
//!
//! GNU C++ allows users to control the order of initialization of objects
//! defined at namespace scope with the `init_priority' attribute by
//! specifying a relative PRIORITY, a constant integral expression currently
//! bounded between 101 and 65535 inclusive. Lower numbers indicate a higher
//! priority.
//!
//! On non GNU C++ compilers, this expands to nothing
#if defined(__GNUC__)
# define BIT_INIT_PRIORITY(x) __attribute__((init_priority(x)))
#else
# define BIT_INIT_PRIORITY(x)
#endif


//! \def BIT_CONSTRUCT_EARLY
//!
//! \brief Construct the element early.
//!
//! Linux has some cases where it may construct elements in a different order
//! than Windows. This forces higher priority to these elements, making them
//! construct in the proper order
#if defined(BIT_PLATFORM_LINUX)
# define BIT_CONSTRUCT_EARLY BIT_INIT_PRIORITY(0)
#else
# define BIT_CONSTRUCT_EARLY
#endif


//! \def BIT_RESTRICT
//! \brief expands to compiler-specific restrict statement
//!
//! The C99 standard defines the keyword restrict is a restrict that can be
//! used in pointer declarations. The restrict keyword is a declaration of
//! intent given by the programmer to the compiler. It says that for the lifetime
//! of the pointer, only it or a value directly derived from it
//! (such as pointer + 1) will be used to access the object to which it points.
//!
//! This keyword is not present in C++, but many compilers provide nonstandard
//! support for it
//!
//! Example Usage:
//! \code
//! void memcpy( void* BIT_RESTRICT to, const void* BIT_RESTRICT from, size_t size ); // Pointers are always relative to either 'to' or 'from'
//! \endcode
#if defined(BIT_COMPILER_CLANG)
# define BIT_RESTRICT __restrict__
#elif defined(BIT_COMPILER_GNUC) && (BIT_COMPILER_VERSION >= 3100)
# define BIT_RESTRICT __restrict__
#elif (defined(BIT_COMPILER_MSVC) && BIT_COMPILER_VERSION >= 1400) || defined(BIT_COMPILER_INTEL)
# define BIT_RESTRICT __restrict
#elif defined(BIT_STANDARD_C99)
# define BIT_RESTRICT restrict
#else
# define BIT_RESTRICT
#endif


//! \def BIT_ALLOCATED
//!
//! \brief Compiler hint that memory allocated from the marked function is
//!        treated as memory allocated from a call to malloc()
//!
//! From GCC's documentation:
//! > The malloc attribute is used to tell the compiler that a function may
//! > be treated as if any non-NULL pointer it returns cannot alias any other
//! > pointer valid when the function returns and that the memory has undefined
//! > content. This often improves optimization. Standard functions with this
//! > property include malloc and calloc. realloc-like functions do not have
//! > this property as the memory pointed to does not have undefined content.
//!
//! \see https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
#if defined(BIT_COMPILER_GNUC) || defined(BIT_COMPILER_CLANG)
# define BIT_ALLOCATED __attribute__((__malloc__))
#elif (defined(BIT_COMPILER_MSVC) && BIT_COMPILER_VERSION >= 1400)
# define BIT_ALLOCATED __declspec(restrict)
#else
# define BIT_ALLOCATED
#endif


//! \def BIT_NO_VTABLE
//!
//! \brief Tells the compiler not to create a virtual table as it is an incomplete
//!        class (Abstract class)
#if defined(_MSC_VER)
# define BIT_NO_VTABLE __declspec(novtable)
#else
# define BIT_NO_VTABLE
#endif


//! \def BIT_STDCALL
//!
//! \brief Macro for the calling convention used to call Win32 API functions.
//!
//! The callee cleans the stack, so the compiler makes vararg functions __cdecl.
//! Functions that use this calling convention require a function prototype.
#if defined( _WIN32 ) && !defined( _X360 )
# define BIT_STDCALL  __stdcall
#else
# define BIT_STDCALL
#endif


//! \def BIT_CDECL
//!
//! \brief Macro for the calling convention used to call DLL functions
//!
//! __cdecl is the default calling convention for C and C++ programs. Because
//! the stack is cleaned up by the caller, it can do vararg functions.
//! The __cdecl calling convention creates larger executables than __stdcall,
//! because it requires each function call to include stack cleanup code.
#if defined( _WIN32 )
# define BIT_CDECL __cdecl
#else
# define BIT_CDECL
#endif


//! \def BIT_FASTCALL
//!
//! \brief Macro for the calling fastcall convention, which specifies that arguments
//!        to functions are to be passed in registers, when possible.
//!
//! This calling convention only applies to the x86 architecture.
#if defined( _WIN32 ) && !defined( _X360 )
# define BIT_FASTCALL __fastcall
#else
# define BIT_FASTCALL
#endif

//! \def BIT_VECTORCALL
//!
//! \brief Macro for vector calling convention, which specifies that arguments
//!        to functions are to be passed in registers, when possible.
//!
//! This uses more registers for arguments than BIT_FASTCALL or the
//! default x64 calling convention use.
#if defined( _WIN32 ) && !defined( _X360 )
# define BIT_VECTORCALL __vectorcall
#else
# define BIT_VECTORCALL
#endif


//! \def BIT_FUNCTION_NAME
//!
//! \brief Expands to the name of the function this symbol is used in
#if (defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))) || (defined(__ICC) && BIT_COMPILER_VERSION >= 600)
# define BIT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
# define BIT_FUNCTION __FUNCSIG__
#elif defined(BIT_COMPILER_GNUC) || defined(BIT_COMPILER_MSVC) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 600)
# define BIT_FUNCTION __FUNCTION__
#elif defined (__sun) || defined(BIT_COMPILER_C99) || defined(BIT_COMPILER_CPP11)
# define BIT_FUNCTION __func__
#else
# define BIT_FUNCTION "no function info"
#endif


//! \def BIT_UNALIGNED
//!
//! \brief Creates a data-structure that is known to be unaligned
#if !defined(BIT_UNALIGNED)
#  if defined(_M_IA64) || defined(_M_AMD64)
#    define BIT_UNALIGNED __unaligned
#  else
#    define BIT_UNALIGNED
#  endif
#endif


//! \def BIT_DEPRECATED
//!
//! \brief Creates a compiler message when a function marked as deprecated is called
#ifdef BIT_COMPILER_HAS_CPP14_DEPRECATED
# define BIT_DEPRECATED [[deprecated]]
#elif defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
# define BIT_DEPRECATED   __attribute__((deprecated))
#elif defined(_MSC_VER) && (_MSC_VER >= 1300)
# define BIT_DEPRECATED   __declspec(deprecated)
#else
# define BIT_DEPRECATED
#endif

#ifdef BIT_COMPILER_HAS_CPP14_DEPRECATED
# define BIT_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#elif defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
# define BIT_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1300)
# define BIT_DEPRECATED_MSG(msg) __declspec(deprecated(msg))
#else
# define BIT_DEPRECATED_MSG(msg)
#endif


#endif /* BIT_STL_UTILITIES_DETAIL_STDDEF_COMPILER_TRAITS_HPP */
