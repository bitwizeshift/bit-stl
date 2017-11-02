/**
 * \file is_same_cv.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CV_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CV_HPP

#include "../bool_constant.hpp"

#include <type_traits> // std::is_const std::is_volatile

namespace bit {
  namespace stl {

    template<typename T, typename U>
    struct is_same_volatility : bool_constant<
      (std::is_const<T>::value == std::is_const<U>::value) &&
      (std::is_volatile<T>::value == std::is_volatile<U>::value)
    >{};

    template<typename T, typename U>
    constexpr bool is_same_volatility_v = is_same_volatility<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CV_HPP */