/**
 * \file is_derived_from.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP

#include "../conjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    template<typename Derived, typename...Bases>
    struct is_derived_from_all : conjunction<std::is_base_of<Bases,Derived>...>{};

    template<typename Derived, typename...Bases>
    constexpr bool is_derived_from_all_v = is_derived_from_all<Derived,Bases...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP */
