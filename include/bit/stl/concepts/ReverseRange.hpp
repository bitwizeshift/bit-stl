/**
 * \file ReverseRange.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_REVERSE_RANGE_HPP
#define BIT_STL_CONCEPTS_REVERSE_RANGE_HPP

#include "Iterator.hpp"

#include "../traits/bool_constant.hpp"
#include "../traits/conjunction.hpp"

namespace bit {
  namespace stl {
    namespace detail {

    template<typename T, typename = void>
    struct is_reverse_range_impl : false_type{};

    template<typename T>
    struct is_reverse_range_impl<T,
      void_t<
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
      >
    > : conjunction<is_iterator<decltype(std::declval<T>().rbegin())>,
                    is_iterator<decltype(std::declval<T>().rend())>>{};
    } // namespace detail

    template<typename T>
    struct is_reverse_range : detail::is_reverse_range_impl<std::decay_t<T>>{};

    template<typename...Types>
    struct are_reverse_ranges : conjunction<is_reverse_range<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_REVERSE_RANGE_HPP */
