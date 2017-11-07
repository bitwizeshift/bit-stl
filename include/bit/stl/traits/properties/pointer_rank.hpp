/**
 * \file pointer_rank.hpp
 *
 * \brief This header defines the type-trait for determining the level of
 *        indirection
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_POINTER_RANK_HPP
#define BIT_STL_TRAITS_PROPERTIES_POINTER_RANK_HPP

#include "../composition/size_constant.hpp"

#include <type_traits> // std::decay_t
#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {

    namespace detail {

      template<typename T, std::size_t Count>
      struct pointer_rank : size_constant<Count>{};

      template<typename T, std::size_t Count>
      struct pointer_rank<T*,Count> : pointer_rank<std::decay_t<T>,Count+1>{};
    }

    /// \brief Determines the level of indirection of a given type T
    ///
    /// This effectively counts the number of pointer types in a given type T
    ///
    /// The result is stored in \c ::value
    template<typename T>
    using pointer_rank = detail::pointer_rank<T,0>;

    /// \brief Helper utility to extract pointer_rank::value
    template<typename T>
    constexpr std::size_t pointer_rank_v = pointer_rank< std::decay_t<T> >::value;
  } // namespace stl
} // namespace bit



#endif /* BIT_STL_TRAITS_PROPERTIES_POINTER_RANK_HPP */
