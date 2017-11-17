/**
 * \file is_trivially_move_assignable.hpp
 *
 * \brief This header defines a type trait for checking trivially move
 *        assignability
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_trivially_move_assignable

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is trivially move-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_trivially_move_assignable = std::is_trivially_move_assignable<T>;

    /// \brief Helper utility to extract is_trivially_move_assignable::type
    template<typename T>
    constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        trivially move-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_trivially_move_assignable : conjunction<is_trivially_move_assignable<Ts>...>{};

    /// \brief Helper utility to extract are_trivially_move_assignable::type
    template<typename...Ts>
    constexpr bool are_trivially_move_assignable_v = are_trivially_move_assignable<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP */
