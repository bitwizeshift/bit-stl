/**
 * \file disjunction.hpp
 *
 * \brief This header contains the disjunction utility metafunction
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_DISJUNCTION_HPP
#define BIT_STL_TRAITS_DISJUNCTION_HPP

#include "bool_constant.hpp"

#include <type_traits> // std::conditional_t

namespace bit {
  namespace stl {

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        OR operations of other bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename...>
    struct disjunction : false_type { };

    template<typename B1>
    struct disjunction<B1> : B1{};

    template<typename B1, typename... Bn>
    struct disjunction<B1, Bn...>
      : std::conditional_t<B1::value != false, B1, disjunction<Bn...>>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_DISJUNCTION_HPP */
