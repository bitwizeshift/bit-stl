/**
 * \file circular_array.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CONTAINERS_CIRCULAR_ARRAY_HPP
#define BIT_STL_CONTAINERS_CIRCULAR_ARRAY_HPP

#include "circular_buffer.hpp"

#include <type_traits>

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A circular buffer that uses an array for storage
    ///
    /// \tparam T the underlying type of this circular array
    /// \tparam N the size of the underlying array
    //////////////////////////////////////////////////////////////////////////
    template<typename T, std::size_t N>
    class circular_array
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type      = T;
      using reference       = std::add_lvalue_reference_t<T>;
      using pointer         = std::add_pointer_t<T>;
      using const_reference = std::add_lvalue_reference_t<std::add_const_t<T>>;
      using const_pointer   = std::add_pointer_t<std::add_const_t<T>>;

      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;

      using iterator       = typename circular_buffer<T>::iterator;
      using const_iterator = typename circular_buffer<T>::const_iterator;
      using reverse_iterator       = typename circular_buffer<T>::reverse_iterator;
      using const_reverse_iterator = typename circular_buffer<T>::const_reverse_iterator;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a circular_array with no entries
      circular_array() noexcept;

      /// \brief Constructs a circular_array with up to \p N default values
      circular_array( T(&&array)[N] )
        noexcept(std::is_nothrow_move_constructible<T>::value);

      circular_array( const circular_array& other )
        noexcept(std::is_nothrow_copy_constructible<T>::value);

      circular_array( circular_array&& other )
        noexcept(std::is_nothrow_move_constructible<T>::value);

      //----------------------------------------------------------------------

      circular_array& operator=(const circular_array& other);

      circular_array& operator=(circular_array&& other);

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Invokes \p T's constructor with the given \p args, storing
      ///        the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c front of the buffer before construction
      ///
      /// \param args the arguments to forward to T
      template<typename...Args>
      reference emplace_back( Args&&...args );

      /// \brief Invokes \p T's constructor with the given \p args, storing
      ///        the result at the beginning of the bugger
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c end of the buffer before construction
      ///
      /// \param args the arguments to forward to T
      template<typename...Args>
      reference emplace_front( Args&&...args );

      //----------------------------------------------------------------------

      /// \brief Constructs a \p T object by calling the copy-constructor, and
      ///        storing the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c front of the buffer before construction
      ///
      /// \param value the value to copy
      void push_back( const T& value );

      /// \brief Constructs a \p T object by calling the move-constructor, and
      ///        storing the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c front of the buffer before construction
      ///
      /// \param value the value to move
      void push_back( T&& value );

      //----------------------------------------------------------------------

      /// \brief Constructs a \p T object by calling the copy-constructor, and
      ///        storing the result at the front of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c back of the buffer before construction
      ///
      /// \param value the value to copy
      void push_front( const T& value );

      /// \brief Constructs a \p T object by calling the move-constructor, and
      ///        storing the result at the end of the buffer
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c back of the buffer before construction
      ///
      /// \param value the value to copy
      void push_front( T&& value );

      //----------------------------------------------------------------------

      /// \brief Pops the entry at the front of the circular_array
      void pop_front();

      /// \brief Pops the entry at the back of the circular_array
      void pop_back();

      //----------------------------------------------------------------------

      /// \brief Clears all entries from this circular_array
      void clear();

      /// \brief Swaps this circular_array with another one
      ///
      /// \param other the other buffer to swap with
      void swap( circular_array& other ) noexcept;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
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
      /// \return the max number of elements this circular_array can contain
      size_type max_size() const noexcept;

      /// \brief Returns the capacity of this buffer
      ///
      /// \return the capacity of this circular_array
      size_type capacity() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Returns a reference to the front element of this
      ///        circular_array
      ///
      /// \return reference to the front element of this circular_array
      reference front() noexcept;

      /// \copydoc front()
      const_reference front() const noexcept;

      /// \brief Returns a reference to the back element of this
      ///        circular_array
      ///
      /// \return reference to the front element of this circular_array
      reference back() noexcept;

      /// \copydoc back()
      const_reference back() const noexcept;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
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

      //----------------------------------------------------------------------

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

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using storage_type = std::aligned_storage_t<sizeof(T[N]),alignof(T[N])>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      circular_buffer<T> m_buffer;  ///< The circular buffer
      storage_type       m_storage; ///< The storage
    };
  } // namespace stl
} // namespace bit

#include "detail/circular_array.inl"

#endif /* BIT_STL_CONTAINERS_CIRCULAR_ARRAY_HPP */
