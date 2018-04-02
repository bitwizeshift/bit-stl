/*****************************************************************************
 * \file
 * \brief This header contains the definitions for a type-trait that determines
 *        explicit constructibility
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
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONSTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONSTRUCTIBLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../composition/bool_constant.hpp"
#include "../composition/type_list.hpp"
#include "../composition/void_t.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename TypeList, typename = void>
      struct is_explicitly_constructible_impl : std::false_type {};

      template<typename T, typename...Args>
      struct is_explicitly_constructible_impl<T,type_list<Args...>,void_t<
        decltype(T(std::declval<Args>()...))
      >> : true_type{};

    } // namespace detail

    /// \brief Type trait to determine whether a type is explicitly
    ///        constructible from a given set of arguments
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Args>
    struct is_explicitly_constructible
      : detail::is_explicitly_constructible_impl<T, type_list<Args...>>{};

    /// \brief Helper utility to extract is_explicitly_constructible::type
    template<typename T, typename...Args>
    constexpr bool is_explicitly_constructible_v = is_explicitly_constructible<T,Args...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONSTRUCTIBLE_HPP */
