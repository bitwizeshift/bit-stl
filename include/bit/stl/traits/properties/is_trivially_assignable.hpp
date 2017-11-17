/**
 * \file is_nothrow_assignable.hpp
 *
 * \brief This header defines a type trait for checking nothrow-assignability
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_ASSIGNABLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_ASSIGNABLE_HPP

#include "../composition/conjunction.hpp"

#include <type_traits> // std::is_nothrow_assignable

namespace bit {
  namespace stl {

    /// \brief Type trait for determining if a type is nothrow assignable
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    using is_nothrow_assignable = std::is_nothrow_assignable<T,U>;

    /// \brief Helper utility to extract is_nothrow_assignable::type
    template<typename T, typename U>
    constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_NOTHROW_ASSIGNABLE_HPP */
