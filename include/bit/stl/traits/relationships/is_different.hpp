/*****************************************************************************
 * \file
 * \brief This header contains the relationship type-trait for determining if
 *        types are different
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
