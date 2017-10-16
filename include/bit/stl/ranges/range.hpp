/**
 * \file range.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_RANGES_RANGE_HPP
#define BIT_STL_RANGES_RANGE_HPP

#include <utility> // std::forward

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \class range
    ///
    /// \brief Constructs a range from a given Container
    ///
    /// A range is a contruct that wraps the iterator begin/end range in a
    /// single type
    ///////////////////////////////////////////////////////////////////////////
    template<typename Iterator, typename Sentinel = Iterator>
    class range
    {
      //-----------------------------------------------------------------------
      // Public Member Type
      //-----------------------------------------------------------------------
    public:

      using iterator = Iterator;
      using sentinel = Sentinel;

      //-----------------------------------------------------------------------
      // Constructor
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs a range from a given iterator range
      ///
      /// \param iterator the start of the input range
      /// \param sentinel the end input range
      constexpr range( Iterator iterator, Sentinel sentinel ) noexcept;

      /// \brief Constructs a range by copying another range
      ///
      /// \param other the other range to copy
      constexpr range( const range& other ) = default;

      /// \brief Constructs a range by moving another range
      ///
      /// \param other the other range to move
      constexpr range( range&& other ) = default;

      //-----------------------------------------------------------------------
      // Iterators
      //-----------------------------------------------------------------------
    public:

      /// \brief Gets the start iterator from the iterator range
      ///
      /// \param returns the start iterator
      constexpr iterator begin();

      /// \brief Gets the end iterator from the iterator range
      ///
      /// \param returns the end iterator
      constexpr sentinel end();

      //-----------------------------------------------------------------------
      // Private Member Types
      //-----------------------------------------------------------------------
    private:

      iterator m_first;
      sentinel m_last;
    };

    //-------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename I, typename S>
    constexpr range<I,S> make_range( I iterator, S sentinel );

    //-------------------------------------------------------------------------

#if __cplusplus >= 201703L

    template<typename Iterator, typename Sentinel>
    range( Iterator, Sentinel ) -> range<Iterator,Sentinel>;

#endif

  } // namespace stl
} // namespace bit

#include "detail/range.inl"

#endif /* BIT_STL_RANGES_RANGE_HPP */
