/*****************************************************************************
 * \file
 * \brief TODO: Add description
 *****************************************************************************/
#ifndef BIT_STL_UTILITIES_DETAIL_TUPLE_SIZE_HPP
#define BIT_STL_UTILITIES_DETAIL_TUPLE_SIZE_HPP

#include <cstddef> // std::size_t

namespace bit {
  namespace stl {

    template<typename Tuple>
    struct tuple_size;

    template<typename Tuple>
    constexpr std::size_t tuple_size_v = tuple_size<Tuple>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_TUPLE_SIZE_HPP */
