/*****************************************************************************
 * \file
 * \brief This header defines a type-trait for extracting the \c nth type from
 *        a variadic pack
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_NTH_TYPE_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_NTH_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../composition/identity.hpp"

#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {

    /// \brief Type-trait for extracting the \c Ith type from a variadic pack
    ///
    /// The result is aliased as \c ::type
    template<std::size_t I, typename...Types>
    struct nth_type;

    template<std::size_t I, typename Type0, typename...Types>
    struct nth_type<I,Type0, Types...> : nth_type<I-1,Types...>{};

    template<>
    struct nth_type<0>{}; // SFINAE-disable type

    template<typename Type0, typename...Types>
    struct nth_type<0,Type0,Types...> : identity<Type0>{};

    /// \brief Helper utility to extract nth_type::type
    template<std::size_t I, typename...Types>
    using nth_type_t = typename nth_type<I,Types...>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_NTH_TYPE_HPP */
