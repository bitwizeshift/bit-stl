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
#ifndef BIT_STL_RANGES_ZIP_RANGE_HPP
#define BIT_STL_RANGES_ZIP_RANGE_HPP

#include "range.hpp" // range

#include "../iterators/zip_iterator.hpp" // zip_iterator

#include <type_traits> // std::declval

namespace bit {
  namespace stl {

    template<typename...Iterators>
    using zip_range = range<
      zip_iterator<Iterators>...,
      zip_iterator<Iterators>...
    >;

    //-------------------------------------------------------------------------

    /// \brief Makes a zip range from a selection of zip iterators
    ///
    /// \param r0 the first range entry
    /// \param rn the rest of the range entries
    /// \return the type-deduced range
    template<typename Range0, typename...RangeN>
    constexpr auto make_zip_range( Range0&& r0, RangeN&&...rn )
      -> range<zip_iterator<decltype( r0.begin() ), decltype( rn.begin() )...>,
               zip_iterator<decltype( r0.end() ), decltype( rn.end() )...>>;

  } // namespace stl
} // namespace bit

#include "detail/zip_range.inl"

#endif /* BIT_STL_RANGES_ZIP_RANGE_HPP */
