/**
 * \file string.hpp
 *
 * \brief This header contains extension to the standard C++ char_traits
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CONTAINERS_STRING_HPP
#define BIT_STL_CONTAINERS_STRING_HPP

#include "detail/string_hash.hpp"

#include <string> // std::char_traits
#include <locale> // std::toupper<CharT>

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Char Traits
    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief Char traits to allow case-insensitive comparisons for strings
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT>
    struct insensitive_char_traits : public std::char_traits<CharT>
    {
      static constexpr CharT to_upper( CharT ch ) noexcept;

      static constexpr bool eq( CharT lhs, CharT rhs ) noexcept;

      static constexpr bool lt( CharT lhs, CharT rhs ) noexcept;

      static constexpr int compare( const CharT* s1,
                                    const CharT* s2,
                                    std::size_t count ) noexcept;

      static constexpr const CharT* find(const CharT* s, int n, CharT a) noexcept;
    };

    //------------------------------------------------------------------------
    // Utilities
    //------------------------------------------------------------------------

    /// \brief Hashes a std::basic_string
    ///
    /// \param str the string to hash
    /// \return the hash
    template<typename CharT, typename Traits, typename Allocator>
    std::size_t hash_value( const std::basic_string<CharT,Traits,Allocator>& str ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/string.inl"

#endif /* BIT_STL_CONTAINERS_STRING_HPP */
