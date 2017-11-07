/**
 * \file is_volatile_member_function_pointer.hpp
 *
 * \brief This header defines a type-trait for determining volatile-qualified
 *        member function pointers
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_VOLATILE_MEMBER_FUNCTION_POINTER_HPP_
#define BIT_STL_TRAITS_PROPERTIES_IS_VOLATILE_MEMBER_FUNCTION_POINTER_HPP_

#include "../bool_constant.hpp"

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c Func is a volatile member function
    ///        pointer
    ///
    /// \tparam Func the function pointer to check
    template<typename Func>
    struct is_volatile_member_function_pointer : std::false_type{};

    template<typename C, typename R, typename...Args>
    struct is_volatile_member_function_pointer<R (C::*)(Args...) volatile> : true_type{};

    template<typename C, typename R, typename...Args>
    struct is_volatile_member_function_pointer<R (C::*)(Args...) const volatile> : true_type{};

    /// \brief Helper utility to extract is_volatile_member_function_pointer::type
    template<typename Func>
    constexpr bool is_volatile_member_function_pointer_v
      = is_volatile_member_function_pointer<Func>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_VOLATILE_MEMBER_FUNCTION_POINTER_HPP_ */
