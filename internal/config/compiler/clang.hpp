/**
 * \brief This header detects compiler-specific features for Clang c++
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_INTERNAL_CONFIG_COMPILER_CLANG_HPP
#define BIT_INTERNAL_CONFIG_COMPILER_CLANG_HPP

//-----------------------------------------------------------------------------
// Compiler Detection
//-----------------------------------------------------------------------------
#define BIT_COMPILER_CLANG    1
#define BIT_COMPILER_NAME     "Clang"
#define BIT_COMPILER_STRING   BIT_COMPILER_NAME " " BIT_STRINGIZE(__clang_major__) "." BIT_STRINGIZE(__clang_minor__)
#define BIT_COMPILER_VERSION  (__clang_major * 1000 + __clang_minor__ * 100 )

#if !defined(__EXCEPTIONS)
# define BIT_COMPILER_NO_EXCEPTIONS
#endif

#ifndef __has_extension
  #define __has_extension __has_feature // Compatibility with pre-3.0 compilers.
#endif

//-----------------------------------------------------------------------------
// C++11 Standards detection
//-----------------------------------------------------------------------------
#if defined(__cplusplus) && (__cplusplus >= 201103L)
#  if __has_extension(cxx_alignas)
#    define BIT_COMPILER_HAS_CPP11_ALIGN_AS         1
#  endif

#  if __has_extension(cxx_alignof)
#    define BIT_COMPILER_HAS_CPP11_ALIGN_OF         1
#  endif

#  if __has_extension(cxx_attributes)
#    define BIT_COMPILER_HAS_CPP11_ATTRIBUTES       1
#  endif

#  if __has_extension(cxx_constexpr)
#    define BIT_COMPILER_HAS_CPP11_CONSTEXPR        1
#  endif

#  if __has_extension(cxx_override_control)
#    define BIT_COMPILER_HAS_CPP11_FINAL            1
#  endif

#  if __has_extension(cxx_noexcept)
#    define BIT_COMPILER_HAS_CPP11_NOEXCEPT         1
#  endif

#  if __has_extension(cxx_nullptr)
#    define BIT_COMPILER_HAS_CPP11_NULLPTR          1
#  endif

#  if __has_extension(cxx_override_control)
#    define BIT_COMPILER_HAS_CPP11_OVERRIDE         1
#  endif

#  if __has_extension(cxx_static_assert)
#    define BIT_COMPILER_HAS_CPP11_STATIC_ASSERT    1
#  endif

#  if __has_feature(cxx_thread_local)
#    define BIT_COMPILER_HAS_CPP11_THREADS          1
#  endif

#  if __has_extension(cxx_variadic_templates)
#    define BIT_COMPILER_HAS_CPP11_VA_TEMPLATE      1
#  endif

#  if __has_extension(cxx_decltype)
#    define BIT_COMPILER_HAS_CPP11_DECLTYPE         1
#  endif
#endif // c++11

//-----------------------------------------------------------------------------
// C++ Type Traits Intrinsics Detection
//-----------------------------------------------------------------------------

// Clang has the __has_feature to poll for extensions
#if __has_feature(is_union)
#  define BIT_IS_UNION(T)                __is_union(T)
#endif
#if __has_feature(is_pod)
#  define BIT_IS_POD(T)                  __is_pod(T)
#endif
#if __has_feature(is_empty)
#  define BIT_IS_EMPTY(T)                __is_empty(T)
#endif
#if __has_feature(has_trivial_constructor)
#  define BIT_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#endif
#if __has_feature(has_trivial_copy)
#  define BIT_HAS_TRIVIAL_COPY(T)        __has_trivial_copy(T)
#endif
#if __has_feature(has_trivial_assign)
#  define BIT_HAS_TRIVIAL_ASSIGN(T)      __has_trivial_assign(T)
#endif
#if __has_feature(has_trivial_destructor)
#  define BIT_HAS_TRIVIAL_DESTRUCTOR(T)  __has_trivial_destructor(T)
#endif
#if __has_feature(has_nothrow_constructor)
#  define BIT_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#endif
#if __has_feature(has_nothrow_copy)
#  define BIT_HAS_NOTHROW_COPY(T)        __has_nothrow_copy(T)
#endif
#if __has_feature(has_nothrow_assign)
#  define BIT_HAS_NOTHROW_ASSIGN(T)      __has_nothrow_assign(T)
#endif
#if __has_feature(has_virtual_destructor)
#  define BIT_HAS_VIRTUAL_DESTRUCTOR(T)  __has_virtual_destructor(T)
#endif
#if __has_feature(is_abstract)
#  define BIT_IS_ABSTRACT(T)             __is_abstract(T)
#endif
#if __has_feature(is_base_of)
#  define BIT_IS_BASE_OF(T,U)            __is_base_of(T,U)
#endif
#if __has_feature(is_class)
#  define BIT_IS_CLASS(T)                __is_class(T)
#endif
#if __has_feature(is_convertible_to)
#  define BIT_IS_CONVERTIBLE(T,U)        __is_convertible_to(T,U)
#endif
#if __has_feature(is_enum)
#  define BIT_IS_ENUM(T)                 __is_enum(T)
#endif
#if __has_feature(is_polymorphic)
#  define BIT_IS_POLYMORPHIC(T)          __is_polymorphic(T)
#endif
#if __has_feature(has_trivial_move_constructor)
#  define BIT_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) __has_trivial_move_constructor(T)
#endif
#if __has_feature(has_trivial_move_assign)
#  define BIT_HAS_TRIVIAL_MOVE_ASSIGN(T)      __has_trivial_move_assign(T)
#endif
#if __has_feature(is_final)
#  define BIT_IS_FINAL(T)                     __is_final(T)
#endif

#define BIT_COMPILER_HAS_TYPE_TRAITS_INTRINSICS 1

//-----------------------------------------------------------------------------
// C++ Extensions Detections
//-----------------------------------------------------------------------------

#define BIT_COMPILER_ASM_STYLE_ATT 1

#if defined(__AVX__)
#  define BIT_PLATFORM_HAS_AVX    1
#endif
#if defined(__AVX2__)
#  define BIT_PLATFORM_HAS_AVX2   1
#endif
#if (defined(__SSE__) && __SSE__) || defined(__SSE_MATH__ )
#  define BIT_PLATFORM_HAS_SSE    1
#endif
#if defined(__SSE2__) || defined(__SSE2_MATH__ )
#  define BIT_PLATFORM_HAS_SSE2   1
#endif
#if defined(__SSE3__)
#  define BIT_PLATFORM_HAS_SSE3   1
#endif
#if defined(__SSE4_1__)
#  define BIT_PLATFORM_HAS_SSE4_1 1
#endif
#if defined(__SSE4_2__)
#  define BIT_PLATFORM_HAS_SSE4_2 1
#endif

#define BIT_COMPILER_HAS_LONG_LONG 1

#if defined(__SIZEOF_INT128__)
#  define BIT_COMPILER_HAS_INT128   1
#endif

#define BIT_WEAK __attribute__((weak))
#define BIT_COMPILER_WEAK_SUPPORTED 1


//----------------------------------------------------------------------------
// Symbol Import/Export (DLL/shared library)
//----------------------------------------------------------------------------

#define BIT_COMPILER_SYMBOL_EXPORT  __attribute__((visibility("default")))
#define BIT_COMPILER_SYMBOL_IMPORT
#define BIT_COMPILER_SYMBOL_VISIBLE __attribute__((visibility("default")))
#define BIT_COMPILER_SYMBOL_LOCAL   __attribute__((visibility("hidden")))

#endif /* BIT_INTERNAL_CONFIG_COMPILER_CLANG_HPP */
