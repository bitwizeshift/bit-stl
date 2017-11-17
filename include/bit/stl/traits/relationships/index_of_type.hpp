/**
 * \file index_of_type.hpp
 *
 * \brief This header defines a type-trait to determine the index of a type in
 *        a variadic pack
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_INDEX_OF_TYPE_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_INDEX_OF_TYPE_HPP

#include "../composition/size_constant.hpp"

#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {
    namespace detail {
      template<std::size_t I, typename T, typename...Types>
      struct index_of_type_impl;

      template<std::size_t I, typename T, typename Type0, typename...Types>
      struct index_of_type_impl<I,T,Type0,Types...>
        : index_of_type_impl<I+1,T,Types...>{};

      template<std::size_t I, typename T, typename...Types>
      struct index_of_type_impl<I,T,T,Types...> : size_constant<I>{};

    } // namespace detail

    /// \brief Type trait to determine the index of \c T in the variadic pack
    ///        \c Types
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename...Types>
    struct index_of_type : detail::index_of_type_impl<0,T,Types...>{};

    /// \brief Helper utility to extract index_of_type::value
    template<typename T, typename...Types>
    constexpr std::size_t index_of_type_v = index_of_type<T,Types...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_INDEX_OF_TYPE_HPP */
