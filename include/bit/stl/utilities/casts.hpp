/**
 * \file casts.hpp
 *
 * \brief This header contains a collection of utilities for casts.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_CASTS_HPP
#define BIT_STL_UTILITIES_CASTS_HPP

#include "stddef.hpp"
#include "assert.hpp"

#include "../traits/relationships/is_same_sign.hpp"

#include <cstring> // std::memcpy
#include <limits>  // std::numeric_limits

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
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      using std::runtime_error::runtime_error;
    };

    inline namespace casts {

      //-----------------------------------------------------------------------
      // Casts
      //-----------------------------------------------------------------------

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

      //---------------------------------------------------------------------=-

      /// \brief Statically casts a pointer if the pointer is dynamically
      ///        castable to that type, asserting otherwise.
      ///
      /// \note This will only assert in debug builds
      ///
      /// \param ptr the pointer to cast
      /// \return the statically casted pointer
      template<typename To, typename From>
      To pointer_cast( From ptr ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Performs a cast between types by copying bytes from \p from
      ///        to the new type.
      ///
      /// \note Bytes are truncated to fit into type \p To. If the size of
      ///       \p From is smaller than \p To, the remaining bytes are left
      ///       untouched (and thus may be UB to access)
      ///
      /// \param from the value to convert
      /// \return the converted value
      template<typename To, typename From>
      To copy_cast( const From& from ) noexcept;

      //-----------------------------------------------------------------------

      /// \brief Performs an implicit cast between two types, such that the
      ///        cast is actually performed using the implicit language
      ///        casting
      ///
      /// This can be used to signal cases that would otherwise produce
      /// warnings when type promotions are performed.
      ///
      /// \tparam To the type to convert to
      /// \param from the type being converted
      template<typename To, typename From>
      To implicit_cast( From&& from );

    } // inline namespace casts
  } // namespace stl
} // namespace bit

#include "detail/casts.inl"

#endif /* BIT_STL_UTILITIES_CASTS_HPP */
