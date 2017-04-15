/**
 * \file casts.hpp
 *
 * \brief This header contains a collection of utilities for casts.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CASTS_HPP
#define BIT_STL_CASTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl local libraries
#include "stddef.hpp"
#include "assert.hpp"
#include "type_traits.hpp"

// std libraries
#include <cstring> // for std::memcpy
#include <limits>  // for std::numeric_limits


namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception for failed narrow_casts.
    ///
    /// This exception is thrown if a narrow_cast fails
    //////////////////////////////////////////////////////////////////////////
    struct bad_narrow_cast : public std::runtime_error
    {
      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      using std::runtime_error::runtime_error;
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception for failed pointer cast.
    ///
    /// This exception is thrown if a pointer_cast fails
    //////////////////////////////////////////////////////////////////////////
    struct bad_pointer_cast : public std::runtime_error
    {
      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      using std::runtime_error::runtime_error;
    };

    inline namespace casts {

      //----------------------------------------------------------------------
      // Casts
      //----------------------------------------------------------------------

      /// \brief Performs a bounded casting safely between numeric types.
      ///
      /// This method will assert if the value being casted does not properly
      /// fit into the value being converted to.
      /// Calling this method has the same form as calling static_cast
      ///
      /// \tparam To the value type to cast to
      /// \tparam From the value type to cast from. This should always be
      ///         inferred
      ///
      /// \param from the value to cast
      /// \return the casted value
      template<typename To, typename From>
      constexpr To narrow_cast( From from ) noexcept;

      // ---------------------------------------------------------------------

      /// \brief Statically casts a pointer if the pointer is dynamically
      ///        castable to that type, asserting otherwise.
      ///
      /// \note This will only assert in debug builds
      ///
      /// \param ptr the pointer to cast
      /// \return the statically casted pointer
      template<typename To, typename From>
      To pointer_cast( From ptr ) noexcept;

      // ---------------------------------------------------------------------

      /// \brief Performs a ca st between types by copying bytes from \p from
      ///        to the new type.
      ///
      /// This is safer than calling #byte_cast or #union_cast as it will
      /// conform to the proper alignment requirements
      ///
      /// \param from the value to convert
      /// \return the converted value
      template<typename To, typename From>
      To copy_cast( const From& from ) noexcept;

    } // inline namespace casts
  } // namespace stl
} // namespace bit

#include "detail/casts.inl"

#endif /* BIT_STL_CASTS_HPP */
