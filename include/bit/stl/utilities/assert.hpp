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

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl local libraries
#include "stddef.hpp"
#include "source_location.hpp"

namespace bit {
  namespace stl {

    //========================================================================
    // assertion_failure
    //========================================================================

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception thrown from assertion failures when
    ///        BIT_COMPILER_EXCEPTIONS_ENABLED is defined
    //////////////////////////////////////////////////////////////////////////
    class assertion_failure final : public std::runtime_error
    {
      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an assertion_failure exception from a message
      ///        and a source location
      ///
      /// \param message the message to display when calling .what()
      /// \param source  the source location of this assertion failure
      assertion_failure( const char* message, source_location source );

      //----------------------------------------------------------------------
      // Accessors
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the source of this assertion
      ///
      /// \return the location where this assertion was hit
      source_location source() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      source_location m_location;
    };

  } // namespace stl
} // namespace bit

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::stl::assertion_failure
  ::assertion_failure( const char* message, source_location source )
  : std::runtime_error(message),
    m_location( std::move(source) )
{

}

//------------------------------------------------------------------------
// Accessors
//------------------------------------------------------------------------

inline bit::stl::source_location bit::stl::assertion_failure::source()
  const noexcept
{
  return m_location;
}

// Runtime assertion (Only available when in debug)
#if defined(BIT_DEBUG) || defined(BIT_ALWAYS_ASSERT)
# if BIT_COMPILER_EXCEPTIONS_ENABLED
#   include <iostream>
# endif

namespace bit {
  namespace stl {

# if BIT_COMPILER_EXCEPTIONS_ENABLED




#   define BIT_INTERNAL_ASSERT(condition,message) \
      throw ::bit::stl::assertion_failure("assertion_failure: condition '" condition "' failed with message \"" message "\"", BIT_MAKE_SOURCE_LOCATION() );

# else
    namespace detail {

      inline void assert_internal(string_view message, source_location source)
      {
        std::cerr << "[assertion] " << source.file_name() << "(" << source.line() << ")::" << source.function_name() << "\n"
                     "[assertion] " << message << "\n" << std::flush;
        BIT_BREAKPOINT();
      }

    } // namespace detail
#   define BIT_INTERNAL_ASSERT(condition,message) ::bit::stl::detail::assert_internal("assertion failure: condition '" condition "' failed with message \"" message "\"", BIT_MAKE_SOURCE_LOCATION() );
# endif
  } // namespace stl
} // namespace bit
#else
# define BIT_INTERNAL_ASSERT(...)
#endif

//============================================================================
// Assertion Macros
//============================================================================

//! \def BIT_ASSERT(condition, message, ...)
//!
//! \brief A runtime assertion when \a condition fails, displaying \a message
//!        to the user.
#if defined(BIT_DEBUG) || defined(BIT_ALWAYS_ASSERT)
# define BIT_ASSERT(condition,message)                            \
    do {                                                          \
      if(!(condition))                                            \
      {                                                           \
        BIT_INTERNAL_ASSERT( BIT_STRINGIZE(condition), message ); \
      }                                                           \
    } while(0)
#else
# define BIT_ASSERT(...)
#endif

#if BIT_COMPILER_EXCEPTIONS_ENABLED
# define BIT_ASSERT_OR_THROW(exception,condition,message) \
  do {                                                    \
    if(!(condition)) {                                    \
      throw exception{message};                           \
    }                                                     \
  } while(0)
#else
# define BIT_ASSERT_OR_THROW(exception,condition,message) \
  BIT_ASSERT(condition,message)
#endif

//! \def BIT_SANITY_CHECK(a,b)
//!
//! Performs a sanity check on a condition. This is used as a way to
//! assert that the condition will never be both simultaneously true and false
//!
//! \note this is primarily used as a utility to check user-built class
//!       operations, such as a class's "operator ==", to ensure that
//!       operator == and operator != don't always return the same value
#if defined(BIT_DEBUG)
#  define BIT_SANITY_CHECK(a,b) BIT_ASSERT(                     \
    !((a)&&(b)),                                                \
    "Sanity check failed: "                                     \
    "Conditions " #a " and " #b " cannot both be true." )
#else
#  define BIT_SANITY_CHECK(a,b)
#endif

#endif /* BIT_STL_UTILITIES_ASSERT_HPP */
