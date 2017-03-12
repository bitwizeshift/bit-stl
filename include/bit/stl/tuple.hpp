/**
 * \file tuple.hpp
 *
 * \brief This header contains utility extensions to the standard utility
 *        header
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_TUPLE_HPP
#define BIT_STL_TUPLE_HPP

// local bfstd library
#include "functional.hpp"

#include <cstddef> // for std::size_t
#include <tuple>   // for std::tuple
#include <utility> // for std::forward

namespace bit {
  namespace stl {

  /// \brief Invoke the Callable object \p function with a \p tuple of
  ///        arguments
  ///
  /// \param function Callable object to be invoked
  /// \param tuple    tuple whose elements to be used as arguments to \p function
  /// \return the value returned from \p function
  template<typename Func, typename Tuple>
  constexpr decltype(auto) apply( Func&& function, Tuple&& tuple );

  /// \brief Construct an object of type \t T, using the elements of the
  ///        tuple t as the arguments to the constructor
  ///
  /// \param tuple tuple whose elements to be used as arguments to the constructor of T
  /// \return The constructed T object
  template<typename T, typename Tuple>
  constexpr T make_from_tuple( Tuple&& tuple );

  } // namespace stl
} // namespace bit

#include "detail/tuple.inl"

#endif /* BIT_STL_TUPLE_HPP */
