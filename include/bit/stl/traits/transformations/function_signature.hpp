/**
 * \file function_signature.hpp
 *
 * \brief This header contains a type trait that determines a function
 *        signature from a function type
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
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_FUNCTION_SIGNATURE_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_FUNCTION_SIGNATURE_HPP

#include "../composition/identity.hpp"

#include <type_traits> // std::decay

namespace bit {
  namespace stl {

    /// \brief Metafunction to extract the signature of a given function type
    ///
    /// The result is aliased as \c ::type
    ///
    /// \tparam fn the function to check
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

    /// \brief Helper utility to extract function_signature::type
    template<typename T>
    using function_signature_t = typename function_signature<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_FUNCTION_SIGNATURE_HPP */
