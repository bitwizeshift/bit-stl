/*****************************************************************************
 * \file
 * \brief This header defines a type-trait to access the nth argument type of
 *        a given function
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
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_FUNCTION_ARGUMENT_TYPE_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_FUNCTION_ARGUMENT_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "nth_type.hpp"

#include <type_traits> // std::decay_t
#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {

    /// \brief Type-trait to access the \c Ith argument type of a given function
    ///
    /// The result is aliased as \c ::type
    template<std::size_t I, typename Fn>
    struct function_argument;

    template<std::size_t I, typename Fn>
    struct function_argument<I,Fn&> : function_argument<I,std::decay_t<Fn>>{};

    template<std::size_t I, typename Fn>
    struct function_argument<I,Fn&&> : function_argument<I,std::decay_t<Fn>>{};

    //-------------------------------------------------------------------------

    template<std::size_t I, typename R, typename...Types>
    struct function_argument<I,R(Types...)> : nth_type<I,Types...>{};

    template<std::size_t I, typename R, typename...Types>
    struct function_argument<I,R(Types...) const> : nth_type<I,Types...>{};

    template<std::size_t I, typename R, typename...Types>
    struct function_argument<I,R(Types...) volatile> : nth_type<I,Types...>{};

    template<std::size_t I, typename R, typename...Types>
    struct function_argument<I,R(Types...) const volatile> : nth_type<I,Types...>{};

    //-------------------------------------------------------------------------

    template<std::size_t I, typename R, typename...Types>
    struct function_argument<I,R(*)(Types...)> : nth_type<I,Types...>{};

    //-------------------------------------------------------------------------

    template<std::size_t I, typename C, typename R, typename...Types>
    struct function_argument<I,R(C::*)(Types...)> : nth_type<I,Types...>{};

    template<std::size_t I, typename C, typename R, typename...Types>
    struct function_argument<I,R(C::*)(Types...) const> : nth_type<I,Types...>{};

    template<std::size_t I, typename C, typename R, typename...Types>
    struct function_argument<I,R(C::*)(Types...) volatile> : nth_type<I,Types...>{};

    template<std::size_t I, typename C, typename R, typename...Types>
    struct function_argument<I,R(C::*)(Types...) const volatile> : nth_type<I,Types...>{};

    //-------------------------------------------------------------------------

    /// \brief Helper utility to extract function_argument::type
    template<std::size_t I, typename Fn>
    using function_argument_t = typename function_argument<I,Fn>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_FUNCTION_ARGUMENT_TYPE_HPP */
