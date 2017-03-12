/**
 * \file type_properties.hpp
 *
 * \brief This internal library detects properties of types.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_DETAIL_TYPE_TRAITS_TYPE_FUNCTION_HPP
#define BIT_STL_DETAIL_TYPE_TRAITS_TYPE_FUNCTION_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

#include <utility>
#include "../../internal/invoke.hpp"

namespace bit {
  namespace stl {
    namespace detail {

      /// \brief Type trait for getting the nth argument type from a variadic
      ///        template.
      ///
      /// This is used for composition in \c function_traits
      ///
      /// The result is aliased as \c ::type
      template<size_t n, typename...Args>
      struct arg_tuple : identity<
          typename std::tuple_element<n, std::tuple<Args...>
        >::type>
      {
        static_assert(n<sizeof...(Args),"Index out of range");
      };

      //------------------------------------------------------------------------

      /// \brief Identity type traits for all function traits to inherit from
      ///
      /// This type is used in composition.
      template<typename Ret,typename...Args>
      struct function_traits_identity{
        static constexpr size_t arity = sizeof...(Args); /// Number of arguments

        typedef Ret result_type; /// Return type

        template<size_t n>
        using arg = arg_tuple<n,Args...>; /// Alias of the nth arg
      };

      //------------------------------------------------------------------------

      /// \brief Type traits for retrieving various parts of a function
      ///
      /// This aliases the following
      /// - The number of arguments to the function as \c ::arity
      /// - The type of the return as \c ::result_type
      /// - The nth argument as \c ::arg<n>::type
      template<typename T>
      struct function_traits_impl{
        static_assert(std::is_function<T>::value,"T must be function type!");
      };

      template <typename Ret, typename...Args>
      struct function_traits_impl<Ret(Args...)>
        : function_traits_identity<Ret,Args...>{};

      template <typename Ret, typename...Args>
      struct function_traits_impl<Ret(*)(Args...)>
        : function_traits_identity<Ret,Args...>{};


      //------------------------------------------------------------------------


      /// \brief Type traits for retrieving various parts of a member function
      ///
      /// This aliases the following
      /// - The number of arguments to the function as \c ::arity
      /// - The type of the return as \c ::result_type
      /// - The nth argument as \c ::arg<n>::type
      template<typename T>
      struct member_function_traits_impl{
        static_assert(std::is_member_function_pointer<T>::value,"T must be member function pointer!");
      };

      template <typename C, typename Ret, typename... Args>
      struct member_function_traits_impl<Ret(C::*)(Args...)>
        : function_traits_identity<Ret,Args...>{};

      template <typename C, typename Ret, typename... Args>
      struct member_function_traits_impl<Ret(C::*)(Args...) const>
        : function_traits_identity<Ret,Args...>{};

      template <typename C, typename Ret, typename... Args>
      struct member_function_traits_impl<Ret(C::*)(Args...) volatile>
        : function_traits_identity<Ret,Args...>{};

      template <typename C, typename Ret, typename... Args>
      struct member_function_traits_impl<Ret(C::*)(Args...) const volatile>
        : function_traits_identity<Ret,Args...>{};

      //------------------------------------------------------------------------

      /// \brief Type trait for retrieving various parts of a functor
      ///
      /// This aliases the following
      /// - The number of arguments to the function as \c ::arity
      /// - The type of the return as \c ::result_type
      /// - The nth argument as \c ::arg<n>::type
      template<typename T>
      struct functor_traits_impl : public member_function_traits_impl<decltype(&T::operator())>{
        static_assert(std::is_class<T>::value,"T must be a class type!");
      };

      //------------------------------------------------------------------------

      /// \brief Type trait for determining whether the given type is a functor
      ///
      /// This only works for normal, non-templated operator() types
      ///
      /// The result is aliased as \c ::value
      template<typename T>
      class has_nontemplated_functor : public sfinae_base{
        template<typename C> static yes_type test(decltype(&C::operator()));
        template<typename C> static no_type  test(...);

      public:
        static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes_type);
      };


      /// \brief type-trait to check if \c T is a functor
      ///
      /// The result is aliased as \c ::value
      template<typename T>
      using is_functor = disjunction<has_nontemplated_functor<T>>;

    } // namespace detail

    /// \brief Type trait to retrieve the various parts of a callable
    ///        function-like object
    ///
    /// This aliases the following
    /// - The number of arguments to the function as \c ::arity
    /// - The type of the return as \c ::result_type
    /// - The nth argument as \c ::arg<n>::type
    ///
    /// \tparam T the function to retrieve types for
    template<typename T>
    struct function_traits : std::conditional<
      std::is_class<typename std::decay<T>::type>::value,
      detail::functor_traits_impl<typename std::decay<T>::type>,
      typename std::conditional<
        std::is_member_function_pointer<typename std::decay<T>::type>::value,
        detail::member_function_traits_impl<typename std::decay<T>::type>,
        detail::function_traits_impl<typename std::decay<T>::type>
      >::type
    >::type{};

    /// \brief Helper variable template for retrieving the \c ::type of
    ///        \c function_traits<T>::arg<N>
    template<typename Func,std::size_t N>
    using nth_argument_of = typename function_traits<Func>::template arg<N>;

    template<typename Func,std::size_t N>
    using nth_argument_of_t = typename nth_argument_of<Func,N>::type;

    //--------------------------------------------------------------------------

    /// \brief Type trait to determine whether \p T can be passed as \p U
    ///        to a function argument
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_passable_as : std::is_convertible<T,U>{};

    template<typename T>
    struct is_passable_as<T,T> : std::is_copy_constructible<T>{};

    template<typename T>
    struct is_passable_as<T const, T> : std::is_copy_constructible<T>{};

    template<typename T>
    struct is_passable_as<T const, T const&> : std::true_type{};

    template<typename T>
    struct is_passable_as<T, T&> : std::true_type{};

    template<typename T>
    struct is_passable_as<T, T const&> : std::true_type{};

    template<typename T>
    struct is_passable_as<T*, T*> : std::true_type{};

    template<typename T>
    struct is_passable_as<T*, T const*> : std::true_type{};

    namespace detail {

      template<typename Fn, typename R = void, typename = void>
      struct is_callable : std::false_type{};

      template<typename Fn>
      struct is_callable<Fn,void,void_t<std::result_of_t<Fn>>>
        : std::true_type{};

      template<typename Func, typename R>
      struct is_callable<Func,R, void_t<std::result_of_t<Func>>>
        : std::is_convertible<std::result_of_t<Func>,R>{};

    } // namespace detail

    template<typename Func, typename R = void>
    using is_callable = detail::is_callable<Func,R>;

    template<typename Func, typename R = void>
    constexpr bool is_callable_v = is_callable<Func,R>::value;

    //------------------------------------------------------------------------

    namespace detail {

      template<typename Fn, typename...Args>
      struct is_invokable
      {
        template<typename Fn2, typename...Args2>
        static auto test( Fn2&&, Args2&&... )
          -> decltype(invoke_impl(std::declval<Fn2>(), std::declval<Args2>()...), std::true_type{});

        static auto test(...)
          -> std::false_type;

        static constexpr bool value =
          decltype(test(std::declval<Fn>(), std::declval<Args>()...))::value;
      };

    } // namespace detail

    /// \brief Type trait to determine whether \p Fn is invokable with
    ///        \p Args...
    ///
    /// Formally, the expression:
    /// \code
    /// INVOKE( std::declval<Fn>(), std::declval<Args>()... )
    /// \endcode
    /// is well formed
    ///
    /// The result is aliased as \c ::value
    template<typename Fn, typename...Args>
    using is_invokable = detail::is_invokable<Fn,Args...>;

    /// \brief Type-trait helper to retrieve the \c ::value of is_invokable
    template<typename Fn, typename...Args>
    constexpr bool is_invokable_v = is_invokable<Fn,Args...>::value;

    //------------------------------------------------------------------------

    namespace detail {

      template<typename Fn, typename...Args>
      struct is_nothrow_invokable
      {
        template<typename Fn2, typename...Args2>
        static auto test( Fn2&&, Args2&&... )
          -> decltype(invoke_impl(std::declval<Fn2>(), std::declval<Args2>()...),
                      std::integral_constant<bool,noexcept(invoke_impl(std::declval<Fn2>(), std::declval<Args2>()...))>{});

        static auto test(...)
          -> std::false_type;

        static constexpr bool value =
          decltype(test(std::declval<Fn>(), std::declval<Args>()...))::value;
      };

    } // namespace detail

    /// \brief Type trait to determine whether \p Fn is nothrow invokable with
    ///        \p Args...
    ///
    /// Formally, the expression:
    /// \code
    /// INVOKE( std::declval<Fn>(), std::declval<Args>()... )
    /// \endcode
    /// is well formed and is known not to throw
    ///
    /// The result is aliased as \c ::value
    template<typename Fn, typename...Args>
    using is_nothrow_invokable = detail::is_nothrow_invokable<Fn,Args...>;

    /// \brief Type-trait helper to retrieve the \c ::value of is_nothrow_invokable
    template<typename Fn, typename...Args>
    constexpr bool is_nothrow_invokable_v = is_nothrow_invokable<Fn,Args...>::value;

    //------------------------------------------------------------------------

    namespace detail {

      template<typename Fn>
      struct normalize_function;

      template<typename R, typename...Args>
      struct normalize_function<R(*)(Args...)> : identity<R(Args...)>{};

      template<typename R, typename C, typename...Args>
      struct normalize_function<R(C::*)(Args...)> : identity<R(Args...)>{};

      template<typename R, typename C, typename...Args>
      struct normalize_function<R(C::*)(Args...) const> : identity<R(Args...)>{};

      template<typename R, typename C, typename...Args>
      struct normalize_function<R(C::*)(Args...) volatile> : identity<R(Args...)>{};

      template<typename R, typename C, typename...Args>
      struct normalize_function<R(C::*)(Args...) const volatile> : identity<R(Args...)>{};

    } // namespace detail

    /// \brief Type trait to normalize a function to a value-type
    ///
    /// The result is aliased as \c ::type
    template<typename Fn>
    using normalize_function = detail::normalize_function<std::decay_t<Fn>>;

    template<typename Fn>
    using normalize_function_t = typename normalize_function<Fn>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_TYPE_TRAITS_TYPE_FUNCTION_HPP */
