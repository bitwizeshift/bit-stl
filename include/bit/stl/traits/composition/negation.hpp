/**
 * \file negation.hpp
 *
 * \brief This header contains the negation utility metafunction
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_COMPOSITION_NEGATION_HPP
#define BIT_STL_TRAITS_COMPOSITION_NEGATION_HPP

#include "bool_constant.hpp"

namespace bit {
  namespace stl {

    /// \brief Utility metafunction for negating a bool_constant
    ///
    /// The result is aliased as \c ::value
    ///
    /// \tparam B the constant
    template<typename B>
    struct negation : bool_constant<!bool(B::value)>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_NEGATION_HPP */
