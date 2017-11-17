/**
 * \file is_copy_assignable.hpp
 *
 * \brief This header defines a type trait for checking copy assignability
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_COPY_ASSIGNABLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_COPY_ASSIGNABLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_copy_assignable

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is copy-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_copy_assignable = std::is_copy_assignable<T>;

    /// \brief Helper utility to extract is_copy_assignable::type
    template<typename T>
    constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        copy-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_copy_assignable : conjunction<is_copy_assignable<Ts>...>{};

    /// \brief Helper utility to extract are_copy_assignable::type
    template<typename...Ts>
    constexpr bool are_copy_assignable_v = are_copy_assignable<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_COPY_ASSIGNABLE_HPP */
