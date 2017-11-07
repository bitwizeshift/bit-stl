/**
 * \file RandomAccessIterator.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP
#define BIT_STL_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP

#include "BidirectionalIterator.hpp"

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"

#include <type_traits> // std::declval
#include <iterator>    // std::iterator_traits

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_random_access_iterator_impl : false_type{};

      template<typename T>
      struct is_random_access_iterator_impl<
        T,
        void_t<
          // it += n, it + n, it - n
          decltype( std::declval<T&>() += std::declval<typename std::iterator_traits<T>::difference_type>() ),
          decltype( std::declval<T&>() + std::declval<typename std::iterator_traits<T>::difference_type>() ),
          decltype( std::declval<typename std::iterator_traits<T>::difference_type>() + std::declval<T&>() ),
          // it -= n, it - n, b - a
          decltype( std::declval<T&>() -= std::declval<typename std::iterator_traits<T>::difference_type>() ),
          decltype( std::declval<T&>() - std::declval<typename std::iterator_traits<T>::difference_type>() ),
          decltype( std::declval<T&>() - std::declval<T&>() ),
          // it[n]
          decltype( std::declval<T&>()[ std::declval<typename std::iterator_traits<T>::difference_type>()] ),
          // comparison
          decltype( static_cast<bool>(std::declval<T&>() <  std::declval<T&>()) ),
          decltype( static_cast<bool>(std::declval<T&>() >  std::declval<T&>()) ),
          decltype( static_cast<bool>(std::declval<T&>() <= std::declval<T&>()) ),
          decltype( static_cast<bool>(std::declval<T&>() >= std::declval<T&>()) )
        >
      > : is_bidirectional_iterator<T>{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is a RandomAccessIterator
    ///
    /// A type is considered an iterator if all \c iterator_traits are supplied
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_random_access_iterator : detail::is_random_access_iterator_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all RandomAccessIterators
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_random_access_iterators : conjunction<is_random_access_iterator<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP */
