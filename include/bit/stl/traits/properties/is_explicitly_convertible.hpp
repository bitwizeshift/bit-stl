/**
 * \file is_explicitly_convertible.hpp
 *
 * \brief This header defines a type-trait for determining whether a type is
 *        explicitly convertible to another type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP

#include "../negation.hpp"
#include "../conjunction.hpp"

#include <type_traits> // is_constructible, is_convertible

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c From is explicitly convertible to
    ///        \c to
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam From the type casting from
    /// \tparam To the type casting to
    template<typename From, typename To>
    struct is_explicitly_convertible :
      conjunction<std::is_constructible<To,From>, negation<std::is_convertible<From,To>>>{};

    /// \brief Helper utility to extract nth_type::type
    template<typename From, typename To>
    constexpr bool is_explicitly_convertible_v = is_explicitly_convertible<From,To>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_EXPLICITLY_CONVERTIBLE_HPP */
