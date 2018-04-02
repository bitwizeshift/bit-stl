/*****************************************************************************
 * \file
 * \brief This header contains various hashing utilities
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
#ifndef BIT_STL_UTILITIES_HASH_HPP
#define BIT_STL_UTILITIES_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../concepts/Container.hpp"

#include <cstddef>          // std::size_t
#include <tuple>            // std::tuple, std::get
#include <utility>          // std::forward
#include <initializer_list> // std::initializer_list

namespace bit {
  namespace stl {

    //-------------------------------------------------------------------------
    // Hashing Utilities
    //-------------------------------------------------------------------------

    /// \brief Combines the hash with another hash
    ///
    /// \param seed The seed to combine the hash with
    /// \param v the value to hash
    template<typename T>
    constexpr void hash_combine( std::size_t& seed, const T& v );

    /// \brief Hashes a range of entries, returning the result
    ///
    /// This is equivalent to combining hashes of all entries within the range
    ///
    /// \param first The beginning of the range to hash
    /// \param last The end of the range to hash
    /// \return the hashed value
    template<typename InputIterator>
    constexpr std::size_t hash_range( InputIterator first, InputIterator last );

    /// \brief Hashes a range of entries
    ///
    /// This is equivalent to combining hashes of all entries within the range
    ///
    /// \param seed The seed to comine the hash with
    /// \param first The beginning of the range to hash
    /// \param last The end of the range to hash
    template<typename InputIterator>
    constexpr void hash_range( std::size_t& seed,
                               InputIterator first,
                               InputIterator last );

    //-------------------------------------------------------------------------
    // Hashing Calculations
    //-------------------------------------------------------------------------

    /// \brief Calculates a hash of a null pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( std::nullptr_t ) noexcept;

    /// \brief Calculates a hash of the given bool
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( bool val ) noexcept;

    /// \brief Calculates a hash of the given char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( char val ) noexcept;

    /// \brief Calculates a hash of the given signed char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( signed char val ) noexcept;

    /// \brief Calculates a hash of the given unsigned char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned char val ) noexcept;

    /// \brief Calculates a hash of the given wchar_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( wchar_t val ) noexcept;

    /// \brief Calculates a hash of the given char16_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( char16_t val ) noexcept;

    /// \brief Calculates a hash of the given char32_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( char32_t val ) noexcept;

    /// \brief Calculates a hash of the given short
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( short val ) noexcept;

    /// \brief Calculates a hash of the given unsigned short
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned short val ) noexcept;

    /// \brief Calculates a hash of the given int
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( int val ) noexcept;

    /// \brief Calculates a hash of the given unsigned int
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned int val ) noexcept;

    /// \brief Calculates a hash of the given long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( long val ) noexcept;

    /// \brief Calculates a hash of the given unsigned long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned long val ) noexcept;

    /// \brief Calculates a hash of the given long long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( long long val ) noexcept;

    /// \brief Calculates a hash of the given unsigned long long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr std::size_t hash_value( unsigned long long val ) noexcept;

    /// \brief Calculates a hash of the given float
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    std::size_t hash_value( float val ) noexcept;

    /// \brief Calculates a hash of the given double
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    std::size_t hash_value( double val ) noexcept;

    /// \brief Calculates a hash of the given long double
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    std::size_t hash_value( long double val ) noexcept;

    /// \brief Calculates a hash of the given pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T>
    std::size_t hash_value( T* const& val ) noexcept;

    /// \brief Calculates a hash of the given T array
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T, unsigned N>
    constexpr std::size_t hash_value( T (&val)[N] );

    /// \brief Calculates a hash of the given T array
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T, unsigned N>
    constexpr std::size_t hash_value( const T (&val)[N] );

    /// \brief Hashes enum values
    ///
    /// \note This only participates in overload resolution if
    ///       \c std::is_enum is \c true
    ///
    /// \param val the enum value to hash
    /// \return the hash value of the enum
#ifndef BIT_DOXYGEN_BUILD
    template<typename Enum, typename = std::enable_if_t<std::is_enum<Enum>::value>>
#else
    template<typename Enum>
#endif
    constexpr std::size_t hash_value( Enum val ) noexcept;

    /// \brief Hashes any given container
    ///
    /// The hash is computed as the combination of all the hashes within the
    /// container
    ///
    /// \note This does not participate in overload resolution unless
    ///       the container defines begin() and end()
    ///
    /// \param container the container to hash
    /// \return the hash value
#ifndef BIT_DOXYGEN_BUILD
    template<typename Container, typename = std::enable_if_t<is_container<Container>::value>>
#else
    template<typename Container>
#endif
    constexpr std::size_t hash_value( const Container& container ) noexcept;

    /// \brief Hashes a std::pair
    ///
    /// \param pair the pair to hash
    template<typename T, typename U>
    constexpr std::size_t hash_value( const std::pair<T,U>& pair );

    /// \brief Hashes a tuple of entries
    ///
    /// \param tuple the tuple to hash
    template<typename...Args>
    constexpr std::size_t hash_value( const std::tuple<Args...>& tuple );

    /// \brief Hashes an initializer_list
    ///
    /// This is equivalent to calling hash_range( il.begin(), il.end() )
    ///
    /// \param il the initializer_list to hash
    /// \return the hash of the initializer_list
    template<typename T>
    constexpr std::size_t hash_value( const std::initializer_list<T>& il );

    //-------------------------------------------------------------------------

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Hash struct that satisfies the requirements of \c std::hash,
    ///        but is implemented in terms of hash_value to allow for
    ///        easy ADL overloads and type-querying
    ///////////////////////////////////////////////////////////////////////////
    template<typename Key>
    struct hash
    {
      /// \brief Functor that hashes all key types
      ///
      /// \param val the value to hash
      /// \return the hash of the \p val
      constexpr std::size_t operator()( const Key& val );
    };

  } // namespace stl
} // namespace bit

#include "detail/hash.inl"

#endif /* BIT_STL_UTILITIES_HASH_HPP */
