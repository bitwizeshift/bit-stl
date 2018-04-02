/*****************************************************************************
 * \file
 * \brief This internal header declares fixed size floating types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
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
#ifndef BIT_STL_UTILITIES_DETAIL_TYPES_FLOAT_TYPES_HPP
#define BIT_STL_UTILITIES_DETAIL_TYPES_FLOAT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Floating point types
    //
    // It is worth noting that float and double may not always be
    // IEEE-754 floats/doubles in which they are 32/64 bits respectively.
    //
    // However, there is rarely a case in which float will be practically less
    // than 32 bits, and having it larger than 32 bits should not pose a
    // problem.
    //------------------------------------------------------------------------

    using f32   = float;       ///< 32-bit floating point (single precision)
    using f64   = double;      ///< 64-bit floating point (double precision)
    using highp = long double; ///< High-precision floating point

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_TYPES_FLOAT_TYPES_HPP */
