/**
 * \file reverse_range.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_RANGES_REVERSE_RANGE_HPP
#define BIT_STL_RANGES_REVERSE_RANGE_HPP

#include "range.hpp" // range, make_range

#include <iterator> // std::reverse_iterator
#include <utility>  // std::forward

namespace bit {
  namespace stl {
    namespace detail {
      template<typename Range>
      using reverse_range_t = range<decltype(std::declval<Range&>().rbegin()),decltype(std::declval<Range&>().rend())>;
    } // namespace detail

    /// \brief A range that contains only reverse iterators
    template<typename Iterator, typename Sentinel = Iterator>
    using reverse_range = range<
      std::reverse_iterator<Iterator>,
      std::reverse_iterator<Sentinel>
    >;

    //-------------------------------------------------------------------------

    /// \brief Makes a reverse range from a given range
    ///
    /// \param range the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr detail::reverse_range_t<Range>
      make_reverse_range( Range&& range );

  } // namespace stl
} // namespace bit

#include "detail/reverse_range.inl"

#endif /* BIT_STL_RANGES_REVERSE_RANGE_HPP */
