/**
 * \file is_base_of_all.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ALL_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ALL_HPP

#include "../conjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    template<typename T, typename...Bases>
    struct is_base_of_all : conjunction<std::is_base_of<Bases,T>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ALL_HPP */
