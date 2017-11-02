/**
 * \file resolves_overload.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_RESOLVES_OVERLOAD_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_RESOLVES_OVERLOAD_HPP

#include "../size_constant.hpp"
#include "../void_t.hpp"
#include "../properties/nth_type.hpp"

#include <cstddef>     // std::size_t
#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<std::size_t I, typename...Types>
      struct resolves_overload_impl;

      // Intermediate case (other args)
      template<std::size_t I, typename T0, typename T1, typename...Types>
      struct resolves_overload_impl<I,T0,T1,Types...> : resolves_overload_impl<I+1,T1,Types...>
      {
        using resolves_overload_impl<I+1,T1,Types...>::operator();

        size_constant<I> operator()( T0 );
      };

      // Base-case (no other args)
      template<std::size_t I, typename T0>
      struct resolves_overload_impl<I,T0>
      {
        size_constant<I> operator()( T0 );
      };

      template<typename T, typename = void, typename...Types>
      struct resolves_overload_index_impl : size_constant<std::size_t(-1)>{};

      template<typename T, typename...Types>
      struct resolves_overload_index_impl<T,void_t<decltype( std::declval<resolves_overload_impl<0,Types...>>()( std::declval<T>() ) )>,Types...>
        : decltype( std::declval<resolves_overload_impl<0,Types...>>()( std::declval<T>() ) ){};

    } // namespace detail

    template<typename T, typename...Types>
    struct resolves_overload_index : detail::resolves_overload_index_impl<T,Types...>{};

    template<typename T, typename...Types>
    struct resolves_overload_type : nth_type<resolves_overload_index<T>::value,Types...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_RESOLVES_OVERLOAD_HPP */
