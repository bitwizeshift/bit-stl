/*****************************************************************************
 * \file
 * \brief This header contains the internal implementation of a zip iterator
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
#ifndef BIT_STL_ITERATOR_DETAIL_ZIP_ITERATOR_HPP
#define BIT_STL_ITERATOR_DETAIL_ZIP_ITERATOR_HPP

#include <iterator>    // std::iterator_traits
#include <type_traits> // std::common_type
#include <tuple>       // std::tuple
#include <cstddef>     // std::ptrdiff_t

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An iterator used for zipping multiple iterator ranges together
    ///        into a single iterator
    ///
    /// A zip_iterator does not have any operator->, since the underlying
    /// reference type is a std::tuple<T&,...> for each iterator entry.
    ///
    /// \tparam InputIterators... The types
    //////////////////////////////////////////////////////////////////////////
    template<typename...InputIterators>
    class zip_iterator
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using iterator_category = typename std::common_type<typename std::iterator_traits<InputIterators>::iterator_category...>::type;
      using value_type = std::tuple<typename std::iterator_traits<InputIterators>::value_type...>;
      using reference  = std::tuple<typename std::iterator_traits<InputIterators>::reference...>;
      using pointer    = std::tuple<typename std::iterator_traits<InputIterators>::pointer...>;
      using difference_type = std::ptrdiff_t;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:


      /// \brief Constructs a zip_iterator from a collection of iterators
      ///
      /// \param iterators the iterators
      constexpr explicit zip_iterator( InputIterators...iterators );

      /// \brief Copy constructs a zip_iterator from another iterator
      ///
      /// \param other the other iterator to copy
      constexpr zip_iterator( const zip_iterator& other ) = default;

      /// \brief Move constructs a zip_iterator from another iterator
      ///
      /// \param other the other iterator to move
      constexpr zip_iterator( zip_iterator&& other ) = default;

      /// \brief Copy assigns a zip_iterator from another iterator
      ///
      /// \param other the other iterator to copy
      /// \return reference to \c (*this)
      zip_iterator& operator=( const zip_iterator& other ) = default;

      /// \brief Move assigns a zip_iterator from another iterator
      ///
      /// \param other the other iterator to move
      /// \return reference to \c (*this)
      zip_iterator& operator=( zip_iterator&& other ) = default;

      //----------------------------------------------------------------------
      // Iteration
      //----------------------------------------------------------------------
    public:

      constexpr zip_iterator& operator++() noexcept;
      constexpr zip_iterator operator++(int) noexcept;

      constexpr zip_iterator& operator--() noexcept;
      constexpr zip_iterator operator--(int) noexcept;

      //----------------------------------------------------------------------
      // Random Access
      //----------------------------------------------------------------------
    public:

      constexpr zip_iterator& operator+=( difference_type n ) noexcept;
      constexpr zip_iterator& operator-=( difference_type n ) noexcept;
      constexpr difference_type operator-( const zip_iterator& rhs ) const noexcept;
      constexpr zip_iterator operator[]( difference_type n ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

//      constexpr pointer operator->() const noexcept;
      constexpr reference operator*() const noexcept;

      //----------------------------------------------------------------------
      // Comparison
      //----------------------------------------------------------------------
    public:

      template<typename...Its>
      constexpr bool operator == ( const zip_iterator<Its...>& rhs ) const noexcept;
      template<typename...Its>
      constexpr bool operator != ( const zip_iterator<Its...>& rhs ) const noexcept;
      template<typename...Its>
      constexpr bool operator <  ( const zip_iterator<Its...>& rhs ) const noexcept;
      template<typename...Its>
      constexpr bool operator <= ( const zip_iterator<Its...>& rhs ) const noexcept;
      template<typename...Its>
      constexpr bool operator >  ( const zip_iterator<Its...>& rhs ) const noexcept;
      template<typename...Its>
      constexpr bool operator >= ( const zip_iterator<Its...>& rhs ) const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using storage_type = std::tuple<InputIterators...>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      storage_type m_storage;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      template<std::size_t...Idxs>
      constexpr reference unpack( std::index_sequence<Idxs...> ) const noexcept;

      //----------------------------------------------------------------------

      template<std::size_t Idx0, std::size_t Idx1, std::size_t...Idxs>
      constexpr void translate( difference_type n, std::index_sequence<Idx0, Idx1, Idxs...> );

      template<std::size_t Idx>
      constexpr void translate( difference_type n, std::index_sequence<Idx> );

      //----------------------------------------------------------------------

      template<std::size_t Idx0, std::size_t Idx1, std::size_t...Idxs>
      constexpr void increment( std::index_sequence<Idx0, Idx1, Idxs...> );

      template<std::size_t Idx>
      constexpr void increment( std::index_sequence<Idx> );

      //----------------------------------------------------------------------

      template<std::size_t Idx0, std::size_t Idx1, std::size_t...Idxs>
      constexpr void decrement( std::index_sequence<Idx0, Idx1, Idxs...> );

      template<std::size_t Idx>
      constexpr void decrement( std::index_sequence<Idx> );

      template<typename...> friend class zip_iterator;
    };

  } // namespace memory
} // namespace bit

#include "detail/zip_iterator.inl"

#endif /* BIT_STL_ITERATOR_DETAIL_ZIP_ITERATOR_HPP */
