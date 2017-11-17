/**
 * \file is_default_constructible.hpp
 *
 * \brief This header defines a type trait for checking default constructibilty
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_default_constructible

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is default-constructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_default_constructible = std::is_default_constructible<T>;

    /// \brief Helper utility to extract is_default_constructible::type
    template<typename T>
    constexpr bool is_default_constructible_v = is_default_constructible<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        default-constructible
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_default_constructible : conjunction<is_default_constructible<Ts>...>{};

    /// \brief Helper utility to extract are_default_constructible::type
    template<typename...Ts>
    constexpr bool are_default_constructible_v = are_default_constructible<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_DEFAULT_CONSTRUCTIBLE_HPP */
