/**
 * \file Range.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_RANGE_HPP
#define BIT_STL_CONCEPTS_RANGE_HPP

#include "Iterator.hpp"

#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"

namespace bit {
  namespace stl {
    namespace detail {

    template<typename T, typename = void>
    struct is_range_impl : false_type{};

    template<typename T>
    struct is_range_impl<T,
      void_t<
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
      >
    > : conjunction<is_iterator<decltype(std::declval<T>().begin())>,
                    is_iterator<decltype(std::declval<T>().end())>>{};
    } // namespace detail

    template<typename T>
    struct is_range : detail::is_range_impl<std::decay_t<T>>{};

    template<typename...Types>
    struct are_ranges : conjunction<is_range<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_RANGE_HPP */
