/**
 * \file is_base_of_all.hpp
 *
 * \brief This header defines a type-trait for determing if a base is the base
 *        of all derived types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ALL_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ALL_HPP

#include "../conjunction.hpp"

#include <type_traits> // std::is_base_of

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine that \c Base is the base of all
    ///        \c Derived
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam Base the base type
    /// \tparam Derived the derived types to check
    template<typename Base, typename...Derived>
    struct is_base_of_all : conjunction<std::is_base_of<Base,Derived>...>{};

    /// \brief Helper utility to extract is_base_of_all::value
    template<typename Base, typename...Derived>
    constexpr bool is_base_of_all_v = is_base_of_all<Base,Derived...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_BASE_OF_ALL_HPP */
