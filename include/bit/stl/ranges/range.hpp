/**
 * \file range.hpp
 *
 * \brief todo: fill in documentation
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
#ifndef BIT_STL_RANGES_RANGE_HPP
#define BIT_STL_RANGES_RANGE_HPP

#include <utility> // std::forward

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \class range
    ///
    /// \brief Constructs a range from a given Container
    ///
    /// A range is a contruct that wraps the iterator begin/end range in a
    /// single type
    ///////////////////////////////////////////////////////////////////////////
    template<typename Iterator, typename Sentinel = Iterator>
    class range
    {
      //-----------------------------------------------------------------------
      // Public Member Type
      //-----------------------------------------------------------------------
    public:

      using iterator = Iterator;
      using sentinel = Sentinel;

      //-----------------------------------------------------------------------
      // Constructor
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs a range from a given iterator range
      ///
      /// \param iterator the start of the input range
      /// \param sentinel the end input range
      constexpr range( Iterator iterator, Sentinel sentinel ) noexcept;

      /// \brief Constructs a range by copying another range
      ///
      /// \param other the other range to copy
      constexpr range( const range& other ) = default;

      /// \brief Constructs a range by moving another range
      ///
      /// \param other the other range to move
      constexpr range( range&& other ) = default;

      //-----------------------------------------------------------------------
      // Iterators
      //-----------------------------------------------------------------------
    public:

      /// \brief Gets the start iterator from the iterator range
      ///
      /// \param returns the start iterator
      constexpr iterator begin();

      /// \brief Gets the end iterator from the iterator range
      ///
      /// \param returns the end iterator
      constexpr sentinel end();

      //-----------------------------------------------------------------------
      // Private Member Types
      //-----------------------------------------------------------------------
    private:

      iterator m_first;
      sentinel m_last;
    };

    //-------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename I, typename S>
    constexpr range<I,S> make_range( I iterator, S sentinel );

    //-------------------------------------------------------------------------

#if __cplusplus >= 201703L

    template<typename Iterator, typename Sentinel>
    range( Iterator, Sentinel ) -> range<Iterator,Sentinel>;

#endif

  } // namespace stl
} // namespace bit

#include "detail/range.inl"

#endif /* BIT_STL_RANGES_RANGE_HPP */
