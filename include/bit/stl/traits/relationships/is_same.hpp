/**
 * \file is_same.hpp
 *
 * \brief This header contains the relationship type-trait for determining if
 *        types are the same
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_HPP

#include "../composition/bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

    /// \brief Type trait to determine if two types are the same
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same : false_type{};

    template<typename T>
    struct is_same<T,T> : true_type{};

    /// \brief Helper utility to extract is_same::type
    template<typename T, typename U>
    constexpr bool is_same_v = is_same<T,U>::value;

    //-------------------------------------------------------------------------

    /// \brief Type-trait to determine that all types are the same type
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Ts>
    struct are_same : false_type{};

    template<typename T, typename...Ts>
    struct are_same<T,T,Ts...> : are_same<T,Ts...>{};

    template<typename T>
    struct are_same<T,T> : true_type{};

    /// \brief Helper utility to extract are_same::value
    template<typename T, typename...Ts>
    constexpr bool are_same_v = are_same<T,Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_HPP */
