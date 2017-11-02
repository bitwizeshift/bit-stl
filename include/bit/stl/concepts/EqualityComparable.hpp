/**
 * \file EqualityComparable.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_EQUALITYCOMPARABLE_HPP
#define BIT_STL_CONCEPTS_EQUALITYCOMPARABLE_HPP

#include "../traits/void_t.hpp"
#include "../traits/bool_constant.hpp"
#include "../traits/conjunction.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
  namespace detail {

      template<typename T, typename = void>
      struct is_equality_comparable_impl : false_type{};

      template<typename T>
      struct is_equality_comparable_impl<T,
        void_t<
          decltype(bool(std::declval<const T&>() == std::declval<const T&>()))
        >
      > : true_type{};
    } // namespace detail

    /// \brief Type trait to determine if a given type is a EqualityComparable
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_equality_comparable : detail::is_equality_comparable_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all
    ///        EqualityComparable
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_equality_comparable : conjunction<is_equality_comparable<Types>...>{};
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_EQUALITYCOMPARABLE_HPP */
