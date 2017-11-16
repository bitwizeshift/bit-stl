/**
 * \file is_explicitly_constructible.hpp
 *
 * \brief This header contains the definitions for a type-trait that determines
 *        explicit constructibility
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONSTRUCTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONSTRUCTIBLE_HPP

#include "../composition/bool_constant.hpp"
#include "../composition/type_list.hpp"
#include "../composition/void_t.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename TypeList, typename = void>
      struct is_explicitly_constructible_impl : std::false_type {};

      template<typename T, typename...Args>
      struct is_explicitly_constructible_impl<T,type_list<Args...>,void_t<
        decltype(T(std::declval<Args>()...))
      >> : true_type{};

    } // namespace detail

    /// \brief Type trait to determine whether a type is explicitly
    ///        constructible from a given set of arguments
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Args>
    struct is_explicitly_constructible
      : detail::is_explicitly_constructible_impl<T, type_list<Args...>>{};

    /// \brief Helper utility to extract is_explicitly_constructible::type
    template<typename T, typename...Args>
    constexpr bool is_explicitly_constructible_v = is_explicitly_constructible<T,Args...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONSTRUCTIBLE_HPP */
