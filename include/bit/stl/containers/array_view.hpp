/*****************************************************************************
 * \file
 * \brief This header contains a type-erased view of immutable
 *        contiguous data
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
#ifndef BIT_STL_CONTAINERS_ARRAY_VIEW_HPP
#define BIT_STL_CONTAINERS_ARRAY_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../traits/composition/bool_constant.hpp"
#include "../concepts/ContiguousContainer.hpp"
#include "../utilities/assert.hpp"
#include "../iterators/tagged_iterator.hpp"

#include <stdexcept> // std::out_of_range
#include <algorithm> // std::equal, std::lexicographical_compare

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief An immutable wrapper around non-owned contiguous data.
    ///
    /// This type behaves like a const span, but is only constructible from
    /// contiguous data containers and raw arrays, not from pointer + size.
    ///
    /// \satisfies{ContiguousContainer}
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    class array_view
    {
      template<typename Container>
      struct is_container_argument : bool_constant<
        is_contiguous_container<Container>::value &&
        !std::is_same<std::decay_t<Container>, array_view>::value
       >{};

      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using value_type      = std::decay_t<T>;
      using pointer         = value_type*;
      using const_pointer   = const value_type*;
      using reference       = value_type&;
      using const_reference = const value_type&;

      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;

      using iterator               = tagged_iterator<const T*,array_view>;
      using const_iterator         = tagged_iterator<const T*,array_view>;
      using reverse_iterator       = std::reverse_iterator<iterator>;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;

      //-----------------------------------------------------------------------
      // Public Static Members
      //-----------------------------------------------------------------------
    public:

      static constexpr size_type npos = size_type(-1);

      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs an empty array_view
      constexpr array_view() noexcept;

      /// \brief Constructs an array_view by copying another array_view
      ///
      /// \param other the other array_view to copy
      constexpr array_view( const array_view& other ) noexcept;

      /// \brief Constructs an array_view by moving the contents of another
      ///        array_view
      ///
      /// \param other the other array_view to move
      constexpr array_view( array_view&& other ) noexcept;

      /// \brief Constructs an array-view from a reference to an array
      ///
      /// \param array the array to view
      template<std::size_t N>
      constexpr array_view( value_type (&array)[N] ) noexcept;

      /// \copydoc array_view( value_type (&)[N] )
      template<std::size_t N>
      constexpr array_view( const value_type (&array)[N] ) noexcept;

      /// \brief Constructs an array_view from a given initializer list
      ///
      /// \param ilist the initializer list for the container
      constexpr array_view( std::initializer_list<value_type> ilist ) noexcept;

      /// \brief Constructs an array-view from a container
      ///
      /// \param container the container to view
#ifndef BIT_DOXYGEN_BUILD
      template<typename Container,
               typename = std::enable_if_t<is_container_argument<Container>::value>>
#else
      template<typename Container>
#endif
      constexpr array_view( const Container& container ) noexcept;

      //-----------------------------------------------------------------------
      // Assignment
      //-----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns this array_view with \p other
      ///
      /// \param other the other array_view to copy
      /// \return reference to \c (*this)
      array_view& operator = ( const array_view& other ) noexcept = default;

      /// \brief Move-assigns this array_view with \p other
      ///
      /// \param other the other array_view to copy
      /// \return reference to \c (*this)
      array_view& operator = ( array_view&& other ) noexcept = default;

      //-----------------------------------------------------------------------
      // Capacity
      //-----------------------------------------------------------------------
    public:

      /// \brief Returns the number of entries in the array_view
      ///
      /// \return the number of entries in the array_view
      constexpr size_type size() const noexcept;

      /// \brief Returns the max size of this array_view
      ///
      /// \return the max number of entries in this array_view
      constexpr size_type max_size() const noexcept;

      /// \brief Returns whether the array_view is empty
      ///
      /// \return \c true if this array_view is empty, \c false otherwise
      constexpr bool empty() const noexcept;

      //-----------------------------------------------------------------------
      // Element Access
      //-----------------------------------------------------------------------
    public:

      /// \brief Gets the data of the current array_view
      ///
      /// \return the data this array_view contains
      constexpr const value_type* data() const noexcept;

      /// \brief Accesses the element at index \p pos
      ///
      /// \param pos the index to access
      /// \return const reference to the entry
      constexpr const_reference operator[]( std::size_t pos ) const noexcept;

      /// \brief Accesses the element at index \p pos
      ///
      /// \param pos the index to access
      /// \return const reference to the entry
      constexpr const_reference at( std::size_t pos ) const;

      /// \brief References the first entry of the array
      ///
      /// \note Undefined behavior if array_view is empty
      ///
      /// \return reference to the first entry of the array
      constexpr const_reference front() const noexcept;

      /// \brief References the last entry of the array
      ///
      /// \note Undefined behavior if array_view is empty
      ///
      /// \return reference to the entry of the array
      constexpr const_reference back() const noexcept;

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Moves the start of the view forward by n entries.
      ///
      /// The behavior is undefined if n > size().
      ///
      /// \param n number of entries to remove from the start of the view
      constexpr void remove_front( size_type n ) noexcept;

      /// \brief Moves the end of the view back by n entries.
      ///
      /// The behavior is undefined if n > size().
      ///
      /// \param n number of entries to remove from the end of the view
      constexpr void remove_back( size_type n ) noexcept;

      /// \brief Swaps this view with the \p other view
      ///
      /// \param other the other view to swap with
      constexpr void swap( array_view<T>& other ) noexcept;

      //-----------------------------------------------------------------------
      // Operations
      //-----------------------------------------------------------------------
    public:

      /// \brief Retrives a subarray of a given array_view
      ///
      /// \param offset the position of the first entry in the subarray
      /// \param count  the length of the subarray
      constexpr array_view subarray( size_type offset = 0, size_type count = npos ) const;

      //-----------------------------------------------------------------------
      // Iterators
      //-----------------------------------------------------------------------
    public:

      /// \brief Retrieves the begin iterator for this array_view
      ///
      /// \return the begin iterator
      constexpr const_iterator begin() const noexcept;

      /// \brief Retrieves the end iterator for this array_view
      ///
      /// \return the end iterator
      constexpr const_iterator end() const noexcept;

      /// \copydoc array_view::begin()
      constexpr const_iterator cbegin() const noexcept;

      /// \copydoc array_view::end()
      constexpr const_iterator cend() const noexcept;

      /// \brief Retrieves the reverse begin iterator for this array_view
      ///
      /// \return the reverse begin iterator
      constexpr const_reverse_iterator rbegin() const noexcept;

      /// \brief Retrieves the reverse end iterator for this array_view
      ///
      /// \return the reverse end iterator
      constexpr const_reverse_iterator rend() const noexcept;

      /// \copydoc array_view::rbegin()
      constexpr const_reverse_iterator crbegin() const noexcept;

      /// \copydoc array_view::rend()
      constexpr const_reverse_iterator crend() const noexcept;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      const T*  m_ptr;  ///< Pointer to the entry
      size_type m_size; ///< The size of the array

      //-----------------------------------------------------------------------
      // Private Constructor
      //-----------------------------------------------------------------------
    private:

      /// \brief Constructs an array_view from a given pointer and size
      ///
      /// \param ptr pointer to the data array
      /// \param size the size of the array
      constexpr array_view( const value_type* ptr, size_type size ) noexcept;

    };

    //=========================================================================
    // Free Functions
    //=========================================================================

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left array view
    /// \param rhs the right array view
    template<typename T>
    constexpr void swap( array_view<T>& lhs, array_view<T>& rhs ) noexcept;

    //-------------------------------------------------------------------------
    // Comparison
    //-------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator==(const array_view<T>& lhs, const array_view<T>& rhs);

    template<typename T>
    constexpr bool operator!=(const array_view<T>& lhs, const array_view<T>& rhs);

    template<typename T>
    constexpr bool operator<(const array_view<T>& lhs, const array_view<T>& rhs);

    template<typename T>
    constexpr bool operator>(const array_view<T>& lhs, const array_view<T>& rhs);

    template<typename T>
    constexpr bool operator<=(const array_view<T>& lhs, const array_view<T>& rhs);

    template<typename T>
    constexpr bool operator>=(const array_view<T>& lhs, const array_view<T>& rhs);

  } // namespace stl
} // namespace bit

#include "detail/array_view.inl"

#endif /* BIT_STL_CONTAINERS_ARRAY_VIEW_HPP */
