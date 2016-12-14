/**
 * \file iterator.hpp
 *
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_ITERATOR_HPP
#define BIT_STL_ITERATOR_HPP

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Constructs a range from a given Container
    ///
    /// A range is a contruct that wraps the iterator begin/end range in a
    /// single type
    //////////////////////////////////////////////////////////////////////////
    template<typename Container>
    class range
    {
      //----------------------------------------------------------------------
      // Public Member Type
      //----------------------------------------------------------------------
    public:

      using iterator = decltype( std::declval<Container&>().begin() );
      using sentinel = decltype( std::declval<Container&>().end() );
      using const_iterator = decltype( std::declval<const Container&>().begin() );
      using const_sentinel = decltype( std::declval<const Container&>().end() );

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a range from a given
      ///
      /// \param container the container to use for this range
      constexpr range( Container& container ) noexcept;

      /// \brief Constructs a range by copying another range
      ///
      /// \param other the other range to copy
      constexpr range( const range& other ) noexcept = default;

      /// \brief Constructs a range by moving another range
      ///
      /// \param other the other range to move
      constexpr range( range&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the start iterator from the iterator range
      ///
      /// \param returns the start iterator
      constexpr iterator begin();

      /// \brief Gets the end iterator from the iterator range
      ///
      /// \param returns the end iterator
      constexpr sentinel end();

      /// \copydoc begin()
      constexpr const_iterator begin() const;

      /// \copydoc end()
      constexpr const_sentinel end() const;

      /// \copydoc begin()
      constexpr const_iterator cbegin() const;

      /// \copydoc end()
      constexpr const_sentinel cend() const;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      Container& m_container; ///< The container to create a range
    };
  } // namespace stl
} // namespace bit

#include "detail/iterator.inl"

#endif /* BIT_STL_ITERATOR_HPP */
