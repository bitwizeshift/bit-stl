/**
 * \file arity.hpp
 *
 * \brief This header defines a type-trait to determine the arity of a function
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_ARITY_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_ARITY_HPP

#include "../composition/size_constant.hpp"

#include <type_traits> // std::decay_t
#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine the arity of a function
    ///
    /// The result is aliased as \c ::value
    template<typename Fn>
    struct arity;

    template<typename Fn>
    struct arity<Fn&> : arity<std::decay_t<Fn>>{};

    template<typename Fn>
    struct arity<Fn&&> : arity<std::decay_t<Fn>>{};

    //-------------------------------------------------------------------------

    template<typename R, typename...Types>
    struct arity<R(Types...)> : size_constant<sizeof...(Types)>{};

    template<typename R, typename...Types>
    struct arity<R(Types...) const> : size_constant<sizeof...(Types)>{};

    template<typename R, typename...Types>
    struct arity<R(Types...) volatile> : size_constant<sizeof...(Types)>{};

    template<typename R, typename...Types>
    struct arity<R(Types...) const volatile> : size_constant<sizeof...(Types)>{};

    //-------------------------------------------------------------------------

    template<typename R, typename...Types>
    struct arity<R(*)(Types...)> : size_constant<sizeof...(Types)>{};

    //-------------------------------------------------------------------------

    template<typename C, typename R, typename...Types>
    struct arity<R(C::*)(Types...)> : size_constant<sizeof...(Types)>{};

    template<typename C, typename R, typename...Types>
    struct arity<R(C::*)(Types...) const> : size_constant<sizeof...(Types)>{};

    template<typename C, typename R, typename...Types>
    struct arity<R(C::*)(Types...) volatile> : size_constant<sizeof...(Types)>{};

    template<typename C, typename R, typename...Types>
    struct arity<R(C::*)(Types...) const volatile> : size_constant<sizeof...(Types)>{};

    //-------------------------------------------------------------------------

    /// \brief Helper utility to extract arity::value
    template<typename Fn>
    constexpr std::size_t arity_v = arity<Fn>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_ARITY_HPP */
