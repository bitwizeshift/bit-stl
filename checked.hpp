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

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A moveable error mechanism.
    ///
    /// This is almost identical to std::error_code, except that it contains
    /// a success state that always that does not contain an error code,
    /// and is moveable.
    ///
    /// When an error is moved from, the state is left in a successful state,
    /// since there is no contained error after the move.
    //////////////////////////////////////////////////////////////////////////
    class error
    {
      //----------------------------------------------------------------------
      // Static Functions
      //----------------------------------------------------------------------
    public:

      /// \brief Creates an error success state
      ///
      /// \return the success state
      static error success();

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
      explicit error( Enum value, const std::error_category& category );

      /// \brief Constructs an error when given the integer value for the code,
      ///        and the error_category
      ///
      /// \param value the integer value of the error code
      /// \param category the category for the error code
      explicit error( int value, const std::error_category& category );

      /// \brief Copy-constructs an error
      ///
      /// \param other the other error to copy
      error( const error& ) = default;

      /// \brief Move-constructs an error
      ///
      /// \param other the other error to move
      error( error&& );

      /// \brief Delete the copy-assign operator
      error& operator=( const error& ) = delete;

      /// \brief Delete the move-assign operator
      error& operator=( error&& ) = delete;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Get the integer value of the error
      ///
      /// \return the integral value
      int value() const;

      /// \brief Get the error category by pointer
      ///
      /// The error category is null on successful error states
      ///
      /// \return a pointer to the error category
      const std::error_category* category() const;

      /// \brief Get the message for the given error
      ///
      /// \return the error from the message category
      std::string message() const;

      /// \brief Returns\c true if this error contains an error value
      ///
      /// \return \c true if this contains an error value, \c false otherwise
      bool is_error() const;

      /// \brief Contextually convertible to bool
      ///
      ///
      ///
      /// \return \c true if this error is a success state
      explicit operator bool() const;

      //----------------------------------------------------------------------
      // Private Constructors
      //----------------------------------------------------------------------
    private:

      error();

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      int m_error_code;
      std::error_category* m_category;

    };

    error::error()
      : m_error_code(0),
        m_category(nullptr)
    {

    }

    error::error( error&& other )
      : m_error_code( std::move(other.m_error_code) ),
        m_category( std::move(other.m_category) )
    {
      m_error_code     = 0;
      other.m_category = nullptr;
    }

    template<typename Enum, std::enable_if_t<std::is_enum<Enum>::value>*>
    error::error( Enum value, const std::error_category& category )
      : error( static_cast<int>(value), category )
    {

    }

    error::error( int value, const std::error_category& category )
      : m_error_code( value ),
        m_category(std::addressof(category))
    {

    }

    int error::value()
      const
    {
      return m_error_code;
    }

    const std::error_category* error::category()
      const
    {
      return m_category;
    }

    std::string error::message()
      const
    {
      return m_category->message(m_error_code);
    }

    bool error::is_error()
      const
    {
      return m_category;
    }

    error::operator bool()
      const
    {
      return is_error();
    }


    //////////////////////////////////////////////////////////////////////////
    /// \class bit::stl::checked
    ///
    /// \brief A checked type is a wrapper around an error and a value type.
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class checked final
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type = T;     ///< The value type
      using error_type = error; ///< The error type

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a checked type
      checked();

      template<typename U>
      checked( U&& u );

      template<typename...Args>
      checked( in_place_t, Args&&...args );

      template<typename U, typename...Args>
      checked( in_place_t, std::initializer_list<U> ilist, Args&&...args );

      /// \brief Destructs this checked type, calling abort if its unchecked
      ~checked();

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Checks whether this checked contains a boolean value
      ///
      /// \return \c true if there is no error
      BIT_NODISCARD bool check();

      /// \brief Consumes the error so that it's accessible from outside
      ///        this type
      ///
      /// \return The error from this checked
      BIT_NODISCARD error consume();

      /// \brief Checks whether this checked contains a boolean value
      ///
      /// \return \c true if there is no error
      BIT_NODISCARD explicit operator bool() const noexcept;

      T& value() &;
      const T& value() const &;
      T&& value() &&;
      const T&& value() const &&;

      template<typename U>
      T& value_or( U&& default_value ) &;

      template<typename U>
      const T& value_or( U&& default_value ) &;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      union storage_type
      {
        T     entry;
        error error;

        template<typename...Args>
        storage_type( in_place_type_t<T>, Args&&...args );

        storage_type( std::error_code );

        ~storage_type(){}
      };

      enum state
      {
        checked   = 0x1,
        has_value = 0x2
      };

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      void set_checked( bool checked );

    private:

      state m_state;

    private:

      void assert_if_not_checked();
    };

  } // namespace stl
} // inline namespace bit

#endif /* BIT_STL_CHECKED_HPP */
