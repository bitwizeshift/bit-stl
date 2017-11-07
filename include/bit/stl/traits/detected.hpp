/**
 * \file detected.hpp
 *
 * \brief This header defines type traits for the detected_t idiom
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_DETECTED_HPP
#define BIT_STL_TRAITS_DETECTED_HPP

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

#endif /* BIT_STL_TRAITS_DETECTED_HPP */
