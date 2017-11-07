/**
 * \file size_constant.hpp
 *
 * \brief This header contains the definition to the utility metafunction
 *        size_constant
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_COMPOSITION_SIZE_CONSTANT_HPP
#define BIT_STL_TRAITS_COMPOSITION_SIZE_CONSTANT_HPP

#include "integral_constant.hpp"
#include "bool_constant.hpp"

#include <cstddef> // std::size_t

namespace bit {
  namespace stl {

    /// \brief This utility metafunction provides compile-time size values
    ///        as an integral constant
    ///
    /// The value is aliased as \c ::value
    template<std::size_t Size>
    using size_constant = std::integral_constant<std::size_t,Size>;

    /// \brief Convenience template variable to extract size_constant::value
    ///
    /// This is always the same as the template variable (trivial)
    template<std::size_t Size>
    constexpr std::size_t size_constant_v = size_constant<Size>::value;

    //-------------------------------------------------------------------------

    /// \brief Utility metafunction that determines whether \p T is a
    ///        size_constant
    ///
    /// \tparam T the type to check
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_size_constant : false_type{};

    template<std::size_t Size>
    struct is_size_constant<size_constant<Size>> : true_type{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_SIZE_CONSTANT_HPP */
