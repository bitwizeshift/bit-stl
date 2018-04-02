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

#include <cstring> // std::memcpy
#include <limits>  // std::numeric_limits

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception for failed narrow_casts.
    ///
    /// This exception is thrown if a narrow_cast fails
    //////////////////////////////////////////////////////////////////////////
    struct bad_narrow_cast : public std::runtime_error
    {
      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      using std::runtime_error::runtime_error;
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception for failed pointer cast.
    ///
    /// This exception is thrown if a pointer_cast fails
    //////////////////////////////////////////////////////////////////////////
    struct bad_pointer_cast : public std::runtime_error
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      using std::runtime_error::runtime_error;
    };

    inline namespace casts {

      //-----------------------------------------------------------------------
      // Casts
      //-----------------------------------------------------------------------

      /// \brief Performs a bounded casting safely between numeric types.
      ///
      /// This method will assert if the value being casted does not properly
      /// fit into the value being converted to.
      /// Calling this method has the same form as calling static_cast
      ///
      /// \tparam To the value type to cast to
      /// \tparam From the value type to cast from. This should always be
      ///         inferred
      ///
      /// \param from the value to cast
      /// \return the casted value
      template<typename To, typename From>
      constexpr To narrow_cast( From from ) noexcept;

      //---------------------------------------------------------------------=-

      /// \brief Statically casts a pointer if the pointer is dynamically
      ///        castable to that type, asserting otherwise.
      ///
      /// \note This will only assert in debug builds
      ///
      /// \param ptr the pointer to cast
      /// \return the statically casted pointer
      template<typename To, typename From>
      To pointer_cast( From ptr ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Performs a cast between types by copying bytes from \p from
      ///        to the new type.
      ///
      /// \note Bytes are truncated to fit into type \p To. If the size of
      ///       \p From is smaller than \p To, the remaining bytes are left
      ///       untouched (and thus may be UB to access)
      ///
      /// \note Both types \p To and \p From must satisfy \c TriviallyCopyable
      ///
      /// \param from the value to convert
      /// \return the converted value
      template<typename To, typename From>
      To copy_cast( const From& from ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Performs an implicit cast between two types, such that the
      ///        cast is actually performed using the implicit language
      ///        casting
      ///
      /// This can be used to signal cases that would otherwise produce
      /// warnings when type promotions are performed.
      ///
      /// \tparam To the type to convert to
      /// \param from the type being converted
      template<typename To, typename From>
      To implicit_cast( From&& from );

    } // inline namespace casts
  } // namespace stl
} // namespace bit

#include "detail/casts.inl"

#endif /* BIT_STL_UTILITIES_CASTS_HPP */
