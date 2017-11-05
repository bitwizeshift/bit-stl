/**
 * \file is_one_of.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_ONE_OF_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_ONE_OF_HPP

#include "../bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

    template<typename T, typename...Ts>
    struct is_one_of;

    template<typename T, typename T0, typename...Ts>
    struct is_one_of<T,T0,Ts...> : is_one_of<T,Ts...>{};

    template<typename T, typename...Ts>
    struct is_one_of<T,T,Ts...> : true_type{};

    template<typename T>
    struct is_one_of<T> : false_type{};

    template<typename T, typename...Ts>
    constexpr bool is_one_of_v = is_one_of<T,Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_ONE_OF_HPP */
