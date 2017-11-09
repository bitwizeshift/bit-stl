/**
 * \file tuple_element_range.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_RANGES_TUPLE_ELEMENT_RANGE_HPP
#define BIT_STL_RANGES_TUPLE_ELEMENT_RANGE_HPP

#include "range.hpp" // range

#include "../iterators/tuple_element_iterator.hpp" // tuple_element_iterator

namespace bit {
  namespace stl {

    template<std::size_t N, typename Iterator, typename Sentinel>
    using tuple_element_range = range<
      tuple_element_iterator<N,Iterator>,
      tuple_element_iterator<N,Sentinel>
    >;

    //-------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///        iterating values of a given tuple
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced tuple_element range
    template<std::size_t N, typename Iterator, typename Sentinel>
    constexpr tuple_element_range<N,Iterator,Sentinel>
      make_tuple_element_range( Iterator iterator, Sentinel sentinel );

    /// \brief Makes a tuple element range from a range
    ///
    /// \param r the range
    /// \return the type-deduced tuple_element range
    template<std::size_t N, typename Range>
    constexpr auto make_tuple_element_range( Range&& r )
      -> decltype(make_tuple_element_range<N>( r.begin(), r.end()));


    //-------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///        iterating the first value of a given tuple
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced tuple_element range
    template<typename Iterator, typename Sentinel>
    constexpr auto make_key_range( Iterator iterator, Sentinel sentinel )
      -> range<tuple_element_iterator<0,Iterator>,tuple_element_iterator<0,Sentinel>>;

    /// \brief Makes a key range from another range
    ///
    /// \param r the range
    /// \return a key range
    template<typename Range>
    constexpr auto make_key_range( Range&& r )
      -> decltype(make_key_range( r.begin(), r.end()));

    //-------------------------------------------------------------------------

    /// \brief Makes a range from a given \p iterator \p sentinel pair
    ///        iterating the second value of a given tuple
    ///
    /// \param iterator the beginning of a range
    /// \param sentinel the end of a range
    /// \return the type-deduced tuple_element range
    template<typename Iterator, typename Sentinel>
    constexpr auto make_value_range( Iterator iterator, Sentinel sentinel )
      -> range<tuple_element_iterator<1,Iterator>,tuple_element_iterator<1,Sentinel>>;

    /// \brief Makes a value range from another range
    ///
    /// \param r the range
    /// \return a value range
    template<typename Range>
    constexpr auto make_value_range( Range&& r )
      -> decltype(make_value_range( r.begin(), r.end()));

  } // namespace stl
} // namespace bit

#include "detail/tuple_element_range.inl"

#endif /* BIT_STL_RANGES_TUPLE_ELEMENT_RANGE_HPP */
