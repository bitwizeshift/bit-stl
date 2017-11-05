/**
 * \file Container.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_CONTAINER_HPP
#define BIT_STL_CONCEPTS_CONTAINER_HPP

#include "EqualityComparable.hpp"

#include "../traits/void_t.hpp"
#include "../traits/conjunction.hpp"
#include "../traits/bool_constant.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_container_impl : false_type{};

      template<typename T>
      struct is_container_impl<T,
        void_t<
          typename T::value_type,
          typename T::reference,
          typename T::const_reference,
          typename T::iterator,
          typename T::const_iterator,
          typename T::difference_type,
          typename T::size_type,
          decltype(typename T::iterator(std::declval<T&>().begin())),
          decltype(typename T::iterator(std::declval<T&>().end())),
          decltype(typename T::const_iterator(std::declval<const T&>().cbegin())),
          decltype(typename T::const_iterator(std::declval<const T&>().cend())),
          decltype(bool(std::declval<const T&>() == std::declval<const T&>() )),
          decltype(bool(std::declval<const T&>() != std::declval<const T&>() )),
          decltype(std::declval<T&>().swap( std::declval<T&>() )),
          decltype(typename T::size_type( std::declval<const T&>().size() )),
          decltype(typename T::size_type( std::declval<const T&>().max_size() )),
          decltype(bool( std::declval<const T&>().empty() ))
        >
      > : conjunction<
        std::is_default_constructible<T>,
        std::is_copy_constructible<T>,
        is_equality_comparable<typename T::value_type>
      >{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is a Container
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_container : detail::is_container_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all Containers
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_containers : conjunction<is_container<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_CONTAINER_HPP */
