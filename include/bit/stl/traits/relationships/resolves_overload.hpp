/*****************************************************************************
 * \file
 * \brief This header defines a type trait for determining which type would
 *        be resolved when presented with parallel overloads
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
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
