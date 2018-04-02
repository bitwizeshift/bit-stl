/*****************************************************************************
 * \file
 * \brief This header defines a type-trait for detecting if two types are the
 *        same after being decayed
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_DECAY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_DECAY_HPP

#include <type_traits> // std::is_same, std::decay_t

namespace bit {
  namespace stl {

    /// \brief Type trait to determine whether a type is the same with a different
    ///        decay type
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    using is_same_decay = std::is_same<std::decay_t<T>,std::decay_t<U>>;

    /// \brief Helper utility to extract is_same_decay::value
    template<typename T, typename U>
    constexpr bool is_same_decay_v = is_same_decay<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_DECAY_HPP */
