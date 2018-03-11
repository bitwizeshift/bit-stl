/**
 * \file is_const_member_function_pointer.hpp
 *
 * \brief This header defines a type-trait for determining const-qualified
 *        member function pointers
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
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_CONST_MEMBER_FUNCTION_POINTER_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_CONST_MEMBER_FUNCTION_POINTER_HPP

#include "../composition/bool_constant.hpp"

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c Func is a const member function
    ///        pointer
    ///
    /// \tparam Func the function pointer to check
    template<typename Func>
    struct is_const_member_function_pointer : false_type{};

    template<typename C, typename R, typename...Args>
    struct is_const_member_function_pointer<R (C::*)(Args...) const> : true_type{};

    template<typename C, typename R, typename...Args>
    struct is_const_member_function_pointer<R (C::*)(Args...) const volatile> : true_type{};

    /// \brief Helper utility to extract is_const_member_function_pointer::type
    template<typename Func>
    constexpr bool is_const_member_function_pointer_v
      = is_const_member_function_pointer<Func>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_CONST_MEMBER_FUNCTION_POINTER_HPP */
