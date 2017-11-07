/**
 * \file function_argument.hpp
 *
 * \brief This header defines a type-trait to access the nth argument type of
 *        a given function
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_FUNCTION_ARGUMENT_TYPE_HPP
#define BIT_STL_TRAITS_PROPERTIES_FUNCTION_ARGUMENT_TYPE_HPP

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

#endif /* BIT_STL_TRAITS_PROPERTIES_FUNCTION_ARGUMENT_TYPE_HPP */
