/**
 * \file is_explicitly_convertible.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP

#include "../negation.hpp"
#include "../conjunction.hpp"

#include <type_traits> // is_constructible, is_convertible

namespace bit {
  namespace stl {

    template<typename T, typename U>
    struct is_explicitly_convertible :
      conjunction<std::is_constructible<U,T>, negation<std::is_convertible<T,U>>>
    {};

    template<typename T, typename U>
    constexpr bool is_explicitly_convertible_v = is_explicitly_convertible<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP */
