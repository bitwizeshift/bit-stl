/*****************************************************************************
 * \file
 * \brief This header contains utility extensions to the standard utility
 *        header
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
#ifndef BIT_STL_UTILITIES_TUPLE_HPP
#define BIT_STL_UTILITIES_TUPLE_HPP

#include <cstddef> // for std::size_t
#include <tuple>   // for std::tuple
#include <utility> // for std::forward

namespace bit {
  namespace stl {

  /// \brief Invoke the Callable object \p function with a \p tuple of
  ///        arguments
  ///
  /// \param function Callable object to be invoked
  /// \param tuple    tuple whose elements to be used as arguments to \p function
  /// \return the value returned from \p function
  template<typename Func, typename Tuple>
  constexpr decltype(auto) apply( Func&& function, Tuple&& tuple );

  /// \brief Construct an object of type \t T, using the elements of the
  ///        tuple t as the arguments to the constructor
  ///
  /// \param tuple tuple whose elements to be used as arguments to the constructor of T
  /// \return The constructed T object
  template<typename T, typename Tuple>
  constexpr T make_from_tuple( Tuple&& tuple );

  } // namespace stl
} // namespace bit

#include "detail/tuple.inl"

#endif /* BIT_STL_UTILITIES_TUPLE_HPP */
