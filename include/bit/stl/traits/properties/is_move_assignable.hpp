/**
 * \file is_move_assignable.hpp
 *
 * \brief This header defines a type trait for checking move assignability
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_MOVE_ASSIGNABLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_MOVE_ASSIGNABLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_move_assignable

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is move-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_move_assignable = std::is_move_assignable<T>;

    /// \brief Helper utility to extract is_move_assignable::type
    template<typename T>
    constexpr bool is_move_assignable_v = is_move_assignable<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        move-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_move_assignable : conjunction<is_move_assignable<Ts>...>{};

    /// \brief Helper utility to extract are_move_assignable::type
    template<typename...Ts>
    constexpr bool are_move_assignable_v = are_move_assignable<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_MOVE_ASSIGNABLE_HPP */
