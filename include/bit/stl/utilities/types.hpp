/**
 * \file types.hpp
 *
 * \brief This header contains aliases for fundamental types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_TYPES_HPP
#define BIT_STL_UTILITIES_TYPES_HPP

// IWYU pragma: begin_exports
#include "detail/types/integral_types.hpp"
#include "detail/types/char_types.hpp"
#include "detail/types/float_types.hpp"
// IWYU pragma: end_exports

#include <cstddef> // std::ptrdiff_t, std::size_t

/// \brief The parent namespace for all projects
namespace bit {

  /// \brief The standard namespace for this project
  ///
  /// Every class, free function, and sub-namespace will be defined inside
  /// of this namespace.
  namespace stl {

    /// \brief Inline namespace for managing cast utilities
    ///
    /// This allows for better granularity, so that simple casts can be
    /// imported and used globally
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

    //-------------------------------------------------------------------------
    // System-Specific Lexical Types
    //-------------------------------------------------------------------------

    using word  = int;          ///< Signed instruction-sized integer (Word)
    using uword = unsigned int; ///< Unsigned instruction-sized integer (Word)

    //-------------------------------------------------------------------------

    using uchar     = unsigned char;  ///< Unsigned char type
    using ushort    = unsigned short; ///< Unsigned short type
    using uint      = unsigned int;   ///< Unsigned int type
    using ulong     = unsigned long;  ///< Unsigned long type
    using ulonglong = unsigned long long;

    //-------------------------------------------------------------------------

    using size_t  = std::size_t;    ///< Type representing size of objects
    using align_t = std::size_t;    ///< Type representing alignment of an object
    using index_t = std::ptrdiff_t; ///< Type representing index of objects
    using hash_t  = std::size_t;    ///< Type used for hashes

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

      //-----------------------------------------------------------------------

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

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_TYPES_HPP */
