/**
 * \file utility.hpp
 *
 * \brief This header contains extensions to the standard 'utility' header
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_UTILITY_HPP
#define BIT_STL_UTILITY_HPP

// bit::stl libraries
#include "type_traits.hpp"

// std libraries
#include <type_traits> // for std::remove_reference
#include <utility>     // for std::forward
#include <stdexcept>   // for std::out_of_range

namespace bit {
  namespace stl {
    namespace detail {

      /// \brief Used to disambiguate unspecialized in_place
      struct in_place_ctor_tag{};

      /// \brief Used to disambiguate typed in-place
      template<typename T>
      struct in_place_ctor_type_tag{};

      /// \brief Used to disambiguate indexed in-place
      template<std::size_t I>
      struct in_place_ctor_index_tag{};

    } // namespace detail

    //--------------------------------------------------------------------------
    // In Place Tags / Types
    //--------------------------------------------------------------------------

    /// \brief in_place_tag is an empty struct type used as the return types
    ///        of the in_place functions for disambiguation.
    struct in_place_tag
    {
      in_place_tag() = delete;
      in_place_tag(int){}
    };

    /// \brief This function is a special disambiguation tag for variadic functions, used in
    ///        any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
#ifndef BIT_DOXYGEN_BUILD
    inline in_place_tag in_place( detail::in_place_ctor_tag = detail::in_place_ctor_tag() ){ return {0}; }
#else
    in_place_tag in_place();
#endif

    /// \brief This function is a special disambiguation tag for variadic functions, used in
    ///        any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<typename T>
#ifndef BIT_DOXYGEN_BUILD
    inline in_place_tag in_place( detail::in_place_ctor_type_tag<T> = detail::in_place_ctor_type_tag<T>() ){ return {0}; }
#else
    in_place_tag in_place();
#endif

    /// \brief This function is a special disambiguation tag for variadic functions, used in
    ///        any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<std::size_t I>
#ifndef BIT_DOXYGEN_BUILD
    inline in_place_tag in_place( detail::in_place_ctor_index_tag<I> = detail::in_place_ctor_index_tag<I>() ){ return {0}; }
#else
    in_place_tag in_place();
#endif

    /// \brief A tag type used for dispatching in_place calls
    using in_place_t = in_place_tag(&)( detail::in_place_ctor_tag );

    /// \brief A tag type used for type-based dispatching in_place calls
    template<typename T>
    using in_place_type_t = in_place_tag(&)( detail::in_place_ctor_type_tag<T> );

    /// \brief A tag type used for type-based dispatching in_place calls
    template <std::size_t I>
    using in_place_index_t = in_place_tag(&)( detail::in_place_ctor_index_tag<I> );

    /// \brief Type-trait to determine if the type is an in_place type
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_in_place : std::false_type{};

    template<>
    struct is_in_place<in_place_t> : std::true_type{};

    template<typename T>
    struct is_in_place<in_place_type_t<T>> : std::true_type{};

    template<std::size_t I>
    struct is_in_place<in_place_index_t<I>> : std::true_type{};

    template<typename T>
    constexpr bool is_in_place_v = is_in_place<T>::value;

    //--------------------------------------------------------------------------
    // Final Act
    //--------------------------------------------------------------------------

    /// \brief A wrapper around std::forward that removes the need for
    ///        specifying the type T.
    ///
    /// \param x the value to forward
    template<typename T>
    constexpr decltype(auto) fwd(T&& x) noexcept;

    /// \brief A wrapper function that acts like std::forward while decaying
    ///        the underlying type
    ///
    /// \param x the value to forward
    /// \return the decay-forwarded value
    template<typename T>
    constexpr decltype(auto) decay_forward(T&& x) noexcept;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief This class leverages RAII to perform cleanup actions at the end
    ///        of a scope
    ///
    /// This is guaranteed to run the action, even if an exception is thrown
    ////////////////////////////////////////////////////////////////////////////
    template<typename Func>
    class final_act final
    {
      //------------------------------------------------------------------------
      // Constructors
      //------------------------------------------------------------------------
    public:
      /// \brief Constructs an action to perform on end-of-scope
      ///
      /// \param function The function to call at the end
      constexpr explicit final_act( Func&& function );

      /// \brief Move-constructs a final act to perform on end-of-scope
      ///
      /// \param other the other act to move
      constexpr final_act(final_act&& other);

      /// \brief Disallow copy-construction
      final_act(const final_act&) = delete;

      /// \brief Move-assigns a final act to perform an end-of-scope
      ///
      /// \param other the other act to move
      final_act& operator=(final_act&& other);

      /// \brief Disallow copy-assignment
      final_act& operator=(const final_act&) = delete;

      /// \brief Destroys the final act, invoking the action
      ~final_act();

      //------------------------------------------------------------------------
      // API
      //------------------------------------------------------------------------
    public:

      /// \brief Cancels the final act from occurring
      void cancel() noexcept;

      //------------------------------------------------------------------------
      // Private Member Function
      //------------------------------------------------------------------------
    private:

        Func m_action;      ///< The action to perform
        bool m_will_invoke; ///< Whether or not this will invoke
    };

    /// \brief Convenience function to generate a final_act
    ///
    /// \param function the function to perform on the final act
    template<typename Func>
    inline constexpr final_act<Func> finally( Func&& function ) noexcept;

    //--------------------------------------------------------------------------
    // Indexing
    //--------------------------------------------------------------------------

    namespace detail {

      template<typename T, typename Key, typename = void>
      struct has_at : std::false_type{};

      template<typename T, typename Key>
      struct has_at<
        T,
        Key,
        void_t<decltype(std::declval<T>().at( std::declval<Key>() ))>
      > : std::true_type{};

    } // namespace detail

    /// \brief Safely retrieves the value at the given index, otherwise asserts
    ///
    /// \param array reference to the array to index into
    /// \param n     the index to retrieve
    /// \return reference to instance
    template<typename T, std::size_t N>
    constexpr T& at( T (&array)[N], std::size_t n );

    /// \brief Safely retrieves the value at the given index, otherwise asserts
    ///
    /// \param array reference to the array to index into
    /// \param n     the index to retrieve
    /// \return reference to instance
#ifndef BIT_DOXYGEN_BUILD
    template<typename Container, typename Key, typename = std::enable_if_t<detail::has_at<Container,Key>::value>>
#else
    template<typename Container, typename Key>
#endif
    constexpr decltype(auto) at( Container& container, Key&& key );

    //--------------------------------------------------------------------------
    // Hashing Utilities
    //--------------------------------------------------------------------------

    /// \brief Combines the hash with another hash
    ///
    /// \param seed The seed to combine the hash with
    /// \param v the value to hash
    template<typename T>
    constexpr void hash_combine( std::size_t& seed, const T& v );

    /// \brief Hashes a range of entries, returning the result
    ///
    /// This is equivalent to combining hashes of all entries within the range
    ///
    /// \param first The beginning of the range to hash
    /// \param last The end of the range to hash
    /// \return the hashed value
    template<typename InputIterator>
    constexpr std::size_t hash_range( InputIterator first, InputIterator last );

    /// \brief Hashes a range of entries
    ///
    /// This is equivalent to combining hashes of all entries within the range
    ///
    /// \param seed The seed to comine the hash with
    /// \param first The beginning of the range to hash
    /// \param last The end of the range to hash
    template<typename InputIterator>
    constexpr void hash_range( std::size_t& seed,
                               InputIterator first,
                               InputIterator last );

    //--------------------------------------------------------------------------
    // Hashing Calculations
    //--------------------------------------------------------------------------

    /// \brief Calculates a hash of a null pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( std::nullptr_t ) noexcept;

    /// \brief Calculates a hash of the given bool
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( bool val ) noexcept;

    /// \brief Calculates a hash of the given char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( char val ) noexcept;

    /// \brief Calculates a hash of the given signed char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( signed char val ) noexcept;

    /// \brief Calculates a hash of the given unsigned char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned char val ) noexcept;

    /// \brief Calculates a hash of the given wchar_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( wchar_t val ) noexcept;

    /// \brief Calculates a hash of the given char16_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( char16_t val ) noexcept;

    /// \brief Calculates a hash of the given char32_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( char32_t val ) noexcept;

    /// \brief Calculates a hash of the given short
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( short val ) noexcept;

    /// \brief Calculates a hash of the given unsigned short
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned short val ) noexcept;

    /// \brief Calculates a hash of the given int
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( int val ) noexcept;

    /// \brief Calculates a hash of the given unsigned int
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned int val ) noexcept;

    /// \brief Calculates a hash of the given long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( long val ) noexcept;

    /// \brief Calculates a hash of the given unsigned long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned long val ) noexcept;

    /// \brief Calculates a hash of the given long long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( long long val ) noexcept;

    /// \brief Calculates a hash of the given unsigned long long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned long long val ) noexcept;

    /// \brief Calculates a hash of the given float
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    std::size_t hash_value( float val ) noexcept;

    /// \brief Calculates a hash of the given double
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    std::size_t hash_value( double val ) noexcept;

    /// \brief Calculates a hash of the given long double
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    std::size_t hash_value( long double val ) noexcept;

    /// \brief Calculates a hash of the given pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T>
    std::size_t hash_value( T* const& val ) noexcept;

    /// \brief Calculates a hash of the given T array
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T, unsigned N>
    constexpr std::size_t hash_value( T (&val)[N] );

    /// \brief Calculates a hash of the given T array
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T, unsigned N>
    constexpr std::size_t hash_value( const T (&val)[N] );

    /// \brief Hashes enum values
    ///
    /// \note This only participates in overload resolution if
    ///       \c std::is_enum is \c true
    ///
    /// \param val the enum value to hash
    /// \return the hash value of the enum
#ifndef BIT_DOXYGEN_BUILD
    template<typename Enum, typename = std::enable_if_t<std::is_enum<Enum>::value>>
#else
    template<typename Enum>
#endif
    constexpr std::size_t hash_value( Enum val ) noexcept;

    /// \brief Hashes any given container
    ///
    /// The hash is computed as the combination of all the hashes within the
    /// container
    ///
    /// \note This does not participate in overload resolution unless
    ///       the container defines begin() and end()
    ///
    /// \param container the container to hash
    /// \return the hash value
#ifndef BIT_DOXYGEN_BUILD
    template<typename Container, typename = std::enable_if_t<has_const_iterators<Container>::value>>
#else
    template<typename Container>
#endif
    constexpr std::size_t hash_value( const Container& container ) noexcept;

    /// \brief Hashes a std::pair
    ///
    /// \param pair the pair to hash
    template<typename T, typename U>
    constexpr std::size_t hash_value( const std::pair<T,U>& pair );

    /// \brief Hashes a tuple of entries
    ///
    /// \param tuple the tuple to hash
    template<typename...Args>
    constexpr std::size_t hash_value( const std::tuple<Args...>& tuple );

    /// \brief Hashes an initializer_list
    ///
    /// This is equivalent to calling hash_range( il.begin(), il.end() )
    ///
    /// \param il the initializer_list to hash
    /// \return the hash of the initializer_list
    template<typename T>
    constexpr std::size_t hash_value( const std::initializer_list<T>& il );

    //--------------------------------------------------------------------------

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Hash struct that satisfies the requirements of \c std::hash,
    ///        but is implemented in terms of hash_value to allow for
    ///        easy ADL overloads and type-querying
    ////////////////////////////////////////////////////////////////////////////
    template<typename Key>
    struct hash
    {
      /// \brief Functor that hashes all key types
      ///
      /// \param val the value to hash
      /// \return the hash of the \p val
      constexpr std::size_t operator()( const Key& val );
    };

    //--------------------------------------------------------------------------
    // Tuple Applications
    //--------------------------------------------------------------------------

    /// \brief Construct an object of type T, using the elements of the tuple t as
    ///        the arguments to the constructor
    ///
    /// \tparam T the type to construct
    /// \param t tuple whose elements to be used as arguments to the constructor of T
    /// \return The constructed T object
    template <typename T, typename Tuple>
    constexpr T make_from_tuple( Tuple&& t );

    /// \brief Invoke the Callable object f with a tuple of arguments
    ///
    /// \param f Callable object to be invoked
    /// \param t tuple whose elements to be used as arguments to \p f
    /// \return The value returned from invoking \p f with \p t's elements
    template <typename F, typename Tuple>
    constexpr decltype(auto) apply( F&& f, Tuple&& t );

    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper to propagate the const qualifier
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class propagate_const
    {

      template<typename U>
      using is_enabled_and_explicit = conjunction<
        std::is_constructible<T, U&&>,
        negation<std::is_convertible<U&&, T>>
      >;

      template<typename U>
      using is_enabled_and_implicit = conjunction<
        std::is_constructible<T, U&&>,
        std::is_convertible<U&&, T>
      >;

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = std::remove_reference_t<decltype(*std::declval<T&>())>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      constexpr propagate_const() = default;

      constexpr propagate_const( propagate_const&& p ) = default;

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_explicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      constexpr propagate_const( propagate_const<U>&& pu );

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_implicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      explicit constexpr propagate_const( propagate_const<U>&& pu );

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_explicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      constexpr propagate_const( U&& u );

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_implicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      explicit constexpr propagate_const( U&& u );

      propagate_const( const propagate_const& ) = delete;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      constexpr propagate_const& operator=( propagate_const&& p ) = default;

      template<typename U>
      constexpr propagate_const& operator=( propagate_const<U>&& pu );

      template<typename U>
      constexpr propagate_const& operator=( U&& u );

      propagate_const& operator=( const propagate_const& ) = delete;

      //----------------------------------------------------------------------
      // Member Functions
      //----------------------------------------------------------------------
    public:

      constexpr void swap( propagate_const& pt );

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      constexpr element_type* get();

      constexpr const element_type* get() const;

      constexpr explicit operator bool() const;

      constexpr element_type& operator*();

      constexpr const element_type& operator*() const;

      constexpr element_type* operator->();

      constexpr const element_type* operator->() const;

      constexpr operator element_type*();

      constexpr operator const element_type*() const;

    };

  } // namespace stl
} // namespace bit

#include "detail/utility.inl"

#endif /* BIT_STL_UTILITY_HPP */
