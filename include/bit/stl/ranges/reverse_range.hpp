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
#ifndef BIT_STL_RANGES_REVERSE_RANGE_HPP
#define BIT_STL_RANGES_REVERSE_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "range.hpp" // range, make_range

#include <iterator> // std::reverse_iterator
#include <utility>  // std::forward

namespace bit {
  namespace stl {
    namespace detail {
      template<typename Range>
      using reverse_range_t = range<decltype(std::declval<Range&>().rbegin()),decltype(std::declval<Range&>().rend())>;
    } // namespace detail

    /// \brief A range that contains only reverse iterators
    template<typename Iterator, typename Sentinel = Iterator>
    using reverse_range = range<
      std::reverse_iterator<Iterator>,
      std::reverse_iterator<Sentinel>
    >;

    //-------------------------------------------------------------------------

    /// \brief Makes a reverse range from a given range
    ///
    /// \param range the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr detail::reverse_range_t<Range>
      make_reverse_range( Range&& range );

  } // namespace stl
} // namespace bit

#include "detail/reverse_range.inl"

#endif /* BIT_STL_RANGES_REVERSE_RANGE_HPP */
