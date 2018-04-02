/*****************************************************************************
 * \file
 * \brief This header defines the concept for Desructible
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
#ifndef BIT_STL_CONCEPTS_DESTRUCTIBLE_HPP
#define BIT_STL_CONCEPTS_DESTRUCTIBLE_HPP

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_destructible_impl : false_type{};

      template<typename T>
      struct is_destructible_impl<T,
        void_t<
          decltype( std::declval<T&>().~T() )
        >
      > : true_type{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is Destructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_destructible : detail::is_destructible_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all
    ///        Destructibles
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_destructible : conjunction<is_destructible<Types>...>{};

  } // namespace stl
} // namespace bit

///////////////////////////////////////////////////////////////////////////////
/// \concept{Destructible}
///
/// \brief Specifies that an instance of the type can be destructed.
///
/// ## Requirements
///
/// The type \c T satisfies \ref Destructible if
///
/// Given
///
/// - \c u, a expression of type \c T
///
/// The following expressions must be valid and have their specified effects
///
/// \code
/// u.~T()
/// \endcode
///
/// All resources owned by u are reclaimed, no exceptions are thrown
///////////////////////////////////////////////////////////////////////////////

#endif /* BIT_STL_CONCEPTS_DESTRUCTIBLE_HPP */
