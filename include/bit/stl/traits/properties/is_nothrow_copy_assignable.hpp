/*****************************************************************************
 * \file
 * \brief This header defines a type trait for checking nothrow copy
 *        assignability
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
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_COPY_ASSIGNABLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_COPY_ASSIGNABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_nothrow_copy_assignable

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is nothrow copy-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_nothrow_copy_assignable = std::is_nothrow_copy_assignable<T>;

    /// \brief Helper utility to extract is_nothrow_copy_assignable::type
    template<typename T>
    constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Type trait for determining if a set of types are all
    ///        nothrow copy-assignable
    ///
    /// The result is aliased as \c ::value
    template<typename...Ts>
    struct are_nothrow_copy_assignable : conjunction<is_nothrow_copy_assignable<Ts>...>{};

    /// \brief Helper utility to extract are_nothrow_copy_assignable::type
    template<typename...Ts>
    constexpr bool are_nothrow_copy_assignable_v = are_nothrow_copy_assignable<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_COPY_ASSIGNABLE_HPP */
