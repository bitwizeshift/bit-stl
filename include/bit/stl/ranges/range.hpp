/**
 * \file range.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_RANGE_HPP
#define BIT_STL_RANGE_HPP

#include "../iterators/iterator.hpp"

#include <utility> // std::forward

// IWYU pragma: begin_exports
#include "detail/range/range.hpp"
// IWYU pragma: end_exports

namespace bit {
  namespace stl {

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

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///        iterating values of a given tuple
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced tuple_element range
    template<std::size_t N, typename I, typename S>
    constexpr auto make_tuple_element_range( I iterator, S sentinel )
      -> range<tuple_element_iterator<N,I>,tuple_element_iterator<N,S>>;

    /// \brief Makes a tuple element range from a range
    ///
    /// \param r the range
    /// \return the type-deduced tuple_element range
    template<std::size_t N, typename Range>
    constexpr auto make_tuple_element_range( Range&& r )
      -> decltype(make_tuple_element_range( r.begin(), r.end()));

    //------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///        iterating the first value of a given tuple
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced tuple_element range
    template<typename I, typename S>
    constexpr auto make_key_range( I iterator, S sentinel )
      -> range<tuple_element_iterator<0,I>,tuple_element_iterator<0,S>>;

    /// \brief Makes a key range from another range
    ///
    /// \param r the range
    /// \return a key range
    template<typename Range>
    constexpr auto make_key_range( Range&& r )
      -> decltype(make_key_range( r.begin(), r.end()));

    //------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///        iterating the second value of a given tuple
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced tuple_element range
    template<typename I, typename S>
    constexpr auto make_value_range( I iterator, S sentinel )
      -> range<tuple_element_iterator<1,I>,tuple_element_iterator<1,S>>;

    /// \brief Makes a value range from another range
    ///
    /// \param r the range
    /// \return a value range
    template<typename Range>
    constexpr auto make_value_range( Range&& r )
      -> decltype(make_value_range( r.begin(), r.end()));

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
    /// \param irange the range to deduce
    /// \return the type-deduced range
    template<typename Range>
    constexpr auto make_reverse_range( Range&& r )
      -> decltype(make_range( r.rbegin(), r.rend() ));

    //------------------------------------------------------------------------

    /// \brief Makes a zip range from a selection of zip iterators
    ///
    /// \param r0 the first range entry
    /// \param rn the rest of the range entries
    /// \return the type-deduced range
    template<typename Range0, typename...RangeN>
    constexpr auto make_zip_range( Range0&& r0, RangeN&&...rn )
      -> range<zip_iterator<decltype( std::declval<Range0>().begin()), decltype(std::declval<RangeN>().begin())...>,
               zip_iterator<decltype( std::declval<Range0>().end()), decltype(std::declval<RangeN>().end())...>>;

  } // namespace stl
} // namespace bit

#include "detail/range.inl"

#endif /* BIT_STL_RANGE_HPP */
