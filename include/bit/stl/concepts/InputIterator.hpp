/**
 * \file InputIterator.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_INPUT_ITERATOR_HPP
#define BIT_STL_CONCEPTS_INPUT_ITERATOR_HPP

#include "Iterator.hpp"

#include "../traits/void_t.hpp"
#include "../traits/bool_constant.hpp"
#include "../traits/conjunction.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_input_iterator_impl : false_type{};

      template<typename T>
      struct is_input_iterator_impl<
        T,
        void_t<
          decltype( std::declval<T&>() != std::declval<T>() ),
          decltype( std::declval<T&>() == std::declval<T>() ),
          decltype( std::declval<T&>()++ ),
          decltype( *std::declval<T&>()++ )
        >
      > : is_iterator<T>{};
    } // namespace detail

    /// \brief Type trait to determine if a given type is an InputIterator
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_input_iterator : detail::is_input_iterator_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all InputIterators
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_input_iterators : conjunction<is_input_iterator<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_INPUT_ITERATOR_HPP */
