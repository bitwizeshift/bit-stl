/**
 * \file ReversibleContainer.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_REVERSIBLE_CONTAINER_HPP
#define BIT_STL_CONCEPTS_REVERSIBLE_CONTAINER_HPP

#include "Container.hpp"
#include "BidirectionalIterator.hpp"

#include "../traits/conjunction.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_reversible_container_impl : false_type{};

      template<typename T>
      struct is_reversible_container_impl<T,
        void_t<
          typename T::reverse_iterator,
          typename T::const_reverse_iterator,
          decltype(typename T::reverse_iterator( std::declval<T&>().rbegin() )),
          decltype(typename T::reverse_iterator( std::declval<T&>().rend() )),
          decltype(typename T::const_reverse_iterator( std::declval<T&>().crbegin() )),
          decltype(typename T::const_reverse_iterator( std::declval<T&>().crend() ))
        >
      > : conjunction<
        is_container<T>,
        is_bidirectional_iterator<typename T::reverse_iterator>,
        is_bidirectional_iterator<typename T::const_reverse_iterator>
      >{};
    } // namespace detail

  /// \brief Type trait to determine if a given type is a ReversibleContainer
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct is_reversible_container : detail::is_reversible_container_impl<std::decay_t<T>>{};

  /// \brief Type trait to determine if a series of \c Types are all
  ///        ReversibleContainers
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_reversible_containers : conjunction<is_reversible_container<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_REVERSIBLE_CONTAINER_HPP */
