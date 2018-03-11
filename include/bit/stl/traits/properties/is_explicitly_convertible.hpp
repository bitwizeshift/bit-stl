/**
 * \file is_explicitly_convertible.hpp
 *
 * \brief This header defines a type-trait for determining whether a type is
 *        explicitly convertible to another type
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
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP

#include "../composition/bool_constant.hpp"
#include "../composition/void_t.hpp"

#include "is_explicitly_constructible.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T>
      struct is_explicitly_convertible_dummy
      {
        static void test( T );
      };

      template<typename From, typename To, typename = void>
      struct is_explicitly_convertible_impl : is_explicitly_constructible<To,From>{};

      template<typename From, typename To>
      struct is_explicitly_convertible_impl<From,To,void_t<
        decltype( is_explicitly_convertible_dummy<To>::test( static_cast<To>(std::declval<From>()) ) )
      >> : true_type{};
    } // namespace detail

    /// \brief Type trait to determine if From is explicitly convertible to
    ///        To
    ///
    /// A type is considered explicitly convertible if one of the following
    /// expressions is well-formed:
    ///
    /// \code
    /// To test(){ return static_cast<To>(std::declval<From>()); }
    /// \endcode
    ///
    /// or
    /// \code
    /// To test(){ return To(std::declval<From>()) }
    /// \endcode
    ///
    /// For the purpose of the above illustrations, std::declval is not
    /// considered ODR-used.
    ///
    /// The result is aliased as \c ::value
    template<typename From, typename To>
    struct is_explicitly_convertible
      : detail::is_explicitly_convertible_impl<From,To>{};

    /// \brief Helper utility to extract is_explicitly_convertible::type
    template<typename From, typename To>
    constexpr bool is_explicitly_convertible_v = is_explicitly_convertible<From,To>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP */
