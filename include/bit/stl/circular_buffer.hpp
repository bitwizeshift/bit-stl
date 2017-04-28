/**
 * \file circular_buffer.hpp
 *
 * \brief
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CIRCULAR_BUFFER_HPP
#define BIT_STL_CIRCULAR_BUFFER_HPP

#include "memory.hpp" // stl::destroy_at

#include <iterator> // std::bidirectional_iterator_tag, std::reverse_iterator

namespace bit {
  namespace stl {
    namespace detail {
      //////////////////////////////////////////////////////////////////////////
      ///
      /// \tparam T the underlying type
      //////////////////////////////////////////////////////////////////////////
      template<typename Container, typename T>
      class circular_buffer_iterator
      {
        //----------------------------------------------------------------------
        // Public Member Types
        //----------------------------------------------------------------------
      public:

        using value_type = T;
        using reference  = std::add_lvalue_reference_t<T>;
        using pointer    = std::add_pointer_t<T>;
        using size_type  = std::size_t;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        //----------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------
      public:

        explicit circular_buffer_iterator( Container& container, T* ptr, bool is_full );

        circular_buffer_iterator( const circular_buffer_iterator& other ) noexcept = default;

        circular_buffer_iterator( circular_buffer_iterator&& other ) noexcept = default;

        //----------------------------------------------------------------------

        circular_buffer_iterator& operator=( const circular_buffer_iterator& other ) noexcept = default;

        circular_buffer_iterator& operator=( circular_buffer_iterator&& other ) noexcept = default;

        //----------------------------------------------------------------------
        // Iteration
        //----------------------------------------------------------------------
      public:

        circular_buffer_iterator& operator++() noexcept;
        circular_buffer_iterator operator++(int) noexcept;

        circular_buffer_iterator& operator--() noexcept;
        circular_buffer_iterator operator--(int) noexcept;

        //----------------------------------------------------------------------
        // Observers
        //----------------------------------------------------------------------
      public:

        reference operator*() noexcept;
        pointer operator->() noexcept;

        //----------------------------------------------------------------------
        // Private Members
        //----------------------------------------------------------------------
      private:

        value_type* m_ptr;       ///< Pointer to the location in the buffer
        Container*  m_container; ///< The underlying container
        bool        m_is_full;   ///< Is this buffer full

        template<typename C, typename U>
        friend bool operator==( const circular_buffer_iterator<C,U>& lhs,
                                const circular_buffer_iterator<C,U>& rhs ) noexcept;

      };

      template<typename C, typename T>
      bool operator==( const circular_buffer_iterator<C,T>& lhs,
                       const circular_buffer_iterator<C,T>& rhs ) noexcept;

      template<typename C, typename T>
      bool operator!=( const circular_buffer_iterator<C,T>& lhs,
                       const circular_buffer_iterator<C,T>& rhs ) noexcept;

    } // namespace detail

    //////////////////////////////////////////////////////////////////////////
    /// \brief This class is an implementation of a non-owning circular
    ///        buffer
    ///
    /// All emplace/push operations perform constructions inside the buffer.
    /// If the buffer is already filled, the destructor of the previous
    /// function is invoked prior to construction of the newly added item.
    ///
    /// \tparam T the underlying type of this buffer
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class circular_buffer
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

      using iterator       = detail::circular_buffer_iterator<circular_buffer,T>;
      using const_iterator = detail::circular_buffer_iterator<circular_buffer,const T>;
      using reverse_iterator       = std::reverse_iterator<iterator>;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a circular buffer from an uninitialized buffer
      ///        that holds \p size \p T entries
      ///
      /// \param buffer a pointer to the buffer
      /// \param size the size of the buffer
      circular_buffer( void* buffer, std::size_t size ) noexcept;

      /// \brief Move-constructs a circular buffer from another buffer
      ///
      /// \param other the other circular_buffer to move
      circular_buffer( circular_buffer&& other ) noexcept;

      /// \brief Move-assigns a circular_buffer from another one
      ///
      /// \param other the other circular_buffer to move
      /// \return a reference to \c (*this)
      circular_buffer& operator=( circular_buffer&& other ) noexcept = default;

      /// \brief Destructs this circular_buffer, destructing all instances
      ~circular_buffer();

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
      void emplace_back( Args&&...args );

      /// \brief Invokes \p T's constructor with the given \p args, storing
      ///        the result at the beginning of the bugger
      ///
      /// \note If the buffer is full, this will destruct the entry currently
      ///       at the \c end of the buffer before construction
      ///
      /// \param args the arguments to forward to T
      template<typename...Args>
      void emplace_front( Args&&...args );

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

      /// \brief Pops the entry at the front of the circular_buffer
      void pop_front();

      /// \brief Pops the entry at the back of the circular_buffer
      void pop_back();

      //----------------------------------------------------------------------

      /// \brief Clears all entries from this circular_buffer
      void clear();

      /// \brief Swaps this circular_buffer with another one
      ///
      /// \param other the other buffer to swap with
      void swap( circular_buffer& other ) noexcept;

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
      size_type size() const noexcept;
      size_type max_size() const noexcept;
      size_type capacity() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      reference front() noexcept;
      const_reference front() const noexcept;

      reference back() noexcept;
      const_reference back() const noexcept;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      const_iterator cbegin() const noexcept;

      iterator end() noexcept;
      const_iterator end() const noexcept;
      const_iterator cend() const noexcept;

      //----------------------------------------------------------------------

      reverse_iterator rend() noexcept;
      const_reverse_iterator rend() const noexcept;
      const_reverse_iterator crend() const noexcept;

      reverse_iterator rbegin() noexcept;
      const_reverse_iterator rbegin() const noexcept;
      const_reverse_iterator crbegin() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      T* m_buffer; ///< Pointer to the underlying buffer
      T* m_begin;  ///< The beginning pointer
      T* m_end;    ///< The end pointer
      std::size_t m_capacity; ///< The size of the buffer
      std::size_t m_size; ///< The total entries in the circular_buffer

      template<typename,typename> friend class detail::circular_buffer_iterator;

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      T*& increment( T*& iter ) noexcept;
      T*& decrement( T*& iter ) noexcept;
    };

  } // namespace stl
} // namespace bit

#include "detail/circular_buffer.inl"

#endif /* BIT_STL_CIRCULAR_BUFFER_HPP */
