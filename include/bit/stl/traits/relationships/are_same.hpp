/**
 * \file are_same.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_ARE_SAME_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_ARE_SAME_HPP

#include "../bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

    template<typename T, typename...Ts>
    struct are_same : false_type{};

    template<typename T, typename...Ts>
    struct are_same<T,T,Ts...> : are_same<T,Ts...>{};

    template<typename T>
    struct are_same<T,T> : true_type{};

    template<typename T, typename...Ts>
    constexpr bool are_same_v = are_same<T,Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_ARE_SAME_HPP */
