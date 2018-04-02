/*****************************************************************************
 * \file
 * \brief This header contains the definition of a metafunction for extracting
 *        the base of a type without any qualifiers
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
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_BASE_TYPE_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_BASE_TYPE_HPP

#include "../composition/identity.hpp"

#include <type_traits> // std::decay_t

namespace bit {
  namespace stl {

    /// \brief Obtains the base type of T without modifiers
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct base_type : identity<std::decay_t<T>>{};

    template<typename T>
    struct base_type<T*> : base_type<std::decay_t<T>>{};

    template<typename T>
    struct base_type<T&> : base_type<std::decay_t<T>>{};

    template<typename T>
    struct base_type<T&&> : base_type<std::decay_t<T>>{};

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        base_type
    template<typename T>
    using base_type_t = typename base_type<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_BASE_TYPE_HPP */
