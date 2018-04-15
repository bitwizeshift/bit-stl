/*****************************************************************************
 * \file
 * \brief This header contains an implementation of std::variant that
 *        satisfies the
 *****************************************************************************/

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
#ifndef BIT_STL_UTILITIES_VARIANT_HPP
#define BIT_STL_UTILITIES_VARIANT_HPP

#include "in_place.hpp"
#include "monostate.hpp"
#include "utility.hpp"

#include "../traits/composition/sfinae.hpp"      // enable_overload_if
#include "../traits/composition/conjunction.hpp" // conjunction
#include "../traits/relationships/nth_type.hpp"  // nth_type

#include <initializer_list> // std::initializer_list
#include <memory>           // std::uses_allocator
#include <exception>        // std::exception

namespace bit {
  namespace stl {

    //=========================================================================
    // 23.7.3 : class template variant
    //=========================================================================

    template<typename...Types>
    class variant;

    namespace detail {

      struct variant_empty{};

      //=======================================================================
      // variant_union
      //=======================================================================

      template<bool IsTrivial, typename...Types>
      union variant_union;

      template<typename Type0, typename...Types>
      union variant_union<true,Type0,Types...>
      {
        using current_type = Type0;
        using next_type    = variant_union<true,Types...>;

        variant_empty empty;
        current_type  current;
        next_type     next;

        //---------------------------------------------------------------------
        // Constructors
        //---------------------------------------------------------------------

        constexpr variant_union() : empty(){}

        template<typename...Args>
        constexpr variant_union( in_place_index_t<0>, Args&&...args )
          : current( std::forward<Args>(args)... )
        {

        }

        template<std::size_t N, typename...Args>
        constexpr variant_union( in_place_index_t<N>, Args&&...args )
          : next( in_place_index<N-1>, std::forward<Args>(args)... )
        {

        }

        //---------------------------------------------------------------------
        // Observers
        //---------------------------------------------------------------------

        constexpr current_type& get( in_place_index_t<0> )
        {
          return current;
        }
        constexpr const current_type& get( in_place_index_t<0> ) const
        {
          return current;
        }

        template<std::size_t N>
        constexpr auto& get( in_place_index_t<N> )
        {
          return next.get( in_place_index<N-1> );
        }
        template<std::size_t N>
        constexpr const auto& get( in_place_index_t<N> ) const
        {
          return next.get( in_place_index<N-1> );
        }

      };

      template<typename Type0, typename...Types>
      union variant_union<false,Type0,Types...>
      {
        using current_type = Type0;
        using next_type    = variant_union<false,Types...>;

        variant_empty empty;
        current_type  current;
        next_type     next;

        constexpr variant_union() : empty(){}

        template<typename...Args>
        constexpr variant_union( in_place_index_t<0>, Args&&...args )
          : current( std::forward<Args>(args)... )
        {

        }

        template<std::size_t N, typename...Args>
        constexpr variant_union( in_place_index_t<N>, Args&&...args )
          : next( in_place_index<N-1>, std::forward<Args>(args)... )
        {

        }

        ~variant_union(){}

        constexpr current_type& get( in_place_index_t<0> )
        {
          return current;
        }
        constexpr const current_type& get( in_place_index_t<0> ) const
        {
          return current;
        }

        template<std::size_t N>
        constexpr auto& get( in_place_index_t<N> )
        {
          return next.get( in_place_index<N-1> );
        }
        template<std::size_t N>
        constexpr const auto& get( in_place_index_t<N> ) const
        {
          return next.get( in_place_index<N-1> );
        }

      };

      template<bool B>
      union variant_union<B>
      {

        variant_empty empty;

        constexpr variant_union() : empty(){}

        template<typename...Args>
        constexpr variant_union( in_place_index_t<0> )
          : empty()
        {

        }
      };

      //=======================================================================
      // variant_base
      //=======================================================================

      template<bool IsTrivial, typename...Types>
      class variant_base;

      template<typename...Types>
      class variant_base<true,Types...>
      {
      public:

        constexpr variant_base()
          : m_union(),
            m_index(-1)
        {

        }

        template<std::size_t N, typename...Args>
        constexpr variant_base( in_place_index_t<N>, Args&&...args )
          : m_union( in_place_index<N>, std::forward<Args>(args)... ),
            m_index( N )
        {

        }

        //---------------------------------------------------------------------
        // Protected Members
        //---------------------------------------------------------------------
      protected:

        variant_union<true,Types...> m_union;
        std::size_t                  m_index;

        //---------------------------------------------------------------------
        // Protected Member Functions
        //---------------------------------------------------------------------
      protected:

        void destruct()
        {
          m_index = std::size_t(-1);
        }

        template<std::size_t I>
        constexpr nth_type_t<I,Types...>& get( in_place_index_t<I> )
          noexcept
        {
          return m_union.get( in_place_index<I> );
        }

        template<std::size_t I>
        constexpr const nth_type_t<I,Types...>& get( in_place_index_t<I> )
          const noexcept
        {
          return m_union.get( in_place_index<I> );
        }

      };

      template<typename...Types>
      class variant_base<false,Types...>
      {
      public:

        constexpr variant_base()
          : m_union(),
            m_index(-1)
        {

        }

        template<std::size_t N, typename...Args>
        constexpr variant_base( in_place_index_t<N>, Args&&...args )
          : m_union( in_place_index<N>, std::forward<Args>(args)... ),
            m_index( N )
        {

        }

        ~variant_base()
        {
          destruct();
        }

        //---------------------------------------------------------------------
        // Protected Members
        //---------------------------------------------------------------------
      protected:

        variant_union<false,Types...> m_union;
        std::size_t                   m_index;

        //---------------------------------------------------------------------
        // Protected Member Functions
        //---------------------------------------------------------------------
      protected:

        void destruct()
        {
          if( m_index == std::size_t(-1) ) return;

          destroy_impl( m_index, m_union );
          m_index = std::size_t(-1);
        }

        template<std::size_t I>
        constexpr nth_type_t<I,Types...>& get( in_place_index_t<I> )
          noexcept
        {
          return m_union.get( in_place_index<I> );
        }

        template<std::size_t I>
        constexpr const nth_type_t<I,Types...>& get( in_place_index_t<I> )
          const noexcept
        {
          return m_union.get( in_place_index<I> );
        }

        void swap( variant_base& other )
        {
          swap_impl( 0, m_index, m_union, other.m_union );
        }

        //---------------------------------------------------------------------
        // Private Static Member Functions
        //---------------------------------------------------------------------
      private:

        template<bool B, typename T0, typename T1, typename...Ts>
        static void swap_impl( std::size_t current,
                               std::size_t index,
                               variant_union<B,T0,T1,Ts...>& lhs,
                               variant_union<B,T0,T1,Ts...>& rhs )
        {
          using std::swap;

          if( current == index ) {
            swap( lhs.current, rhs.current );
          } else {
            swap_impl( current+1, index, lhs.next, rhs.next );
          }
        }

        template<bool B, typename T0>
        static void swap_impl( std::size_t,
                               std::size_t,
                               variant_union<B,T0>& lhs,
                               variant_union<B,T0>& rhs )
        {
          using std::swap;

          swap( lhs.current, rhs.current );
        }

        template<typename T0>
        static void destroy_impl( std::size_t n, variant_union<false,T0>& storage )
        {
          storage.current.~T0();
        }

        template<typename T0, typename T1, typename...Ts>
        static void destroy_impl( std::size_t n, variant_union<false,T0,T1,Ts...>& storage )
        {
          if( n == 0 ) {
            storage.current.~T0();
          } else {
            destroy_impl( n-1, storage.next );
          }
        }

      };

      //-----------------------------------------------------------------------

      template<std::size_t I, typename T, typename...Ts>
      struct index_from_impl;

      template<std::size_t I, typename T, typename T0, typename...Ts>
      struct index_from_impl<I,T,T0,Ts...> : index_from_impl<I+1,T,Ts...>{};

      template <std::size_t I, typename T, typename...Ts>
      struct index_from_impl<I,T,T,Ts...> : std::integral_constant<std::size_t,I>{};

      template <typename T, typename...Ts>
      struct index_from : index_from_impl<0,T,Ts...>{};

      //-----------------------------------------------------------------------

      template <std::size_t I, typename T, typename...Ts>
      struct index_from_constructible_impl;

      // Base case
      template <std::size_t I, typename T>
      struct index_from_constructible_impl<I,T> : std::integral_constant<std::size_t,std::size_t(-1)>{};

      // test each type
      template <std::size_t I, typename T, typename T0, typename...Ts>
      struct index_from_constructible_impl<I,T,T0,Ts...> :
        std::conditional<std::is_constructible<T0,T>::value,
          std::integral_constant<std::size_t,I>,
          index_from_constructible_impl<I+1,T,Ts...>>{};

      template <typename T, typename...Ts>
      struct index_from_constructible : index_from_constructible_impl<0,T,Ts...>{};

      //-----------------------------------------------------------------------

      template <typename T>
      struct is_not_in_place : std::true_type{};

      template <typename T>
      struct is_not_in_place<in_place_type_t<T>> : std::false_type{};

      template <std::size_t N>
      struct is_not_in_place<in_place_index_t<N>> : std::false_type{};

      template<>
      struct is_not_in_place<in_place_t> : std::false_type{};

      //-----------------------------------------------------------------------

      template<std::size_t I, typename...Types>
      struct variant_f_impl;

      template<std::size_t I, typename T0, typename T1, typename...Types>
      struct variant_f_impl<I,T0,T1,Types...> : variant_f_impl<I+1,T1,Types...>
      {
        using variant_f_impl<I+1,T1,Types...>::operator();

        std::integral_constant<std::size_t,I> operator()( T0 );
      };
      template<std::size_t I, typename T0>
      struct variant_f_impl<I,T0>
      {
        std::integral_constant<std::size_t,I> operator()( T0 );
      };

      template<typename...Types>
      struct variant_f : variant_f_impl<0,Types...>
      {

      };

      template<typename T, typename Variant, typename = void>
      struct conversion_index : std::integral_constant<std::size_t,std::size_t(-1)>{};

      template<typename T, typename...Types>
      struct conversion_index<T,variant<Types...>,void_t<decltype( std::declval<variant_f<Types...>>()( std::declval<T>() ))>>
        : decltype( std::declval<variant_f<Types...>>()( std::declval<T>() ) ){};

      template<typename T, typename Variant>
      constexpr auto conversion_index_v = conversion_index<T,Variant>::value;

      template<std::size_t I, typename Variant>
      struct conversion_type_or_void_impl;

      template<std::size_t I, typename...Types>
      struct conversion_type_or_void_impl<I,variant<Types...>> : std::tuple_element<I,std::tuple<Types...>>{};

      template<typename...Types>
      struct conversion_type_or_void_impl<std::size_t(-1),variant<Types...>> : identity<void>{};

      template<typename T, typename Variant>
      using conversion_type_or_void_t = typename conversion_type_or_void_impl<conversion_index_v<T,Variant>,Variant>::type;

      //-----------------------------------------------------------------------

      template<typename T>
      struct variant_union_has_next;

      template<bool B, typename T>
      struct variant_union_has_next<variant_union<B,T>> : std::false_type{};

      template<bool B, typename...Types>
      struct variant_union_has_next<variant_union<B,Types...>> : std::true_type{};

    } // namespace detail


    //=========================================================================
    // 23.7.4 : variant helper classes
    //=========================================================================

    /// \{
    /// \brief Provides access to the number of alternatives in a possibly
    ///        cv-qualified variant as a compile-time constant expression.
    ///
    /// The result is accessible as \c ::value
    template<typename T> struct variant_size; // not defined
    template<typename T> struct variant_size<const T> : variant_size<T>{};
    template<typename T> struct variant_size<volatile T> : variant_size<T>{};
    template<typename T> struct variant_size<const volatile T> : variant_size<T>{};
    template<typename...Types>
    struct variant_size<variant<Types...>> : std::integral_constant<std::size_t,sizeof...(Types)>{};
    /// \}

    /// \brief Helper variable template for extracting \c variant_size<T>::value
    template<typename T>
    constexpr size_t variant_size_v = variant_size<T>::value;

    //-------------------------------------------------------------------------

    ///
    ///
    ///
    template<std::size_t I, typename T> struct variant_alternative; // not defined
    template<std::size_t I, typename T> struct variant_alternative<I, const T>
      : std::add_const<typename variant_alternative<I,T>::type>{};
    template<std::size_t I, typename T> struct variant_alternative<I, volatile T>
      : std::add_volatile<typename variant_alternative<I,T>::type>{};
    template<std::size_t I, typename T> struct variant_alternative<I, const volatile T>
      : std::add_cv<typename variant_alternative<I,T>::type>{};
    template<std::size_t I, typename...Types>
    struct variant_alternative<I, variant<Types...>>
      : std::tuple_element<I,std::tuple<Types...>>{};

    ///
    ///
    ///
    template<std::size_t I, typename T>
    using variant_alternative_t = typename variant_alternative<I, T>::type;

    //-------------------------------------------------------------------------

    /// \brief  This is a special value equal to the largest value
    ///         representable by the type std::size_t, used as the return type
    ///         of index() when valueless_by_exception() is true
    constexpr auto variant_npos = std::size_t(-1);

    //=========================================================================
    // 23.7.11 : class bad_variant_access
    //=========================================================================

    //////////////////////////////////////////////////////////////////////////
    /// \brief Exception thrown by variant
    ///
    /// bad_variant_access is the type of the exception thrown in the
    /// following situations:
    /// - get(std::variant) called with an index or type that does not match
    ///   the currently active alternative
    /// - visit called to visit a variant that is valueless_by_exception
    //////////////////////////////////////////////////////////////////////////
    class bad_variant_access : public std::exception
    {
      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a new instance of bad_variant_access.
      bad_variant_access() noexcept = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief returns an explanatory string of the exception
      ///
      /// \return string explaining the issue
      const char* what() const noexcept override{ return "bad_variant_access"; }
    };

    //=========================================================================
    // 23.7.3 : class template variant
    //=========================================================================

    ///////////////////////////////////////////////////////////////////////////
    /// \brief The class template variant represents a type-safe union.
    ///
    /// An instance of variant at any given time either holds a value of
    /// one of its alternative types, or it holds no value (this state is hard
    /// to achieve, \see valueless_by_exception ).
    ///
    /// As with unions, if a variant holds a value of some object type T, the
    /// object representation of T is allocated directly within the object
    /// representation of the variant itself. Variant is not allowed to allocate
    /// additional (dynamic) memory.
    ///
    /// A variant is not permitted to hold references, arrays, or the type void.
    /// Empty variants are also ill-formed (variant<monostate> can be
    /// used instead).
    ///
    /// A variant is permitted to hold the same type more than once, and to hold
    /// differently cv-qualified versions of the same type.
    ///
    /// As with unions, the default-initialized variant holds a value of its
    /// first alternative, unless that alternative is not default-constructible
    /// (in which case default constructor won't compile: the helper class
    /// monostate can be used to make such variants default-constructible)
    ///
    /// \tparam Types the types that may be stored in this variant. All types
    ///         must be (possibly cv-qualified) non-array object types
    ///////////////////////////////////////////////////////////////////////////
    template<typename...Types>
    class variant : detail::variant_base<conjunction<std::is_trivially_destructible<Types>...>::value,Types...>
    {
      static_assert( sizeof...(Types) > 0,
                     "A variant of 0 types is ill-formed. Use variant<monostate> instead." );

      using T0 = std::tuple_element_t<0,std::tuple<Types...>>;
      using base_type = detail::variant_base<conjunction<std::is_trivially_destructible<Types>...>::value,Types...>;

      static constexpr bool is_default_constructible = std::is_default_constructible<T0>::value;

      static constexpr bool is_move_constructible = conjunction<
        std::is_move_constructible<Types>...
      >::value;

      static constexpr bool is_copy_constructible = conjunction<
        std::is_copy_constructible<Types>...
      >::value;

      static constexpr bool is_nothrow_move_constructible = conjunction<
        std::is_nothrow_move_constructible<Types>...
      >::value;

      static constexpr bool is_nothrow_copy_constructible = conjunction<
        std::is_nothrow_copy_constructible<Types>...
      >::value;

      template<typename U>
      static constexpr bool is_convertible =
        !std::is_same<std::decay_t<U>, variant>::value &&
        detail::is_not_in_place<std::decay_t<U>>::value &&
        detail::conversion_index<U,variant>::value != std::size_t(-1) &&
        std::is_constructible<detail::conversion_type_or_void_t<U,variant>,U>::value;

      static constexpr bool is_copy_assignable = conjunction<
        std::is_copy_constructible<Types>...,
        std::is_copy_assignable<Types>...
      >::value;

      static constexpr bool is_move_assignable = conjunction<
        std::is_move_constructible<Types>...,
        std::is_move_assignable<Types>...
      >::value;

      template<typename U>
      static constexpr bool is_convert_assignable =
        !std::is_same<std::decay_t<U>, variant>::value &&
        detail::conversion_index<U,variant>::value != std::size_t(-1) &&
        std::is_constructible<detail::conversion_type_or_void_t<U,variant>,U>::value &&
        std::is_assignable<detail::conversion_type_or_void_t<U,variant>,U>::value;

      template<typename U>
      using T_j = nth_type_t<detail::conversion_index<U,variant>::value,Types...>;

      struct variant_ctor{};

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      // (1)

      /// \brief Default constructor.
      ///
      /// Constructs a variant holding the value-initialized value of the first
      /// alternative (index() is zero).
      ///
      /// \note This constructor is constexpr if and only if the value
      ///       initialization of the alternative type T_0 would satisfy the
      ///       requirements for a constexpr function.
      ///
      /// \note This overload only participates in overload resolution if
      ///       std::is_default_constructible_v<T_0> is true.
#ifndef BIT_DOXYGEN_BUILD
      constexpr variant( enable_overload_if_t<is_default_constructible,variant_ctor> = {} )
        noexcept(std::is_nothrow_default_constructible<T0>::value);
#else
      constexpr variant()
        noexcept(std::is_nothrow_default_constructible<T0>::value);
#endif

      // (2)

      /// \brief Copy constructor.
      ///
      /// If other is not valueless_by_exception, constructs a variant holding
      /// the same alternative as other and direct-initializes the contained
      /// value with std::get<other.index()>(other).
      /// Otherwise, initializes a valueless_by_exception variant.
      ///
      /// \note This overload only participates in overload resolution if
      ///       std::is_copy_constructible_v<T_i> is true for all T_i in Types....
      ///
      /// \param other the other variant to copy
#ifndef BIT_DOXYGEN_BUILD
      variant( enable_overload_if_t<is_copy_constructible,const variant&> other )
        noexcept( conjunction<std::is_nothrow_copy_constructible<Types>...>::value );
      variant( disable_overload_if_t<is_copy_constructible,const variant&> other ) = delete;
#else
      variant( const variant& other );
#endif

      // (3)

      /// \brief Move constructor.
      ///
      /// If other is not valueless_by_exception, constructs a variant holding
      /// the same alternative as other and direct-initializes the contained
      /// value with std::get<other.index()>(std::move(other)).
      /// Otherwise, initializes a valueless_by_exception variant.
      ///
      /// \note This overload only participates in overload resolution if
      ///       std::is_move_constructible_v<T_i> is true for all T_i in Types...
      ///
      /// \param other the other variant to move
#ifndef BIT_DOXYGEN_BUILD
      variant( enable_overload_if_t<is_move_constructible,variant&&> other )
        noexcept( conjunction<std::is_nothrow_move_constructible<Types>...>::value );
      variant( disable_overload_if_t<is_move_constructible,variant&&> other ) = delete;
#else
      variant( variant&& other )
        noexcept( conjunction<std::is_nothrow_move_constructible<Types>...>::value );
#endif

      // (4)

      /// \brief Converting constructor.
      ///
      /// Constructs a variant holding the alternative type T_j that would be
      /// selected by overload resolution for the expression
      /// F(std::forward<T>(t)) if there was an overload of imaginary function
      /// F(T_i) for every T_i from Types... in scope at the same time.
      ///
      /// Direct-initializes the contained value as if by direct
      /// non-list-initialization from std::forward<T>(t).
      ///
      /// \note This overload only participates in overload resolution if
      ///       - sizeof...(Types) > 0
      ///       - std::is_same_v<std::decay_t<T>, variant> is false
      ///       - std::decay_t<T> is neither a specialization of in_place_type_t
      ///         nor a specialization of in_place_index_t
      ///       - std::is_constructible_v<T_j, T> is true
      ///       - and the expression F(std::forward<T>(t)) (with F being the
      ///         above-mentioned set of imaginary functions) is well formed.
      ///
      /// \note This constructor is a constexpr constructor if T_j's selected
      ///       constructor is a constexpr constructor.
      ///
      /// \param t the value to direct-initialize
#ifndef BIT_DOXYGEN_BUILD
      template<typename T, typename=std::enable_if_t<is_convertible<T>>>
      constexpr variant( T&& t )
        noexcept( std::is_nothrow_constructible<T_j<T>,T>::value );
#else
      template<typename T>
      constexpr variant( T&& t )
        noexcept( std::is_nothrow_constructible<T_j<T>>::value );
#endif
//        noexcept( ... );

      // (5)

      /// \brief Constructs a variant with the specified alternative T and
      ///        initializes the contained value with the arguments
      ///        std::forward<Args>(args)....
      ///
      /// \note If T's selected constructor is a constexpr constructor, this
      ///       constructor is also a constexpr constructor.
      ///
      /// \note This overload only participates in overload resolution if
      ///       there is exactly one occurrence of T in Types... and
      ///       std::is_constructible_v<T, Args...> is true
      ///
      /// \param args the arguments to forward to \p T's constructor
#ifndef BIT_DOXYGEN_BUILD
      template<typename T, typename... Args,
               typename = std::enable_if_t<std::is_constructible<T,Args...>::value>>
      constexpr explicit variant( in_place_type_t<T>, Args&&... args );
#else
      template<typename T, typename...Args>
      constexpr explicit variant( in_place_type_t<T>, Args&&...args );
#endif

      // (6)

      /// \brief Constructs a variant with the specified alternative T and
      ///        initializes the contained value with the arguments il,
      ///        std::forward<Args>(args).....
      ///
      /// \note If T's selected constructor is a constexpr constructor, this
      ///       constructor is also a constexpr constructor.
      ///
      /// \note This overload only participates in overload resolution if
      ///       there is exactly one occurrence of T in Types... and
      ///       std::is_constructible_v<T, initializer_list<U>&, Args...> is true.
      ///
      /// \param il initializer list of type \p U
      /// \param args the arguments to forward to \p T's constructor
#ifndef BIT_DOXYGEN_BUILD
      template<typename T, typename U, typename... Args,
               typename = std::enable_if_t<std::is_constructible<T,std::initializer_list<U>,Args...>::value>>
#else
      template<typename T, typename U, typename... Args>
#endif
      constexpr explicit variant( in_place_type_t<T>,
                                  std::initializer_list<U> il, Args&&... args );

      // (7)

      /// \brief Constructs a variant with the alternative T_i specified by
      ///        the index I and initializes the contained value with the
      ///        arguments std::forward<Args>(args)....
      ///
      /// \note If T_i's selected constructor is a constexpr constructor, this
      ///       constructor is also a constexpr constructor.
      ///
      /// \note This overload only participates in overload resolution if
      ///       I < sizeof...(Types) and std::is_constructible_v<T_i, Args...>
      ///       is true
      ///
      /// \param args the arguments to forward to \p T_i's constructor
#ifndef BIT_DOXYGEN_BUILD
      template<std::size_t I, typename... Args,
               typename = std::enable_if_t<(I<sizeof...(Types)) && std::is_constructible<variant_alternative_t<I,variant>,Args...>::value>>
#else
      template<std::size_t I, typename... Args>
#endif
      constexpr explicit variant( in_place_index_t<I>, Args&&... args );

      // (8)

      /// \brief Constructs a variant with the alternative T_i specified by
      ///        the index I and initializes the contained value with the
      ///        arguments il, std::forward<Args>(args)....
      ///
      /// \note If T_i's selected constructor is a constexpr constructor, this
      ///       constructor is also a constexpr constructor.
      ///
      /// \note This overload only participates in overload resolution if
      ///       I < sizeof...(Types) and
      ///       std::is_constructible_v<T_i, std::initializer_list<U>&, Args...>
      ///       is true.
      ///
      /// \param il initializer list of type \p U
      /// \param args the arguments to forward to \p T_i 's constructor
#ifndef BIT_DOXYGEN_BUILD
      template<std::size_t I, typename U, typename... Args,
               typename = std::enable_if_t<(I<sizeof...(Types)) && std::is_constructible<variant_alternative_t<I,variant>,std::initializer_list<U>,Args...>::value>>
#else
      template<std::size_t I, typename U, typename... Args>
#endif
      constexpr explicit variant( in_place_index_t<I>,
                                  std::initializer_list<U> il, Args&&... args );

      //----------------------------------------------------------------------

#ifndef BIT_DOXYGEN_BUILD
      /// \brief Copy assignment
      ///
      /// \param other
      variant& operator=( enable_overload_if_t<is_copy_assignable,const variant&> other );
      variant& operator=( disable_overload_if_t<is_copy_assignable,const variant&> other ) = delete;
#else
      variant& operator=( const variant& other );
#endif

#ifndef BIT_DOXYGEN_BUILD
      variant& operator=( enable_overload_if_t<is_move_assignable,variant&&> other )
        noexcept( conjunction<std::is_nothrow_move_constructible<Types>...,
                              std::is_nothrow_move_assignable<Types>...>::value);
      variant& operator=( disable_overload_if_t<is_move_assignable,variant&&> other ) = delete;
#else
      variant& operator=( variant&& other );
#endif

#ifndef BIT_DOXYGEN_BUILD
      template<typename T, typename = std::enable_if_t<is_convert_assignable<T>>>
#else
      template<typename T>
#endif
      variant& operator=(T&& t)
        noexcept( std::is_nothrow_assignable<T_j<T>,T>::value &&
                  std::is_nothrow_constructible<T_j<T>,T>::value );

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Returns the zero-based index of the alternative that is
      ///        currently held by the variant.
      ///
      /// If the variant is \c valueless_by_exception, returns \c variant_npos.
      ///
      /// \return the zero-based index
      constexpr std::size_t index() const noexcept;

      /// \brief Returns false if and only if the variant holds a value
      ///
      /// \return \c false if and only if the variant holds a value
      constexpr bool valueless_by_exception() const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Creates a new value in-place
      ///
      /// Equivalent to emplace<I>(std::forward<Args>(args)...), where I is the
      /// zero-based index of T in Types....
      ///
      /// \note This overload only participates in overload resolution if
      ///       \c std::is_constructible_v<T, Args...> is \c true, and \c T
      ///       occurs exactly once in \c Types...
      ///
      /// \tparam T the type to construct
      /// \param args the arguments to forward to \p T's constructor
      /// \return reference to constructed element
      template<typename T, typename...Args,
               typename=std::enable_if_t<std::is_constructible<T,Args...>::value>>
      T& emplace( Args&&... args );

      /// \brief Creates a new value in-place
      ///
      /// Equivalent to emplace<I>(il, std::forward<Args>(args)...), where I is
      /// the zero-based index of T in Types....
      ///
      /// \note This overload only participates in overload resolution if
      ///       \c std::is_constructible_v<T, std::initializer_list<U>, Args...>
      ///       is \c true, and \p T occurs exactly once in Types...
      ///
      /// \tparam T the type to construct
      /// \param il an initializer list of entries
      /// \param args the arguments to forward to \p T's constructor
      /// \return reference to constructed element
      template<typename T, typename U, typename...Args,
               typename=std::enable_if_t<std::is_constructible<T,std::initializer_list<U>&,Args...>::value>>
      T& emplace( std::initializer_list<U> il, Args&&... args );

      /// \brief Creates a new value in-place
      ///
      /// First, destroys the currently contained value (if any).
      /// Then direct-initializes the contained value as if constructing a
      /// value of type \c T_I with the arguments \c std::forward<Args>(args)...
      ///
      /// If an exception is thrown, \c *this may become
      /// \c valueless_by_exception.
      ///
      /// \note This overload only participates in overload resolution if
      ///       \c std::is_constructible_v<T_I, Args...> is \c true.
      ///
      /// The behavior is undefined if I is not less than sizeof...(Types).
      ///
      /// \tparam I the index of the variant alternative to construct
      /// \param args the arguments to forward to \p T's constructor
      /// \return reference to constructed element
      template<std::size_t I, typename... Args,
               typename=std::enable_if_t<std::is_constructible<nth_type_t<I,Types...>,Args...>::value>>
      variant_alternative_t<I, variant>& emplace( Args&&... args );

      /// \brief Creates a new value in-place
      ///
      /// First, destroys the currently contained value (if any).
      /// Then direct-initializes the contained value as if constructing a
      /// value of type \c T_I with the arguments
      /// \c il,std::forward<Args>(args)...
      ///
      /// If an exception is thrown, \c *this may become
      /// \c valueless_by_exception.
      ///
      /// \note This overload only participates in overload resolution if
      ///       \c std::is_constructible_v<T_I, std::initializer_list<U> Args...>
      ///       is \c true.
      ///
      /// The behavior is undefined if I is not less than sizeof...(Types).
      ///
      /// \tparam I the index of the variant alternative to construct
      /// \param args the arguments to forward to \p T's constructor
      /// \return reference to constructed element
      template<std::size_t I, typename U, typename... Args,
               typename=std::enable_if_t<std::is_constructible<nth_type_t<I,Types...>,std::initializer_list<U>&,Args...>::value>>
      variant_alternative_t<I, variant>& emplace( std::initializer_list<U> il, Args&&... args );

      void swap( variant& rhs );
//        noexcept( ... )

      //----------------------------------------------------------------------
      // Private Static Members
      //----------------------------------------------------------------------
    private:

      static constexpr bool is_trivial = conjunction<std::is_trivially_destructible<Types>...>::value;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      template<typename...Ts>
      using union_type = detail::variant_union<is_trivial,Ts...>;

      //----------------------------------------------------------------------
      // Private Element Access
      //----------------------------------------------------------------------
    private:

      template<std::size_t I>
      constexpr variant_alternative_t<I,variant>&
        get( in_place_index_t<I> ) noexcept;

      template<std::size_t I>
      constexpr const variant_alternative_t<I,variant>&
        get( in_place_index_t<I> ) const noexcept;

      template<std::size_t I, typename...UTypes>
      friend constexpr variant_alternative_t<I, variant<UTypes...>>&
        get( variant<UTypes...>& v );
      template<std::size_t I, typename...UTypes>
      friend constexpr const variant_alternative_t<I, variant<UTypes...>>&
        get( const variant<UTypes...>& v );


      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      template<typename VariantUnion>
      void runtime_assign( std::size_t index, VariantUnion&& source );

      template<typename VariantUnion>
      static void runtime_assign_impl( std::size_t current,
                                       VariantUnion& dest,
                                       VariantUnion&& source,
                                       std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      template<typename VariantUnion>
      static void runtime_assign_impl( std::size_t current,
                                       VariantUnion& dest,
                                       VariantUnion&& source,
                                       std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      template<typename VariantUnion>
      static void runtime_assign_impl( std::size_t current,
                                       VariantUnion& dest,
                                       const VariantUnion& source,
                                       std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      template<typename VariantUnion>
      static void runtime_assign_impl( std::size_t current,
                                       VariantUnion& dest,
                                       const VariantUnion& source,
                                       std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      //----------------------------------------------------------------------

      template<std::size_t I, typename T>
      void static_assign( T&& value );

      /// \{
      template<typename VariantUnion, typename T>
      static void static_assign( in_place_index_t<std::size_t(-1)>,
                                 VariantUnion&, T&& );

      template<std::size_t I, typename VariantUnion, typename T>
      static void static_assign( in_place_index_t<I>,
                                 VariantUnion& dest,
                                 T&& value );

      template<typename VariantUnion, typename T>
      static void static_assign( in_place_index_t<0>,
                                 VariantUnion& dest,
                                 T&& value );
      /// \}

      //----------------------------------------------------------------------

      template<typename VariantUnion>
      void runtime_emplace( std::size_t index,
                            VariantUnion&& source );

      template<typename VariantUnion>
      void runtime_emplace_impl( std::size_t current,
                                 VariantUnion& dest,
                                 VariantUnion&& source,
                                 std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      template<typename VariantUnion>
      void runtime_emplace_impl( std::size_t current,
                                 VariantUnion& dest,
                                 VariantUnion&& source,
                                 std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      template<typename VariantUnion>
      void runtime_emplace_impl( std::size_t current,
                                 VariantUnion& dest,
                                 const VariantUnion& source,
                                 std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      template<typename VariantUnion>
      void runtime_emplace_impl( std::size_t current,
                                 VariantUnion& dest,
                                 const VariantUnion& source,
                                 std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* = nullptr);

      //----------------------------------------------------------------------

      /// \{
      /// \brief Statically emplaces
      ///
      /// \param storage
      /// \param args
      template<std::size_t I, std::size_t N, typename...Ts, typename...Args>
      static variant_alternative_t<I, variant>&
        static_emplace( in_place_index_t<N>,
                        union_type<Ts...>& storage,
                        Args&&...args );

      template<std::size_t I, typename...Ts, typename...Args>
      static variant_alternative_t<I, variant>&
        static_emplace( in_place_index_t<0>,
                        union_type<Ts...>& storage,
                        Args&&...args );
      /// \}
    };

    //-------------------------------------------------------------------------
    // Comparison
    //-------------------------------------------------------------------------

    template<typename...Types>
    constexpr bool operator==( const variant<Types...>& lhs,
                               const variant<Types...>& rhs ) noexcept;
    template<typename...Types>
    constexpr bool operator!=( const variant<Types...>& lhs,
                               const variant<Types...>& rhs ) noexcept;
    template<typename...Types>
    constexpr bool operator<( const variant<Types...>& lhs,
                              const variant<Types...>& rhs ) noexcept;
    template<typename...Types>
    constexpr bool operator>( const variant<Types...>& lhs,
                              const variant<Types...>& rhs ) noexcept;
    template<typename...Types>
    constexpr bool operator<=( const variant<Types...>& lhs,
                               const variant<Types...>& rhs ) noexcept;
    template<typename...Types>
    constexpr bool operator>=( const variant<Types...>& lhs,
                               const variant<Types...>& rhs ) noexcept;

    //=========================================================================
    // 23.7.5 : value access
    //=========================================================================

    /// \brief Checks if the variant v holds the alternative T.
    ///
    /// The call is ill-formed if T appears more than once in Types...
    ///
    /// \param v variant to examine
    /// \return \c true if the variant currently holds the alternative T
    template<typename T, typename...Types>
    constexpr bool holds_alternative( const variant<Types...>& v ) noexcept;

    //-------------------------------------------------------------------------

    /// \{
    template<std::size_t I, typename...Types>
    constexpr variant_alternative_t<I, variant<Types...>>&
      get( variant<Types...>& v );
    template<std::size_t I, typename...Types>
    constexpr variant_alternative_t<I, variant<Types...>>&&
      get( variant<Types...>&& v );
    template<std::size_t I, typename...Types>
    constexpr const variant_alternative_t<I, variant<Types...>>&
      get( const variant<Types...>& v );
    template<std::size_t I, typename...Types>
    constexpr const variant_alternative_t<I, variant<Types...>>&&
      get( const variant<Types...>&& v );
    /// \}

    //-------------------------------------------------------------------------

    /// \{
    /// \brief Gets the
    ///
    /// \throws bad_variant_access if \c T is not the active alternative
    ///
    /// \tparam T the type of the alternative to retrieve
    /// \param v the variant to extract the entry from
    /// \return the alternative
    template<typename T, typename...Types>
    constexpr T& get( variant<Types...>& v );
    template<typename T, typename...Types>
    constexpr T&& get( variant<Types...>&& v );
    template<typename T, typename...Types>
    constexpr const T& get( const variant<Types...>& v );
    template<typename T, typename...Types>
    constexpr const T&& get( const variant<Types...>&& v );
    /// \}

    //-------------------------------------------------------------------------

    /// \{
    /// \brief Index-based non-throwing accessor
    ///
    /// If \p pv is not a null pointer and \c pv->index() == I, returns a
    /// pointer to the value stored in the variant pointed to by pv.
    /// Otherwise, returns a null pointer value.
    ///
    /// The call is ill-formed if I is not a valid index in the variant
    ///
    /// \tparam I the index of the alternative to extract
    /// \param pv the pointer to the variant to extract the value from
    /// \return pointer to the variant alternative when successful
    template<std::size_t I, typename...Types>
    constexpr std::add_pointer_t<variant_alternative_t<I, variant<Types...>>>
      get_if( variant<Types...>* pv ) noexcept;
    template<std::size_t I, typename...Types>
    constexpr std::add_pointer_t<const variant_alternative_t<I, variant<Types...>>>
      get_if( const variant<Types...>* pv ) noexcept;
    /// \}

    /// \{
    /// \brief Type-based non-throwing accessor
    ///
    /// Equivalent to the index-based \c get_if with \c I being the zero-based
    /// index of \p T in \c Types....
    ///
    /// The call is ill-formed if T is not a unique element of Types.
    ///
    /// \tparam T the alternative type to retrieve
    /// \param pv the pointer to the variant to extract the value from
    /// \return pointer to the variant alternative when successful
    template<typename T, typename...Types>
    constexpr std::add_pointer_t<T> get_if( variant<Types...>* pv ) noexcept;
    template<typename T, typename...Types>
    constexpr std::add_pointer_t<const T> get_if( const variant<Types...>* pv ) noexcept;
    /// \}

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Computes the hash of this variant
    ///
    /// The computed hash is the hash of the active variant alternative.
    ///
    /// \param val the variant to hash
    /// \return the hash of the underlying value
    template<typename...Types>
    constexpr hash_t hash_value( const variant<Types...>& val ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/variant.inl"

#endif /* BIT_STL_UTILITIES_VARIANT_HPP */
