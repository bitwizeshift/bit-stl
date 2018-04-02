/*****************************************************************************
 * \file
 * \brief TODO: Add description
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
#ifndef BIT_STL_CONCEPTS_EQUALITYCOMPARABLE_HPP
#define BIT_STL_CONCEPTS_EQUALITYCOMPARABLE_HPP

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
  namespace detail {

      template<typename T, typename = void>
      struct is_equality_comparable_impl : false_type{};

      template<typename T>
      struct is_equality_comparable_impl<T,
        void_t<
          decltype(bool(std::declval<const T&>() == std::declval<const T&>()))
        >
      > : true_type{};
    } // namespace detail

    /// \brief Type trait to determine if a given type is a EqualityComparable
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_equality_comparable : detail::is_equality_comparable_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all
    ///        EqualityComparable
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_equality_comparable : conjunction<is_equality_comparable<Types>...>{};
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_EQUALITYCOMPARABLE_HPP */
