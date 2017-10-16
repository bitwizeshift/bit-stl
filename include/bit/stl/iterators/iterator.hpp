/**
 * \file iterator.hpp
 *
 * \brief This header contains various utilities for iteration and ranges
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_ITERATORS_ITERATOR_HPP
#define BIT_STL_ITERATORS_ITERATOR_HPP

#include <utility>  // std::move
#include <tuple>    // std::tuple_element
#include <iterator> // std::make_move_iterator

// IWYU pragma: begin_exports
#include "detail/tuple_element_iterator.hpp"
#include "detail/zip_iterator.hpp"
#include "detail/pointer_iterator.hpp"
// IWYU pragma: end_exports

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Iterator Adapters : make utilities
    //------------------------------------------------------------------------

    /// \brief Utility function to type-deduce and make an iterator for
    ///        iterating specific tuple elements
    ///
    /// \param iter the iterator
    /// \return the tuple element iterator
    template<std::size_t N,typename Iter>
    constexpr tuple_element_iterator<N,Iter> make_tuple_element_iterator( Iter iter );

    /// \brief Convenience function for making a tuple iterator that only
    ///        iterates the first tuple element, which is the key in
    ///        associative containers
    ///
    /// \param iter the iterator
    /// \return the tuple element iterator
    template<typename Iter>
    constexpr tuple_element_iterator<0,Iter> make_key_iterator( Iter iter );

    /// \brief Convenience function for making a tuple iterator that only
    ///        iterates the second tuple element, which is the value in
    ///        associative containers
    ///
    /// \param iter the iterator
    /// \return the tuple element iterator
    template<typename Iter>
    constexpr tuple_element_iterator<1,Iter> make_value_iterator( Iter iter );

  } // namespace stl
} // namespace bit

#include "detail/iterator.inl"

#endif /* BIT_STL_ITERATORS_ITERATOR_HPP */
