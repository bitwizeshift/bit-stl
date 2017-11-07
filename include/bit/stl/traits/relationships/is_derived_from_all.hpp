/**
 * \file is_derived_from_all.hpp
 *
 * \brief This header defines a type-trait for determining if a given type is
 *        derived from all bases
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine that \c Derived is derived from all
    ///        \c Bases
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam Derived the derived type
    /// \tparam Bases the base types to check
    template<typename Derived, typename...Bases>
    struct is_derived_from_all : conjunction<std::is_base_of<Bases,Derived>...>{};

    /// \brief Helper utility to extract is_derived_from_all::value
    template<typename Derived, typename...Bases>
    constexpr bool is_derived_from_all_v = is_derived_from_all<Derived,Bases...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP */
