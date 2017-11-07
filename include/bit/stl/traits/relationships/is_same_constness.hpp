/**
 * \file is_same_constness.hpp
 *
 * \brief This header defines a type-trait for detecting if a type has the same
 *        constness
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CONSTNESS_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CONSTNESS_HPP

#include "../bool_constant.hpp"

#include <type_traits> // std::is_const

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c T and \c U have the same const-
    ///        qualification
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same_constness : bool_constant<
      (std::is_const<T>::value == std::is_const<U>::value)
    >{};

    /// \brief Helper utility to extract is_same_constness::value
    template<typename T, typename U>
    constexpr bool is_same_constness_v = is_same_constness<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CONSTNESS_HPP */
