/*****************************************************************************
 * \file
 * \brief This file contains source_location, a type used to contain
 *        information regarding source details from exceptions
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
#ifndef BIT_STL_UTILITIES_SOURCE_LOCATION_HPP
#define BIT_STL_UTILITIES_SOURCE_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstddef> // std::size_t

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Source location is a small, immutable type used for representing
    ///        where retrieving information about where this type is constructed
    ///
    /// The common approach is intended for this class to be embedded within
    /// exceptions and assertions in order to easily runtime-query the exact
    /// location an exception was thrown.
    //////////////////////////////////////////////////////////////////////////
    class source_location
    {
      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a source_location with the given \p file_name,
      ///        \p function_name, and \p line
      ///
      /// \param file_name     The name of the file
      /// \param function_name The name of the function
      /// \param line          The line number of the given
      constexpr source_location( const char* file_name,
                                 const char* function_name,
                                 std::size_t line );

      /// \brief Copies a given source_location
      constexpr source_location( const source_location& ) = default;

      /// \brief Moves a given source_location
      constexpr source_location( source_location&& ) = default;

      //----------------------------------------------------------------------
      // Access
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the line o the source_location
      ///
      /// \return the line of the source file
      constexpr std::size_t line() const noexcept;

      /// \brief Retrieves the function_name of the source_location
      ///
      /// \return the name of the function
      constexpr const char* function_name() const noexcept;

      /// \brief Retrieves the file_name of the source_location
      ///
      /// \return the name of the file
      constexpr const char* file_name() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      const char* m_file;     ///< The current file
      const char* m_function; ///< The current function
      std::size_t m_line;     ///< The line number
    };

    /// \brief Determines equality between two source_locations
    ///
    /// \param lhs The source_location on the left side of the equation
    /// \param rhs The source_location on the right side of the equation
    /// \return \c true if \p lhs is equal to \p rhs
    bool operator==( const source_location& lhs,
                     const source_location& rhs ) noexcept;

    /// \brief Determines inequality between two source_locations
    ///
    /// \param lhs The source_location on the left side of the equation
    /// \param rhs The source_location on the right side of the equation
    /// \return \c true if \p lhs is not equal to \p rhs
    bool operator!=( const source_location& lhs,
                     const source_location& rhs ) noexcept;

    //! \def BIT_MAKE_SOURCE_LOCATION
    //!
    //! \brief Retrieves the current source location for where this macro is
    //!        invoked
#   define BIT_MAKE_SOURCE_LOCATION() ::bit::stl::source_location( __FILE__, __func__, __LINE__ )

  } // namespace stl
} // namespace bit

#include "detail/source_location.inl"

#endif /* BIT_STL_UTILITIES_SOURCE_LOCATION_HPP */
