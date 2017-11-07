/**
 * \file is_same_sign.hpp
 *
 * \brief This header defines a type-trait for detecting if a type is the same
 *        sign
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_SIGN_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_SIGN_HPP

#include "../bool_constant.hpp"

#include <type_traits> // std::is_signed, std::is_unsigned

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c T and \c U have the same sign
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same_sign : bool_constant<
      (std::is_signed<T>::value   == std::is_signed<U>::value)   &&
      (std::is_unsigned<T>::value == std::is_unsigned<U>::value)
    >{};

    /// \brief Helper utility to extract is_same_sign::value
    template<typename T, typename U>
    constexpr bool is_same_sign_v = is_same_sign<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_SIGN_HPP */
