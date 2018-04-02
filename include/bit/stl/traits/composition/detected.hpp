/*****************************************************************************
 * \file
 * \brief This header defines type traits for the detected_t idiom
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
#ifndef BIT_STL_TRAITS_COMPOSITION_DETECTED_HPP
#define BIT_STL_TRAITS_COMPOSITION_DETECTED_HPP

#include "nonesuch.hpp" // nonesuch
#include "void_t.hpp"   // void_t

#include <type_traits> // std::is_convertible, std::is_same

namespace bit {
  namespace stl {
    namespace detail {

      template<typename Default,
               typename AlwaysVoid,
               template<typename...> class Op,
               typename...Args>
      struct detector
      {
        using value_t = std::false_type;
        using type = Default;
      };

      template<typename Default,
               template<typename...> class Op,
               typename...Args>
      struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
        using value_t = std::true_type;
        using type = Op<Args...>;
      };

    } // namespace detail

    template<template<typename...> class Op, typename... Args>
    using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

    template<template<typename...> class Op, typename... Args >
    constexpr bool is_detected_v = is_detected<Op, Args...>::value;

    template<template<typename...> class Op, typename... Args>
    using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

    //-------------------------------------------------------------------------

    template<typename Default, template<typename...> class Op, typename... Args>
    using detected_or = detail::detector<Default, void, Op, Args...>;

    template<typename Default, template<typename...> class Op, typename... Args >
    using detected_or_t = typename detected_or<Default, Op, Args...>::type;

    //-------------------------------------------------------------------------

    template<typename Expected, template<typename...> class Op, typename... Args>
    using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

    template<typename Expected, template<typename...> class Op, typename... Args>
    constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

    //-------------------------------------------------------------------------

    template<typename To, template<typename...> class Op, typename... Args>
    using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

    template<typename To, template<typename...> class Op, typename... Args>
    constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_DETECTED_HPP */
