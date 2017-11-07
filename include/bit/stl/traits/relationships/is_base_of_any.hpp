/**
 * \file is_base_of_any.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP

#include "../disjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    template<typename Base, typename...Derived>
    struct is_base_of_any : disjunction<std::is_base_of<Base,Derived>...>{};

    template<typename Base, typename...Derived>
    constexpr bool is_base_of_any_v = is_base_of_any<Base,Derived...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP */
