/**
 * \file move_range.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_RANGES_MOVE_RANGE_HPP
#define BIT_STL_RANGES_MOVE_RANGE_HPP

#include "range.hpp" // range

#include <iterator> // std::move_iterator

namespace bit {
  namespace stl {

    template<typename Iterator, typename Sentinel>
    using move_range = range<std::move_iterator<Iterator>,std::move_iterator<Sentinel>>;

    //-------------------------------------------------------------------------

    /// \brief Makes a movable range from a given \p iterator \p sentinal pair
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced range
    template<typename Iterator, typename Sentinel>
    constexpr move_range<Iterator,Sentinel>
      make_move_range( Iterator iterator, Sentinel sentinel );

    /// \brief Makes a reverse range from a given \p iterator \p sentinal pair
    ///
    /// \param irange the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr auto make_move_range( Range&& r )
      -> decltype(make_move_range( r.begin(), r.end() ));

  } // namespace stl
} // namespace bit

#include "detail/move_range.inl"

#endif /* BIT_STL_RANGES_MOVE_RANGE_HPP */
