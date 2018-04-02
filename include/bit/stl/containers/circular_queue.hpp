/*****************************************************************************
 * \file
 * \brief This header contains the implementation of a circular buffer using a
 *        queue API
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
#ifndef BIT_STL_CONTAINERS_CIRCULAR_QUEUE_HPP
#define BIT_STL_CONTAINERS_CIRCULAR_QUEUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "circular_buffer.hpp"

#include "detail/circular_buffer_storage.hpp"

#include <algorithm>   // std::equal
#include <memory>      // std::allocator
#include <type_traits> // std::is_nothrow_copy_constructible, std::is_same, etc

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief A circular buffer with a queue API
    ///
    /// Memory is allocated up-front from the specified allocator
    ///
    /// \tparam T the underlying type
    /// \tparam Allocator the allocator type
    ///////////////////////////////////////////////////////////////////////////
    template<typename T, typename Allocator=std::allocator<T>>
    class circular_queue
    {
      using traits_type = std::allocator_traits<Allocator>;

      static_assert( std::is_same<T,typename traits_type::value_type>::value,
                     "value_type must be the same as type 'T'" );

      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using value_type      = typename circular_buffer<T>::value_type;
      using reference       = typename circular_buffer<T>::reference;
      using const_reference = typename circular_buffer<T>::const_reference;
      using pointer         = typename circular_buffer<T>::pointer;
      using const_pointer   = typename circular_buffer<T>::const_pointer;

      using size_type       = typename circular_buffer<T>::size_type;
      using difference_type = typename circular_buffer<T>::difference_type;

      using allocator_type = Allocator;

      using iterator = typename circular_buffer<T>::iterator;
      using const_iterator = typename circular_buffer<T>::const_iterator;
      using reverse_iterator = typename circular_buffer<T>::reverse_iterator;
      using const_reverse_iterator = typename circular_buffer<T>::const_reverse_iterator;

      //-----------------------------------------------------------------------
      // Constructors / Assignment
      //-----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a circular_queue
      circular_queue();

      /// \brief Constructs a circular_queue with a given allocator
      ///
      /// \param alloc the allocator
      explicit circular_queue( const Allocator& alloc );


      /// \brief Constructs a circular_queue with \p count copy-constructed
      ///        entries
      ///
      /// \param count the number of elements this circular_queue should contain
      /// \param value the default value to copy
      /// \param alloc the allocator
      circular_queue( size_type count,
                      const T& value,
                      const Allocator& alloc = Allocator() );

      /// \brief Constructs a circular_queue with the specified size
      ///
      /// \param count the number of elements this circular_queue should contain
      /// \param alloc the allocator
      circular_queue( size_type count,
                      const Allocator& alloc = Allocator() );

      /// \brief Copy-constructs from another circular_queue
      ///
      /// \param other the other circular_queue to copy
      circular_queue( const circular_queue& other );

      /// \brief Copy-constructs from another circular_queue
      ///
      /// \param other the other circular_queue to copy
      /// \param alloc the allocator
      circular_queue( const circular_queue& other, const Allocator& alloc );

      /// \brief Move-constructs from another circular_queue
      ///
      /// \param other the other circular_queue to copy
      circular_queue( circular_queue&& other );

      /// \brief Move-constructs from another circular_queue
      ///
      /// \param other the other circular_queue to copy
      /// \param alloc the allocator
      circular_queue( circular_queue&& other, const Allocator& alloc );

      //-----------------------------------------------------------------------

      /// \brief Assigns another circular_queue to this bufer
      ///
      /// \param other the other circular_queue
      /// \return reference to \c (*this)
      circular_queue& operator=( circular_queue other ) noexcept;

      //-----------------------------------------------------------------------
      // Element Access
      //-----------------------------------------------------------------------
    public:

      /// \brief Gets the underlying allocator
      ///
      /// \return the allocator
      allocator_type get_allocator() const;

      /// \brief Returns a reference to the front element of this
      ///        circular_queue
      ///
      /// \return reference to the front element of this circular_buffer
      reference front() noexcept;

      /// \copydoc front()
      const_reference front() const noexcept;

      /// \brief Returns a reference to the back element of this
      ///        circular_queue
      ///
      /// \return reference to the front element of this circular_buffer
      reference back() noexcept;

      /// \copydoc back()
      const_reference back() const noexcept;

      //-----------------------------------------------------------------------
      // Capacity
      //-----------------------------------------------------------------------
    public:

      /// \brief Returns whether this buffer is empty
      ///
      /// \return \c true if the buffer is empty
      bool empty() const noexcept;

      /// \brief Returns whether this buffer is full
      ///
      /// \return \c true if the buffer is full
      bool full() const noexcept;

      /// \brief Returns the number of elements in this circular buffer
      ///
      /// \return the number of elements in this buffer
      size_type size() const noexcept;

      /// \brief Returns the max size of this buffer
      ///
      /// \note This result is always the same as capacity
      /// \return the max number of elements this circular_buffer can contain
      size_type max_size() const noexcept;

      /// \brief Returns the capacity of this buffer
      ///
      /// \return the capacity of this circular_buffer
      size_type capacity() const noexcept;

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Resizes the size of this circular queue to be at least \p n
      ///
      /// \param n the size to reallocate to
      void resize( size_type n );

      /// \brief Constructs a \p T object by calling the copy-constructor, and
      ///        storing the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c front of the buffer before construction
      ///
      /// \param value the value to copy
      template<typename U=T, typename = std::enable_if_t<std::is_copy_constructible<U>::value>>
      void push( const value_type& value );

      /// \brief Constructs a \p T object by calling the move-constructor, and
      ///        storing the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c front of the buffer before construction
      ///
      /// \param value the value to copy
      template<typename U=T,typename = std::enable_if_t<std::is_move_constructible<U>::value>>
      void push( value_type&& value );

      /// \brief Invokes \p T's constructor with the given \p args, storing
      ///        the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c front of the buffer before construction
      ///
      /// \param args the arguments to forward to T
      template<typename...Args, typename = std::enable_if_t<std::is_constructible<T,Args...>::value>>
      reference emplace( Args&&...args );

      /// \brief Pops the entry at the front of the circular_queue
      void pop();

      /// \brief Swaps the contents of this circular_queue with \p other
      ///
      /// \param other the other queue to swap with
      void swap( circular_queue& other ) noexcept;

      //-----------------------------------------------------------------------
      // Iterators
      //-----------------------------------------------------------------------
    public:

      /// \brief Gets the iterator to the beginning of this range
      ///
      /// \return the begin iterator
      iterator begin() noexcept;

      /// \copydoc begin
      const_iterator begin() const noexcept;

      /// \copydoc begin
      const_iterator cbegin() const noexcept;

      /// \brief Gets the iterator to the end of this range
      ///
      /// \return the end iterator
      iterator end() noexcept;

      /// \copydoc end
      const_iterator end() const noexcept;

      /// \copydoc end
      const_iterator cend() const noexcept;

      //-----------------------------------------------------------------------

      /// \brief Gets the iterator to the beginning of the reverse range
      ///
      /// \return the reverse iterator
      reverse_iterator rbegin() noexcept;

      /// \copydoc rbegin()
      const_reverse_iterator rbegin() const noexcept;

      /// \copydoc rbegin()
      const_reverse_iterator crbegin() const noexcept;

      /// \brief Gets the iterator to the end of the reverse range
      ///
      /// \return the reverse iterator
      reverse_iterator rend() noexcept;

      /// \copydoc rend()
      const_reverse_iterator rend() const noexcept;

      /// \copydoc rend()
      const_reverse_iterator crend() const noexcept;

      //-----------------------------------------------------------------------
      // Private Member Types
      //-----------------------------------------------------------------------
    private:

      using storage_type = detail::circular_storage_type<T,Allocator>;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      storage_type m_storage; ///< The underlying storage

      void resize( std::true_type, size_type n );
      void resize( std::false_type, size_type n );
    };

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Swaps two circular_deques
    ///
    /// \param lhs the left deque
    /// \param rhs the right deque
    template<typename T, typename Allocator>
    void swap( circular_queue<T,Allocator>& lhs,
               circular_queue<T,Allocator>& rhs ) noexcept;

    //-------------------------------------------------------------------------
    // Equality
    //-------------------------------------------------------------------------

    template<typename T, typename Allocator>
    bool operator==( const circular_queue<T,Allocator>& lhs,
                     const circular_queue<T,Allocator>& rhs ) noexcept;
    template<typename T, typename Allocator>
    bool operator!=( const circular_queue<T,Allocator>& lhs,
                     const circular_queue<T,Allocator>& rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/circular_queue.inl"

#endif /* BIT_STL_CONTAINERS_CIRCULAR_QUEUE_HPP */
