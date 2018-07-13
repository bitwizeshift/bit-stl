/*****************************************************************************
 * \file
 * \brief This header contains a collection of utilities for casts.
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
#ifndef BIT_STL_UTILITIES_CASTS_HPP
#define BIT_STL_UTILITIES_CASTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "assert.hpp"
#include "compiler_traits.hpp"

#include "../traits/relationships/is_same_sign.hpp"
#include "../traits/properties/is_implicitly_convertible.hpp"

#include <cstring>     // std::memcpy
#include <type_traits> // std::is_integral, std::enable_if
#include <utility>     // std::forward

namespace bit {
  namespace stl {

    //=========================================================================
    // X.Y.1 : casts
    //=========================================================================

    inline namespace casts {

      /// \brief Performs a bounded casting safely between numeric types.
      ///
      /// This method will assert if the value being casted does not properly
      /// fit into the value being converted to.
      /// Calling this method has the same form as calling static_cast
      ///
      /// \note This cast does not participate in overload resolution unless
      ///       \c is_integral<To>::value and \c is_integral<From>::value are
      ///       both \c true.
      ///
      /// \tparam To the type to cast to
      /// \param from the value to cast
      /// \return the casted value
      template<typename To, typename From,
               typename=std::enable_if_t<std::is_integral<To>::value && std::is_integral<From>::value>>
      constexpr To narrow_cast( From from ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Statically casts a pointer if the pointer is dynamically
      ///        castable to that type, asserting otherwise.
      ///
      /// \note This will only assert in debug builds
      ///
      /// \note This cast does not participate in overload resolution unless
      ///       \c is_pointer<To>::value and \c is_pointer<From>::value are both
      ///       \c true
      ///
      /// \tparam To the type to cast to
      /// \param ptr the pointer to cast
      /// \return the statically casted pointer
      template<typename To, typename From,
               typename=std::enable_if_t<std::is_pointer<To>::value &&
                                         std::is_pointer<From>::value>>
      To pointer_cast( From ptr ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Performs a cast between types by copying bytes from \p from
      ///        to the new type.
      ///
      /// \note Bytes are truncated to fit into type \p To. If the size of
      ///       \p From is smaller than \p To, the remaining bytes are left
      ///       untouched (and thus may be UB to access)
      ///
      /// \note This cast does not participate in overload resolution unless
      ///       \c is_trivially_copyable<To>::value and
      ///       \c is_trivially_copyable<From>::value are both \c true
      ///
      /// \tparam To the type to cast to
      /// \param from the value to convert
      /// \return the converted value
      template<typename To, typename From,
               typename=std::enable_if_t<std::is_trivially_copyable<To>::value &&
                                         std::is_trivially_copyable<From>::value>>
      To copy_cast( const From& from ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Performs an implicit cast between two types, such that the
      ///        cast is actually performed using the implicit language
      ///        casting
      ///
      /// This can be used to signal cases that would otherwise produce
      /// warnings when type promotions are performed.
      ///
      /// \note This cast does not participate in overload resolution unless
      ///       \c is_implicitly_convertible<From,To>::value is \c true
      ///
      /// \tparam To the type to convert to
      /// \param from the type being converted
      template<typename To, typename From,
               typename=std::enable_if_t<is_implicitly_convertible<From,To>::value>>
      To implicit_cast( From&& from );

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Performs an explicit cast to the signed variant of the input.
      ///
      /// If the input is an enum, it is first converted to the underlying
      /// integral type first before being converted.
      /// If the type is already signed, no conversion occurs
      ///
      /// \param from the integral type being converted
      /// \return a signed integral
      template<typename Integral,
               typename=std::enable_if_t<std::is_integral<Integral>::value>>
      constexpr std::make_signed_t<Integral> as_signed( Integral from ) noexcept;
      template<typename Enum,
               typename=std::enable_if_t<std::is_enum<Enum>::value>>
      constexpr std::make_signed_t<std::underlying_type_t<Enum>> as_signed( Enum from ) noexcept;
      /// \}

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Performs an explicit cast to the unsigned variant of the input.
      ///
      /// If the input is an enum, it is first converted to the underlying
      /// integral type first before being converted.
      /// If the type is already unsigned, no conversion occurs
      ///
      /// \param from the integral type being converted
      /// \return an unsigned integral
      template<typename Integral,
               typename=std::enable_if_t<std::is_integral<Integral>::value>>
      constexpr std::make_unsigned_t<Integral> as_unsigned( Integral from ) noexcept;
      template<typename Enum,
               typename=std::enable_if_t<std::is_enum<Enum>::value>>
      constexpr std::make_unsigned_t<std::underlying_type_t<Enum>> as_unsigned( Enum from ) noexcept;
      /// \}

    } // inline namespace casts
  } // namespace stl
} // namespace bit

#include "detail/casts.inl"

#endif /* BIT_STL_UTILITIES_CASTS_HPP */
