/*****************************************************************************
 * \file
 * \brief This header contains various forwards and utilities for classes that
 *        act and behave as tuples. This includes, but is not limited to,
 *        the 'array', 'tuple, 'pair', 'compressed_tuple', and 'compressed_pair'
 *        classes.
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef BIT_STL_UTILITIES_TUPLE_UTILITIES_HPP
#define BIT_STL_UTILITIES_TUPLE_UTILITIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "types.hpp"   // size_t
#include <type_traits> // std::decay
#include <utility>     // std::forward, std::index_sequence

namespace bit {
  namespace stl {

    // Note: Neither std::tuple_size nor std::tuple_element are allowed, by the
    //       standard, to be specialized by user types. In order to work around
    //       this, bit::stl defines tuple_size and tuple_element that *are*
    //       safe to specialize.

    template<typename Tuple>
    struct tuple_size;

    template<typename Tuple>
    constexpr size_t tuple_size_v = tuple_size<Tuple>::value;

    //-------------------------------------------------------------------------

    template<size_t I, typename Tuple>
    struct tuple_element;

    template<size_t I, typename Tuple>
    using tuple_element_t = typename tuple_element<I,Tuple>::type;

    //-------------------------------------------------------------------------

    // Forward declaration with no definition
    // This exists so that ADL-lookup can be done with 'get' from different
    // namespaces, if they are so provided for types. This allows std::get to
    // function independently from bit::stl::get
    template<size_t I, typename Tuple>
    tuple_element_t<I,std::decay_t<Tuple>>& get( Tuple& t );
    template<size_t I, typename Tuple>
    const tuple_element_t<I,std::decay_t<Tuple>>& get( const Tuple& t );
    template<size_t I, typename Tuple>
    tuple_element_t<I,std::decay_t<Tuple>>&& get( Tuple&& t );
    template<size_t I, typename Tuple>
    const tuple_element_t<I,std::decay_t<Tuple>>&& get( const Tuple&& t );
    template<typename T, typename Tuple>
    T& get( Tuple& t );
    template<typename T, typename Tuple>
    const T& get( const Tuple& t );
    template<typename T, typename Tuple>
    T&& get( Tuple&& t );
    template<typename T, typename Tuple>
    const T&& get( const Tuple&& t );

    //-------------------------------------------------------------------------

    /// \brief Invoke the Callable object \p function with a \p tuple of
    ///        arguments
    ///
    /// \param function Callable object to be invoked
    /// \param tuple    tuple whose elements to be used as arguments to
    ///                 \p function
    /// \return the value returned from \p function
    template<typename Func, typename Tuple>
    constexpr decltype(auto) apply( Func&& function, Tuple&& tuple );

    /// \brief Construct an object of type \t T, using the elements of the
    ///        tuple t as the arguments to the constructor
    ///
    /// \param tuple tuple whose elements to be used as arguments to the
    ///              constructor of T
    /// \return The constructed T object
    template<typename T, typename Tuple>
    constexpr T make_from_tuple( Tuple&& tuple );

  } // namespace stl
} // namespace bit

#include "detail/tuple_utilities.inl"

#endif /* BIT_STL_UTILITIES_TUPLE_UTILITIES_HPP */
