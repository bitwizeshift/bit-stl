/**
 * \file is_same_volatility.hpp
 *
 * \brief This header defines a type-trait for detecting if a type has the same
 *        volatile qualifications
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_VOLATILITY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_VOLATILITY_HPP

#include "../bool_constant.hpp"

#include <type_traits> // std::is_volatile

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c T and \c U have the same volatile-
    ///        qualification
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same_volatility : bool_constant<
      (std::is_volatile<T>::value == std::is_volatile<U>::value)
    >{};

    /// \brief Helper utility to extract is_same_volatility::value
    template<typename T, typename U>
    constexpr bool is_same_volatility_v = is_same_volatility<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_VOLATILITY_HPP */
