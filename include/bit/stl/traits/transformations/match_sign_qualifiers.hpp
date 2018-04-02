/*****************************************************************************
 * \file
 * \brief This header contains a utility metafunction for matching
 *        sign-qualifiers of a given qualified type
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
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_SIGN_QUALIFIERS_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_SIGN_QUALIFIERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../composition/identity.hpp"

#include <type_traits> // std::make_signed, std::make_unsigneds

namespace bit {
  namespace stl {
    namespace detail {

      template<typename Unqualified,
               bool IsSigned,
               bool IsUnsigned>
      struct sign_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct sign_selector<Unqualified, true, false>
        : std::make_signed<Unqualified>{};

      template<typename Unqualified>
      struct sign_selector<Unqualified, false, true>
        : std::make_unsigned<Unqualified>{};
    } // namespace detail

    /// \brief Type trait to match the sign qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified, typename Unqualified>
    using match_sign_qualifiers = detail::sign_selector<
      Unqualified,
      std::is_signed<Qualified>::value,
      std::is_unsigned<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_sign_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_sign_qualifiers_t =
      typename match_sign_qualifiers<Qualified, Unqualified>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_SIGN_QUALIFIERS_HPP */
