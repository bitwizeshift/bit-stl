/**
 * \file type_composite.hpp
 *
 * \brief This internal library provides type traits for composition with other
 *        traits.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_UTILITIES_DETAIL_TYPE_TRAITS_TYPE_COMPOSITE_HPP
#define BIT_STL_UTILITIES_DETAIL_TYPE_TRAITS_TYPE_COMPOSITE_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

namespace bit {
  namespace stl {

    /// \brief Base class for sfinae types
    struct sfinae_base
    {
      /// \brief Type corresponding to yes (is) instances using SFINAE.
      /// \note bit::yes_type is guaranteed to be a different size than bit::no_type
      using yes_type = char(&)[1];

      /// \brief Type corresponding to no (is not) instances using SFINAE.
      /// \note bit::no_type is guaranteed to be a different size than bit::yes_type
      using no_type = char(&)[4];
    };

    //--------------------------------------------------------------------------

    /// \brief This template is designed to provide compile-time boolean
    ///        constants as types
    ///
    /// The value is aliased as \c ::value
    template<bool Bool>
    using bool_constant = std::integral_constant<bool,Bool>;

    /// \brief This template is designed to provide compile-time size
    ///        constants as types
    ///
    /// The value is aliased as \c ::value
    template<std::size_t Size>
    using size_constant = std::integral_constant<std::size_t,Size>;

    //--------------------------------------------------------------------------

    /// \brief This utility is used for creating composite classes
    template <typename T>
    struct empty{};

    /// \brief This utility is used for creating composite classes for
    ///        type-traits
    template<typename T>
    struct identity
    {
      using type = T;
    };

    template<typename T>
    using identity_t = typename identity<T>::type;

    /// \brief identity function that returns the same value as the input
    ///
    /// \param val the value to forward back to the result
    /// \return val the value to return
    template<typename T>
    inline constexpr T& identity_fn( T& val ){ return val; }

    //--------------------------------------------------------------------------

    /// \brief This template is designed to provide compile-time constants as
    ///        types.
    template<int i>
    struct int_to_type : std::integral_constant<int,i>
    {
      using next     = int_to_type<i+1>; ///< the type of the next int_to_type
      using previous = int_to_type<i-1>; ///< the type of the previous int_to_type
    };

    //--------------------------------------------------------------------------
    // Template Voidify
    //--------------------------------------------------------------------------

    /// \brief Type trait for managing the \c void_t idiom
    ///
    /// This aliases \c void as \c ::type
    template<typename...Args>
    struct voidify : public identity<void>{};


    /// \brief Type trait for the \c void_t idiom
    ///
    /// This is always aliased as \c void
    template<typename...Args>
    using void_t = typename voidify<Args...>::type;

    //////////////////////////////////////////////////////////////////////////
    /// \brief nonesuch is a class type used by detected_t to indicate
    ///        detection failure.
    //////////////////////////////////////////////////////////////////////////
    struct nonesuch
    {
        nonesuch() = delete;
        nonesuch(const nonesuch&) = delete;
        nonesuch(nonesuch&&) = delete;
        ~nonesuch() = delete;
        nonesuch& operator=(const nonesuch&) = delete;
        nonesuch& operator=(nonesuch&&) = delete;
    };

    //---------------------------------------------------------------------------

    namespace detail {

      template<typename Default, typename AlwaysVoid,
               template<typename...> class Op, typename... Args>
      struct detector {
        using value_t = std::false_type;
        using type = Default;
      };

      template<typename Default,
               template<typename...> class Op, typename... Args>
      struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
        using value_t = std::true_type;
        using type = Op<Args...>;
      };

    } // namespace detail

    template<template<class...> class Op, class... Args>
    using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

    template<template<typename...> class Op, typename... Args >
    constexpr bool is_detected_v = is_detected<Op, Args...>::value;

    template<template<class...> class Op, class... Args>
    using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

    //---------------------------------------------------------------------------

    template<typename Default, template<typename...> class Op, typename... Args>
    using detected_or = detail::detector<Default, void, Op, Args...>;

    template<typename Default, template<typename...> class Op, typename... Args >
    using detected_or_t = typename detected_or<Default, Op, Args...>::type;

    //---------------------------------------------------------------------------

    template<typename Expected, template<typename...> class Op, typename... Args>
    using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

    template<typename Expected, template<typename...> class Op, typename... Args>
    constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

    //---------------------------------------------------------------------------

    template<typename To, template<typename...> class Op, typename... Args>
    using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

    template<typename To, template<typename...> class Op, typename... Args>
    constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;

    //---------------------------------------------------------------------------
    // Boolean Operations
    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        NOT operation on a given boolean value
    ///
    /// The result is aliased as \c ::value
    template<bool Bool>
    struct type_not : std::true_type{};

    template<>
    struct type_not<true> : std::false_type{};

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        NOT operation of another \c bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename Type>
    using type_not_c = type_not<Type::value>;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the bool_constant from a logical
    ///        AND operation of other bool_constants
    ///
    /// The result is aliased as \c ::value
    template<typename B>
    struct negation : bool_constant<!B::value>{ };

    /// \brief Type trait to determine whether a type is the same with a different
    ///        CV qualifier
    template<typename T, typename U>
    using is_same_remove_cv = std::is_same<std::remove_cv_t<T>,std::remove_cv_t<U>>;

    template<typename T, typename U>
    constexpr bool is_same_remove_cv_v = is_same_remove_cv<T,U>::value;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine whether a type is the same with a different
    ///        decay type
    template<typename T, typename U>
    using is_same_decay = std::is_same<std::decay_t<T>,std::decay_t<U>>;

    template<typename T, typename U>
    constexpr bool is_same_decay_v = is_same_decay<T,U>::value;

    //---------------------------------------------------------------------------

    template<typename T, typename...Ts>
    struct are_same : std::false_type{};

    template<typename T, typename...Ts>
    struct are_same<T,T,Ts...> : are_same<T,Ts...>{};

    template<typename T>
    struct are_same<T,T> : std::true_type{};

    template<typename T, typename...Ts>
    constexpr bool are_same_v = are_same<T,Ts...>::value;

    //---------------------------------------------------------------------------

    template<typename T, typename U, typename...Ts>
    struct is_one_of : is_one_of<T,Ts...>{};

    template<typename T, typename...Ts>
    struct is_one_of<T,T,Ts...> : std::true_type{};

    template<typename T, typename U>
    struct is_one_of<T,U> : std::false_type{};

    template<typename T, typename...Ts>
    constexpr bool is_one_of_v = is_one_of<T,Ts...>::value;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        AND operation of boolean values
    ///
    /// The result is aliased as \c ::value
    template<bool...Bools>
    struct type_and : std::false_type{};

    template<bool...Bools>
    struct type_and<true,Bools...> : type_and<Bools...>{};

    template<>
    struct type_and<true> : std::true_type{};

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        AND operation of other \c bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename...Types>
    using type_and_c = type_and<Types::value...>;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the bool_constant from a logical
    ///        AND operation of other bool_constants
    ///
    /// The result is aliased as \c ::value
    template<typename...>
    struct conjunction;

    template<typename B1>
    struct conjunction<B1>
      : B1 { };

    template<typename B1, typename... Bn>
    struct conjunction<B1, Bn...>
      : std::conditional_t<B1::value, conjunction<Bn...>, B1>  {};

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        NAND operation of boolean values
    ///
    /// The result is aliased as \c ::value
    template<bool...Bools>
    using type_nand = type_not<type_and<Bools...>::value>;


    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        NAND operation of other \c bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename...Types>
    using type_nand_c = type_nand<Types::value...>;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        OR operations of boolean values
    ///
    /// The result is aliased as \c ::value
    template<bool...Bools>
    struct type_or : std::false_type{};

    template<bool...Bools>
    struct type_or<false,Bools...> : type_or<Bools...>{};

    template<bool...Bools>
    struct type_or<true,Bools...> : std::true_type{};

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        OR operation of other \c bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename...Types>
    using type_or_c = type_or<Types::value...>;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        OR operations of other bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename...>
    struct disjunction : std::false_type { };

    template<typename B1>
    struct disjunction<B1>
      : B1 { };

    template<typename B1, typename... Bn>
    struct disjunction<B1, Bn...>
      : std::conditional_t<B1::value != false, B1, disjunction<Bn...>>  {};

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        NOR operations of boolean values
    ///
    /// The result is aliased as \c ::value
    template<bool...Bools>
    using type_nor = type_not<type_or<Bools...>::value>;

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        NOR operation of other \c bool_constant
    ///
    /// The result is aliased as \c ::value
    template<typename...Types>
    using type_nor_c = type_nor<Types::value...>;

    //---------------------------------------------------------------------------

    namespace detail {

      template<bool Value, bool...Bools>
      struct type_xor_impl;

      template<bool B1, bool B2, bool...Bools>
      struct type_xor_impl<B1,B2,Bools...> : type_xor_impl<(B1^B2),Bools...>{};

      template<bool Value>
      struct type_xor_impl<Value> : bool_constant<Value>{};

    } // namespace detail

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        XOR operation of boolean values
    ///
    /// The result is aliased as \c ::value
    template<bool...Bools>
    using type_xor = detail::type_xor_impl<Bools...>;

    /// \brief Type trait to determine the \c bool_constant from a logical
    ///        XOR operation of other \c bool_Constant
    ///
    /// The result is aliased as \c ::value
    template<typename...Types>
    using type_xor_c = type_xor<Types::value...>;

    //---------------------------------------------------------------------------
    // Type Equality
    //---------------------------------------------------------------------------

    /// \brief Type trait to determine whether \p t1 and \p t2 are equal
    ///
    /// The result is aliased as \c ::value
    template<typename T, T t1, T t2>
    using type_equal = bool_constant<t1==t2>;


    /// \brief Type trait to determine whether \p t1 and \p t2 are not equal
    ///
    /// The result is aliased as \c ::value
    template<typename T, T t1, T t2>
    using type_not_equal = bool_constant<t1!=t2>;


    /// \brief Type trait to determine whether \p t1 is greater than \p t2
    ///
    /// The result is aliased as \c ::value
    template<typename T, T t1, T t2>
    using type_gt = bool_constant<(t1 > t2)>;


    /// \brief Type trait to determine whether \p t1 is greater than or equal
    ///        to \p t2
    ///
    /// The result is aliased as \c ::value
    template<typename T, T t1, T t2>
    using type_ge = bool_constant<(t1 >= t2)>;


    /// \brief Type trait to determine whether \p t1 is less than \p t2
    ///
    /// The result is aliased as \c ::value
    template<typename T, T t1, T t2>
    using type_lt = bool_constant<(t1 < t2)>;


    /// \brief Type trait to determine whether \p t1 is less than or equal
    ///        to \p t2
    ///
    /// The result is aliased as \c ::value
    template<typename T, T t1, T t2>
    using type_le = bool_constant<(t1 <= t2)>;

    //---------------------------------------------------------------------------

    /// \brief Type trait to sfinae-disable an overload when a condition is \c true
    ///
    /// \tparam B the boolean instance
    template<bool B, typename T = void>
    struct disable_if : std::enable_if<!B,T>{};

    /// \brief Convenience alias to access the \c ::type member of
    ///        \c disable_if_t
    template<bool B, typename T = void>
    using disable_if_t = typename disable_if<B,T>::type;

    /// \brief Convenience alias to determine multiple boolean
    ///        clauses at one for a \c disable_if
    template<typename...Clauses>
    using disable_if_c = disable_if<conjunction<Clauses...>::value>;

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c disable_if_c
    template<typename...Clauses>
    using disable_if_c_t = typename disable_if_c<Clauses...>::type;

    //---------------------------------------------------------------------------

    /// \brief Convenience alias to determine multiple boolean
    ///        clauses at one for a \c enable_if
    template<typename...Clauses>
    using enable_if_c = std::enable_if<conjunction<Clauses...>::value>;

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c enable_if_c
    template<typename...Clauses>
    using enable_if_c_t = typename enable_if_c<Clauses...>::type;

    //---------------------------------------------------------------------------

    /// \brief Similar to enable_if, but doesn't sfinae-away a type; instead
    ///        produces an uninstantiable unique type when true
    ///
    /// This is used to selectively disable constructors, since sfinae doesn't
    /// work for copy/move constructors
    template<bool b, typename T>
    struct block_if : identity<T>{};

    template<typename T>
    struct block_if<true,T>
    {
      class type{ type() = delete; ~type() = delete; };
    };

    /// \brief Inverse of \c block_if
    template<bool b, typename T>
    using block_unless = block_if<!b,T>;

    /// \brief Convenience aliase to retrieve the \c ::type member of
    ///        \c block_if
    template<bool b, typename T>
    using block_if_t = typename block_if<b,T>::type;

    /// \brief Convenience aliase to retrieve the \c ::type member of
    ///        \c block_unless
    template<bool b, typename T>
    using block_unless_t = typename block_if<!b,T>::type;

    //---------------------------------------------------------------------------

    /// \brief Type trait to determine if all \p Froms are convertible
    ///        to \p To
    ///
    /// \tparam To the type to try to convert to
    /// \tparam Froms The types to try to convert from
    template<typename To, typename...Froms>
    struct are_convertible : conjunction< std::is_convertible<Froms,To>... >{};

    template<typename To, typename...Froms>
    constexpr bool are_convertible_v = are_convertible<To,Froms...>::value;

  } // namespace stl
} // namespace bit
#endif /* BIT_STL_UTILITIES_DETAIL_TYPE_TRAITS_TYPE_COMPOSITE_HPP */