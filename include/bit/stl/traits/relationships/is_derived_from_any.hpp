/**
 * \file is_derived_from_any.hpp
 *
 * \brief This header defines a type-trait for determing if a base is the base
 *        of any derived types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_ANY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_ANY_HPP

#include "../disjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine that \c Derived is derived from any
    ///        \c Bases
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam Derived the derived type
    /// \tparam Bases the base types to check
    template<typename Derived, typename...Bases>
    struct is_derived_from_any : disjunction<std::is_base_of<Bases,Derived>...>{};

    /// \brief Helper utility to extract is_derived_from_any::value
    template<typename Derived, typename...Bases>
    constexpr bool is_derived_from_any_v = is_derived_from_any<Derived,Bases...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_ANY_HPP */
