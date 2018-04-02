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

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "types.hpp"
#include "tuple_utilities.hpp"
#include "../traits/composition/size_constant.hpp"
#include "../traits/relationships/nth_type.hpp"

#include <tuple>   // for std::tuple

namespace bit {
  namespace stl {

    using ::std::tuple;
    using ::std::get;

    using ::std::tuple_cat;
    using ::std::make_tuple;
    using ::std::forward_as_tuple;

    template<typename...Ts>
    struct tuple_size<tuple<Ts...>> : size_constant<sizeof...(Ts)>{};

    template<size_t Idx, typename...Ts>
    struct tuple_element<Idx,tuple<Ts...>> : nth_type<Idx,Ts...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_TUPLE_HPP */
