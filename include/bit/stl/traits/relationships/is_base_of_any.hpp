/**
 * \file is_base_of_any.hpp
 *
 * \brief This header defines a type-trait for determing if a base is the base
 *        of any derived types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP

#include "../disjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine that \c Base is the base of any
    ///        \c Derived
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam Base the base type
    /// \tparam Derived the derived types to check
    template<typename Base, typename...Derived>
    struct is_base_of_any : disjunction<std::is_base_of<Base,Derived>...>{};

    /// \brief Helper utility to extract is_base_of_any::value
    template<typename Base, typename...Derived>
    constexpr bool is_base_of_any_v = is_base_of_any<Base,Derived...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP */
