/*****************************************************************************
 * \file
 * \brief This header contains the 'expected' monadic type for indicating
 *        possible error conditions
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
#ifndef BIT_STL_UTILITIES_EXPECTED_HPP
#define BIT_STL_UTILITIES_EXPECTED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/empty.hpp"
#include "../traits/composition/sfinae.hpp"

#include "invoke.hpp"          // invoke, invoke_result_t
#include "in_place.hpp"        // in_place
#include "tribool.hpp"         // tribools
#include "compiler_traits.hpp" // BIT_COMPILER_EXCEPTIONS_ENABLED
#include "assert.hpp"          // BIT_ALWAYS_ASSERT

#include <initializer_list> // std::initializer_list
#include <stdexcept>        // std::logic_error
#include <type_traits>  // std::is_constructible
#include <system_error> // std::error_condition

namespace bit {
  namespace stl {

    template<typename T, typename E>
    class expected;

    //=========================================================================
    // trait : is_expected
    //=========================================================================

    template<typename T>
    struct is_expected : std::false_type{};

    template<typename T, typename E>
    struct is_expected<expected<T,E>> : std::true_type{};

    template<typename T>
    constexpr bool is_expected_v = is_expected<T>::value;

    //=========================================================================
    // class : bad_expected_access
    //=========================================================================

    ///////////////////////////////////////////////////////////////////////////
    /// \brief The exception type thrown when accessing a non-active expected
    ///        member
    ///
    /// \tparam E the error type
    ///////////////////////////////////////////////////////////////////////////
    template<typename E>
    class bad_expected_access : public std::logic_error
    {
      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using error_type = E;

      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs a bad_expected_access from a given error, \p e
      ///
      /// \param e the error
      explicit bad_expected_access( error_type e );

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Gets the underlying error
      ///
      /// \return the error type
      error_type& error() & noexcept;
      error_type&& error() && noexcept;
      const error_type& error() const & noexcept;
      const error_type&& error() const && noexcept;
      /// \}

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      error_type m_error_value;
    };

    //=========================================================================

    template<>
    class bad_expected_access<void> : std::logic_error
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs a bad_expected_access
      bad_expected_access();

    };

    //=========================================================================
    // class : unexpected_type
    //=========================================================================

    ///////////////////////////////////////////////////////////////////////////
    /// \brief A type representing an unexpected value coming from an expected
    ///        type
    ///
    /// \tparam E the unexpected type
    ///////////////////////////////////////////////////////////////////////////
    template<typename E>
    class unexpected_type
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      // Deleted default constructor
      unexpected_type() = delete;

      /// \brief Moves an unexpected_type from an existing one
      ///
      /// \param other the other unexpected_type to move
      constexpr unexpected_type( unexpected_type&& other ) = default;

      /// \brief Copies an unexpected_type from an existing one
      ///
      /// \param other the other unexpected_type to copy
      constexpr unexpected_type( const unexpected_type& other ) = default;

      /// \brief Move-converts an expected_type to this type
      ///
      /// \note This constructor only participates in overload resolution if E2
      ///       is convertible to E
      ///
      /// \param other the other unexpected_type to move-convert
      template<typename E2, typename = std::enable_if_t<std::is_convertible<E2,E>::value>>
      constexpr unexpected_type( unexpected_type<E2>&& other );

      /// \brief Copy converts an expected_Type to this type
      ///
      /// \note This constructor only participates in overload resolution if E2
      ///       is convertible to E
      ///
      /// \param other the other unexpected_type to copy-convert
      template<typename E2, typename = std::enable_if_t<std::is_convertible<E2,E>::value>>
      constexpr unexpected_type( const unexpected_type<E2>& other );

      /// \brief Constructs the expected_type by copying the underlying
      ///        unexpected_type by value
      ///
      /// \param value the value to copy
      constexpr explicit unexpected_type( const E& value );

      /// \brief Constructs the expected_type by copying the underlying
      ///        unexpected_type by value
      ///
      /// \param value the value to copy
      constexpr explicit unexpected_type( E&& value );

      /// \brief Constructs the underlying unexpected_type by forwarding \p args
      ///        to \p E's constructor
      ///
      /// \throws ... any exception that E's constructor may throw
      /// \param args the arguments to forward
      template<typename...Args, typename = std::enable_if_t<std::is_constructible<E,Args...>::value>>
      constexpr explicit unexpected_type( in_place_t, Args&&...args );

      /// \brief Constructs the underlying unexpected_type by forwarding \p args
      ///        to \p E's constructor
      ///
      /// \throws ... any exception that E's constructor may throw
      /// \param ilist an initializer list of arguments
      /// \param args the arguments to forward
      template<typename U, typename...Args, typename = std::enable_if_t<std::is_constructible<E,std::initializer_list<U>,Args...>::value>>
      constexpr explicit unexpected_type( in_place_t,
                                          std::initializer_list<U> ilist,
                                          Args&&...args );

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Extracts the value for this unexpected_type
      ///
      /// \return reference to the value
      constexpr E& value() &;
      constexpr const E& value() const &;
      constexpr E&& value() &&;
      constexpr const E&& value() const &&;
      /// \}

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      E m_value;
    };

    //=========================================================================
    // trait : is_unexpected
    //=========================================================================

    template<typename T>
    struct is_unexpected_type : std::false_type{};

    template<typename T>
    struct is_unexpected_type<unexpected_type<T>> : std::true_type{};

    template<typename T>
    constexpr bool is_unexpected_type_v = is_unexpected_type<T>::value;

    //=========================================================================
    // utilities : class unexpected
    //=========================================================================

    /// \brief Makes an unexpected type \c E
    ///
    /// \tparam E the unexpected type to make
    /// \param args the arguments to forward
    /// \return the unexpected type
    template<typename E, typename...Args>
    constexpr unexpected_type<E> make_unexpected( Args&&...args );

    //=========================================================================
    // relational operators : class unexpected_type
    //=========================================================================

    template<typename E>
    constexpr bool operator==( const unexpected_type<E>& lhs,
                               const unexpected_type<E>& rhs );
    template<typename E>
    constexpr bool operator!=( const unexpected_type<E>& lhs,
                               const unexpected_type<E>& rhs );
    template<typename E>
    constexpr bool operator<( const unexpected_type<E>& lhs,
                              const unexpected_type<E>& rhs );
    template<typename E>
    constexpr bool operator>( const unexpected_type<E>& lhs,
                              const unexpected_type<E>& rhs );
    template<typename E>
    constexpr bool operator<=( const unexpected_type<E>& lhs,
                               const unexpected_type<E>& rhs );
    template<typename E>
    constexpr bool operator>=( const unexpected_type<E>& lhs,
                               const unexpected_type<E>& rhs );

    //=========================================================================
    // class : unexpect tag
    //=========================================================================

    /// \brief A tag type used for tag-dispatch
    struct unexpect_t
    {
      unexpect_t() = delete;
      constexpr unexpect_t(int){}
    };

    //-------------------------------------------------------------------------

    constexpr unexpect_t unexpect{0};

    //=========================================================================
    // X.Z.4, expected for object types
    //=========================================================================

    namespace detail {

      //=======================================================================
      // expected_base
      //=======================================================================

      template<bool Trivial, typename T, typename E>
      class expected_base;

      template<typename T, typename E>
      class expected_base<true,T,E>
      {
        //-----------------------------------------------------------------------
        // Constructors
        //-----------------------------------------------------------------------
      public:

        constexpr expected_base();
        template<typename...Args>
        constexpr expected_base( in_place_t, Args&&...args );
        template<typename...Args>
        constexpr expected_base( unexpect_t, Args&&...args );

        //---------------------------------------------------------------------
        // Observers
        //---------------------------------------------------------------------
      protected:

        constexpr bool has_value() const noexcept;
        constexpr bool has_error() const noexcept;
        constexpr bool valueless_by_exception() const noexcept;

        //---------------------------------------------------------------------

        constexpr T& get_value() & noexcept;
        constexpr T&& get_value() && noexcept;
        constexpr const T& get_value() const & noexcept;
        constexpr const T&& get_value() const && noexcept;

        //---------------------------------------------------------------------

        constexpr unexpected_type<E>& get_unexpected() & noexcept;
        constexpr unexpected_type<E>&& get_unexpected() && noexcept;
        constexpr const unexpected_type<E>& get_unexpected() const & noexcept;
        constexpr const unexpected_type<E>&& get_unexpected() const && noexcept;

        //---------------------------------------------------------------------
        // Modifiers
        //---------------------------------------------------------------------
      protected:

        template<typename...Args>
        void emplace_value( Args&&...args );
        template<typename...Args>
        void emplace_error( Args&&...args );

        //---------------------------------------------------------------------

        template<typename U>
        void assign_value( U&& value );
        template<typename U>
        void assign_error( U&& error );

        //---------------------------------------------------------------------
        // Protected Member Types
        //---------------------------------------------------------------------
      protected:

        union storage_type
        {
          constexpr storage_type()
            : dummy{}
          {

          }

          template<typename...Args>
          constexpr storage_type( in_place_t, Args&&...args )
            : value( std::forward<Args>(args)... )
          {

          }

          template<typename...Args>
          constexpr storage_type( unexpect_t, Args&&...args )
            : error( std::forward<Args>(args)... )
          {

          }

          empty<void>        dummy;
          T                  value;
          unexpected_type<E> error;
        };

        //---------------------------------------------------------------------
        // Private Members
        //---------------------------------------------------------------------
      private:

        storage_type m_storage;
        tribool      m_has_value;
      };

      //=======================================================================

      template<typename T, typename E>
      class expected_base<false,T,E>
      {
        //---------------------------------------------------------------------
        // Constructors / Destructor
        //---------------------------------------------------------------------
      public:

        constexpr expected_base();
        template<typename...Args>
        constexpr expected_base( in_place_t, Args&&...args );
        template<typename...Args>
        constexpr expected_base( unexpect_t, Args&&...args );

        //---------------------------------------------------------------------

        ~expected_base();

        //---------------------------------------------------------------------
        // Observers
        //---------------------------------------------------------------------
      protected:

        constexpr bool has_value() const noexcept;
        constexpr bool has_error() const noexcept;
        constexpr bool valueless_by_exception() const noexcept;

        //---------------------------------------------------------------------

        constexpr T& get_value() & noexcept;
        constexpr T&& get_value() && noexcept;
        constexpr const T& get_value() const & noexcept;
        constexpr const T&& get_value() const && noexcept;

        //---------------------------------------------------------------------

        constexpr unexpected_type<E>& get_unexpected() & noexcept;
        constexpr unexpected_type<E>&& get_unexpected() && noexcept;
        constexpr const unexpected_type<E>& get_unexpected() const & noexcept;
        constexpr const unexpected_type<E>&& get_unexpected() const && noexcept;

        //---------------------------------------------------------------------
        // Modifiers
        //---------------------------------------------------------------------
      protected:

        void destruct();

        //---------------------------------------------------------------------

        template<typename...Args>
        void emplace_value( Args&&...args );

        template<typename...Args>
        void emplace_error( Args&&...args );

        //---------------------------------------------------------------------

        template<typename U>
        void assign_value( U&& value );

        template<typename U>
        void assign_error( U&& error );

        //---------------------------------------------------------------------
        // Protected Member Types
        //---------------------------------------------------------------------
      protected:

        union storage_type
        {
          constexpr storage_type()
            : dummy{}
          {

          }

          template<typename...Args>
          constexpr storage_type( in_place_t, Args&&...args )
            : value( std::forward<Args>(args)... )
          {

          }

          template<typename...Args>
          constexpr storage_type( unexpect_t, Args&&...args )
            : error( std::forward<Args>(args)... )
          {

          }

          ~storage_type(){}

          empty<void>        dummy;
          T                  value;
          unexpected_type<E> error;
        };

        //---------------------------------------------------------------------
        // Private Members
        //---------------------------------------------------------------------
      private:

        storage_type m_storage;
        tribool      m_has_value;
      };
    } // namespace detail

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \tparam T the type
    /// \tparam Error the error type
    ///////////////////////////////////////////////////////////////////////////
    template<typename T, typename E=std::error_condition>
    class expected
      : detail::expected_base<std::is_trivially_destructible<T>::value &&
                              std::is_trivially_destructible<E>::value,T,E>
    {
      using base_type = detail::expected_base<std::is_trivially_destructible<T>::value &&
                                              std::is_trivially_destructible<E>::value,T,E>;

      template<typename U, typename G>
      static constexpr bool is_constructible = std::is_constructible<T, U&>::value &&
                                               std::is_constructible<E, G&>::value;


      template<typename U, typename G>
      static constexpr bool is_copyable = std::is_copy_constructible<U>::value &&
                                          std::is_copy_assignable<U>::value &&
                                          std::is_copy_constructible<G>::value &&
                                          std::is_copy_assignable<G>::value;
      template<typename U, typename G>
      static constexpr bool is_moveable = std::is_move_constructible<U>::value &&
                                          std::is_move_assignable<U>::value &&
                                          std::is_move_constructible<G>::value &&
                                          std::is_move_assignable<G>::value;

      template<typename U, typename V>
      static constexpr bool is_value_assignable = std::is_constructible<U,V>::value &&
                                                  std::is_assignable<U,V>::value;

      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using value_type = T;
      using error_type = E;

      template<typename U>
      struct rebind
      {
        using type = expected<U, error_type>;
      };

      //-----------------------------------------------------------------------
      // Constructors / Destructor / Assignment
      //-----------------------------------------------------------------------
    public:

      // X.Z.4.1, constructors

      /// \brief Initializes the contained value as if direct-non-list-
      ///        initializing an object of type T with the expression T{}
      ///
      /// \post \code bool(*this) \endcode
      template<typename U=T,typename = std::enable_if_t<std::is_default_constructible<T>::value>>
      constexpr expected();

      //-----------------------------------------------------------------------

      /// \brief Copy-constructs an expected from an existing expected
      ///
      /// \param other the other expected
      expected( enable_overload_if<std::is_copy_constructible<T>::value &&
                                   std::is_copy_constructible<E>::value,
                                   const expected&> other );
      expected( disable_overload_if<std::is_copy_constructible<T>::value &&
                                    std::is_copy_constructible<E>::value,
                                    const expected&> other ) = delete;

      //-----------------------------------------------------------------------

      /// \brief Move-constructs an expected from an existing expected
      ///
      /// \param other the other expected
      expected( enable_overload_if<std::is_move_constructible<T>::value &&
                                   std::is_move_constructible<E>::value,
                                   expected&&> other );
      expected( disable_overload_if<std::is_move_constructible<T>::value &&
                                    std::is_move_constructible<E>::value,
                                    expected&&> other ) = delete;

      //-----------------------------------------------------------------------

      /// \brief Copy converts an expected from an existing expected
      ///
      /// \param other the other expected
#ifndef BIT_DOXYGEN
      template<typename U, typename G, typename = std::enable_if_t<std::is_constructible<T,const U&>::value &&
                                                                   std::is_constructible<E,const G&>::value>>
#else
      template<typename U, typename G>
#endif
      expected( const expected<U,G>& other );

      /// \brief Copy converts an expected from an existing expected
      ///
      /// \param other the other expected
#ifndef BIT_DOXYGEN
      template<typename U, typename G, typename = std::enable_if_t<std::is_constructible<T,U&&>::value &&
                                                                   std::is_constructible<E,G&&>::value>>
#else
      template<typename U, typename G>
#endif
      expected( expected<U,G>&& other );

      //-----------------------------------------------------------------------

      /// \brief Constructs the underlying value of the expected from \p value
      ///
      /// \param value the value to construct the underlying expected
      template<typename U=T,typename = std::enable_if_t<std::is_copy_constructible<U>::value>>
      constexpr expected( const T& value );

      /// \brief Constructs the underlying value of the expected from \p value
      ///
      /// \param value the value to construct the underlying expected
      template<typename U=T,typename = std::enable_if_t<std::is_move_constructible<U>::value>>
      constexpr expected( T&& value );

      //-----------------------------------------------------------------------

      /// \brief Constructs the underlying value of the expected by
      ///        constructing the value in place
      ///
      /// \param args the arguments to forward
      template<typename...Args, typename = std::enable_if_t<std::is_constructible<T,Args...>::value>>
      constexpr explicit expected( in_place_t,
                                   Args&&...args );

      /// \brief Constructs the underlying value of the expected by
      ///        constructing the value in place
      ///
      /// \param ilist an initializer list to forward
      /// \param args the arguments to forward
      template<typename U, typename...Args, typename = std::enable_if_t<std::is_constructible<T,std::initializer_list<U>,Args...>::value>>
      constexpr explicit expected( in_place_t,
                                   std::initializer_list<U> ilist,
                                   Args&&...args );

      //-----------------------------------------------------------------------

      /// \brief Constructs the underlying error from a given unexpected type
      ///
      /// \param unexpected the unexpected type
      template<typename UError=E, typename = std::enable_if_t<std::is_copy_constructible<UError>::value>>
      constexpr expected( unexpected_type<E> const& unexpected );

      /// \brief Constructs the underlying error from a given unexpected type
      ///
      /// \param unexpected the unexpected type
      template<typename Err, typename = std::enable_if_t<std::is_convertible<Err,E>::value>>
      constexpr expected( unexpected_type<Err> const& unexpected );

      //-----------------------------------------------------------------------

      /// \brief Constructs the underlying error of the expected by
      ///        constructing the value in place
      ///
      /// \param args the arguments to forward
      template<typename...Args, typename = std::enable_if_t<std::is_constructible<E, Args...>::value>>
      constexpr explicit expected( unexpect_t,
                                   Args&&...args );

      /// \brief Constructs the underlying error of the expected by
      ///        constructing the value in place
      ///
      /// \param ilist an initializer list to forward
      /// \param args the arguments to forward
      template<typename U, typename...Args, typename = std::enable_if_t<std::is_constructible<E,std::initializer_list<U>,Args...>::value>>
      constexpr explicit expected( unexpect_t,
                                   std::initializer_list<U> ilist,
                                   Args&&...args );

      //-----------------------------------------------------------------------

      // X.Z.4.3, assignment
      template<typename U=T,typename F=E,typename = std::enable_if_t<is_copyable<U,F>>>
      expected& operator=( const expected& other );

      template<typename U=T,typename F=E,typename = std::enable_if_t<is_moveable<U,F>>>
      expected& operator=( expected&& other );

      template<typename U,typename = std::enable_if<is_value_assignable<T,U>>>
      expected& operator=( U&& value );

      expected& operator=( const unexpected_type<E>& unexpected );

      expected& operator=( unexpected_type<E>&& unexpected );

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Consturcts the underlying value type in-place
      ///
      /// If the expected already contains a value, it is destructed first.
      ///
      /// \param args the arguments to forward to \c T's constructors
      template<typename...Args, typename = std::enable_if_t<std::is_constructible<T,Args...>::value>>
      void emplace( Args&&...args );

      /// \brief Consturcts the underlying value type in-place
      ///
      /// If the expected already contains a value, it is destructed first.
      ///
      /// \param ilist the initializer list of arguments to forward
      /// \param args the arguments to forward to \c T's constructors
      template<typename U, typename...Args, typename = std::enable_if_t<std::is_constructible<T,Args...>::value>>
      void emplace( std::initializer_list<U> ilist, Args&&...args );

      /// \brief Swaps this expected with \p other
      ///
      /// \param other the other expected to swap
      void swap( expected& other );

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Queries whether the expected has a value
      ///
      /// \return \c true if the expected has a value
      constexpr bool has_value() const noexcept;

      /// \brief Queries whether the expected has an error
      ///
      /// \return \c true if the expected has an error
      constexpr bool has_error() const noexcept;

      /// \brief Queries whether the expected is valueless_by_exception
      ///
      /// \return \c true if the expected is valueless-by-exception
      constexpr bool valueless_by_exception() const noexcept;

      /// \brief Explicitly convertible to \c bool
      ///
      /// \return \c true if the expected has a value
      constexpr explicit operator bool() const noexcept;

      //-----------------------------------------------------------------------

      constexpr T* operator->();
      constexpr const T* operator->() const;

      constexpr T& operator*() &;
      constexpr const T& operator*() const&;
      constexpr T&& operator*() &&;
      constexpr const T&& operator*() const &&;

      //-----------------------------------------------------------------------

      constexpr const T& value() const&;
      constexpr T& value() &;
      constexpr const T&& value() const &&;
      constexpr T&& value() &&;

      /// \{
      /// \brief Gets the underlying value if there is an value, otherwise
      ///        returns \p default_value
      ///
      /// \param default_value the default value to use
      /// \return the value
      template<typename U>
      constexpr T value_or( U&& default_value ) const &;
      template<typename U>
      constexpr T value_or( U&& default_value ) &&;
      /// \}

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Gets the underlying error
      ///
      /// \throw bad_expected_access<void> if not currently in an error state
      /// \return reference to the underlying error
      constexpr E& error() &;
      constexpr E&& error() &&;
      constexpr const E& error() const &;
      constexpr const E&& error() const &&;
      /// \}

      /// \{
      /// \brief Gets the underlying error if there is an error, otherwise
      ///        returns \p default_value
      ///
      /// \param default_value the default value to use
      /// \return the error
      template<typename U>
      constexpr E error_or( U&& default_value ) const &;
      template<typename U>
      constexpr E error_or( U&& default_value ) &&;
      /// \}

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Gets the underlying expected type
      ///
      /// \throw bad_expected_access<void> if not currently in an error state
      /// \return reference to the unexpected_type
      constexpr unexpected_type<E>& get_unexpected() &;
      constexpr unexpected_type<E>&& get_unexpected() &&;
      constexpr const unexpected_type<E>& get_unexpected() const &;
      constexpr const unexpected_type<E>&& get_unexpected() const &&;
      /// \}

      //------------------------------------------------------------------------
      // Monadic Functionality
      //------------------------------------------------------------------------
    public:

      /// \brief Invokes the function \p fn with this expected as the argument
      ///
      /// If this expected contains an error, the result also contains an error
      /// \param fn the function to invoke with this
      /// \return The result of the function being called
      template<typename Fn,
               typename=std::enable_if_t<conjunction<is_invocable<Fn, const T&>,
                                                     is_expected<invoke_result_t<Fn, const T&>>>::value>>
      invoke_result_t<Fn,const T&> flat_map( Fn&& fn ) const;

      /// \brief Invokes this function \p fn with this expected as the argument
      ///
      /// If this expected contains an error, the result of this function
      /// will contain that error.
      /// Otherwise this function wraps the result and returns it as an expected
      ///
      /// \param fn the function to invoke with this
      /// \return The expected result of the function invoked
      template<typename Fn,
               typename=std::enable_if_t<is_invocable<Fn, const T&>::value>>
      expected<invoke_result_t<Fn,const T&>,E> map( Fn&& fn ) const;

    };

    //=========================================================================
    // X.Z.5, Specialization for void.
    //=========================================================================

    template<typename E>
    class expected<void, E>
      : detail::expected_base<std::is_trivially_destructible<E>::value,empty<void>,E>
    {
      using base_type = detail::expected_base<std::is_trivially_destructible<E>::value,empty<void>,E>;

      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using value_type = void;
      using error_type = E;

      template<typename U>
      struct rebind
      {
        typedef expected<U, error_type> type;
      };

      //-----------------------------------------------------------------------
      // Constructors / Destructor / Assignment
      //-----------------------------------------------------------------------
    public:

      /// \brief Default constructs this expected type with no error
      constexpr expected() noexcept;

      //-----------------------------------------------------------------------

      /// \brief Copy-constructs an expected from an existing expected
      ///
      /// \param other the other expected
      expected( enable_overload_if<std::is_copy_constructible<E>::value,
                                   const expected&> other );
      expected( disable_overload_if<std::is_copy_constructible<E>::value,
                                    const expected&> other ) = delete;

      //-----------------------------------------------------------------------

      /// \brief Move-constructs an expected from an existing expected
      ///
      /// \param other the other expected
      expected( enable_overload_if<std::is_move_constructible<E>::value,
                                   expected&&> other );
      expected( disable_overload_if<std::is_move_constructible<E>::value,
                                    expected&&> other ) = delete;

      //-----------------------------------------------------------------------

      /// \brief Copy-converts this expected type from an existing expected
      ///
      /// \param other the other expected to copy
      template<typename G, typename = std::enable_if_t<std::is_constructible<E,const G&>::value>>
      expected( const expected<void,G>& other );

      /// \brief Move-converts this expected type from an existing expected
      ///
      /// \param other the other expected to move
      template<typename G, typename = std::enable_if_t<std::is_constructible<E,G&&>::value>>
      expected( expected<void,G>&& other );

      //-----------------------------------------------------------------------

      /// \brief Constructs this expected type with no error
      constexpr explicit expected( in_place_t );

      //-----------------------------------------------------------------------

      /// \brief Constructs the underlying error from a given unexpected type
      ///
      /// \param unexpected the unexpected type
      template<typename UError=E, typename = std::enable_if_t<std::is_copy_constructible<UError>::value>>
      constexpr expected( unexpected_type<E> const& unexpected );

      /// \brief Constructs the underlying error from a given unexpected type
      ///
      /// \param unexpected the unexpected type
      template<typename Err, typename = std::enable_if_t<std::is_convertible<Err,E>::value>>
      constexpr expected( unexpected_type<Err> const& unexpected );

      //-----------------------------------------------------------------------

      /// \brief Constructs the underlying error of the expected by
      ///        constructing the value in place
      ///
      /// \param args the arguments to forward
      template<typename...Args, typename = std::enable_if_t<std::is_constructible<E, Args...>::value>>
      constexpr explicit expected( unexpect_t,
                                   Args&&...args );

      /// \brief Constructs the underlying error of the expected by
      ///        constructing the value in place
      ///
      /// \param ilist an initializer list to forward
      /// \param args the arguments to forward
      template<typename U, typename...Args, typename = std::enable_if_t<std::is_constructible<E,std::initializer_list<U>,Args...>::value>>
      constexpr explicit expected( unexpect_t,
                                   std::initializer_list<U> ilist,
                                   Args&&...args );

      //-----------------------------------------------------------------------

      /// \brief Copy-assigns an expected from an existing expected
      ///
      /// \param other the other expected
      /// \return reference to \c (*this)
      expected& operator=( const expected& other );

      /// \brief Move-assigns an expected from an existing expected
      ///
      /// \param other the other expected
      /// \return reference to \c (*this)
      expected& operator=( expected&& other );

      //-----------------------------------------------------------------------

      expected& operator=( const unexpected_type<E>& unexpected );

      expected& operator=( unexpected_type<E>&& unexpected );

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs this expected without an error state
      void emplace();

      /// \brief Swaps this expected with \p other
      ///
      /// \param other the other expected to swap
      void swap( expected& other );

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Queries whether the expected has a value
      ///
      /// \return \c true if the expected has a value
      constexpr bool has_value() const noexcept;

      /// \brief Queries whether the expected has an error
      ///
      /// \return \c true if the expected has an error
      constexpr bool has_error() const noexcept;

      /// \brief Queries whether the expected is valueless_by_exception
      ///
      /// \return \c true if the expected is valueless-by-exception
      constexpr bool valueless_by_exception() const noexcept;

      /// \brief Explicitly convertible to \c bool
      ///
      /// \return \c true if the expected has a value
      constexpr explicit operator bool() const noexcept;

      //-----------------------------------------------------------------------

      /// \brief Throws the error, if there is a stored error
      void value() const;

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Gets the underlying error
      ///
      /// \throw bad_expected_access<void> if not currently in an error state
      /// \return reference to the underlying error
      constexpr E& error() &;
      constexpr E&& error() &&;
      constexpr const E& error() const &;
      constexpr const E&& error() const &&;
      /// \}

      /// \{
      /// \brief Gets the underlying error if there is an error, otherwise
      ///        returns \p default_value
      ///
      /// \param default_value the default value to use
      /// \return the error
      template<typename U>
      constexpr E error_or( U&& default_value ) const &;
      template<typename U>
      constexpr E error_or( U&& default_value ) &&;
      /// \}

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Gets the underlying expected type
      ///
      /// \throw bad_expected_access<void> if not currently in an error state
      /// \return reference to the unexpected_type
      constexpr unexpected_type<E>& get_unexpected() &;
      constexpr unexpected_type<E>&& get_unexpected() &&;
      constexpr const unexpected_type<E>& get_unexpected() const &;
      constexpr const unexpected_type<E>&& get_unexpected() const &&;
      /// \}

      //------------------------------------------------------------------------
      // Monadic Functionality
      //------------------------------------------------------------------------
    public:

      /// \brief Invokes the function \p fn with this expected as the argument
      ///
      /// If this expected contains an error, the result also contains an error
      /// \param fn the function to invoke with this
      /// \return The result of the function being called
      template<typename Fn,
               typename=std::enable_if_t<conjunction<is_invocable<Fn>,
                                                     is_expected<invoke_result_t<Fn>>>::value>>
      invoke_result_t<Fn> flat_map( Fn&& fn ) const;

      /// \brief Invokes this function \p fn with this expected as the argument
      ///
      /// If this expected contains an error, the result of this function
      /// will contain that error.
      /// Otherwise this function wraps the result and returns it as an expected
      ///
      /// \param fn the function to invoke with this
      /// \return The expected result of the function invoked
      template<typename Fn,
               typename=std::enable_if_t<is_invocable<Fn>::value>>
      expected<invoke_result_t<Fn>,E> map( Fn&& fn ) const;

    };

    //=========================================================================
    // X.Z.8, Expected relational operators
    //=========================================================================

    template<typename T, typename E>
    constexpr bool operator==( const expected<T,E>& lhs,
                               const expected<T,E>& rhs );
    template<typename T, typename E>
    constexpr bool operator!=( const expected<T,E>& lhs,
                               const expected<T,E>& rhs );
    template<typename T, typename E>
    constexpr bool operator<( const expected<T,E>& lhs,
                              const expected<T,E>& rhs );
    template<typename T, typename E>
    constexpr bool operator>( const expected<T,E>& lhs,
                              const expected<T,E>& rhs );
    template<typename T, typename E>
    constexpr bool operator<=( const expected<T,E>& lhs,
                               const expected<T,E>& rhs );
    template<typename T, typename E>
    constexpr bool operator>=( const expected<T,E>& lhs,
                               const expected<T,E>& rhs );

    //=========================================================================
    // X.Z.9, Comparison with T
    //=========================================================================

    template<typename T, typename E>
    constexpr bool operator==( const expected<T,E>& x, const T& v );
    template<typename T, typename E>
    constexpr bool operator==( const T& v, const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator!=( const expected<T,E>& x, const T& v );
    template<typename T, typename E>
    constexpr bool operator!=( const T& v, const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator<( const expected<T,E>& x, const T& v );
    template<typename T, typename E>
    constexpr bool operator<( const T& v, const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator<=( const expected<T,E>& x, const T& v );
    template<typename T, typename E>
    constexpr bool operator<=( const T& v, const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator>( const expected<T,E>& x, const T& v );
    template<typename T, typename E>
    constexpr bool operator>( const T& v, const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator>=( const expected<T,E>& x, const T& v );
    template<typename T, typename E>
    constexpr bool operator>=( const T& v, const expected<T,E>& x );

    //=========================================================================
    // X.Z.10, Comparison with unexpected_type<E>
    //=========================================================================

    template<typename T, typename E>
    constexpr bool operator==( const expected<T,E>& x,
                               const unexpected_type<E>& e );
    template<typename T, typename E>
    constexpr bool operator==( const unexpected_type<E>& e,
                               const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator!=( const expected<T,E>& x,
                               const unexpected_type<E>& e );
    template<typename T, typename E>
    constexpr bool operator!=( const unexpected_type<E>& e,
                               const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator<( const expected<T,E>& x,
                              const unexpected_type<E>& e );
    template<typename T, typename E>
    constexpr bool operator<( const unexpected_type<E>& e,
                              const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator<=( const expected<T,E>& x,
                               const unexpected_type<E>& e );
    template<typename T, typename E>
    constexpr bool operator<=( const unexpected_type<E>& e,
                               const expected<T,E>& x );
    template<typename T, typename E>
    constexpr bool operator>( const expected<T,E>& x,
                              const unexpected_type<E>& e );
    template<typename T, typename E>
    constexpr bool operator>( const unexpected_type<E>& e,
                              const expected<T,E>& x ) ;
    template<typename T, typename E>
    constexpr bool operator>=( const expected<T,E>& x,
                               const unexpected_type<E>& e );
    template<typename T, typename E>
    constexpr bool operator>=( const unexpected_type<E>& e,
                               const expected<T,E>& x );

    // X.Z.11, Specialized algorithms
    template<typename T, typename E>
    void swap( expected<T,E>& lhs, expected<T,E>& rhs );

  } // namespace stl
} // namespace bit

#include "detail/expected.inl"

#endif /* BIT_STL_UTILITIES_EXPECTED_HPP */
