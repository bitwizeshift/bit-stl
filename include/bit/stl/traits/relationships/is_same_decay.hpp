/**
 * \file is_same_decay.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_DECAY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_DECAY_HPP

#include <type_traits> // std::is_same, std::decay_t

namespace bit {
  namespace stl {

    /// \brief Type trait to determine whether a type is the same with a different
    ///        decay type
    template<typename T, typename U>
    using is_same_decay = std::is_same<std::decay_t<T>,std::decay_t<U>>;

    template<typename T, typename U>
    constexpr bool is_same_decay_v = is_same_decay<T,U>::value;


  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_DECAY_HPP */
