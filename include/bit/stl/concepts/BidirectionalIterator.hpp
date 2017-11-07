/**
 * \file BidirectionalIterator.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
#define BIT_STL_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP

#include "ForwardIterator.hpp"

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_bidirectional_iterator_impl : false_type{};

      template<typename T>
      struct is_bidirectional_iterator_impl<
        T,
        void_t<
          decltype( --std::declval<T&>() ),
          decltype( std::declval<T&>()-- ),
          decltype( *std::declval<T&>()-- )
        >
      > : is_forward_iterator<T>{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is a BidirectionalIterator
    ///
    /// A type is considered an iterator if all \c iterator_traits are supplied
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_bidirectional_iterator : detail::is_bidirectional_iterator_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all BidirectionalIterators
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_bidirectional_iterators : conjunction<is_bidirectional_iterator<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP */
