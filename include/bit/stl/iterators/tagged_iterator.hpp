/*****************************************************************************
 * \file
 * \brief This header contains a type used for creating unique iterators out
 *        of other iteraotrs. This allows for iterators that are incompatible to
 *        pointers, but are as lightweight as a normal ponter.
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
#ifndef BIT_STL_ITERATORS_DETAIL_TAGGED_ITERATOR_HPP
#define BIT_STL_ITERATORS_DETAIL_TAGGED_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory> // std::pointer_traits
#include <iterator> // std::random_access_iterator_tag

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A thin wrapper around a different iterator type to add
    ///        uniqueness
    ///
    /// This makes any regular Iterator type such as a pointer to be unique,
    /// and incomparable to other pointers.
    ///
    /// \tparam Iterator the pointer type to wrap
    /// \tparam U a type to make this iterator unique, and not comparable with
    ///           other tagged_iterators
    //////////////////////////////////////////////////////////////////////////
    template<typename Iterator, typename U = void>
    class tagged_iterator
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
      using value_type        = typename std::iterator_traits<Iterator>::value_type;
      using pointer           = typename std::iterator_traits<Iterator>::pointer;
      using reference         = typename std::iterator_traits<Iterator>::reference;
      using difference_type   = typename std::iterator_traits<Iterator>::difference_type;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a tagged_iterator from a given pointer
      ///
      /// \param it the iterator to construct this tagged_iterator
      constexpr tagged_iterator( const Iterator& it ) noexcept;

      /// \brief Copy-constructs a tagged_iterator
      ///
      /// \param other the iterator to copy
      constexpr tagged_iterator( const tagged_iterator& other ) noexcept = default;

      /// \brief Move-constructs a tagged_iterator
      ///
      /// \param other the iterator to move
      constexpr tagged_iterator( tagged_iterator&& other ) noexcept = default;

      /// \brief Copy-assigns a tagged_iterator
      ///
      /// \param other the iterator to copy
      tagged_iterator& operator=( const tagged_iterator& other ) noexcept = default;

      /// \brief Move-assigns a tagged_iterator
      ///
      /// \param other the iterator to move
      tagged_iterator& operator=( tagged_iterator&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Iteration
      //----------------------------------------------------------------------
    public:

      constexpr tagged_iterator& operator++() noexcept;
      constexpr tagged_iterator operator++(int) noexcept;

      constexpr tagged_iterator& operator--() noexcept;
      constexpr tagged_iterator operator--(int) noexcept;

      //----------------------------------------------------------------------
      // Random Access
      //----------------------------------------------------------------------
    public:

      constexpr tagged_iterator& operator+=( difference_type n ) noexcept;

      constexpr tagged_iterator& operator-=( difference_type n ) noexcept;

      constexpr difference_type operator-( const tagged_iterator& rhs ) const noexcept;

      constexpr reference operator[]( difference_type index ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      constexpr pointer operator->() const noexcept;
      constexpr reference operator*() const noexcept;

      //----------------------------------------------------------------------
      // Comparison
      //----------------------------------------------------------------------
    public:

      constexpr bool operator == ( const tagged_iterator& rhs ) const noexcept;
      constexpr bool operator != ( const tagged_iterator& rhs ) const noexcept;
      constexpr bool operator <  ( const tagged_iterator& rhs ) const noexcept;
      constexpr bool operator <= ( const tagged_iterator& rhs ) const noexcept;
      constexpr bool operator >  ( const tagged_iterator& rhs ) const noexcept;
      constexpr bool operator >= ( const tagged_iterator& rhs ) const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      Iterator m_iter; ///< The iterator used for iteration

    };

    //------------------------------------------------------------------------
    // Random Access (free functions)
    //------------------------------------------------------------------------

    template<typename Ptr, typename U>
    constexpr tagged_iterator<Ptr,U>
      operator+( const tagged_iterator<Ptr,U>& lhs,
                 typename tagged_iterator<Ptr,U>::difference_type rhs ) noexcept;

    template<typename Ptr, typename U>
    constexpr tagged_iterator<Ptr,U>
      operator+( typename tagged_iterator<Ptr,U>::difference_type rhs,
                 const tagged_iterator<Ptr,U>& lhs ) noexcept;

    template<typename Ptr, typename U>
    constexpr tagged_iterator<Ptr,U>
      operator-( const tagged_iterator<Ptr,U>& lhs,
                 typename tagged_iterator<Ptr,U>::difference_type rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/tagged_iterator.inl"

#endif /* BIT_STL_ITERATORS_DETAIL_TAGGED_ITERATOR_HPP */
