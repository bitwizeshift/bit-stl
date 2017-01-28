/**
 * \file bit/core/internal/type_transformations.hpp
 *
 * \brief This internal header provides transformations for types.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_INTERNAL_TYPE_TRANSFORMATIONS_HPP
#define BIT_INTERNAL_TYPE_TRANSFORMATIONS_HPP

// Prevent warnings for __int128 when using -wpedantic from being warned
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

namespace bit {
  namespace stl {

    namespace detail {

      template<typename T>
      struct unqualified : identity<T>{};

      template<typename T>
      struct unqualified<T*> : unqualified< std::decay_t<T> >{};

      template<typename T>
      struct unqualified<T&> : unqualified< std::decay_t<T> >{};

      template<typename T>
      struct unqualified<T&&> : unqualified< std::decay_t<T> >{};

      template<typename T>
      struct unqualified<const T> : unqualified<T>{};

      template<typename T>
      struct unqualified<volatile T> : unqualified<T>{};

      template<typename T>
      struct unqualified<const volatile T> : unqualified<T>{};

    } // namespace detail

    /// \brief Retrieves the underlying type, unqualified, of the given
    ///        qualified type
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    using unqualified = detail::unqualified< std::decay_t<T> >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        unqualified
    template<typename T>
    using unqualified_t = typename unqualified<T>::type;

    //---------------------------------------------------------------------------

    /// \brief Obtains the base type of T without modifiers
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct base_type : identity< std::decay_t< unqualified_t<T> > >{};

    template<typename T>
    struct base_type<T*> : base_type< std::decay_t< unqualified_t<T> > >{};

    template<typename T>
    struct base_type<T&> : base_type< std::decay_t< unqualified_t<T> > >{};

    template<typename T>
    struct base_type<T&&> : base_type< std::decay_t< unqualified_t<T> > >{};

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        base_type
    template<typename T>
    using base_type_t = typename base_type<T>::type;

    //--------------------------------------------------------------------------

    namespace detail{

      /// \struct bit::detail::cv_selector
      ///
      /// \brief Helper to select the proper cv-qualifiers
      template<
        typename Unqualified,
        bool is_const_type,
        bool is_volatile_type
      >
      struct cv_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, false, true>
        : std::add_volatile<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, true, false>
        : std::add_const<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, true, true>
        : std::add_cv<Unqualified>{};

    } // namespace detail

    /// \brief Type trait to match the cv qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified,typename Unqualified>
    using match_cv_qualifiers = detail::cv_selector<
      Unqualified,
      std::is_const<Qualified>::value,
      std::is_volatile<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_cv_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_cv_qualifiers_t =
      typename match_cv_qualifiers<Qualified, Unqualified>::type;

    //---------------------------------------------------------------------------

    namespace detail {

      template<typename Unqualified,
               bool is_lvalue,
               bool is_rvalue>
      struct ref_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct ref_selector<Unqualified, true, false>
        : std::add_lvalue_reference<Unqualified>{};

      template<typename Unqualified>
      struct ref_selector<Unqualified, false, true>
        : std::add_rvalue_reference<Unqualified>{};

    } // namespace detail

    /// \brief Type trait to match the ref qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified, typename Unqualified>
    using match_ref_qualifiers = detail::ref_selector<
      Unqualified,
      std::is_lvalue_reference<Qualified>::value,
      std::is_rvalue_reference<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_ref_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_ref_qualifiers_t =
      typename match_ref_qualifiers<Qualified, Unqualified>::type;

    //---------------------------------------------------------------------------

    namespace detail {

      template<typename Unqualified,
               bool is_signed,
               bool is_unsigned>
      struct sign_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct sign_selector<Unqualified, true, false>
        : std::make_signed<Unqualified>{};

      template<typename Unqualified>
      struct sign_selector<Unqualified, false, true>
        : std::make_unsigned<Unqualified>{};
    } // namespace detail

    /// \brief Type trait to match the sign qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified, typename Unqualified>
    using match_sign_qualifiers = detail::sign_selector<
      Unqualified,
      std::is_signed<Qualified>::value,
      std::is_unsigned<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_sign_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_sign_qualifiers_t =
      typename match_sign_qualifiers<Qualified, Unqualified>::type;

    //---------------------------------------------------------------------------

    /// \brief Type trait to match the qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified, typename Unqualified>
    using match_qualifiers = match_cv_qualifiers<Qualified,match_ref_qualifiers<Qualified,Unqualified>>;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_qualifiers_t =
      typename match_qualifiers<Qualified, Unqualified>::type;

    //---------------------------------------------------------------------------

    // todo: integer promotion

    template<typename T>
    struct promote{};

    //---------------------------------------------------------------------------

    /// \struct bit::bit_size
    ///
    /// \brief Calculates the number of bits type T takes
    template<typename T>
    using bit_sizeof = std::integral_constant<std::size_t, (sizeof(T) * CHAR_BIT)>;

    //---------------------------------------------------------------------------

    /// \brief Normalizes character types T to non-signed/unsigned character
    ///        types
    ///
    /// The result is aliased as \t ::type
    template<typename T>
    struct normalize_char : identity<T>{};

    template<>
    struct normalize_char<signed char> : identity<char>{};

    template<>
    struct normalize_char<unsigned char> : identity<char>{};

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        normalize_char
    template<typename T>
    using normalize_char_t = typename normalize_char<T>::type;

    //--------------------------------------------------------------------------

    template<typename Func>
    struct make_uniform_function;

    template<typename R, typename...Args>
    struct make_uniform_function<R(*)(Args...)> : identity<R(*)(Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...)> : identity<R(*)(C&,Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) const> : identity<R(*)(const C&, Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) volatile> : identity<R(*)(volatile C&, Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) const volatile> : identity<R(*)(const volatile C&, Args...)>{};


    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) &> : identity<R(*)(C&,Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) const &> : identity<R(*)(const C&, Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) volatile &> : identity<R(*)(volatile C&, Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) const volatile &> : identity<R(*)(const volatile C&, Args...)>{};


    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) &&> : identity<R(*)(C&&,Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) const &&> : identity<R(*)(const C&&, Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) volatile &&> : identity<R(*)(volatile C&&, Args...)>{};

    template<typename C, typename R, typename...Args>
    struct make_uniform_function<R(C::*)(Args...) const volatile &&> : identity<R(*)(const volatile C&&, Args...)>{};

    //--------------------------------------------------------------------------

    /// \brief Removes all pointers from a given type
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct remove_all_pointers : identity<T>{};

    template<typename T>
    struct remove_all_pointers<T*> : remove_all_pointers<T>{};

    template<typename T>
    struct remove_all_pointers<T* const> : remove_all_pointers<T>{};

    template<typename T>
    struct remove_all_pointers<T* volatile> : remove_all_pointers<T>{};

    template<typename T>
    struct remove_all_pointers<T* const volatile> : remove_all_pointers<T>{};

    /// \brief Convenience template to retrieve the \c ::type of
    ///        remove_all_pointers
    template<typename T>
    using remove_all_pointers_t = typename remove_all_pointers<T>::type;

    //--------------------------------------------------------------------------

    /// \brief Removes the constness of a member function pointer
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct remove_member_function_pointer_const : identity<T>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_const<R (T::*)(Args...) const> : identity<R (T::*)(Args...)>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_const<R (T::*)(Args...) const volatile> : identity<R (T::*)(Args...) volatile>{};

    /// \brief Convenience template to retrieve the \c ::type of
    ///        remove_member_function_const
    template<typename T>
    using remove_member_function_pointer_const_t = typename remove_member_function_pointer_const<T>::type;

    //--------------------------------------------------------------------------

    /// \brief Removes volatility of a member function pointer
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct remove_member_function_pointer_volatile : identity<T>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_volatile<R (T::*)(Args...) volatile> : identity<R (T::*)(Args...)>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_volatile<R (T::*)(Args...) const volatile> : identity<R (T::*)(Args...) const>{};

    /// \brief Convenience template to retrieve the \c ::type of
    ///        remove_member_function_volatile
    template<typename T>
    using remove_member_function_pointer_volatile_t = typename remove_member_function_pointer_volatile<T>::type;

    //--------------------------------------------------------------------------

    /// \brief Removes the cv-ness of a member function pointer
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct remove_member_function_pointer_cv : identity<T>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_cv<R (T::*)(Args...) const> : identity<R (T::*)(Args...)>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_cv<R (T::*)(Args...) volatile> : identity<R (T::*)(Args...)>{};

    template<typename R, typename T, typename...Args>
    struct remove_member_function_pointer_cv<R (T::*)(Args...) const volatile> : identity<R (T::*)(Args...)>{};

    /// \brief Convenience template to retrieve the \c ::type of
    ///        remove_member_function_cv
    template<typename T>
    using remove_member_function_pointer_cv_t = typename remove_member_function_pointer_cv<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_INTERNAL_TYPE_TRANSFORMATIONS_HPP */
