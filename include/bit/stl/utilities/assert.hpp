/*****************************************************************************
 * \file
 * \brief This header contains the definitions for both static and
 *        runtime assertions.
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
#ifndef BIT_STL_UTILITIES_ASSERT_HPP
#define BIT_STL_UTILITIES_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "source_location.hpp" // source_location
#include "compiler_traits.hpp" // BIT_DEBUG, BIT_COMPILER_EXCEPTIONS_ENABLED
#include "macros.hpp"          // BIT_STRINGIZE

#include <cstdio> // std::printf, stderr

//=============================================================================
// X.Y.1 : Assertion Macros
//=============================================================================

// Assertions default to enabled in debug mode unless otherwise specified
#ifndef BIT_STL_ASSERTIONS_ENABLED
# ifdef BIT_DEBUG
#   define BIT_STL_ASSERTIONS_ENABLED 1
# endif
#endif

#ifdef BIT_ALWAYS_ASSERT
# error duplicate definition of BIT_ALWAYS_ASSERT
#endif

#ifdef BIT_ASSERT
# error duplicate definition of BIT_ASSERT
#endif

#ifdef BIT_ALWAYS_ASSERT_
# error duplicate definition of BIT_ALWAYS_ASSERT_
#endif

#define BIT_INTERNAL_ALWAYS_ASSERT(condition,message,source) \
  ::bit::stl::detail::assert_internal("assertion failure: condition '" \
                                      condition "' failed with message \"" \
                                      message "\"", source )

//! \def BIT_ASSERT(condition, message)
//!
//! \brief A runtime assertion when \a condition fails, displaying \a message
//!        to the user.
//!
//! \param condition the condition that, when false, triggers an assertion
//! \param message   the message for the failure
#define BIT_ALWAYS_ASSERT(condition,message) \
  ((BIT_LIKELY(condition)) ? ((void)0) : [](::bit::stl::source_location source){ BIT_INTERNAL_ALWAYS_ASSERT( BIT_STRINGIZE(condition), message, source ); }(BIT_MAKE_SOURCE_LOCATION()) )

//! \def BIT_ASSERT(condition, message, ...)
//!
//! \brief A runtime assertion when \a condition fails, displaying \a message
//!        to the user.
//!
//! \param condition the condition that, when false, triggers an assertion
//! \param message   the message for the failure
#if BIT_STL_ASSERTIONS_ENABLED
# define BIT_ASSERT(condition,message) BIT_ALWAYS_ASSERT(condition,message)
#else
# define BIT_ASSERT(...) ((void)0)
#endif

//! \def BIT_ASSERT_OR_THROW(condition, exception, message)
//!
//! \brief An assertion that either throws the given exception, if exceptions
//!        are enabled, or calls the default assert
//!
//! \param condition the condition that, when false, triggers either an
//!                  assertion or throws an exception
//! \param exception the exception to throw
//! \param message   the message for the failure
#if BIT_COMPILER_EXCEPTIONS_ENABLED
# define BIT_ASSERT_OR_THROW(condition,exception,message) \
  ((BIT_LIKELY(condition)) ? ((void)0) : []{ throw exception{ message }; }())
#else
# define BIT_ASSERT_OR_THROW(condition,exception,message) \
  BIT_ASSERT(condition,message)
#endif

#include "detail/assert.inl"

#endif /* BIT_STL_UTILITIES_ASSERT_HPP */
