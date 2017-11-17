/**
 * \file is_nothrow_copy_constructible.hpp
 *
 * \brief This header defines a type trait for checking nothrow
 *        copy-constructibilty
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_nothrow_copy_constructible

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is copy-constructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_nothrow_copy_constructible = std::is_nothrow_copy_constructible<T>;

    /// \brief Helper utility to extract is_nothrow_copy_constructible::type
    template<typename T>
    constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        copy-constructible
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_nothrow_copy_constructible : conjunction<is_nothrow_copy_constructible<Ts>...>{};

    /// \brief Helper utility to extract are_nothrow_copy_constructible::type
    template<typename...Ts>
    constexpr bool are_nothrow_copy_constructible_v = are_nothrow_copy_constructible<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP */
