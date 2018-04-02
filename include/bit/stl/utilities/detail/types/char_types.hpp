/*****************************************************************************
 * \file
 * \brief This internal header declares character types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
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
#ifndef BIT_STL_UTILITIES_DETAIL_TYPES_CHAR_TYPES_HPP
#define BIT_STL_UTILITIES_DETAIL_TYPES_CHAR_TYPES_HPP

namespace bit {
  namespace stl {

    // Decide tchar type; implementation specific character type
    // that supports multiple character encodings
#if defined(BIT_UTF32) && !defined(BIT_TCHAR_DEFINED)

    #define BIT_CHAR32_IS_TCHAR 1
    #define BIT_TCHAR_DEFINED   1

    using tchar = char32_t;

#elif defined(BIT_UTF16) && !defined(BIT_TCHAR_DEFINED)

    #define BIT_CHAR16_IS_TCHAR 1
    #define BIT_TCHAR_DEFINED   1

    using tchar = char16_t;

#elif defined(BIT_UNICODE) && !defined(BIT_TCHAR_DEFINED)

    #define BIT_WCHAR_IS_TCHAR  1
    #define BIT_TCHAR_DEFINED   1

    using tchar = wchar_t;

#elif !defined(BIT_TCHAR_DEFINED)

    #define BIT_CHAR_IS_TCHAR   1
    #define BIT_TCHAR_DEFINED   1

    using tchar = char;

    #ifndef BIT_ANSI
      #define BIT_ANSI          1
    #endif

#endif

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_TYPES_CHAR_TYPES_HPP */
