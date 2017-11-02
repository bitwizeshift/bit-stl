/**
 * \file is_const_member_function_pointer.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_CONST_MEMBER_FUNCTION_POINTER_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_CONST_MEMBER_FUNCTION_POINTER_HPP

#include "../bool_constant.hpp"

namespace bit {
  namespace stl {

    template<typename Func>
    struct is_const_member_function_pointer : false_type{};

    template<typename C, typename R, typename...Args>
    struct is_const_member_function_pointer<R (C::*)(Args...) const> : true_type{};

    template<typename C, typename R, typename...Args>
    struct is_const_member_function_pointer<R (C::*)(Args...) const volatile> : true_type{};

    template<typename Func>
    constexpr bool is_const_member_function_pointer_v
      = is_const_member_function_pointer<Func>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_CONST_MEMBER_FUNCTION_POINTER_HPP */
