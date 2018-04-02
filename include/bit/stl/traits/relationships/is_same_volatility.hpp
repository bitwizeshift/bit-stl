/*****************************************************************************
 * \file
 * \brief This header defines a type-trait for detecting if a type has the same
 *        volatile qualifications
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_VOLATILITY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_VOLATILITY_HPP

#include "../composition/bool_constant.hpp"

#include <type_traits> // std::is_volatile

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c T and \c U have the same volatile-
    ///        qualification
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same_volatility : bool_constant<
      (std::is_volatile<T>::value == std::is_volatile<U>::value)
    >{};

    /// \brief Helper utility to extract is_same_volatility::value
    template<typename T, typename U>
    constexpr bool is_same_volatility_v = is_same_volatility<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_VOLATILITY_HPP */
