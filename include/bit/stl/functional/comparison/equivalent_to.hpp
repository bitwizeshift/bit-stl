/**
 * \file equivalent_to.hpp
 *
 * \brief TODO: Add description
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
#ifndef BIT_STL_FUNCTIONAL_EQUIVALENT_TO_HPP
#define BIT_STL_FUNCTIONAL_EQUIVALENT_TO_HPP

#include <utility> // std::forward

namespace bit {
  namespace stl {

    /// \brief Function object for performing equivalence using a
    ///        weakly-ordered comparisons.
    ///
    /// Effectively calls operator< on (lhs,rhs) and (rhs,lhs)
    struct equivalent_to
    {
      constexpr equivalent_to() = default;

      template<typename T, typename U>
      constexpr bool operator()( T&& lhs, U&& rhs )
      {
        return !compare( std::forward<T>(lhs), std::forward<U>(rhs) ) &&
               !compare( std::forward<U>(rhs), std::forward<T>(lhs) );
      }
    };

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_FUNCTIONAL_EQUIVALENT_TO_HPP */
