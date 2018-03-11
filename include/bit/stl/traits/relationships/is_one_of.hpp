/**
 * \file is_one_of.hpp
 *
 * \brief This header defines a type-trait to determine if a given type is part
 *        of a variadic set
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_ONE_OF_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_ONE_OF_HPP

#include "../composition/bool_constant.hpp" // true_type, false_type

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c T is one of \c Ts
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Ts>
    struct is_one_of;

    template<typename T, typename T0, typename...Ts>
    struct is_one_of<T,T0,Ts...> : is_one_of<T,Ts...>{};

    template<typename T, typename...Ts>
    struct is_one_of<T,T,Ts...> : true_type{};

    template<typename T>
    struct is_one_of<T> : false_type{};

    /// \brief Helper utility to extract is_one_of::value
    template<typename T, typename...Ts>
    constexpr bool is_one_of_v = is_one_of<T,Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_ONE_OF_HPP */
