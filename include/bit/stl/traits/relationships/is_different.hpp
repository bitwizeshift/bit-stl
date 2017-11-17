/**
 * \file is_different.hpp
 *
 * \brief This header contains the relationship type-trait for determining if
 *        types are different
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_DIFFERENT_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_DIFFERENT_HPP

#include "../composition/bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

  /// \brief Type trait to determine if two types are different
  ///
  /// The result is aliased as \c ::value
  template<typename T, typename U>
  struct is_different : true_type{};

  template<typename T>
  struct is_different<T,T> : false_type{};

  /// \brief Helper utility to extract is_different::type
  template<typename T, typename U>
  constexpr bool is_different_v = is_different<T,U>::value;

  //-------------------------------------------------------------------------

  /// \brief Type-trait to determine that all types are different types
  ///
  /// \note This is not the same as negation<are_same<Ts...>>; this checks if
  ///       ALL types are unique
  ///
  /// The result is aliased as \c ::value
  template<typename T, typename...Ts>
  struct are_different : true_type{};

  template<typename T, typename...Ts>
  struct are_different<T,T,Ts...> : false_type{};

  template<typename T, typename U, typename...Ts>
  struct are_different<T,U,Ts...> : are_different<U,Ts...>{};

  /// \brief Helper utility to extract are_different::value
  template<typename T, typename...Ts>
  constexpr bool are_different_v = are_different<T,Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_DIFFERENT_HPP */
