/**
 * \file checked.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CHECKED_HPP
#define BIT_STL_CHECKED_HPP

#define BIT_NODISCARD __attribute__((warn_unused_result))

#include "stddef.hpp"
#include "assert.hpp"
#include "utility.hpp"
#include "type_traits.hpp"
#include "memory.hpp"

#include <system_error>

namespace bit {
  namespace stl {

    template<typename> class checked;

    namespace detail {

      template<typename T, typename U>
      struct checked_is_enabled_ctor_base : negation<
        disjunction<
          std::is_constructible<T, checked<U>&>,
          std::is_constructible<T, const checked<U>&>,
          std::is_constructible<T, checked<U>&&>,
          std::is_constructible<T, const checked<U>&&>,

          std::is_convertible<checked<U>&, T>,
          std::is_convertible<const checked<U>&, T>,
          std::is_convertible<checked<U>&&, T>,
          std::is_convertible<const checked<U>&&, T>
        >
      >{};

      template<typename T, typename U>
      struct checked_is_enabled_copy_ctor : conjunction<
        checked_is_enabled_ctor_base<T,U>,
        std::is_constructible<T,const U&>
      >{};

      template<typename T, typename U>
      struct checked_is_enabled_move_ctor : conjunction<
      checked_is_enabled_ctor_base<T,U>,
        std::is_constructible<T, U&&>
      >{};

      template<typename T, typename U>
      struct checked_is_enabled_assignment_base : negation<
        disjunction<
          std::is_constructible<T, checked<U>&>,
          std::is_constructible<T, const checked<U>&>,
          std::is_constructible<T, checked<U>&&>,
          std::is_constructible<T, const checked<U>&&>,

          std::is_convertible<checked<U>&, T>,
          std::is_convertible<const checked<U>&, T>,
          std::is_convertible<checked<U>&&, T>,
          std::is_convertible<const checked<U>&&, T>,

          std::is_assignable<T&, checked<U>&>,
          std::is_assignable<T&, const checked<U>&>,
          std::is_assignable<T&, checked<U>&&>,
          std::is_assignable<T&, const checked<U>&&>
        >
      >{};

      template<typename T, typename U>
      struct checked_is_enabled_copy_assignment : conjunction<
        checked_is_enabled_assignment_base<T,U>,
        std::is_assignable<T&, const U&>,
        std::is_constructible<T, const U&>
      >{};

      template<typename T, typename U>
      struct checked_is_enabled_move_assignment : conjunction<
        checked_is_enabled_assignment_base<T,U>,
        std::is_assignable<T&, U&&>,
        std::is_constructible<T, U&&>
      >{};

      template<typename T, typename U>
      struct checked_is_direct_initializable : conjunction<
        std::is_constructible<T, U&&>,
        negation<std::is_same<std::decay_t<U>,in_place_t>>,
        negation<std::is_same<std::decay_t<U>,checked<T>>>
      >{};

      template<typename T, typename U>
      struct checked_is_direct_init_assignable : conjunction<
        negation<std::is_same<std::decay_t<U>,checked<T>>>,
        std::is_constructible<T,U>,
        std::is_assignable<T,U>,
        disjunction<
          negation<std::is_scalar<U>>,
          negation<std::is_same<std::decay_t<U>,T>>
        >
      >{};

    } // namespace detail

    //========================================================================
    // error_code
    //========================================================================

    //////////////////////////////////////////////////////////////////////////
    /// \brief A moveable error mechanism.
    ///
    /// This is almost identical to std::error_code, except that it contains
    /// a success state that does not contain an error value,
    /// and is moveable.
    ///
    /// When an error is moved from, the state is left in a successful state,
    /// since there is no contained error after the move.
    //////////////////////////////////////////////////////////////////////////
    class error_code
    {
      //----------------------------------------------------------------------
      // Static Functions
      //----------------------------------------------------------------------
    public:

      /// \brief Creates an error success state
      ///
      /// \return the success state
      static error_code success() noexcept;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an error when given the enum value, and
      ///        error_category
      ///
      /// \param value The value for the error code
      /// \param category The category for the error code
      template<typename Enum, std::enable_if_t<std::is_enum<Enum>::value>* = nullptr>
      explicit error_code( Enum value, const std::error_category& category )
        noexcept;

      /// \brief Constructs an error when given the integer value for the code,
      ///        and the error_category
      ///
      /// \param value the integer value of the error code
      /// \param category the category for the error code
      explicit error_code( int value, const std::error_category& category )
        noexcept;

      /// \brief Copy-constructs an error
      ///
      /// \param other the other error to copy
      error_code( const error_code& other ) noexcept = default;

      /// \brief Move-constructs an error
      ///
      /// \param other the other error to move
      error_code( error_code&& other ) noexcept;

      /// \brief Delete the copy-assign operator
      error_code& operator=( const error_code& ) = delete;

      /// \brief Delete the move-assign operator
      error_code& operator=( error_code&& ) = delete;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Get the integer value of the error
      ///
      /// \return the integral value
      int value() const noexcept;

      /// \brief Get the error category by pointer
      ///
      /// The error category is null on successful error states
      ///
      /// \return a pointer to the error category
      const std::error_category* category() const noexcept;

      /// \brief Get the message for the given error
      ///
      /// \return the error from the message category
      std::string message() const;

      /// \brief Returns\c true if this error contains an error value
      ///
      /// \return \c true if this contains an error value, \c false otherwise
      bool is_error() const noexcept;

      /// \brief Contextually convertible to bool
      ///
      /// \return \c true if this error is a success state
      explicit operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Private Constructors
      //----------------------------------------------------------------------
    private:

      /// \brief Constructs a success error condition
      error_code() noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      int m_error_code; ///< The integral error code
      const std::error_category* m_category; ///< The error category

    };

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief
    ///
    /// \param error
    /// \param category
    /// \return
    template<typename Error, std::enable_if_t<std::is_enum<Error>::value>* = nullptr>
    error_code make_error( Error error, const std::error_category& category )
      noexcept;

    /// \brief
    ///
    /// \param error
    /// \param category
    /// \return
    error_code make_error( int error, const std::error_category& category )
      noexcept;

    //========================================================================
    // checked
    //========================================================================


    //////////////////////////////////////////////////////////////////////////
    /// \brief A checked type is a wrapper around an error or a value type.
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class checked final
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type = T;          ///< The value type
      using error_type = error_code; ///< The error type

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a checked type
      checked()
        noexcept( std::is_nothrow_default_constructible<T>::value );

      /// \brief Constructs a checked from a given error
      ///
      /// \param err the error to use
      explicit checked( error_code err ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Deleted copy constructor
      ///
      /// \param other the other entry to copy
      checked( const checked& other ) = delete;

      /// \brief Move-constructs a checked
      ///
      /// \param other the other entry to move
      checked( checked&& other )
        noexcept( std::is_nothrow_move_constructible<T>::value );

      //----------------------------------------------------------------------

      /// \brief Deleted copy-conversion constructor
      ///
      /// \param other the other entry to copy
      template<typename U>
      checked( const checked<U>& other ) = delete;

      //----------------------------------------------------------------------

      /// \brief Move-constructs a checked type from a convertible checked
      ///
      /// \note This constructor is explicit if const U& is convertible to T
      ///
      /// \param other the checked to copy
#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<detail::checked_is_enabled_move_ctor<T,U>::value && !std::is_convertible<U&&, T>::value>* = nullptr>
#else
      template<typename U>
#endif
      checked( checked<U>&& other )
        noexcept(std::is_nothrow_constructible<T,U&&>::value);

      /// \copydoc checked( checked<U>&& )
#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<detail::checked_is_enabled_move_ctor<T,U>::value && std::is_convertible<U&&, T>::value>* = nullptr>
#else
      template<typename U>
#endif
      explicit checked( checked<U>&& other )
        noexcept(std::is_nothrow_constructible<T,U&&>::value);

      //----------------------------------------------------------------------

      /// \brief Constructs an initialized checked that will be constructed
      ///        with the arguments specified in \p args...
      ///
      /// \param args the arguments to use for deferred construction
      template<typename...Args>
      explicit checked( in_place_t, Args&&...args )
        noexcept(std::is_nothrow_constructible<T,Args...>::value);

      /// \brief Constructs an initialized checked that will be constructed
      ///        with the arguments specified in \p ilist and \p args...
      ///
      /// \param ilist the initializer list to forward for deferred construction
      /// \param args the arguments to use for deferred construction
      template<typename U, typename...Args>
      explicit checked( in_place_t, std::initializer_list<U> ilist, Args&&...args )
        noexcept(std::is_nothrow_constructible<T,std::initializer_list<U>,Args...>::value);

      //----------------------------------------------------------------------

      /// \brief Constructs this checked by constructing the underlying
      ///        type as if by direct initializing by type U
      ///
      /// \param value the value to use to use to initialzie the checked
#ifndef BIT_DOXYGEN_BUILD
      template<typename U = T, std::enable_if_t<detail::checked_is_direct_initializable<T,U>::value && !is_callable<U&>::value && std::is_convertible<U&&, T>::value>* = nullptr>
#else
      template<typename U>
#endif
      checked( U&& value )
        noexcept(std::is_nothrow_constructible<T,U>::value);

      /// \copydoc checked( U&& )
#ifndef BIT_DOXYGEN_BUILD
      template<typename U = T, std::enable_if_t<detail::checked_is_direct_initializable<T,U>::value && !is_callable<U&>::value && !std::is_convertible<U&&, T>::value>* = nullptr>
#else
      template<typename U>
#endif
      explicit checked( U&& value )
        noexcept(std::is_nothrow_constructible<T,U>::value);

      /// \brief Destructs this checked type, calling abort if its unchecked
      ~checked();

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      checked& operator=( const checked& other ) = delete;

      checked& operator=( checked&& other ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Checks whether this checked contains a value
      ///
      /// \return \c true if there is no error
      BIT_NODISCARD bool check() const noexcept;

      /// \brief Consumes the error so that it's accessible from outside
      ///        this type
      ///
      /// \return The error from this checked
      BIT_NODISCARD error_code consume() const noexcept;

      /// \brief Checks whether this checked contains a boolean value
      ///
      /// \return \c true if there is no error
      BIT_NODISCARD explicit operator bool() const noexcept;

      /// \brief Checks whether this checked contains a value
      ///
      /// \return \c true if there is no error
      BIT_NODISCARD bool has_value() const noexcept;

      /// \brief Checks whether this checked contains an error
      ///
      /// \return \c true if there is an error
      BIT_NODISCARD bool has_error() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Returns a pointer to the contained value
      ///
      /// Undefined behaviour if this checked does not contain a value
      ///
      /// \return the contained value
      T* operator->() noexcept;

      /// \copydoc operator->() noexcept
      const T* operator->() const noexcept;

      /// \brief Returns a reference to the contained value
      ///
      /// Undefined behaviour if this checked does not contain a value
      ///
      /// \return reference to the contained value
      T& operator*() & noexcept;

      /// \copydoc operator*() noexcept
      const T& operator*() const & noexcept;

      /// \copydoc operator*() noexcept
      T&& operator*() && noexcept;

      /// \copydoc operator*() noexcept
      const T&& operator*() const && noexcept;

      //----------------------------------------------------------------------

      /// \brief Returns the contained value
      ///
      /// If this checked has not been checked first, calls std::abort
      ///
      /// \return the contained value
      T& value() &;

      /// \copydoc value() &
      const T& value() const &;

      /// \copydoc value() &
      T&& value() &&;

      /// \copydoc value() &
      const T&& value() const &&;

      /// \brief Returns the contained value if not an error, otherwise
      ///        returns the \p default_value
      ///
      /// This function counts as checking the checked
      ///
      /// \return the contained value, or \p default_value
      template<typename U>
      T value_or( U&& default_value ) &&;

      /// \copydoc value_or( U&& ) &&
      template<typename U>
      T value_or( U&& default_value ) const &;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      struct dummy{};

      union storage_type
      {
        value_type value;
        error_type error;
        dummy      stateless;

        storage_type()
          : stateless()
        {

        }

        template<typename...Args, std::enable_if_t<std::is_constructible<T,Args...>::value>* = nullptr>
        storage_type( in_place_type_t<T>, Args&&...args )
          : value( std::forward<Args>(args)... )
        {

        }

        storage_type( error_type error )
          : error( std::move(error) )
        {

        }

        ~storage_type(){}
      };


      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      storage_type m_storage;
      mutable bool m_is_checked : 1;
      bool         m_has_value  : 1;

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      /// \brief Destructs the contained checked
      void destruct();

      /// \brief Aborts if this is unchecked
      void abort_if_unchecked() const;
    };

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    template<typename T, typename...Args>
    checked<T> make_checked( Args&&...args );

    template<typename T, typename U, typename...Args>
    checked<T> make_checked( std::initializer_list<U> ilist, Args&&...args );

  } // namespace stl
} // inline namespace bit

#include "detail/checked.inl"

#endif /* BIT_STL_CHECKED_HPP */
