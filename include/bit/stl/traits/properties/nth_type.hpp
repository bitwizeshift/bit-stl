/**
 * \file nth_type.hpp
 *
 * \brief This header defines a type-trait for extracting the \c nth type from
 *        a variadic pack
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_NTH_TYPE_HPP
#define BIT_STL_TRAITS_PROPERTIES_NTH_TYPE_HPP

#include "../identity.hpp"

#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {

    /// \brief Type-trait for extracting the \c Ith type from a variadic pack
    ///
    /// The result is aliased as \c ::type
    template<std::size_t I, typename...Types>
    struct nth_type;

    template<std::size_t I, typename Type0, typename...Types>
    struct nth_type<I,Type0, Types...> : nth_type<I-1,Types...>{};

    template<typename Type0, typename...Types>
    struct nth_type<0,Type0,Types...> : identity<Type0>{};

    /// \brief Helper utility to extract nth_type::type
    template<std::size_t I, typename...Types>
    using nth_type_t = typename nth_type<I,Types...>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_NTH_TYPE_HPP */
