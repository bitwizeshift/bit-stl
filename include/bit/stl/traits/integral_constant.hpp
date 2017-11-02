/**
 * \file integral_constant.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_INTEGRAL_CONSTANT_HPP
#define BIT_STL_TRAITS_INTEGRAL_CONSTANT_HPP

#include <type_traits>

namespace bit {
  namespace stl {

    template<typename T, T V>
    using integral_constant = std::integral_constant<T,V>;

    template<typename T, T V>
    using integral_constant_t = typename integral_constant<T,V>::type;

    template<typename T, T V>
    constexpr T integral_constant_v = integral_constant<T,V>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_INTEGRAL_CONSTANT_HPP */