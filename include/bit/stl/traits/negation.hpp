/**
 * \file negation.hpp
 *
 * \brief This header contains the negation utility metafunction
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_NEGATION_HPP
#define BIT_STL_TRAITS_NEGATION_HPP

#include "bool_constant.hpp"

namespace bit {
  namespace stl {

    template<typename B>
    struct negation : bool_constant<!bool(B::value)>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_NEGATION_HPP */
