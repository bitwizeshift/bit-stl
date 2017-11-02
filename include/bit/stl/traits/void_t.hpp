/**
 * \file void_t.hpp
 *
 * \brief This header defines utilities for the void_t idiom
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_VOID_T_HPP
#define BIT_STL_TRAITS_VOID_T_HPP

#include "identity.hpp"

namespace bit {
  namespace stl {
    namespace detail {
      /// \brief struct helper for void_t
      template<typename...>
      struct voidify : identity<void>{};
    } // namespace detail

    /// \brief Utility metafunction that maps a sequence of any types to the
    ///        type void
    ///
    /// This is used for determining validity of expressions using SFINAE
    template<typename...Types>
    using void_t = typename detail::voidify<Types...>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_VOID_T_HPP */
