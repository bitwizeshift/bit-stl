/**
 * \file is_nothrow_move_constructible.hpp
 *
 * \brief This header defines a type trait for checking nothrow
 *        move-constructibilty
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_nothrow_move_constructible

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is move-constructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_nothrow_move_constructible = std::is_nothrow_move_constructible<T>;

    /// \brief Helper utility to extract is_nothrow_move_constructible::type
    template<typename T>
    constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        move-constructible
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_nothrow_move_constructible : conjunction<is_nothrow_move_constructible<Ts>...>{};

    /// \brief Helper utility to extract are_nothrow_move_constructible::type
    template<typename...Ts>
    constexpr bool are_nothrow_move_constructible_v = are_nothrow_move_constructible<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP */
