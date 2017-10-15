/**
 * \file type_relationships.hpp
 *
 * \brief This internal library provides type-traits for relationships between
 *        types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_STL_DETAIL_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP
#define BIT_STL_DETAIL_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP

#include "../invoke.hpp"

namespace bit {
  namespace stl {

    namespace detail {

      template<typename T, std::size_t Count>
      struct pointer_rank : size_constant<Count>{};

      template<typename T, std::size_t Count>
      struct pointer_rank<T*,Count> : pointer_rank<std::decay_t<T>,Count+1>{};
    }

    /// \brief Determines the level of indirection of a given type T
    ///
    /// This effectively counts the number of pointer types in a given type T
    ///
    /// The result is stored in \c ::value
    template<typename T>
    using pointer_rank = detail::pointer_rank<T,0>;

    template<typename T>
    constexpr std::size_t pointer_rank_v = pointer_rank< std::decay_t<T> >::value;

    //--------------------------------------------------------------------------

    template<typename T, typename U>
    struct is_same_sign : bool_constant<
      (std::is_signed<T>::value   == std::is_signed<U>::value)   &&
      (std::is_unsigned<T>::value == std::is_unsigned<U>::value)
    >{};

    template<typename T, typename U>
    struct is_same_constness : bool_constant<
      (std::is_const<T>::value == std::is_const<U>::value)
    >{};

    template<typename T, typename U>
    struct is_same_volatility : bool_constant<
      (std::is_volatile<T>::value == std::is_volatile<U>::value)
    >{};

    template<typename T, typename U>
    struct is_same_cv : bool_constant<
      is_same_constness<T,U>::value &&
      is_same_volatility<T,U>::value
    >{};

    template<typename T, typename U>
    struct is_same_ref : bool_constant<
      std::is_lvalue_reference<T>::value == std::is_lvalue_reference<U>::value &&
      std::is_rvalue_reference<T>::value == std::is_rvalue_reference<U>::value &&
      std::is_reference<T>::value == std::is_reference<U>::value
    >{};

    template<typename T, typename U>
    struct is_same_pointer : bool_constant<
      pointer_rank<T>::value == pointer_rank<U>::value &&
      std::is_pointer<T>::value == std::is_pointer<U>::value
    >{};

    template<typename T, typename U>
    constexpr bool is_same_pointer_v = is_same_pointer<T,U>::value;

    //--------------------------------------------------------------------------

    template<typename Func>
    struct is_const_member_function_pointer : std::false_type{};

    template<typename C, typename R, typename...Args>
    struct is_const_member_function_pointer<R (C::*)(Args...) const> : std::true_type{};

    template<typename C, typename R, typename...Args>
    struct is_const_member_function_pointer<R (C::*)(Args...) const volatile> : std::true_type{};

    template<typename Func>
    constexpr bool is_const_member_function_pointer_v
      = is_const_member_function_pointer<Func>::value;

    //--------------------------------------------------------------------------

    template<typename Func>
    struct is_volatile_member_function_pointer : std::false_type{};

    template<typename C, typename R, typename...Args>
    struct is_volatile_member_function_pointer<R (C::*)(Args...) volatile> : std::true_type{};

    template<typename C, typename R, typename...Args>
    struct is_volatile_member_function_pointer<R (C::*)(Args...) const volatile> : std::true_type{};

    template<typename Func>
    constexpr bool is_volatile_member_function_pointer_v
      = is_volatile_member_function_pointer<Func>::value;

    //--------------------------------------------------------------------------

    template<typename Func>
    struct is_cv_member_function_pointer : std::false_type{};

    template<typename C, typename R, typename...Args>
    struct is_cv_member_function_pointer<R (C::*)(Args...) const volatile> : std::true_type{};

    template<typename Func>
    constexpr bool is_cv_member_function_poiner_v
      = is_cv_member_function_pointer<Func>::value;

    //--------------------------------------------------------------------------
    // Type Relationships
    //--------------------------------------------------------------------------

    template<typename Fn, typename... Types>
    using is_invocable = is_detected<invoke_result_t,Fn,Types...>;

    template<typename Fn, typename... Types>
    constexpr bool is_invocable_v = is_invocable<Fn,Types...>::value;

    //--------------------------------------------------------------------------

    template<typename R, typename Fn, typename... Types>
    using is_invocable_r = is_detected_convertible<R,invoke_result_t,Fn,Types...>;

    template<typename R, typename Fn, typename... Types>
    constexpr bool is_invocable_r_v = is_invocable_r<R,Fn,Types...>::value;

    //--------------------------------------------------------------------------

    template<typename Fn, typename... Types>
    using is_nothrow_invocable = conjunction<bool_constant<noexcept( detail::INVOKE( std::declval<Fn>(), std::declval<Types>()... ) )>,
                                             is_invocable<Fn,Types...>>;

    template<typename Fn, typename... Types>
    constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Fn,Types...>::value;

    //--------------------------------------------------------------------------

    template<typename R, typename Fn, typename... Types>
    using is_nothrow_invocable_r = conjunction<bool_constant<noexcept( detail::INVOKE( std::declval<Fn>(), std::declval<Types>()... ) )>,
                                               is_invocable_r<R,Fn,Types...>>;

    template<typename R, typename Fn, typename... Types>
    constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<R,Fn,Types...>::value;

    //--------------------------------------------------------------------------
    // Plural Comparisons
    //--------------------------------------------------------------------------

    template<typename...Ts>
    struct type_list{};

    template<typename To, typename...Froms>
    struct are_convertible_to : conjunction<std::is_convertible<Froms,To>...>{};

    template<typename Derived, typename...Bases>
    struct are_bases_of : conjunction<std::is_base_of<Bases,Derived>...>{};

    template<typename Base, typename...Derived>
    struct is_bases_of : conjunction<std::is_base_of<Base,Derived>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP */
