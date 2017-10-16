/**
 * \file range.hpp
 *
 * \brief This header contains an implementation of a range
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_RANGES_DETAIL_RANGE_RANGE_HPP
#define BIT_STL_RANGES_DETAIL_RANGE_RANGE_HPP

#include <utility> // std::move

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \class range range.hpp <bit/stl/iterator.hpp>
    ///
    /// \brief Constructs a range from a given Container
    ///
    /// A range is a contruct that wraps the iterator begin/end range in a
    /// single type
    //////////////////////////////////////////////////////////////////////////
    template<typename I, typename S>
    class range
    {
      //----------------------------------------------------------------------
      // Public Member Type
      //----------------------------------------------------------------------
    public:

      using iterator = I;
      using sentinel = S;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a range from a given iterator range
      ///
      /// \param iterator the start of the input range
      /// \param sentinel the end input range
      constexpr range( I iterator, S sentinel ) noexcept;

      /// \brief Constructs a range by copying another range
      ///
      /// \param other the other range to copy
      constexpr range( const range& other ) = default;

      /// \brief Constructs a range by moving another range
      ///
      /// \param other the other range to move
      constexpr range( range&& other ) = default;

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

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      iterator m_first;
      sentinel m_last;
    };

  } // namespace stl
} // namespace bit

#include "range.inl"

#endif /* BIT_STL_RANGES_DETAIL_RANGE_RANGE_HPP */
