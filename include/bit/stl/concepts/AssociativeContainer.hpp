/**
 * \file AssociativeContainer.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_ASSOCIATIVECONTAINER_HPP
#define BIT_STL_CONCEPTS_ASSOCIATIVECONTAINER_HPP

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/bool_constant.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_associative_container_impl : false_type{};

      template<typename T>
      struct is_associative_container_impl<T,
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
          decltype(typename T::const_iterator(std::declval<T&>().cbegin())),
          decltype(typename T::const_iterator(std::declval<T&>().cend())),
          decltype(bool(std::declval<T&>() == std::declval<T&>() )),
          decltype(bool(std::declval<T&>() != std::declval<T&>() )),
          decltype(std::declval<T&>().swap( std::declval<T&>() )),
          decltype(typename T::size_type( std::declval<T&>().size() )),
          decltype(typename T::size_type( std::declval<T&>().max_size() )),
          decltype(bool( std::declval<T&>().empty() ))
        >
      > : conjunction<
        std::is_default_constructible<T>,
        std::is_copy_constructible<T>
      >{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is a AssociativeContainer
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_associative_container : detail::is_associative_container_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all Containers
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_associative_containers : conjunction<is_associative_container<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_ASSOCIATIVECONTAINER_HPP */
