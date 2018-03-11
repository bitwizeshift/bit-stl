/**
 * \file match_cv_qualifiers.hpp
 *
 * \brief This header contains a utility metafunction for matching CV-qualifiers
 *        of a given qualified type
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
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_CV_QUALIFIERS_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_CV_QUALIFIERS_HPP

#include "../composition/identity.hpp"

#include <type_traits> // std::add_const, std::add_volatile, std::is_const, etc

namespace bit {
  namespace stl {
    namespace detail{

      /// \brief Helper to select the proper cv-qualifiers
      template<
        typename Unqualified,
        bool is_const_type,
        bool is_volatile_type
      >
      struct cv_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, false, true>
        : std::add_volatile<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, true, false>
        : std::add_const<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, true, true>
        : std::add_cv<Unqualified>{};

    } // namespace detail

    /// \brief Type trait to match the cv qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified,typename Unqualified>
    using match_cv_qualifiers = detail::cv_selector<
      Unqualified,
      std::is_const<Qualified>::value,
      std::is_volatile<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_cv_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_cv_qualifiers_t =
      typename match_cv_qualifiers<Qualified, Unqualified>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_CV_QUALIFIERS_HPP */
