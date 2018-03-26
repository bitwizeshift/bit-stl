/**
 * \file use_first.hpp
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
#ifndef BIT_STL_FUNCTIONAL_EXTRACTION_USE_FIRST_HPP
#define BIT_STL_FUNCTIONAL_EXTRACTION_USE_FIRST_HPP

#include "../../traits/composition/bool_constant.hpp"
#include "../../traits/composition/void_t.hpp"

#include <type_traits> // std::declval, std::enable_if_t
#include <utility>     // std::forward

namespace bit {
  namespace stl {

    struct use_first
    {
      template<typename Pair>
      constexpr decltype(auto) operator()( Pair&& pair );
    };

  } // namespace stl
} // namespace bit

template<typename Pair>
inline constexpr decltype(auto) bit::stl::use_first::operator()( Pair&& pair )
{
  using std::get;
  return get<0>(pair);
}

#endif /* BIT_STL_FUNCTIONAL_EXTRACTION_USE_FIRST_HPP */
