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
#ifndef BIT_STL_FUNCTIONAL_EXTRACTION_USE_SECOND_HPP
#define BIT_STL_FUNCTIONAL_EXTRACTION_USE_SECOND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../../utilities/tuple_utilities.hpp" // adl::get

#include <type_traits> // std::declval, std::enable_if_t
#include <utility>     // std::forward, get

namespace bit {
  namespace stl {

    struct use_second
    {
      template<typename Tuple>
      constexpr decltype(auto) operator()( Tuple&& tuple );
    };

  } // namespace stl
} // namespace bit

template<typename Tuple>
inline constexpr decltype(auto) bit::stl::use_second::operator()( Tuple&& tuple )
{
  using ::bit::stl::adl::get;

  return get<1>(tuple);
}

#endif /* BIT_STL_FUNCTIONAL_EXTRACTION_USE_SECOND_HPP */
