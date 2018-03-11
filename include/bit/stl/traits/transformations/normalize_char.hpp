/**
 * \file normalize_char.hpp
 *
 * \brief This header contains utility metafunctions for normalizing characters
 *        to just the 'char' type
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
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_NORMALIZE_CHAR_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_NORMALIZE_CHAR_HPP

#include "../composition/identity.hpp"

namespace bit {
  namespace stl {

    /// \brief Normalizes character types T to non-signed/unsigned character
    ///        types
    ///
    /// The result is aliased as \t ::type
    ///
    /// \note The result is undefined for anything that is not a char-type
    template<typename T>
    struct normalize_char;

    template<>
    struct normalize_char<char> : identity<char>{};

    template<>
    struct normalize_char<signed char> : identity<char>{};

    template<>
    struct normalize_char<unsigned char> : identity<char>{};

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        normalize_char
    template<typename T>
    using normalize_char_t = typename normalize_char<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_NORMALIZE_CHAR_HPP */
