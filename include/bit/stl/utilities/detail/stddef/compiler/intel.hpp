/**
 * \file compiler/intel.hpp
 *
 * \brief This header detects compiler-specific features for Intel using either
 *        GCC or MSVC back-end.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_UTILITIES_DETAIL_STDDEF_COMPILER_INTEL_HPP
#define BIT_STL_UTILITIES_DETAIL_STDDEF_COMPILER_INTEL_HPP

//-----------------------------------------------------------------------------
// Compiler Detection
//-----------------------------------------------------------------------------

#define BIT_COMPILER_INTEL 1
#if defined(__ICL)
# define BIT_COMPILER_VERSION __ICL
#elif defined(__ICC)
# define BIT_COMPILER_VERSION __ICC
#else
# define BIT_COMPILER_VERSION __ECC
#endif
#define BIT_COMPILER_NAME    "Intel C++"
#define BIT_COMPILER_STRING BIT_COMPILER_NAME " " BIT_STRINGIZE(BIT_COMPILER_VERSION)

// Detect what OS the compiler is being used on (needed for proper declarations)
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
# define BIT_COMPILER_INTEL_WINDOWS 1
#else
# define BIT_COMPILER_INTEL_LINUX   1
#endif

// Intel provides a custom header, mkl.h, along with custom malloc method
// mkl_malloc/mkl_free that creates aligned allocations.
#define BIT_PLATFORM_HAS_MKL_H      1
#define BIT_PLATFORM_HAS_MKL_MALLOC 1

//-----------------------------------------------------------------------------
// C++ Standards Detection
//   Version numbers for detecting the various features were taken from
//   https://software.intel.com/en-us/articles/c0x-features-supported-by-intel-c-compiler/
//   https://software.intel.com/en-us/articles/c14-features-supported-by-intel-c-compiler/
//-----------------------------------------------------------------------------

#if (defined(_MSC_VER) && (_MSC_VER > 1200)) || defined(__GNUC__)
# define BIT_COMPILER_HAS_INCLASS_MEMBER_INITIALIZATION 1
#endif

#if (defined(_MSC_VER) && (_MSC_VER >= 1600)) || defined(__GNUC__)
# define BIT_PLATFORM_HAS_STDINT_H 1
#endif

//-----------------------------------------------------------------------------

// C++11 Detections
#if BIT_COMPILER_VERSION >= 1100 // Intel version 11.1
# define BIT_COMPILER_HAS_CPP11_STATIC_ASSERT   1
#endif

#if BIT_COMPILER_VERSION >= 1200 // Intel version 12.0
# define BIT_COMPILER_HAS_CPP11_RVALUE            1
# define BIT_COMPILER_HAS_CPP11_DEFAULT_FUNCTIONS 1
# define BIT_COMPILER_HAS_CPP11_DELETED_FUNCTIONS 1
#endif

#if BIT_COMPILER_VERSION >= 1210 // Intel version 12.1 (12 update 6)
# define BIT_COMPILER_HAS_CPP11_VA_TEMPLATE     1
# define BIT_COMPILER_HAS_CPP11_TEMPLATE_ALIAS  1
# define BIT_COMPILER_HAS_CPP11_NULLPTR         1
# define BIT_COMPILER_HAS_CPP11_ATTRIBUTES      1
  // Windows didn't support char16_t or char32_t definitions properly until later on
# if !(defined(_WIN32) || defined(_WIN64) || defined(WIN32))
#  define BIT_COMPILER_HAS_CPP11_CHAR16_T      1
#  define BIT_COMPILER_HAS_CPP11_CHAR32_T      1
# endif
#endif

#if BIT_COMPILER_VERSION >= 1300 // Intel version 13.0
# define BIT_COMPILER_HAS_CPP11_EXPLICIT_CAST   1
# define BIT_COMPILER_HAS_CPP11_RANGE_BASED_FOR 1
#endif

#if BIT_COMPILER_VERSION >= 1400 // Intel version 14.0
# define BIT_COMPILER_HAS_CPP11_DELEGATE_CONSTRUCTORS 1
# define BIT_COMPILER_HAS_CPP11_INLINE_NAMESPACE      1
# define BIT_COMPILER_HAS_CPP11_NOEXCEPT              1
# define BIT_COMPILER_HAS_CPP11_CONSTEXPR             1
# if !defined(BIT_COMPILER_HAS_CPP11_CHAR16_T)
#  define BIT_COMPILER_HAS_CPP11_CHAR16_T            1
# endif
# if !defined(BIT_COMPILER_HAS_CPP11_CHAR32_T)
#  define BIT_COMPILER_HAS_CPP11_CHAR32_T            1
# endif
#endif

#if BIT_COMPILER_VERSION >= 1500 // Intel version 15.0
# define BIT_COMPILER_HAS_CPP11_USER_DEFINED_LITERALS 1
# define BIT_COMPILER_HAS_CPP11_ALIGN_OF              1
# define BIT_COMPILER_HAS_CPP11_ALIGN_AS              1
#endif

//-----------------------------------------------------------------------------

// C++14 Detections

//-----------------------------------------------------------------------------
// C++ Type Traits Intrinsics Detection
//-----------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER >= 1500))
# define BIT_IS_UNION(T)                __is_union(T)
# define BIT_IS_POD(T)                 (__is_pod(T) && __has_trivial_constructor(T))
# define BIT_IS_EMPTY(T)                __is_empty(T)
# define BIT_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
# define BIT_HAS_TRIVIAL_COPY(T)        __has_trivial_copy(T)
# define BIT_HAS_TRIVIAL_ASSIGN(T)      __has_trivial_assign(T)
# define BIT_HAS_TRIVIAL_DESTRUCTOR(T)  __has_trivial_destructor(T)
# define BIT_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
# define BIT_HAS_NOTHROW_COPY(T)        __has_nothrow_copy(T)
# define BIT_HAS_NOTHROW_ASSIGN(T)      __has_nothrow_assign(T)
# define BIT_HAS_VIRTUAL_DESTRUCTOR(T)  __has_virtual_destructor(T)

# define BIT_IS_ABSTRACT(T)             __is_abstract(T)
# define BIT_IS_BASE_OF(T,U)            __is_base_of(T,U) && !is_same<T,U>::value)
# define BIT_IS_CLASS(T)                __is_class(T)
# define BIT_IS_CONVERTIBLE(T,U)      ((__is_convertible_to(T,U) || (::bit::is_same<T,U>::value && !::bit::is_function<U>::value)) && !__is_abstract(U))
# define BIT_IS_ENUM(T)                 __is_enum(T)

# if defined(_MSC_VER) && (_MSC_VER >= 1700)
#  define BIT_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) ((__has_trivial_move_constructor(T) || __is_pod(T)) )
#  define BIT_HAS_TRIVIAL_MOVE_ASSIGN(T)      ((__has_trivial_move_assign(T) || __is_pod(T)))
# endif
# if _MSC_FULL_VER >= 180020827
#  define BIT_IS_NOTHROW_MOVE_ASSIGN(T)    (__is_nothrow_assignable(T&, T&&))
#  define BIT_IS_NOTHROW_MOVE_CONSTRUCT(T) (__is_nothrow_constructible(T, T&&))
# endif
# define BIT_COMPILER_HAS_TYPE_TRAITS_INTRINSICS 1
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
# define BIT_IS_UNION(T)                 __is_union(T)
# define BIT_IS_POD(T)                   __is_pod(T)
# define BIT_IS_EMPTY(T)                 __is_empty(T)
# define BIT_HAS_TRIVIAL_CONSTRUCTOR(T) (__has_trivial_constructor(T) || __is_pod(T))
# define BIT_HAS_TRIVIAL_COPY(T)        (__has_trivial_copy(T) || __is_pod(T))
# define BIT_HAS_TRIVIAL_ASSIGN(T)      (__has_trivial_assign(T) || __is_pod(T))
# define BIT_HAS_TRIVIAL_DESTRUCTOR(T)  (__has_trivial_destructor(T) || __is_pod(T))
# define BIT_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) || __is_pod(T))
# define BIT_HAS_NOTHROW_COPY(T)        (__has_nothrow_copy(T) || __is_pod(T))
# define BIT_HAS_NOTHROW_ASSIGN(T)      (__has_nothrow_assign(T) || __is_pod(T))
# define BIT_HAS_VIRTUAL_DESTRUCTOR(T)   __has_virtual_destructor(T)

# define BIT_IS_ABSTRACT(T)              __is_abstract(T)
# define BIT_IS_BASE_OF(T,U)            (__is_base_of(T,U) && !::bit::is_same<T,U>::value)
# define BIT_IS_CLASS(T)                 __is_class(T)
# define BIT_IS_ENUM(T)                  __is_enum(T)
# define BIT_IS_POLYMORPHIC(T)           __is_polymorphic(T)
// For some reason, __is_final wasn't added until GCC 4.7
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))
#  define BIT_IS_FINAL(T) __is_final(T)
# endif
# define BIT_COMPILER_HAS_TYPE_TRAITS_INTRINSICS 1
#endif

//-----------------------------------------------------------------------------
// C++ Extensions Detections
//-----------------------------------------------------------------------------

#define BIT_COMPILER_ASM_STYLE_INTEL 1

#if defined(_MSC_VER) && (_MSC_VER >= 1300)
# define BIT_WEAK __declspec(selectany)
# define BIT_COMPILER_HAS_WEAK_ALIAS 1
#elif defined(GNUC)
# define BIT_WEAK __attribute__((weak))
# define BIT_COMPILER_HAS_WEAK_ALIAS 1
#else
# define BIT_WEAK
#endif

#if defined(BIT_PLATFORM_WINDOWS) && defined(BIT_PROCESSOR_X86) && !defined(__NOSSE__)
# define BIT_SSE 1
#else // GNUC
# if defined(__AVX__)
#  define BIT_PLATFORM_HAS_AVX    1
# endif
# if defined(__AVX2__)
#  define BIT_PLATFORM_HAS_AVX2   1
# endif
# if (defined(__SSE__) && __SSE__) || defined(__SSE_MATH__ )
#  define BIT_PLATFORM_HAS_SSE    1
# endif
# if defined(__SSE2__) || defined(__SSE2_MATH__ )
#  define BIT_PLATFORM_HAS_SSE2   1
# endif
# if defined(__SSE3__)
#  define BIT_PLATFORM_HAS_SSE3   1
# endif
# if defined(__SSE4_1__)
#  define BIT_PLATFORM_HAS_SSE4_1 1
# endif
# if defined(__SSE4_2__)
#  define BIT_PLATFORM_HAS_SSE4_2 1
# endif
#endif

#if BIT_COMPILER_VERSION >= 1100
# define BIT_COMPILER_HAS_LONG_LONG 1
#endif

#if defined(_NATIVE_WCHAR_T_DEFINED) || defined(__WCHAR_TYPE__)
# define BIT_COMPILER_HAS_WCHAR_T   1
#endif

#if defined(__LP64__) && defined(__GNUC__) && (BIT_COMPILER_VERSION >= 1310)
# define BIT_COMPILER_HAS_INT128    1
#endif

#ifdef __GNUC__
# ifdef __EXCEPTIONS
#   define BIT_COMPILER_EXCEPTIONS_ENABLED 1
# else
#   define BIT_COMPILER_EXCEPTIONS_ENABLED 0
# endif
#else
# if defined(_CPPUNWIND)
#   define BIT_COMPILER_EXCEPTIONS_ENABLED 1
# else
#   define BIT_COMPILER_EXCEPTIONS_ENABLED 0
# endif
#endif

//-----------------------------------------------------------------------------
// Symbol Import/Export (DLL/shared library)
//-----------------------------------------------------------------------------

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
# define BIT_COMPILER_HAS_DECLSPEC   1
# define BIT_COMPILER_SYMBOL_EXPORT  __declspec((dllexport))
# define BIT_COMPILER_SYMBOL_IMPORT  __declspec((dllimport))
# define BIT_COMPILER_SYMBOL_VISIBLE
# define BIT_COMPILER_SYMBOL_LOCAL
#elif (__GNUC__ >= 4) // gcc 4.0+ allows visibility("hidden")
# define BIT_COMPILER_SYMBOL_EXPORT  __attribute__((visibility("default")))
# define BIT_COMPILER_SYMBOL_IMPORT
# define BIT_COMPILER_SYMBOL_VISIBLE __attribute__((visibility("default")))
# define BIT_COMPILER_SYMBOL_LOCAL   __attribute__((visibility("hidden")))
#else
# define BIT_COMPILER_SYMBOL_EXPORT  __attribute__((dllexport))
# define BIT_COMPILER_SYMBOL_IMPORT  __attribute__((dllimport))
# define BIT_COMPILER_SYMBOL_VISIBLE
# define BIT_COMPILER_SYMBOL_LOCAL
#endif

#endif /* BIT_STL_UTILITIES_DETAIL_STDDEF_COMPILER_INTEL_HPP */
