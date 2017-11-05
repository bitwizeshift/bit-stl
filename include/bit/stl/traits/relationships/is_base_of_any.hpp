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

    template<typename T, typename...Bases>
    struct is_base_of_any : disjunction<std::is_base_of<Bases,T>...>{};

    template<typename T, typename...Bases>
    constexpr bool is_base_of_any_v = is_base_of_any<T,Bases...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ANY_HPP */
