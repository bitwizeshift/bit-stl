/*****************************************************************************
 * \file
 * \brief This header contains the definitions for the utility type-tags,
 *        in_place
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
#ifndef BIT_STL_UTILITIES_IN_PLACE_HPP
#define BIT_STL_UTILITIES_IN_PLACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <type_traits> // std::true_type, std::false_type

namespace bit {
  namespace stl {

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    struct in_place_t
    {
      explicit in_place_t() = default;
    };
    constexpr in_place_t in_place{};

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<typename T>
    struct in_place_type_t
    {
        explicit in_place_type_t() = default;
    };
    template<typename T>
    constexpr in_place_type_t<T> in_place_type{};


    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<std::size_t I> struct in_place_index_t
    {
      explicit in_place_index_t() = default;
    };

    template<std::size_t I>
    constexpr in_place_index_t<I> in_place_index{};

    //-------------------------------------------------------------------------

    /// \brief Type-trait to determine if the type is an in_place type
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_in_place : std::false_type{};

    template<>
    struct is_in_place<in_place_t> : std::true_type{};

    template<typename T>
    struct is_in_place<in_place_type_t<T>> : std::true_type{};

    template<std::size_t I>
    struct is_in_place<in_place_index_t<I>> : std::true_type{};

    template<typename T>
    constexpr bool is_in_place_v = is_in_place<T>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_IN_PLACE_HPP */
