/*****************************************************************************
 * \file
 * \brief TODO: Add description
 *****************************************************************************/
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_MEMBER_POINTER_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_MEMBER_POINTER_HPP

#include "../composition/disjunction.hpp"
#include "../composition/conjunction.hpp"

#include "is_member_object_pointer.hpp"
#include "is_member_function_pointer.hpp"

namespace bit {
  namespace stl {

    template<typename T>
    struct is_member_pointer : disjunction<is_member_object_pointer<T>,
                                           is_member_function_pointer<T>>{};

    template<typename T>
    constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

    //-------------------------------------------------------------------------

    template<typename...Ts>
    struct are_member_pointers : conjunction<is_member_pointer<Ts>...>{};

    template<typename...Ts>
    constexpr bool are_member_pointers_v = are_member_pointers<Ts...>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_MEMBER_POINTER_HPP */
