/**
 * \file iterator.hpp
 *
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_ITERATOR_HPP
#define BIT_STL_ITERATOR_HPP

#include <utility>
#include <iterator>

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
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

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      iterator m_first;
      sentinel m_last;
    };

    //------------------------------------------------------------------------
    // Ranges
    //------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename I, typename S>
    constexpr range<I,S> make_range( I iterator, S sentinel );

    /// \brief This function acts as an identity function, and exists solely
    ///        for completion.
    ///
    /// \param range a range to iterate over
    /// \return reference to the original range
    template<typename Range>
    constexpr Range&& make_range( Range&& range );

    //------------------------------------------------------------------------

    /// \brief Makes a movable range from a given \p iterator \p sentinal pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename I, typename S>
    constexpr auto make_move_range( I iterator, S sentinel )
      -> range<std::move_iterator<I>,std::move_iterator<S>>;

    /// \brief Makes a reverse range from a given \p iterator \p sentinal pair
    ///
    /// \param irange the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr auto make_move_range( Range&& r )
      -> decltype(make_move_range( r.begin(), r.end() ));

    //------------------------------------------------------------------------

    /// \brief Makes a reverse range from a given \p iterator \p sentinal pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename I, typename S>
    constexpr auto make_reverse_range( I iterator, S sentinel )
      -> range<std::reverse_iterator<I>,std::reverse_iterator<S>>;

    /// \brief Makes a reverse range from a given \p iterator \p sentinal pair
    ///
    /// \param irange the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr auto make_reverse_range( Range&& r )
      -> decltype(make_reverse_range( r.begin(), r.end() ));

  } // namespace stl
} // namespace bit

#include "detail/iterator.inl"

#endif /* BIT_STL_ITERATOR_HPP */
