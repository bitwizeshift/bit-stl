/**
 * \file
 * \brief This header contains the bitwise XOR functor
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
#ifndef BIT_STL_FUNCTIONAL_BITWISE_BIT_XOR_HPP
#define BIT_STL_FUNCTIONAL_BITWISE_BIT_XOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <utility> // std::forward

namespace bit {
  namespace stl {

    /// \brief Function object for performing bitwise xor.
    ///        Effectively calls operator^ on type T.
    struct bit_or
    {
      template<typename T, typename U>
      constexpr auto operator()( T&& lhs, U&& rhs ) const noexcept
        -> decltype( std::forward<T>(lhs) ^ std::forward<U>(rhs) );
    };
  } // namespace stl
} // namespace bit

template<typename T, typename U>
inline constexpr auto bit::stl::bit_or::operator()( T&& lhs, U&& rhs )
  const noexcept
  -> decltype( std::forward<T>(lhs) ^ std::forward<U>(rhs) )
{
  return std::forward<T>(lhs) ^ std::forward<U>(rhs);
}



#endif /* BIT_STL_FUNCTIONAL_BITWISE_BIT_XOR_HPP */
