/**
 * \file array_view.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_ARRAY_VIEW_HPP
#define BIT_ARRAY_VIEW_HPP

#include "type_traits.hpp"

namespace bit {

  template<typename T>
  class array_view_iterator;

  ////////////////////////////////////////////////////////////////////////////
  /// \brief An immutable wrapper around non-owned contiguous data.
  ///
  /// This type behaves like a const span, but is only constructible from
  /// contiguous data containers and raw arrays, not from pointer + size.
  ////////////////////////////////////////////////////////////////////////////
  template<typename T>
  class array_view
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using iterator               = array_view_iterator<T>;
    using const_iterator         = array_view_iterator<T>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------
  public:

    /// \brief Constructs an empty array_view
    constexpr array_view() noexcept;

    /// \brief Constructs an empty array_view
    constexpr array_view( std::nullptr_t ) noexcept;

    /// \brief Constructs an array_view by copying another array_view
    ///
    /// \param other the other array_view to copy
    constexpr array_view( const array_view& other ) noexcept = default;

    /// \brief Constructs an array_view by moving the contents of another
    ///        array_view
    ///
    /// \param other the other array_view to move
    constexpr array_view( array_view&& other ) noexcept = default;

    /// \brief Constructs an array-view from a reference to an array
    ///
    /// \param array the array to view
    template<std::size_t N>
    constexpr array_view(T (&array)[N]) noexcept;

    /// \brief Constructs an array-view from a reference to an array
    ///
    /// \param array the array to view
    template<std::size_t N>
    constexpr array_view(const T (&array)[N]) noexcept;

    /// \brief Constructs an array-view from a container
    ///
    /// \param containe the container to view
#ifndef BFG_DOXYGEN_BUILD
    template<typename Container,
             typename = std::enable_if_t<is_contiguous_container<Container>::value>>
#else
    template<typename Container>
#endif
    constexpr array_view( const Container& container );

    //------------------------------------------------------------------------
    // Assignment
    //------------------------------------------------------------------------
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

    //------------------------------------------------------------------------
    // Element Access
    //------------------------------------------------------------------------
  public:

    constexpr const_reference operator[](size_type pos) const;

    constexpr const_reference at(size_type pos) const;

    constexpr const_reference front() const;

    constexpr const_reference back() const;

    constexpr const_pointer data() const noexcept;

    //------------------------------------------------------------------------
    // Capacity
    //------------------------------------------------------------------------
  public:

    constexpr size_type size() const noexcept;

    constexpr size_type empty() const noexcept;

    //------------------------------------------------------------------------
    // Modifiers
    //------------------------------------------------------------------------
  public:

    /// \brief Moves the start of the view forward by n entries.
    ///
    /// The behavior is undefined if n > size().
    ///
    /// \param n number of entries to remove from the start of the view
    void remove_front( size_type n ) noexcept;

    /// \brief Moves the end of the view back by n entries.
    ///
    /// The behavior is undefined if n > size().
    ///
    /// \param n number of entries to remove from the end of the view
    void remove_back( size_type n ) noexcept;

    /// \brief Swaps this view with the \p other view
    ///
    /// \param other the other view to swap with
    void swap( array_view<T>& other ) noexcept;

    //------------------------------------------------------------------------
    // Iterators
    //------------------------------------------------------------------------
  public:

    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;
    constexpr const_iterator cbegin() const;
    constexpr const_iterator cend() const;

    constexpr const_reverse_iterator rbegin() const;
    constexpr const_reverse_iterator rend() const;
    constexpr const_reverse_iterator crbegin() const;
    constexpr const_reverse_iterator crend() const;

    //------------------------------------------------------------------------
    // Private Members
    //------------------------------------------------------------------------
  private:

    const T*  m_ptr;
    size_type m_size;
  };

  template<typename T>
  void swap( array_view<T>& lhs, array_view<T>& rhs );

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

  ////////////////////////////////////////////////////////////////////////////
  ///
  ///
  ////////////////////////////////////////////////////////////////////////////
  template<typename T>
  class array_view_iterator
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using value_type        = T;
    using pointer           = const T*;
    using reference         = const T&;
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------
  public:

    constexpr array_view_iterator();
    constexpr array_view_iterator(const T* ptr);
    constexpr array_view_iterator(const array_view_iterator&) = default;
    constexpr array_view_iterator(array_view_iterator&&) = default;

    //------------------------------------------------------------------------
    // Incrementing Operators
    //------------------------------------------------------------------------
  public:

    constexpr array_view_iterator& operator++() noexcept;
    constexpr array_view_iterator  operator++(int) noexcept;

    constexpr array_view_iterator& operator--() noexcept;
    constexpr array_view_iterator  operator--(int) noexcept;

    constexpr array_view_iterator& operator+=( difference_type n ) noexcept;
    constexpr array_view_iterator& operator-=( difference_type n ) noexcept;

    constexpr array_view_iterator operator+ ( difference_type n ) const noexcept;
    constexpr array_view_iterator operator- ( difference_type n ) const noexcept;

    pointer operator->() const noexcept;
    reference operator*() const noexcept;

    //------------------------------------------------------------------------
    // Equality Operators
    //------------------------------------------------------------------------
  public:

    constexpr bool operator == ( const array_view_iterator& rhs ) noexcept;
    constexpr bool operator != ( const array_view_iterator& rhs ) noexcept;
    constexpr bool operator <  ( const array_view_iterator& rhs ) noexcept;
    constexpr bool operator <= ( const array_view_iterator& rhs ) noexcept;
    constexpr bool operator >  ( const array_view_iterator& rhs ) noexcept;
    constexpr bool operator >= ( const array_view_iterator& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Private Member Types
    //------------------------------------------------------------------------
  private:

    const T* m_ptr;
  };

} // namespace bit

#include "detail/array_view.inl"

#endif /* BIT_ARRAY_VIEW_HPP */
