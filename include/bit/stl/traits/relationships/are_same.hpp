/**
 * \file are_same.hpp
 *
 * \brief This header defines a type-trait for checking that all types are the
 *        same
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_ARE_SAME_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_ARE_SAME_HPP

#include "../bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

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

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_ARE_SAME_HPP */
