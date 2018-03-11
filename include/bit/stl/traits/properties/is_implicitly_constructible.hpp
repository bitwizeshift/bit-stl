/**
 * \file is_implicitly_constructible.hpp
 *
 * \brief This header contains the definitions for a type-trait that determines
 *        implicit constructibility
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

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
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_IMPLICITLY_CONSTRUCTIBLE_HPP

#include "../composition/bool_constant.hpp"
#include "../composition/type_list.hpp"
#include "../composition/void_t.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T>
      struct is_implicitly_constructible_dummy
      {
        static void test( T );
      };

      template<typename T, typename TypeList, typename = void>
      struct is_implicitly_constructible_impl : false_type{};

      template<typename T, typename...Args>
      struct is_implicitly_constructible_impl<T,type_list<Args...>,void_t<
        decltype( is_implicitly_constructible_dummy<T>::test({ std::declval<Args>()... }) )
      >> : true_type{};
    } // namespace detail

    /// \brief Type trait to determine if T is implicitly constructible with
    ///        braced initialization.
    ///
    /// \note Implicit construction is braced-initialization construction
    ///       without specifying the type being constructed. This means that
    ///       narrowing may occur if integral types are not matched correctly
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Args>
    struct is_implicitly_constructible
      : detail::is_implicitly_constructible_impl<T,type_list<Args...>>{};

    /// \brief Helper utility to extract is_implicitly_constructible::type
    template<typename T, typename...Args>
    constexpr bool is_implicitly_constructible_v = is_implicitly_constructible<T,Args...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_IMPLICITLY_CONSTRUCTIBLE_HPP */
