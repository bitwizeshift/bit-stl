/**
 * \file function_signature.hpp
 *
 * \brief This header contains a type trait that determines a function
 *        signature from a function type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_FUNCTION_SIGNATURE_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_FUNCTION_SIGNATURE_HPP

#include "../identity.hpp"

#include <type_traits> // std::decay

namespace bit {
  namespace stl {

    template<typename Fn>
    struct function_signature;

    // Decay pointers/references

    template<typename Fn>
    struct function_signature<Fn*> : function_signature<std::decay_t<Fn>>{};

    template<typename Fn>
    struct function_signature<Fn&> : function_signature<std::decay_t<Fn>>{};

    template<typename Fn>
    struct function_signature<Fn&&> : function_signature<std::decay_t<Fn>>{};

    // Translate function values

    template<typename R, typename...ArgTypes>
    struct function_signature<R(ArgTypes...)> : identity<R(ArgTypes...)>{};

    template<typename R, typename...ArgTypes>
    struct function_signature<R(ArgTypes...) const> : identity<R(ArgTypes...)>{};

    template<typename R, typename...ArgTypes>
    struct function_signature<R(ArgTypes...) volatile> : identity<R(ArgTypes...)>{};

    template<typename R, typename...ArgTypes>
    struct function_signature<R(ArgTypes...) const volatile> : identity<R(ArgTypes...)>{};

    // Translate member function pointers

    template<typename C, typename R, typename...ArgTypes>
    struct function_signature<R(C::*)(ArgTypes...)> : identity<R(ArgTypes...)>{};

    template<typename C, typename R, typename...ArgTypes>
    struct function_signature<R(C::*)(ArgTypes...) const> : identity<R(ArgTypes...)>{};

    template<typename C, typename R, typename...ArgTypes>
    struct function_signature<R(C::*)(ArgTypes...) volatile> : identity<R(ArgTypes...)>{};

    template<typename C, typename R, typename...ArgTypes>
    struct function_signature<R(C::*)(ArgTypes...) const volatile> : identity<R(ArgTypes...)>{};

    template<typename T>
    using function_signature_t = typename function_signature<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_FUNCTION_SIGNATURE_HPP */
