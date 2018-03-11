/**
 * \file string.hpp
 *
 * \brief This header contains extension to the standard C++ char_traits
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
#ifndef BIT_STL_CONTAINERS_STRING_HPP
#define BIT_STL_CONTAINERS_STRING_HPP

#include "detail/string_hash.hpp"

#include <string> // std::char_traits
#include <locale> // std::toupper<CharT>

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Char Traits
    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief Char traits to allow case-insensitive comparisons for strings
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT>
    struct insensitive_char_traits : public std::char_traits<CharT>
    {
      static constexpr CharT to_upper( CharT ch ) noexcept;

      static constexpr bool eq( CharT lhs, CharT rhs ) noexcept;

      static constexpr bool lt( CharT lhs, CharT rhs ) noexcept;

      static constexpr int compare( const CharT* s1,
                                    const CharT* s2,
                                    std::size_t count ) noexcept;

      static constexpr const CharT* find(const CharT* s, int n, CharT a) noexcept;
    };

    //------------------------------------------------------------------------
    // Utilities
    //------------------------------------------------------------------------

    /// \brief Hashes a std::basic_string
    ///
    /// \param str the string to hash
    /// \return the hash
    template<typename CharT, typename Traits, typename Allocator>
    std::size_t hash_value( const std::basic_string<CharT,Traits,Allocator>& str ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/string.inl"

#endif /* BIT_STL_CONTAINERS_STRING_HPP */
