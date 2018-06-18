/*****************************************************************************
 * \file
 * \brief This header is mostly taken from Microsoft's implementation of
 *        the GSL byte-type.
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
#ifndef BIT_STL_UTILITIES_BYTE_HPP
#define BIT_STL_UTILITIES_BYTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <type_traits> // std::is_integral, std::enable_if_t, etc

namespace bit {
  namespace stl {

    //=========================================================================
    // enum class : byte
    //=========================================================================

    /// \brief Unsigned byte type
    ///
    /// \note Due to a restriction in pre-C++-17, a conversion to a pointer of
    ///       byte types results in undefined behavior due to a violation of
    ///       strict-aliasing.
    enum class byte : unsigned char{};

    //=========================================================================
    // non-member operators : enum class : byte
    //=========================================================================

    //-------------------------------------------------------------------------
    // Operators
    //-------------------------------------------------------------------------

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    constexpr byte operator<<( byte lhs, IntT shift ) noexcept;

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    constexpr byte operator>>( byte lhs, IntT shift ) noexcept;

    constexpr byte operator|( byte lhs, byte rhs ) noexcept;
    constexpr byte operator&( byte lhs, byte rhs ) noexcept;
    constexpr byte operator^( byte lhs, byte rhs ) noexcept;
    constexpr byte operator~( byte lhs ) noexcept;

    //-------------------------------------------------------------------------
    // Compound Assignment Operators
    //-------------------------------------------------------------------------

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    constexpr byte& operator<<=( byte& lhs, IntT shift ) noexcept;

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    constexpr byte& operator>>=( byte& lhs, IntT shift ) noexcept;


    byte& operator|=( byte& lhs, byte rhs ) noexcept;
    byte& operator^=( byte& lhs, byte rhs ) noexcept;
    byte& operator&=( byte& lhs, byte rhs ) noexcept;
  } // namespace stl
} // namespace bit

#include "detail/byte.inl"

#endif /* BIT_STL_UTILITIES_BYTE_HPP */
