/**
 * \file is_same.hpp
 *
 * \brief This header contains the relationship type-trait for determining if
 *        types are the same
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_HPP

#include "../composition/bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

    /// \brief Type trait to determine if two types are the same
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same : false_type{};

    template<typename T>
    struct is_same<T,T> : true_type{};

    /// \brief Helper utility to extract is_same::type
    template<typename T, typename U>
    constexpr bool is_same_v = is_same<T,U>::value;

    //-------------------------------------------------------------------------

    /// \brief Type-trait to determine that all types are the same type
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Ts>
    struct are_same : false_type{};

    template<typename T, typename...Ts>
    struct are_same<T,T,Ts...> : are_same<T,Ts...>{};

    template<typename T>
    struct are_same<T,T> : true_type{};

    /// \brief Helper utility to extract are_same::value
    template<typename T, typename...Ts>
    constexpr bool are_same_v = are_same<T,Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_HPP */
