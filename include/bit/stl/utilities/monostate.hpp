/**
 * \file monostate.hpp
 *
 * \brief This header defines the type 'monotype'
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_MONOSTATE_HPP
#define BIT_STL_UTILITIES_MONOSTATE_HPP

#include <cstddef> // std::size_t

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Unit type intended for use as a well-behaved empty alternative
    ///        in \c variant.
    ///
    /// In particular, a variant of non-default-constructible types may list
    /// monostate as its first alternative: this makes the variant itself
    /// default-constructible.
    ///////////////////////////////////////////////////////////////////////////
    struct monostate{};

    //-------------------------------------------------------------------------
    // Comparison
    //-------------------------------------------------------------------------

    constexpr bool operator<(monostate, monostate) noexcept;
    constexpr bool operator>(monostate, monostate) noexcept;
    constexpr bool operator<=(monostate, monostate) noexcept;
    constexpr bool operator>=(monostate, monostate) noexcept;
    constexpr bool operator==(monostate, monostate) noexcept;
    constexpr bool operator!=(monostate, monostate) noexcept;

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Hashes the monostate
    ///
    /// \return 9
    constexpr std::size_t hash_value( const monostate& );

  } // namespace stl
} // namespace bit

#include "detail/monostate.inl"

#endif /* BIT_STL_UTILITIES_MONOSTATE_HPP */
