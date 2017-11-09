/**
 * \file Iterator.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_ITERATOR_HPP
#define BIT_STL_CONCEPTS_ITERATOR_HPP

#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/void_t.hpp"
#include "../traits/composition/conjunction.hpp"

#include <type_traits> // std::declval
#include <iterator>    // std::iterator_traits

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_iterator_impl : false_type{};

      template<typename T>
      struct is_iterator_impl<T,
        void_t<
          typename std::iterator_traits<T>::value_type,
          typename std::iterator_traits<T>::difference_type,
          typename std::iterator_traits<T>::pointer,
          typename std::iterator_traits<T>::reference,
          typename std::iterator_traits<T>::iterator_category,
          decltype( *std::declval<T&>() ),
          decltype( ++std::declval<T&>() )
        >
      > : true_type{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is an Iterator
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_iterator : detail::is_iterator_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all Iterators
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_iterators : conjunction<is_iterator<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_ITERATOR_HPP */
