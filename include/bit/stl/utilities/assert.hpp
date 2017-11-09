/**
 * \file assert.hpp
 *
 * \brief This header contains the definitions for both static and
 *        runtime assertions.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_ASSERT_HPP
#define BIT_STL_UTILITIES_ASSERT_HPP

#include "source_location.hpp"
#include "compiler_traits.hpp"
#include "macros.hpp"           // BIT_STRINGIZE

#include <stdexcept> // std::runtime_error
#include <cstdio>    // std::printf, stderr
#include <atomic>    // std::atomic

namespace bit {
  namespace stl {

    //=========================================================================
    // X.Y.1, assertion_failure
    //=========================================================================

    ///////////////////////////////////////////////////////////////////////////
    /// \brief An exception thrown from assertion failures when
    ///        BIT_COMPILER_EXCEPTIONS_ENABLED is defined
    ///////////////////////////////////////////////////////////////////////////
    class assertion_failure final : public std::runtime_error
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs an assertion_failure exception from a message
      ///        and a source location
      ///
      /// \param message the message to display when calling .what()
      /// \param source  the source location of this assertion failure
      assertion_failure( const char* message, source_location source );

      //-----------------------------------------------------------------------
      // Accessors
      //-----------------------------------------------------------------------
    public:

      /// \brief Retrieves the source of this assertion
      ///
      /// \return the location where this assertion was hit
      source_location source() const noexcept;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      source_location m_location;
    };

    //=========================================================================
    // X.Y.2, Assertion handlers
    //=========================================================================

    using assert_handler_t = void(*)( const char*, source_location );

    //-------------------------------------------------------------------------

    /// \brief The default assert handler. Prints a message, then triggers a
    ///        breakpoint
    ///
    /// \param message the message to print
    /// \param source the source of the assertion
    void default_assert( const char* message, source_location source );

    /// \brief An exception-throwing assert handler. Throws an
    ///        assertion_failure exception
    ///
    /// \param message the message for the assertion
    /// \param source the source of the assertion
    void throwing_assert( const char* message, source_location source );

    //-------------------------------------------------------------------------

    /// \brief Sets the assertion handler, returning the previous assertion
    ///        handler
    ///
    /// \param f the function to handle
    /// \return the old handler
    assert_handler_t set_assert_handler( assert_handler_t f );

    /// \brief Gets the currently active assertion handler
    ///
    /// \return the handler
    assert_handler_t get_assert_handler();

  } // namespace stl
} // namespace bit

# define BIT_INTERNAL_ASSERT(condition,message,source) \
  ::bit::stl::detail::assert_internal("assertion failure: condition '" \
                                      condition "' failed with message \"" \
                                      message "\"", source )

//=============================================================================
// X.Y.3, Assertion Macros
//=============================================================================

//! \def BIT_ASSERT(condition, message, ...)
//!
//! \brief A runtime assertion when \a condition fails, displaying \a message
//!        to the user.
#define BIT_ALWAYS_ASSERT(condition,message) \
  ((BIT_LIKELY(condition)) ? ((void)0) : [](::bit::stl::source_location source){ BIT_INTERNAL_ASSERT( BIT_STRINGIZE(condition), message, source ); }(BIT_MAKE_SOURCE_LOCATION()) )

//! \def BIT_ASSERT(condition, message, ...)
//!
//! \brief A runtime assertion when \a condition fails, displaying \a message
//!        to the user.
#if BIT_DEBUG
# define BIT_ASSERT(condition,message) BIT_ALWAYS_ASSERT(condition,message)
#else
# define BIT_ASSERT(...) ((void)0)
#endif

#include "detail/assert.inl"

#endif /* BIT_STL_UTILITIES_ASSERT_HPP */
