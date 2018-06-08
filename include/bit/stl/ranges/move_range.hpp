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
#ifndef BIT_STL_RANGES_MOVE_RANGE_HPP
#define BIT_STL_RANGES_MOVE_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "range.hpp" // range

#include <iterator> // std::move_iterator

namespace bit {
  namespace stl {

    template<typename Iterator, typename Sentinel>
    using move_range = range<std::move_iterator<Iterator>,std::move_iterator<Sentinel>>;

    //-------------------------------------------------------------------------

    /// \brief Makes a movable range from a given \p iterator \p sentinal pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename Iterator, typename Sentinel>
    constexpr move_range<Iterator,Sentinel>
      make_move_range( Iterator iterator, Sentinel sentinel );

    /// \brief Makes a reverse range from a given \p iterator \p sentinal pair
    ///
    /// \param irange the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr auto make_move_range( Range&& r )
      -> decltype(::bit::stl::make_move_range( r.begin(), r.end() ));

  } // namespace stl
} // namespace bit

#include "detail/move_range.inl"

#endif /* BIT_STL_RANGES_MOVE_RANGE_HPP */
