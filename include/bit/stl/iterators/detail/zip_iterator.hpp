/**
 * \file zip_iterator.hpp
 *
 * \brief This header contains the internal implementation of a zip iterator
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_ITERATOR_DETAIL_ZIP_ITERATOR_HPP
#define BIT_STL_ITERATOR_DETAIL_ZIP_ITERATOR_HPP

#include <iterator>    // std::iterator_traits
#include <type_traits> // std::common_type
#include <tuple>       // std::tuple

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

#include "zip_iterator.inl"

#endif /* BIT_STL_ITERATOR_DETAIL_ZIP_ITERATOR_HPP */
