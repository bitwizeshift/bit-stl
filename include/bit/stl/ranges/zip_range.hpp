/**
 * \file zip_range.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_RANGES_ZIP_RANGE_HPP
#define BIT_STL_RANGES_ZIP_RANGE_HPP

#include "range.hpp" // range

#include "../iterators/zip_iterator.hpp" // zip_iterator

#include <type_traits> // std::declval

namespace bit {
  namespace stl {

    template<typename...Iterators>
    using zip_range = range<
      zip_iterator<Iterators>...,
      zip_iterator<Iterators>...
    >;

    //-------------------------------------------------------------------------

    /// \brief Makes a zip range from a selection of zip iterators
    ///
    /// \param r0 the first range entry
    /// \param rn the rest of the range entries
    /// \return the type-deduced range
    template<typename Range0, typename...RangeN>
    constexpr auto make_zip_range( Range0&& r0, RangeN&&...rn )
      -> range<zip_iterator<decltype( r0.begin() ), decltype( rn.begin() )...>,
               zip_iterator<decltype( r0.end() ), decltype( rn.end() )...>>;

  } // namespace stl
} // namespace bit

#include "detail/zip_range.inl"

#endif /* BIT_STL_RANGES_ZIP_RANGE_HPP */
