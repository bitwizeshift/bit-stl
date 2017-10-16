/**
 * \file pointer_iterator.hpp
 *
 * \brief This header contains a type used for creating unique iterators out
 *        of pointers. This allows for iterators that are incompatible to
 *        pointers, but are as lightweight as a normal ponter.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_HPP
#define BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_HPP

#include <memory> // std::pointer_traits
#include <iterator> // std::random_access_iterator_tag

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A thin wrapper around a random-access pointer type
    ///
    /// This makes a regular pointer a unique iterator type, incomparable and
    /// not-convertible to normal pointers
    ///
    /// \tparam Ptr the pointer type to wrap
    /// \tparam U a type to make this iterator unique, and not comparable with
    ///           other pointer_iterators
    //////////////////////////////////////////////////////////////////////////
    template<typename Ptr, typename U = void>
    class pointer_iterator
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using iterator_category = std::random_access_iterator_tag;
      using value_type        = typename std::pointer_traits<Ptr>::element_type;
      using pointer           = typename std::pointer_traits<Ptr>::pointer;
      using reference         = value_type&;
      using difference_type   = typename std::pointer_traits<Ptr>::difference_type;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a pointer_iterator from a given pointer
      ///
      /// \param ptr the pointer to construct this pointer_iterator
      constexpr pointer_iterator( const Ptr& ptr ) noexcept;

      /// \brief Copy-constructs a pointer_iterator
      ///
      /// \param other the iterator to copy
      constexpr pointer_iterator( const pointer_iterator& other ) noexcept = default;

      /// \brief Move-constructs a pointer_iterator
      ///
      /// \param other the iterator to move
      constexpr pointer_iterator( pointer_iterator&& other ) noexcept = default;

      /// \brief Copy-assigns a pointer_iterator
      ///
      /// \param other the iterator to copy
      pointer_iterator& operator=( const pointer_iterator& other ) noexcept = default;

      /// \brief Move-assigns a pointer_iterator
      ///
      /// \param other the iterator to move
      pointer_iterator& operator=( pointer_iterator&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Iteration
      //----------------------------------------------------------------------
    public:

      constexpr pointer_iterator& operator++() noexcept;
      constexpr pointer_iterator operator++(int) noexcept;

      constexpr pointer_iterator& operator--() noexcept;
      constexpr pointer_iterator operator--(int) noexcept;

      //----------------------------------------------------------------------
      // Random Access
      //----------------------------------------------------------------------
    public:

      constexpr pointer_iterator& operator+=( difference_type n ) noexcept;

      constexpr pointer_iterator& operator-=( difference_type n ) noexcept;

      constexpr difference_type operator-( const pointer_iterator& rhs ) const noexcept;

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

      constexpr bool operator == ( const pointer_iterator& rhs ) const noexcept;
      constexpr bool operator != ( const pointer_iterator& rhs ) const noexcept;
      constexpr bool operator <  ( const pointer_iterator& rhs ) const noexcept;
      constexpr bool operator <= ( const pointer_iterator& rhs ) const noexcept;
      constexpr bool operator >  ( const pointer_iterator& rhs ) const noexcept;
      constexpr bool operator >= ( const pointer_iterator& rhs ) const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      Ptr m_ptr; ///< The pointer used for iteration

    };

    //------------------------------------------------------------------------
    // Random Access (free functions)
    //------------------------------------------------------------------------

    template<typename Ptr, typename U>
    constexpr pointer_iterator<Ptr,U>
      operator+( const pointer_iterator<Ptr,U>& lhs,
                 typename pointer_iterator<Ptr,U>::difference_type rhs ) noexcept;

    template<typename Ptr, typename U>
    constexpr pointer_iterator<Ptr,U>
      operator+( typename pointer_iterator<Ptr,U>::difference_type rhs,
                 const pointer_iterator<Ptr,U>& lhs ) noexcept;

    template<typename Ptr, typename U>
    constexpr pointer_iterator<Ptr,U>
      operator-( const pointer_iterator<Ptr,U>& lhs,
                 typename pointer_iterator<Ptr,U>::difference_type rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "pointer_iterator.inl"

#endif /* BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_HPP */
