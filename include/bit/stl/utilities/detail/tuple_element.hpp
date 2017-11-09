/**
 * \file tuple_element.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_DETAIL_TUPLE_ELEMENT_HPP
#define BIT_STL_UTILITIES_DETAIL_TUPLE_ELEMENT_HPP

#include <cstddef> // std::size_t

namespace bit {
  namespace stl {

    template<std::size_t I, typename Tuple>
    struct tuple_element;

    template<std::size_t I, typename Tuple>
    using tuple_element_t = typename tuple_element<I,Tuple>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_TUPLE_ELEMENT_HPP */
