/**
 * \file stddef.hpp
 *
 * \brief This header defines a standard set of both lexical and fixed-sized
 *        types.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_STDDEF_HPP
#define BIT_STL_UTILITIES_STDDEF_HPP

// std libraries
#include <cstdlib>

//! \def BIT_DEBUG
//! \brief Debug build
//!
//! \def BIT_UNIT_TEST
//! \brief Unit Test Build
#if !defined(BIT_DEBUG) && !defined(NDEBUG)
# define BIT_DEBUG     1
#endif

//! \def BIT_UNUSED
//!
//! \brief Explicitly marks a variable \p var as being unused within a given function.
//!
//! This is used to silence compiler warnings
//!
//! \param var the variable to explicitly mark as unused
#define BIT_UNUSED(var) (void)(var)

//! \def BIT_NOOP()
//! \brief Macro function indicating no operation will occur
#ifndef BIT_NOOP
# define BIT_NOOP() ((void)0)
#endif

/// \brief The parent namespace for all projects
namespace bit {

/// \brief The standard namespace for this project
///
/// Every class, free function, and sub-namespace will be defined inside
/// of this namespace.
namespace stl {

/// \brief Inline namespace for managing cast utilities
///
/// This allows for better granularity, so that simple casts can be imported
/// and used globally
inline namespace casts{} // namespace casts

/// \brief Inline namespace for managing literal operators
///
/// This follows the c++ standard's approach to literals by storing any
/// \c operator"" overloads in this namespace
inline namespace literals{} // namespace literals

/// \brief Private namespace for managing implementation-details within
///        headers
///
/// \internal
namespace detail{} // namespace detail

} // namespace stl
} // namespace bit

// bit::stl types
// IWYU pragma: begin_exports
#include "detail/stddef/types/integral_types.hpp"
#include "detail/stddef/types/char_types.hpp"
#include "detail/stddef/types/float_types.hpp"
#include "detail/stddef/macros.hpp"
#include "detail/stddef/platform.hpp"
#include "detail/stddef/compiler.hpp"
#include "detail/stddef/compiler_traits.hpp"
#include "detail/stddef/library_export.hpp"
#include "detail/stddef/breakpoint.hpp"
// IWYU pragma: end_exports

namespace bit {
  namespace stl {

    /// \brief An alias for lvalue-references to an array of N entries
    template<typename T, std::size_t N>
    using array_ref_t = T (&)[N];

    /// \brief An alias for rvalue-references to an array of N entries
    template<typename T, std::size_t N>
    using array_rref_t = T (&&)[N];

    namespace detail {

      template<typename Fn>
      struct function_t;

      template<typename R, typename...Args>
      struct function_t<R(Args...)> {
        using type = R(*)(Args...);
      };

#if __cplusplus >= 201703L
      template<typename R, typename...Args>
      struct function_t<R(Args...) noexcept> {
        using type = R(*)(Args...) noexcept;
      }
#endif

      //----------------------------------------------------------------------

      /// \brief
      template<typename T, typename R>
      struct member_function_t;

      template<typename T, typename R, typename...Args>
      struct member_function_t<T,R(Args...)> {
        using type = R(T::*)(Args...);
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const T,R(Args...)> {
        using type = R(T::*)(Args...) const;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<volatile T,R(Args...)> {
        using type = R(T::*)(Args...) volatile;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const volatile T,R(Args...)> {
        using type = R(T::*)(Args...) const volatile;
      };

#if __cplusplus >= 201703L
      template<typename T, typename R, typename...Args>
      struct member_function_t<T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) noexcept;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) const noexcept;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<volatile T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) volatile noexcept;
      };

      template<typename T, typename R, typename...Args>
      struct member_function_t<const volatile T,R(Args...) noexcept> {
        using type = R(T::*)(Args...) const volatile noexcept;
      };
#endif
    } // namespace detail

    /// \brief A type alias for member pointers to make it more readable.
    ///
    /// \note member_t is unable to deduce it's template parameters if
    ///       used in a deduction context.
    template<typename T, typename R>
    using member_t = R T::*;

    /// \brief A type alias for member function pointers to make it more
    ///        readable.
    ///
    /// \note member_function_t is unable to deduce it's template parameters
    ///       if used in a deduction context.
    template<typename T, typename Fn>
    using member_function_t = typename detail::member_function_t<T,Fn>::type;

    /// \brief A type alias for function pointers to make it more readable
    ///
    /// \note That function_t is unable to deduce it's template parameters
    ///       if used in a deduction context.
    template<typename Fn>
    using function_t = typename detail::function_t<Fn>::type;

    //--------------------------------------------------------------------------
    // System-Specific Lexical Types
    //--------------------------------------------------------------------------

    using word  = int;          ///< Signed instruction-sized integer (Word)
    using uword = unsigned int; ///< Unsigned instruction-sized integer (Word)

    //---------------------------------------------------------------------------

    using uchar     = unsigned char;  ///< Unsigned char type
    using ushort    = unsigned short; ///< Unsigned short type
    using uint      = unsigned int;   ///< Unsigned int type
    using ulong     = unsigned long;  ///< Unsigned long type
    using ulonglong = unsigned long long;

    //--------------------------------------------------------------------------

    using size_t  = std::size_t;    ///< Type representing size of objects
    using align_t = std::size_t;    ///< Type representing alignment of an object
    using index_t = std::ptrdiff_t; ///< Type representing index of objects
    using hash_t  = std::size_t;    ///< Type used for hashes

    //------------------------------------------------------------------------
    // Tag-Based Dispatching
    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief Constructor tag used to differentiate const type pointers from
    ///        fixed known type arrays at compile time.
    ///        (e.g. "const T* p" from "const T (&p)[N]")
    ///
    /// This is used primarily for methods that need to differentiate
    /// known string sizes from pointers at compile time -- but can be
    /// extended to any generic form of array/pointer
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT>
    struct const_type_wrapper final
    {
      constexpr const_type_wrapper( const CharT* ptr ) : ptr(ptr){}
      const CharT* ptr;
    };

    using const_char_wrapper   = const_type_wrapper<char>;     /// For ansi strings
    using const_wchar_wrapper  = const_type_wrapper<wchar_t>;  /// For wide strings
    using const_char16_wrapper = const_type_wrapper<char16_t>; /// For UTF16 strings
    using const_char32_wrapper = const_type_wrapper<char32_t>; /// For UTF32 strings
    using const_tchar_wrapper  = const_type_wrapper<tchar>;    /// For specified string types

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_STDDEF_HPP */
