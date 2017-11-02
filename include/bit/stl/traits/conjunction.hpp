/**
 * \file conjunction.hpp
 *
 * \brief This header contains the conjunction utility metafunction
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_CONJUNCTION_HPP
#define BIT_STL_TRAITS_CONJUNCTION_HPP

#include "bool_constant.hpp"

#include <type_traits> // std::conditional_t

namespace bit {
  namespace stl {

    /// \brief Type trait to determine the bool_constant from a logical
    ///        AND operation of other bool_constants
    ///
    /// The result is aliased as \c ::value
    template<typename...>
    struct conjunction;

    template<typename B1>
    struct conjunction<B1> : B1{};

    template<typename B1, typename... Bn>
    struct conjunction<B1, Bn...>
      : std::conditional_t<B1::value, conjunction<Bn...>, B1>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_CONJUNCTION_HPP */
