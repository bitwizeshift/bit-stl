/**
 * \file tuple_element_iterator.hpp
 *
 * \brief This header contains an implementation of the tuple_element_iterator,
 *        an adapter that wraps around iterators that iterate tuples to only
 *        return specific tuple elements.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_HPP
#define BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_HPP

#include <iterator>    // std::iterator_traits
#include <type_traits> // std::common_type
#include <tuple>       // std::tuple

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \class tuple_element_iterator tuple_element_iterator.hpp <bit/stl/iterator.hpp>
    ///
    //////////////////////////////////////////////////////////////////////////
    template<std::size_t N,typename Iter>
    class tuple_element_iterator
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type = std::tuple_element_t<N,typename std::iterator_traits<Iter>::value_type>;
      using difference_type = typename std::iterator_traits<Iter>::difference_type;
      using pointer = value_type*;
      using reference = value_type&;
      using iterator_category = typename std::iterator_traits<Iter>::iterator_category;

      //----------------------------------------------------------------------
      // Constructor / Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a tuple_element_iterator from an underlying iterator
      ///
      /// \param iter the iterator
      constexpr explicit tuple_element_iterator( Iter iter );

      /// \brief Copy constructs a tuple_element_iterator from another iterator
      ///
      /// \param other the other iterator to copy
      constexpr tuple_element_iterator( const tuple_element_iterator& other ) = default;

      /// \brief Move constructs a tuple_element_iterator from another iterator
      ///
      /// \param other the other iterator to move
      constexpr tuple_element_iterator( tuple_element_iterator&& other ) = default;

      /// \brief Copy assigns a tuple_element_iterator from another iterator
      ///
      /// \param other the other iterator to copy
      /// \return reference to \c (*this)
      tuple_element_iterator&
        operator=( const tuple_element_iterator& other ) = default;

      /// \brief Move assigns a tuple_element_iterator from another iterator
      ///
      /// \param other the other iterator to move
      /// \return reference to \c (*this)
      tuple_element_iterator&
        operator=( tuple_element_iterator&& other ) = default;

      //----------------------------------------------------------------------
      // Iteration
      //----------------------------------------------------------------------
    public:

      constexpr tuple_element_iterator& operator++() noexcept;
      constexpr tuple_element_iterator operator++(int) noexcept;

      constexpr tuple_element_iterator& operator--() noexcept;
      constexpr tuple_element_iterator operator--(int) noexcept;

      //----------------------------------------------------------------------
      // Random Access
      //----------------------------------------------------------------------
    public:

      constexpr tuple_element_iterator& operator+=( difference_type n ) noexcept;
      constexpr tuple_element_iterator& operator-=( difference_type n ) noexcept;
      constexpr difference_type operator-( const tuple_element_iterator& rhs ) const noexcept;

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

      constexpr bool operator == ( const tuple_element_iterator& rhs ) const noexcept;
      constexpr bool operator != ( const tuple_element_iterator& rhs ) const noexcept;
      constexpr bool operator <  ( const tuple_element_iterator& rhs ) const noexcept;
      constexpr bool operator <= ( const tuple_element_iterator& rhs ) const noexcept;
      constexpr bool operator >  ( const tuple_element_iterator& rhs ) const noexcept;
      constexpr bool operator >= ( const tuple_element_iterator& rhs ) const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      Iter m_iter; ///< The underlying iterator
    };

  } // namespace stl
} // namespace bit

#include "tuple_element_iterator.inl"

#endif /* BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_HPP */
