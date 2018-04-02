/*****************************************************************************
 * \file
 * \brief This header contains useful SFINAE utilities for selectively enabling
 *        or disabling functionality
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
#ifndef BIT_STL_TRAITS_COMPOSITION_SFINAE_HPP
#define BIT_STL_TRAITS_COMPOSITION_SFINAE_HPP

#include "identity.hpp"

namespace bit {
  namespace stl {

    /// \brief Base class for sfinae types
    struct sfinae_base
    {
      /// \brief Type corresponding to yes (is) instances using SFINAE.
      /// \note bit::yes_type is guaranteed to be a different size than bit::no_type
      using yes_type = char(&)[1];

      /// \brief Type corresponding to no (is not) instances using SFINAE.
      /// \note bit::no_type is guaranteed to be a different size than bit::yes_type
      using no_type = char(&)[4];
    };

    //-------------------------------------------------------------------------

    template<bool B, typename T = void>
    struct enable_if : identity<T>{};

    template<typename T>
    struct enable_if<false,T>{};

    template<bool B, typename T>
    using enable_if_t = typename enable_if<B,T>::type;

    //-------------------------------------------------------------------------

    template<bool B, typename T = void>
    struct disable_if : identity<T>{};

    template<typename T>
    struct disable_if<true,T>{};

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c block_if
    template<bool B, typename T>
    using disable_if_t = typename enable_if<B,T>::type;

    //---------------------------------------------------------------------------

    /// \brief Similar to enable_if, but doesn't sfinae-away a type; instead
    ///        produces an uninstantiable unique type when true
    ///
    /// This is used to selectively disable constructors, since sfinae doesn't
    /// work for copy/move constructors
    template<bool b, typename T>
    struct enable_overload_if : identity<T>{};

    template<typename T>
    struct enable_overload_if<false,T>
    {
      class type{ type() = delete; ~type() = delete; };
    };

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c block_if
    template<bool B, typename T>
    using enable_overload_if_t = typename enable_overload_if<B,T>::type;

    //---------------------------------------------------------------------------

    /// \brief Inverse of \c block_if
    template<bool B, typename T>
    using disable_overload_if = enable_overload_if<!B,T>;

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c block_unless
    template<bool B, typename T>
    using disable_overload_if_t = typename disable_overload_if<B,T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_SFINAE_HPP */
