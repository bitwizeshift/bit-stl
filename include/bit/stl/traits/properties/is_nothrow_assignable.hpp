/**
 * \file is_trivially_assignable.hpp
 *
 * \brief This header defines a type trait for checking trivially-assignability
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_ASSIGNABLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_ASSIGNABLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_trivially_assignable

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is trivially assignable
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    using is_trivially_assignable = std::is_trivially_assignable<T,U>;

    /// \brief Helper utility to extract is_trivially_assignable::type
    template<typename T, typename U>
    constexpr bool is_trivially_assignable_v = is_trivially_assignable<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_TRIVIALLY_ASSIGNABLE_HPP */
