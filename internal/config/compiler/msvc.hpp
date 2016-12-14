/**
 * \brief This header detects compiler-specific features for Microsoft
 *        Visual Studios
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_STL_INTERNAL_CONFIG_COMPILER_MSVC_HPP
#define BIT_STL_INTERNAL_CONFIG_COMPILER_MSVC_HPP

//-----------------------------------------------------------------------------
// Compiler Detection
//-----------------------------------------------------------------------------

#define BIT_COMPILER_MSVC    1
#define BIT_COMPILER_VERSION _MSC_FULL_VER
#define BIT_COMPILER_NAME    "Microsoft Visual C++"
#define BIT_COMPILER_STRING  BIT_COMPILER_NAME " " BIT_STRINGIZE(_MSC_VER)

//-----------------------------------------------------------------------------
// C++ Standards Detection
//-----------------------------------------------------------------------------

#if (_MSC_VER >= 1600)
#  define BIT_PLATFORM_HAS_STDINT_H 1
#endif

#if(_MSC_VER > 1200)
#  define BIT_COMPILER_HAS_INCLASS_MEMBER_INITIALIZATION 1
#endif

//-----------------------------------------------------------------------------

#if defined(__cplusplus) && (__cplusplus >= 201103L)
#  if(_MSC_VER >= 1600) // MSVC++ 10.00 (Visual Studio 2010)
#    define BIT_COMPILER_HAS_CPP11_RVALUE         1
#    define BIT_COMPILER_HAS_CPP11_STATIC_ASSERT  1
#    define BIT_COMPILER_HAS_CPP11_NULLPTR        1
#    define BIT_COMPILER_HAS_CPP11_DECLTYPE       1
#  endif
#  if(_MSC_VER >= 1700) // MSVC++ 11.00 (Visual Studio 2012)
#    define BIT_COMPILER_HAS_CPP11_ALIGNOF        1
#    define BIT_COMPILER_HAS_CPP11_OVERRIDE       1
#    define BIT_COMPILER_HAS_CPP11_FINAL          1
#  endif
#  if(_MSC_VER >= 1800) // MSVC++ 12.0 (Visual Studio 2013)
#    define BIT_COMPILER_HAS_CPP11_VA_TEMPLATE    1
#  endif
#  if(_MSC_VER >= 1900) // MSVC++ 14.0 (Visual Studio 2015)
#    define BIT_COMPILER_HAS_CPP11_CHAR16_T              1
#    define BIT_COMPILER_HAS_CPP11_CHAR32_T              1
#    define BIT_COMPILER_HAS_CPP11_CONSTEXPR             1
#    define BIT_COMPILER_HAS_CPP11_NOEXCEPT              1
#    define BIT_COMPILER_HAS_CPP11_UNICODE_LITERALS      1
#    define BIT_COMPILER_HAS_CPP11_ALIGNAS               1
#    define BIT_COMPILER_HAS_CPP11_USER_DEFINED_LITERALS 1
#  endif
#endif

//-----------------------------------------------------------------------------

// C++14 checks

//-----------------------------------------------------------------------------

// C++17 checks

//-----------------------------------------------------------------------------
// C++ Type Traits Intrinsics Detection
//-----------------------------------------------------------------------------

#if (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >=140050215))
#  define BIT_IS_UNION(T)                __is_union(T)
#  define BIT_IS_POD(T)                 (__is_pod(T) && __has_trivial_constructor(T))
#  define BIT_IS_EMPTY(T)                __is_empty(T)
#  define BIT_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  define BIT_HAS_TRIVIAL_COPY(T)        __has_trivial_copy(T)
#  define BIT_HAS_TRIVIAL_ASSIGN(T)      __has_trivial_assign(T)
#  define BIT_HAS_TRIVIAL_DESTRUCTOR(T)  __has_trivial_destructor(T)
#  define BIT_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#  define BIT_HAS_NOTHROW_COPY(T)        __has_nothrow_copy(T)
#  define BIT_HAS_NOTHROW_ASSIGN(T)      __has_nothrow_assign(T)
#  define BIT_HAS_VIRTUAL_DESTRUCTOR(T)  __has_virtual_destructor(T)

#  define BIT_IS_ABSTRACT(T)             __is_abstract(T)
#  define BIT_IS_BASE_OF(T,U)            __is_base_of(T,U) && !is_same<T,U>::value)
#  define BIT_IS_CLASS(T)                __is_class(T)
#  define BIT_IS_CONVERTIBLE(T,U)      ((__is_convertible_to(T,U) || (bit::is_same<T,U>::value && !bit::is_function<U>::value)) && !__is_abstract(U))
#  define BIT_IS_ENUM(T)                 __is_enum(T)

#  if defined(_MSC_VER) && (_MSC_VER >= 1700)
#    define BIT_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) ((__has_trivial_move_constructor(T) || __is_pod(T)) )
#    define BIT_HAS_TRIVIAL_MOVE_ASSIGN(T)      ((__has_trivial_move_assign(T) || __is_pod(T)))
#  endif
#  if _MSC_FULL_VER >= 180020827
#    define BIT_IS_NOTHROW_MOVE_ASSIGN(T)    (__is_nothrow_assignable(T&, T&&))
#    define BIT_IS_NOTHROW_MOVE_CONSTRUCT(T) (__is_nothrow_constructible(T, T&&))
#  endif
#  define BIT_COMPILER_HAS_TYPE_TRAITS_INTRINSICS 1
#endif

//-----------------------------------------------------------------------------
// C++ Extensions Detections
//-----------------------------------------------------------------------------

#define BIT_COMPILER_ASM_STYLE_INTEL 1

#if defined(__AVX__)
#  define BIT_PLATFORM_HAS_AVX  1
#endif
#if defined(__AVX2__)
#  define BIT_PLATFORM_HAS_AVX2 1
#endif
#if !defined(__NOSSE__) && defined(_M_IX86_FP)
#  if (_M_IX86_FP >= 1)
#    define BIT_PLATFORM_SSE  1
#  endif
#  if (_M_IX86_FP >= 2)
#    define BIT_PLATFORM_SSE2 1
#  endif
#  if (_M_IX86_FP >= 3)
#    define BIT_PLATFORM_SSE3 1
#  endif
#endif

#define BIT_PRAGMA(x)   __pragma(x)

#if (_MSC_VER >= 1300)
#  define BIT_WEAK __declspec(selectany)
#  define BIT_COMPILER_HAS_WEAK_ALIAS 1
#else
#  define BIT_WEAK
#  define BIT_COMPILER_HAS_WEAK_ALIAS 0
#endif

#if defined(_CPPUNWIND)
# define BIT_COMPILER_EXCEPTIONS_ENABLED 1
#endif

#if defined(_NATIVE_WCHAR_T_DEFINED)
#  define BIT_COMPILER_HAS_WCHAR_T
#endif

#if defined(_MSC_EXTENSIONS) || (_MSC_VER >= 1400)
#  define BIT_COMPILER_HAS_LONG_LONG                 1
#endif

// MSVC never has int128 defined, as of yet

//----------------------------------------------------------------------------
// Symbol Import/Export (DLL/shared library)
//----------------------------------------------------------------------------

// MSVC always uses declspec
#define BIT_COMPILER_HAS_DECLSPEC   1
#define BIT_COMPILER_SYMBOL_EXPORT  __declspec((dllexport))
#define BIT_COMPILER_SYMBOL_IMPORT  __declspec((dllimport))
#define BIT_COMPILER_SYMBOL_VISIBLE
#define BIT_COMPILER_SYMBOL_LOCAL

#endif /* BIT_STL_INTERNAL_CONFIG_COMPILER_MSVC_HPP */
