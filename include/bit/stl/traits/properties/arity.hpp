/**
 * \file arity.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_ARITY_HPP
#define BIT_STL_TRAITS_PROPERTIES_ARITY_HPP

#include "../size_constant.hpp"

#include <type_traits> // std::decay_t
#include <cstddef>     // std::size_t

namespace bit {
  namespace stl {

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

    template<typename Fn>
    constexpr std::size_t arity_v = arity<Fn>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_ARITY_HPP */
