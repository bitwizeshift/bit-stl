/**
 * \file variant.hpp
 *
 * \brief This header contains an implementation of the c++17 extension type
 *        std::variant
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_VARIANT_HPP
#define BIT_STL_VARIANT_HPP

#include "utility.hpp"

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Unit type intended for use as a well-behaved empty alternative
    ///        in variant.
    ///
    /// In particular, a variant of non-default-constructible types may list
    /// monostate as its first alternative: this makes the variant itself
    /// default-contructible
    //////////////////////////////////////////////////////////////////////////
    struct monostate { };

    constexpr bool operator<(monostate, monostate) noexcept { return false; }
    constexpr bool operator>(monostate, monostate) noexcept { return false; }
    constexpr bool operator<=(monostate, monostate) noexcept { return true; }
    constexpr bool operator>=(monostate, monostate) noexcept { return true; }
    constexpr bool operator==(monostate, monostate) noexcept { return true; }
    constexpr bool operator!=(monostate, monostate) noexcept { return false; }

    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief bad_variant_access is the type of the exception thrown in the
    ///        following situations:
    ///
    /// - get:   called with an index or type that does not match the
    ///          currently active alternative
    /// - visit: called to visit a variant that is valueless_by_exception
    //////////////////////////////////////////////////////////////////////////
    class bad_variant_access : public std::exception
    {

    };

    //------------------------------------------------------------------------

    //------------------------------------------------------------------------
    // Variant
    //------------------------------------------------------------------------

    constexpr std::size_t variant_npos = -1;

    namespace detail {

      template<typename T, typename...Rest>
      union variant_storage_t
      {
         T                          entry;
         variant_storage_t<Rest...> rest;

         constexpr variant_storage_t() : entry(){}
      };

      template<typename T>
      union variant_storage_t<T>
      {
        T entry;
      };
    }

    //////////////////////////////////////////////////////////////////////////
    /// \brief This type acts as a discriminated type-safe union around a
    ///        fixed sequence of types specified in the template.
    ///
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename...Types>
    class variant
    {

      static_assert(sizeof...(Types) > 0, "variant must contain at least one type");

      using T0 = std::tuple_element_t<0,std::tuple<Types...>>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs this variant of the first alternative
      ///        type (index() is zero).
      ///
      /// This constructor is \c constexpr if and only if the value initialization
      /// of the alternative type \c T0 would satisfy the requirements for a
      /// \c constexpr function
      ///
      /// \note This constructor only participates in overload resolution if
      ///       the first alternative type is default constructible
#ifndef BIT_DOXYGEN_BUILD
      template<typename = std::enable_if_t<std::is_default_constructible<T0>::value>>
#endif
      constexpr variant();

      /// \brief Copy constructs
      ///
      /// \note This constructor only participates in overload resolution if
      ///       \c std::is_copy_constructible is \c true for all Types...
#ifndef BIT_DOXYGEN_BUILD
      template<typename = std::enable_if_t<conjunction<std::is_copy_constructible<Types>...>::value>>
#endif
      variant( const variant& other );

      /// \brief Move constructs
      ///
      /// \note This constructor only participates in overload resolution if
      ///       \c std::is_move_constructible is \c true for all Types...
#ifndef BIT_DOXYGEN_BUILD
      template<typename = std::enable_if_t<conjunction<std::is_move_constructible<Types>...>::value>>
#endif
      variant( variant&& other );

#ifndef BIT_DOXYGEN_BUILD
      template<typename T,
               typename = std::enable_if_t
               <
                 !std::is_same<std::decay_t<T>, variant>::value &&
                 !is_in_place<std::decay_t<T>>::value &&
                 disjunction<std::is_default_constructible<Types>...>::value
                >
              >
#else
      template<typename T>
#endif
      constexpr variant( T&& t );

      template<typename T, typename...Args>
      constexpr explicit variant( in_place_type_t<T>, Args&&... args );

      template<typename T, typename U, typename...Args>
      constexpr explicit variant( in_place_type_t<T>,
                                  std::initializer_list<U> il, Args&&... args );

      template<std::size_t I, typename...Args>
      constexpr explicit variant( in_place_index_t<I>, Args&&... args );

      template<std::size_t I, typename U, typename...Args>
      constexpr explicit variant( in_place_index_t<I>,
                                  std::initializer_list<U> il, Args&&... args );

      template<typename Alloc>
      variant( std::allocator_arg_t, const Alloc& a );

      template<typename Alloc>
      variant( std::allocator_arg_t, const Alloc& a, const variant& other );

      template<typename Alloc>
      variant( std::allocator_arg_t, const Alloc& a, variant&& other );

      template<typename Alloc, typename T>
      variant( std::allocator_arg_t, const Alloc& a, T&& t );

      template<typename Alloc, typename T, typename... Args>
      variant( std::allocator_arg_t, const Alloc& a,
               in_place_type_t<T>, Args&&... args );

      template<typename Alloc, typename T, typename U, typename... Args>
      variant( std::allocator_arg_t, const Alloc& a,
               in_place_type_t<T>, std::initializer_list<U> il, Args&&... args );

      template<typename Alloc, size_t I, typename... Args>
      variant( std::allocator_arg_t, const Alloc& a,
               in_place_index_t<I>, Args&&... args );

      template<typename Alloc, size_t I, typename U, typename... Args>
      variant( std::allocator_arg_t, const Alloc& a,
               in_place_index_t<I>, std::initializer_list<U> il, Args&&... args );

      ~variant();

    public:


    public:

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using data_storage_t = detail::variant_storage_t<Types...>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      data_storage_t m_storage; /// The storage for the variant
      std::size_t    m_index;   /// The active index of the variant

    };

    //------------------------------------------------------------------------
    // Type Traits
    //------------------------------------------------------------------------

    template<typename T>
    struct variant_size;

    template<typename...Types>
    struct variant_size<variant<Types...>>
      : std::integral_constant<std::size_t, sizeof...(Types)> { };

    template<typename T>
    constexpr std::size_t variant_size_v = variant_size<T>::value;

    template <std::size_t I, typename T>
    struct variant_alternative;

    //------------------------------------------------------------------------
    // Hashing
    //------------------------------------------------------------------------

    /// \brief Hashes the value of a monostate
    ///
    /// \note The hash value of a monostate is always 0, because there it
    ///       contains no state (by definition)
    ///
    /// \param  val the monostate value
    /// \return The hash of the monostate (0)
    constexpr std::size_t hash_value( monostate val ) noexcept;

    /// \brief Calculates the hash of the variant
    ///
    /// \param  val the variant to hash
    /// \return The hash of the variant
    template<typename...Types>
    constexpr std::size_t hash_value( variant<Types...> val ) noexcept;



  } // namespace stl
} // namespace bit

#endif /* BIT_STL_VARIANT_HPP */
