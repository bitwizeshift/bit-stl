/*****************************************************************************
 * \file
 * \brief This header defines a type-trait to determine the index of a type in
 *        a variadic pack
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_INDEX_OF_TYPE_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_INDEX_OF_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../composition/size_constant.hpp"

#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {
    namespace detail {
      template<std::size_t I, typename T, typename...Types>
      struct index_of_type_impl;

      template<std::size_t I, typename T, typename Type0, typename...Types>
      struct index_of_type_impl<I,T,Type0,Types...>
        : index_of_type_impl<I+1,T,Types...>{};

      template<std::size_t I, typename T, typename...Types>
      struct index_of_type_impl<I,T,T,Types...> : size_constant<I>{};

    } // namespace detail

    /// \brief Type trait to determine the index of \c T in the variadic pack
    ///        \c Types
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Types>
    struct index_of_type : detail::index_of_type_impl<0,T,Types...>{};

    /// \brief Helper utility to extract index_of_type::value
    template<typename T, typename...Types>
    constexpr std::size_t index_of_type_v = index_of_type<T,Types...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_INDEX_OF_TYPE_HPP */
