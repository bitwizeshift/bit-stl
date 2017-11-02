/**
 * \file bool_constant.hpp
 *
 * \brief This header contains the definition to the utility metafunction
 *        bool_constant
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_BOOL_CONSTANT_HPP
#define BIT_STL_TRAITS_BOOL_CONSTANT_HPP

#include "integral_constant.hpp"

namespace bit {
  namespace stl {

    /// \brief This utility metafunction provides compile-time boolean values
    ///        as an integral constant
    ///
    /// The value is aliased as \c ::value
    template<bool B>
    using bool_constant = integral_constant<bool,B>;

    /// \brief Convenience template variable to extract bool_constant::value
    ///
    /// This is always the same as the template variable (trivial)
    template<bool B>
    constexpr bool bool_constant_v = bool_constant<B>::value;

    //-------------------------------------------------------------------------

    using true_type  = bool_constant<true>;
    using false_type = bool_constant<false>;

    //-------------------------------------------------------------------------

    /// \brief Utility metafunction that determines whether \p T is a
    ///        size_constant
    ///
    /// \tparam T the type to check
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_bool_constant : false_type{};

    template<bool B>
    struct is_bool_constant<bool_constant<B>> : true_type{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_BOOL_CONSTANT_HPP */
