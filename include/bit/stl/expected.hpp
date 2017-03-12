/**
 * \file expected.hpp
 *
 * \brief This header contain an 'optional' like class that holds onto either
 *        an exception, or a value
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_EXPECTED_HPP
#define BIT_STL_EXPECTED_HPP

#include "utility.hpp"

#include <stdexcept>

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception indicating a bad access was attempted for an
    ///        expected type
    ///
    /// bit::stl::bad_expected_access is the type of exception thrown
    /// in the following situations:
    /// - expected::value is called on an expected with a null std::exception_ptr
    /// - expected::value is called on an expected that is valueless_by_exception
    //////////////////////////////////////////////////////////////////////////
    class bad_expected_access : public std::logic_error
    {
    public:
      bad_expected_access() : std::logic_error("bit::bad_expected_access"){}
    };


    //////////////////////////////////////////////////////////////////////////
    /// \brief An expected type is a combination of an optional and an
    ///        exception type.
    ///
    /// Rather than supporting a null-case like optional, expected either
    /// contains an instance of a value, or an exception.
    ///
    /// If it is an exception, and the value is attempted to be accessed, it
    /// will instead throw the stored exception.
    ///
    /// The type of the exception can also be queries, allowing for a query-
    /// based API rather than forcing stack-unwinding
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class expected
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type = T;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs the underlying type-T for this expected
      ///
      /// \note This constructor is only enabled if T has a default-constructor
      constexpr expected()
        noexcept( std::is_nothrow_default_constructible<T>::value );

      /// \brief Constructs an expected from the current exception
      ///
      /// \note If \c std::current_exception() returns null, then the
      ///       expected will contain a bad_expected_access.
      ///
      /// \param tag The type tag for tag dispatch
      explicit expected( in_place_type_t<std::exception_ptr> tag );

      /// \brief Constructs an expected of the exception type, forwarding
      ///        \p args to the constructor
      ///
      /// \param tag  The type tag for the exception to throw
      /// \param args The arguments to the exception type
      template<typename Exception, typename...Args>
      explicit expected( in_place_type_t<Exception> tag, Args&&...args )
        noexcept( std::is_nothrow_constructible<Exception,Args...>::value );

      /// \brief Constructs an expected of the exception type, forwarding
      ///        \p ilist and \p args to the constructor
      ///
      /// \param tag   The type tag for the exception to throw
      /// \param ilist The initializer list to forward to the constructor
      /// \param args  The arguments to the exception type
      template<typename Exception, typename U, typename...Args>
      explicit expected( in_place_type_t<Exception> tag, std::initializer_list<U> ilist, Args&&...args )
        noexcept( std::is_nothrow_constructible<Exception,std::initializer_list<U>,Args...>::value );

      /// \brief Constructs an expected by forwarding the \p args to the
      ///        constructor
      ///
      /// \param tag   Tag to dispatch to \p T's constructor
      /// \param args  The arguments to type \p T
      template<typename...Args>
      constexpr explicit expected( in_place_t tag, Args&&...args )
        noexcept( std::is_nothrow_constructible<Args...>::value );

      /// \brief Constructs an expected by forwarding the \p args to the
      ///        constructor
      ///
      /// \param tag   Tag to dispatch to \p T's constructor
      /// \param ilist The initializer list to forward to the constructor
      /// \param args  The arguments to type \p T
      template<typename U, typename...Args>
      constexpr explicit expected( in_place_t tag, std::initializer_list<U> ilist, Args&&...args )
        noexcept( std::is_nothrow_constructible<std::initializer_list<U>,Args...>::value );

      /// \brief Copy-constructs an expected of type \p T
      ///
      /// \param value the type to move
      constexpr expected( const T& other )
        noexcept( std::is_nothrow_copy_constructible<T>::value );

      /// \brief Move-constructs an expected of type \p T
      ///
      /// \param value the type to move
      constexpr expected( T&& value )
        noexcept( std::is_nothrow_move_constructible<T>::value );

      /// \brief Copy-constructs an expected from another expected
      ///
      /// \param other the other expected to copy
      expected( const expected& other );

      /// \brief Move-constructs an expected from another expected
      ///
      /// \param other the other expected to move
      expected( expected&& other );

      /// \brief Copy-constructs an expected type
      ///
      /// \param other the other expected to copy
      expected& operator=( const expected& other );

      /// \brief Move-constructs an expected type
      ///
      /// \param other the other expected to move
      expected& operator=( expected&& other );

      /// \brief Deletes the expected type
      ~expected();

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Queries whether or not this expected contains a value.
      ///
      /// This is \c true when the it contains a value, false on exception
      constexpr explicit operator bool() const noexcept;

      /// \brief Queries whether this exception is valueless due to an
      ///        exception
      ///
      /// This state is only achieved through a failure in between a
      /// destructor and constructor call
      ///
      /// \return \c true if this expected is valueless by construction
      constexpr bool valueless_by_exception() const noexcept;

      /// \brief Queries whether or not this expected contains a value
      ///
      /// \return \c true when it contains a value
      constexpr bool has_value() const noexcept;

      /// \brief Queries whether or not this expected contains an exception
      ///        of type \p Exception
      ///
      /// \tparam Exception the exception type to query
      /// \return \c true when it contains an exception convertible to type
      ///         \p Exception
      template<typename Exception>
      bool has_exception() const noexcept;

      /// \brief Queries whether or not this expected contains an exception
      ///        of type \p Exception
      ///
      /// \return \c true when it contains an exception
      bool has_exception() const noexcept;

      //------------------------------------------------------------------------

      /// \brief Access the contained value by pointer
      ///
      /// \note It is undefined behaviour to access this while holding onto
      ///       an exception, or being in a state of valueless_by_exception
      ///
      /// \return pointer to the contained value
      constexpr value_type* operator->() noexcept;

      /// \copydoc operator->()
      constexpr const value_type* operator->() const noexcept;

      /// \brief Accesses the containe value by lvalue-reference
      ///
      /// \note It is undefined behaviour to access this while holding onto
      ///       an exception, or being in a state of valueless_by_exception
      ///
      /// \return lvalue-reference to the contained value
      constexpr value_type& operator*() & noexcept;

      /// \brief Accesses the containe value by rvalue-reference
      ///
      /// \note It is undefined behaviour to access this while holding onto
      ///       an exception, or being in a state of valueless_by_exception
      ///
      /// \return rvalue-reference to the contained value
      constexpr value_type&& operator*() && noexcept;

      /// \copdoc operator*() &
      constexpr const value_type& operator*() const& noexcept;

      /// \copdoc operator*() &&
      constexpr const value_type&& operator*() const&& noexcept;

      //------------------------------------------------------------------------

      /// \brief Returns the contained value.
      ///
      /// \throws underlying exception if expected contains an exception.
      ///
      /// \return the value of \c *this
      constexpr value_type& value() &;

      /// \copydoc value() &
      constexpr const value_type & value() const &;

      /// \copydoc value() &
      constexpr value_type&& value() &&;

      /// \copydoc value() &
      constexpr const value_type&& value() const &&;

      //------------------------------------------------------------------------

      /// \brief Returns the contained value if \c *this has a value,
      ///        otherwise returns \p default_value.
      ///
      /// \param default_value the value to use in case \c *this is empty
      /// \return the value to use in case \c *this is empty
      template<typename U>
      constexpr value_type value_or( U&& default_value ) const&;

      /// \copydoc value_or( U&& )
      template<typename U>
      constexpr value_type value_or( U&& default_value ) &&;

      //------------------------------------------------------------------------
      // Modifiers
      //------------------------------------------------------------------------
    public:

      /// \brief Swaps the contents of this with \p rhs
      ///
      /// \param rhs the right-hand-side to exchange with
      void swap( expected<T>& rhs ) noexcept;

      /// \brief Emplaces a value into this expected.
      ///
      /// \note If this currently holds a value, it is destructed first
      ///
      /// \param args the arguments to construct T with
      template<typename...Args >
      void emplace( Args&&... args )
        noexcept( std::is_nothrow_constructible<T,Args...>::value );

      /// \brief Emplaces a value into this expected.
      ///
      /// \note If this currently holds a value, it is destructed first
      ///
      /// \param ilist the initializer list to forward to T
      /// \param args the arguments to construct T with
      template<typename U, typename...Args>
      void emplace( std::initializer_list<U> ilist, Args&&... args )
        noexcept( std::is_nothrow_constructible<T,std::initializer_list<U>,Args...>::value );

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      /// \brief An empty type to use as a placeholder in a union.
      ///
      /// This is trivially destructible to avoid any need for calling a
      /// destructor first
      struct empty_type{ constexpr empty_type() = default; };

      ////////////////////////////////////////////////////////////////////////
      /// \brief A constexpr storage type
      ///
      ////////////////////////////////////////////////////////////////////////
      union storage_type
      {
        empty_type         empty;
        T                  value;
        std::exception_ptr exception;

        constexpr storage_type()
          : empty{}
        {}

        template<typename...Args>
        constexpr storage_type( in_place_type_t<std::exception_ptr>, Args&&...args )
          : exception( std::forward<Args>(args)... )
        {}

        template<typename...Args>
        constexpr storage_type( in_place_type_t<T>, Args&&...args )
          : value( std::forward<Args>(args)... )
        {}

        ~storage_type() noexcept{};
      };

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      storage_type m_storage;      ///< The storage type
      bool         m_is_exception; ///< Whether or not this is an exception

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      /// \brief Private constructor that forwards the exception ptr to the
      ///        expected
      ///
      /// \param tag The type tag for tag dispatch
      /// \param ptr the exception pointer
      explicit expected( in_place_type_t<std::exception_ptr> tag, std::exception_ptr );

      /// \brief Throws an exception if this type is currently holding an
      ///        exception
      void throw_if_exception() const;

      /// \brief Destructs the underlying type
      void destruct();

      /// \brief Reconstructs an expected into a value from the given arguments
      ///
      /// \param expected the expected to construct
      /// \param args     the args to forward for construction
      template<typename...Args>
      static void reconstruct_value( expected<T>& expected, Args&&...args );

      /// \brief Reconstructs an expected into an exception from the given arguments
      ///
      /// \param expected the expected to construct
      /// \param args     the args to forward for construction
      template<typename...Args>
      static void reconstruct_exception( expected<T>& expected, Args&&...args );
    };

    //------------------------------------------------------------------------
    // Comparison Operators
    //------------------------------------------------------------------------

    /// \brief Compares two expected<T> values together for equality
    ///
    /// \param lhs the entry on the left of the equality
    /// \param rhs the entry on the right of the equality
    /// \return \c true if the two entries are equal
    template<typename T>
    constexpr bool operator == ( const expected<T>& lhs, const expected<T>& rhs ) noexcept;

    /// \brief Compares two expected<T> values together for inequality equality
    ///
    /// \param lhs the entry on the left of the equality
    /// \param rhs the entry on the right of the equality
    /// \return \c true if the two entries are not equal
    template<typename T>
    constexpr bool operator != ( const expected<T>& lhs, const expected<T>& rhs ) noexcept;

    /// \brief Compares \p lhs < \p rhs
    ///
    /// \param lhs the entry on the left of the equality
    /// \param rhs the entry on the right of the equality
    /// \return \c true if \p lhs is less than \p rhs
    template<typename T>
    constexpr bool operator < ( const expected<T>& lhs, const expected<T>& rhs ) noexcept;

    /// \brief Compares \p lhs <= \p rhs
    ///
    /// \param lhs the entry on the left of the equality
    /// \param rhs the entry on the right of the equality
    /// \return \c true if \p lhs is less than or equal to \p rhs
    template<typename T>
    constexpr bool operator <= ( const expected<T>& lhs, const expected<T>& rhs ) noexcept;

    /// \brief Compares \p lhs > \p rhs
    ///
    /// \param lhs the entry on the left of the equality
    /// \param rhs the entry on the right of the equality
    /// \return \c true if \p lhs is greater than \p rhs
    template<typename T>
    constexpr bool operator > ( const expected<T>& lhs, const expected<T>& rhs ) noexcept;

    /// \brief Compares \p lhs > \p rhs
    ///
    /// \param lhs the entry on the left of the equality
    /// \param rhs the entry on the right of the equality
    /// \return \c true if \p lhs is greater than or equal to \p rhs
    template<typename T>
    constexpr bool operator >= ( const expected<T>& lhs, const expected<T>& rhs ) noexcept;

    //--------------------------------------------------------------------------
    // Compare an optional object with a T
    //--------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator == ( const T& lhs, const expected<T>& rhs ) noexcept;

    template<typename T>
    constexpr bool operator == ( const expected<T>& lhs, const T& rhs ) noexcept;

    template<typename T>
    constexpr bool operator != ( const T& lhs, const expected<T>& rhs ) noexcept;

    template<typename T>
    constexpr bool operator != ( const expected<T>& lhs, const T& rhs ) noexcept;

    template<typename T>
    constexpr bool operator < ( const T& lhs, const expected<T>& rhs ) noexcept;

    template<typename T>
    constexpr bool operator < ( const expected<T>& lhs, const T& rhs ) noexcept;

    template<typename T>
    constexpr bool operator <= ( const T& lhs, const expected<T>& rhs ) noexcept;

    template<typename T>
    constexpr bool operator <= ( const expected<T>& lhs, const T& rhs ) noexcept;

    template<typename T>
    constexpr bool operator > ( const T& lhs, const expected<T>& rhs ) noexcept;

    template<typename T>
    constexpr bool operator > ( const expected<T>& lhs, const T& rhs ) noexcept;

    template<typename T>
    constexpr bool operator >= ( const T& lhs, const expected<T>& rhs ) noexcept;

    template<typename T>
    constexpr bool operator >= ( const expected<T>& lhs, const T& rhs ) noexcept;


    //------------------------------------------------------------------------
    // Inline Definitions
    //------------------------------------------------------------------------

    /// \brief Creates an expected object from \p value
    ///
    /// \param value the value to construct the optional from
    template<typename T>
    constexpr expected<std::decay_t<T>> make_expected( T&& value )
      noexcept( noexcept( expected<std::decay_t<T>>( std::forward<T>(value) ) ) );

    /// \brief Creates an expected object of type \p T from the given \p args
    ///
    /// \tparam T the type to construct
    /// \param args... the arguments to pass to \p T's constructor
    template<typename T, typename...Args>
    constexpr expected<T> make_expected( Args&&...args )
      noexcept( noexcept( expected<T>( std::forward<Args>(args)... ) ) );


    /// \brief Creates an expected object of type \p T from the given
    ///        \p il \p args
    ///
    /// \tparam T the type to construct
    /// \param il      the initializer list to pass
    /// \param args... the arguments to pass to \p T's constructor
    template<typename T, typename U, typename... Args >
    constexpr expected<T> make_expected( std::initializer_list<U> il, Args&&... args )
      noexcept( noexcept( expected<T>( il, std::forward<Args>(args)... ) ) );

    /// \brief Retrieves the hash from a given expected
    ///
    /// \param val the expected to retrieve the hash from
    /// \return the hash of the string
    template<typename T>
    constexpr std::size_t hash_value( const expected<T>& val ) noexcept;

  } // inline namespace bit
} // namespace bit

#include "detail/expected.inl"

#endif /* BIT_STL_EXPECTED_HPP */
