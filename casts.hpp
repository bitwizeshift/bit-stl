/**
 * \file casts.hpp
 *
 * \brief This header contains a collection of utilities and basic casts.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 * \date   March 08, 2015
 */

#ifndef BIT_CASTS_HPP
#define BIT_CASTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit local libraries
#include "config.hpp"
#include "base_types.hpp"
#include "assert.hpp"
#include "type_traits.hpp"

// std libraries
#include <cstring> // for std::memcpy
#include <limits>  // for std::numeric_limits


namespace bit {


  /// \addtogroup bit
  /// \{

  //--------------------------------------------------------------------------
  // Casts
  //--------------------------------------------------------------------------

  struct narrowing_error : public std::logic_error
  {
  };

  /// \brief Performs a bounded casting safely between numeric types.
  ///
  /// This method will assert if the value being casted does not properly
  /// fit into the value being converted to.
  /// Calling this method has the same form as calling static_cast
  ///
  /// \tparam To the value type to cast to
  /// \tparam From the value type to cast from. This should always be inferred
  ///
  /// \param from the value to cast
  /// \return the casted value
  template<typename To, typename From>
  To narrow_cast( From from ) noexcept;

  // -------------------------------------------------------------------------

  /// \brief Statically casts a pointer if the pointer is dynamically
  ///        castable to that type, asserting otherwise.
  ///
  /// \note This will only assert in debug builds
  ///
  /// \param ptr the pointer to cast
  /// \return the statically casted pointer
  template<typename To, typename From>
  To pointer_cast( From ptr ) noexcept;

  // -------------------------------------------------------------------------

  /// \brief Performs a cast between types by copying bytes from \p from to the
  ///        new type.
  ///
  /// This is safer than calling #byte_cast or #union_cast as it will conform
  /// to the proper alignment requirements
  ///
  /// \param from the value to convert
  /// \return the converted value
  template<typename To, typename From>
  To copy_cast(const From& from) noexcept;

  /// \brief Performs a bit-by-bit cast between types.
  ///
  /// \note The size of the type being converted to must be larger than the
  /// size of the type being converted from
  ///
  /// \param from the value to convert
  /// \return the converted value
  template<typename To, typename From>
  To byte_cast( const From& from ) noexcept;

  /// \brief Performs a bit-by-bit cast between types.
  ///
  /// \note The size of the type being converted to must be larger than the
  /// size of the type being converted from
  ///
  /// \param from the value to convert
  /// \return the converted value
  template<typename To, typename From>
  To byte_cast( const From* from ) noexcept;

  /// \}
} // namespace bit

#include "detail/casts.inl"

#endif /* BIT_CASTS_HPP */
