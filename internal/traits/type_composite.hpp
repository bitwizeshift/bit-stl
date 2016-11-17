/**
 * \file type_composite.hpp
 *
 * \brief This internal library provides type traits for composition with other
 *        traits.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_INTERNAL_TYPE_COMPOSITE_HPP
#define BIT_INTERNAL_TYPE_COMPOSITE_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

namespace bit {

  /// \struct bit::sfinae_base
  ///
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

  /// \struct bit::empty
  ///
  /// This utility is used for creating composite classes
  template <typename T>
  struct empty{};

  /// \struct bit::identity
  ///
  /// This utility is used for creating composite classes for type-traits
  template<typename T>
  struct identity
  {
    using type = T;
  };

  //--------------------------------------------------------------------------

  /// \struct bit::int_to_type
  ///
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
  struct conjunction : std::true_type { };

  template<typename B1>
  struct conjunction<B1>
    : B1 { };

  template<typename B1, typename... Bn>
  struct conjunction<B1, Bn...>
    : std::conditional_t<B1::value != false, conjunction<Bn...>, B1>  {};

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
    : std::conditional_t<B1::value != false, B1, conjunction<Bn...>>  {};

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

} // namespace bit
#endif /* BIT_INTERNAL_TYPE_COMPOSITE_HPP */
