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
    struct is_derived_from : conjunction<std::is_base_of<Bases,Derived>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_DERIVED_FROM_HPP */
