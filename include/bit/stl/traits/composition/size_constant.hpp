/**
 * \file size_constant.hpp
 *
 * \brief This header contains the definition to the utility metafunction
 *        size_constant
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
#ifndef BIT_STL_TRAITS_COMPOSITION_SIZE_CONSTANT_HPP
#define BIT_STL_TRAITS_COMPOSITION_SIZE_CONSTANT_HPP

#include "integral_constant.hpp"
#include "bool_constant.hpp"

#include <cstddef> // std::size_t

namespace bit {
  namespace stl {

    /// \brief This utility metafunction provides compile-time size values
    ///        as an integral constant
    ///
    /// The value is aliased as \c ::value
    template<std::size_t Size>
    using size_constant = std::integral_constant<std::size_t,Size>;

    /// \brief Convenience template variable to extract size_constant::value
    ///
    /// This is always the same as the template variable (trivial)
    template<std::size_t Size>
    constexpr std::size_t size_constant_v = size_constant<Size>::value;

    //-------------------------------------------------------------------------

    /// \brief Utility metafunction that determines whether \p T is a
    ///        size_constant
    ///
    /// \tparam T the type to check
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_size_constant : false_type{};

    template<std::size_t Size>
    struct is_size_constant<size_constant<Size>> : true_type{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_SIZE_CONSTANT_HPP */
