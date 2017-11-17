/**
 * \file is_destructible.hpp
 *
 * \brief This header defines a type trait for checking trivially-destructibility
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_trivially_destructible

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is destructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_trivially_destructible = std::is_trivially_destructible<T>;

    /// \brief Helper utility to extract is_trivially_destructible::type
    template<typename T>
    constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        destructible
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_trivially_destructible : conjunction<is_trivially_destructible<Ts>...>{};

    /// \brief Helper utility to extract are_trivially_destructible::type
    template<typename...Ts>
    constexpr bool are_trivially_destructible_v = are_trivially_destructible<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_DESTRUCTIBLE_HPP */