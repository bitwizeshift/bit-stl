/**
 * \file is_destructible.hpp
 *
 * \brief This header defines a type trait for checking nothrow-destructibility
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_DESTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_DESTRUCTIBLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_nothrow_destructible

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is destructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_nothrow_destructible = std::is_nothrow_destructible<T>;

    /// \brief Helper utility to extract is_nothrow_destructible::type
    template<typename T>
    constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        destructible
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_nothrow_destructible : conjunction<is_nothrow_destructible<Ts>...>{};

    /// \brief Helper utility to extract are_nothrow_destructible::type
    template<typename...Ts>
    constexpr bool are_nothrow_destructible_v = are_nothrow_destructible<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_DESTRUCTIBLE_HPP */
