/**
 * \file ContiguousContainer.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_CONTIGUOUS_CONTAINER_HPP
#define BIT_STL_CONCEPTS_CONTIGUOUS_CONTAINER_HPP

#include "Container.hpp"
#include "RandomAccessIterator.hpp"

#include "../traits/conjunction.hpp"
#include "../traits/bool_constant.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_contiguous_container_impl : false_type{};

      template<typename T>
      struct is_contiguous_container_impl<T,
        void_t<
          decltype(std::declval<const typename T::value_type*&>() = std::declval<const T&>().data())
        >
      > : conjunction<
        is_container<T>,
        is_random_access_iterator<typename T::iterator>,
        is_random_access_iterator<typename T::const_iterator>
      >{};
    } // namespace detail

    /// \brief Type trait to determine if a given type is a ContiguousContainer
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_contiguous_container : detail::is_contiguous_container_impl<T>{};

    /// \brief Type trait to determine if a series of \c Types are all
    ///        ContiguousContainers
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_contiguous_containers : conjunction<is_contiguous_container<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_CONTIGUOUS_CONTAINER_HPP */
