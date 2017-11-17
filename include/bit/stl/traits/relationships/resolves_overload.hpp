/**
 * \file resolves_overload.hpp
 *
 * \brief This header defines a type trait for determining which type would
 *        be resolved when presented with parallel overloads
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_RESOLVES_OVERLOAD_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_RESOLVES_OVERLOAD_HPP

#include "nth_type.hpp"

#include "../composition/size_constant.hpp"
#include "../composition/void_t.hpp"

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

    //-------------------------------------------------------------------------

    /// \brief Metafunction to determine the index of the type that would be
    ///        resolved if presented with Types... simultaneous overloads, and
    ///        presented with \c T
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam T the type to use for resolution
    /// \tparam Types... the types to test for resolution
    template<typename T, typename...Types>
    struct resolves_overload_index : detail::resolves_overload_index_impl<T,Types...>{};

    /// \brief Metafunction to determine the type that would be
    ///        resolved if presented with Types... simultaneous overloads, and
    ///        presented with \c T
    ///
    /// The result is aliased as \c ::type
    ///
    /// \tparam T the type to use for resolution
    /// \tparam Types... the types to test for resolution
    template<typename T, typename...Types>
    struct resolves_overload_type : nth_type<resolves_overload_index<T,Types...>::value,Types...>{};

    //-------------------------------------------------------------------------

    /// \brief Helper utility to extract resolves_overload_index::value
    template<typename T, typename...Types>
    constexpr std::size_t resolves_overload_index_v = resolves_overload_index<T,Types...>::value;

    /// \brief Helper utility to extract resolves_overload_type::type
    template<typename T, typename...Types>
    using resolved_overload_type_t = typename resolves_overload_type<T,Types...>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_RESOLVES_OVERLOAD_HPP */
