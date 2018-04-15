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

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/bool_constant.hpp"
#include "../traits/composition/conjunction.hpp"

#include <cstddef>     // std::size_t
#include <utility>     // std::forward
#include <type_traits> // std::underlying_type_t, std::enable_if, etc

namespace bit {
  namespace stl {

    //=========================================================================
    // hash_t
    //=========================================================================

    /// \brief Type that represents a hash value
    enum class hash_t : std::size_t{};

    //-------------------------------------------------------------------------
    // Compound Operators
    //-------------------------------------------------------------------------

    hash_t& operator+=( hash_t& lhs, hash_t rhs ) noexcept;
    hash_t& operator-=( hash_t& lhs, hash_t rhs ) noexcept;
    hash_t& operator*=( hash_t& lhs, hash_t rhs ) noexcept;
    hash_t& operator/=( hash_t& lhs, hash_t rhs ) noexcept;
    hash_t& operator%=( hash_t& lhs, hash_t rhs ) noexcept;

    //-------------------------------------------------------------------------

    hash_t& operator&=( hash_t& lhs, hash_t rhs ) noexcept;
    hash_t& operator|=( hash_t& lhs, hash_t rhs ) noexcept;
    hash_t& operator^=( hash_t& lhs, hash_t rhs ) noexcept;

    //-------------------------------------------------------------------------

    template<typename IntT,
             typename = std::enable_if_t<std::is_integral<IntT>::value>>
    hash_t& operator<<=( hash_t& lhs, IntT rhs ) noexcept;
    template<typename IntT,
             typename = std::enable_if_t<std::is_integral<IntT>::value>>
    hash_t& operator>>=( hash_t& lhs, IntT rhs ) noexcept;

    //-------------------------------------------------------------------------
    // Binary Operators
    //-------------------------------------------------------------------------

    constexpr hash_t operator+( hash_t lhs, hash_t rhs ) noexcept;
    constexpr hash_t operator-( hash_t lhs, hash_t rhs ) noexcept;
    constexpr hash_t operator*( hash_t lhs, hash_t rhs ) noexcept;
    constexpr hash_t operator/( hash_t lhs, hash_t rhs ) noexcept;
    constexpr hash_t operator%( hash_t lhs, hash_t rhs ) noexcept;

    //-------------------------------------------------------------------------

    constexpr hash_t operator&( hash_t lhs, hash_t rhs ) noexcept;
    constexpr hash_t operator|( hash_t lhs, hash_t rhs ) noexcept;
    constexpr hash_t operator^( hash_t lhs, hash_t rhs ) noexcept;

    //-------------------------------------------------------------------------

    template<typename IntT,
             typename = std::enable_if_t<std::is_integral<IntT>::value>>
    constexpr hash_t operator<<( hash_t lhs, IntT rhs ) noexcept;
    template<typename IntT,
             typename = std::enable_if_t<std::is_integral<IntT>::value>>
    constexpr hash_t operator>>( hash_t lhs, IntT rhs ) noexcept;

    //-------------------------------------------------------------------------
    // Hashing Functions
    //-------------------------------------------------------------------------

    /// \brief Calculates a hash of a null pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( std::nullptr_t ) noexcept;

    /// \brief Calculates a hash of the given bool
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( bool val ) noexcept;

    /// \brief Calculates a hash of the given char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( char val ) noexcept;

    /// \brief Calculates a hash of the given signed char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( signed char val ) noexcept;

    /// \brief Calculates a hash of the given unsigned char
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( unsigned char val ) noexcept;

    /// \brief Calculates a hash of the given wchar_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( wchar_t val ) noexcept;

    /// \brief Calculates a hash of the given char16_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( char16_t val ) noexcept;

    /// \brief Calculates a hash of the given char32_t
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( char32_t val ) noexcept;

    /// \brief Calculates a hash of the given short
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( short val ) noexcept;

    /// \brief Calculates a hash of the given unsigned short
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( unsigned short val ) noexcept;

    /// \brief Calculates a hash of the given int
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( int val ) noexcept;

    /// \brief Calculates a hash of the given unsigned int
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( unsigned int val ) noexcept;

    /// \brief Calculates a hash of the given long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( long val ) noexcept;

    /// \brief Calculates a hash of the given unsigned long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( unsigned long val ) noexcept;

    /// \brief Calculates a hash of the given long long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( long long val ) noexcept;

    /// \brief Calculates a hash of the given unsigned long long
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    constexpr hash_t hash_value( unsigned long long val ) noexcept;

    /// \brief Calculates a hash of the given float
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    hash_t hash_value( float val ) noexcept;

    /// \brief Calculates a hash of the given double
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    hash_t hash_value( double val ) noexcept;

    /// \brief Calculates a hash of the given long double
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    hash_t hash_value( long double val ) noexcept;

    /// \brief Calculates a hash of the given pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T>
    hash_t hash_value( T* val ) noexcept;

    /// \brief Calculates a hash of the given function pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename R, typename...Args>
    hash_t hash_value( R(*val)(Args...) ) noexcept;

    /// \{
    /// \brief Calculates a hash of the given member function pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename R, typename C, typename...Args>
    hash_t hash_value( R(C::*val)(Args...) ) noexcept;
    template<typename R, typename C, typename...Args>
    hash_t hash_value( R(C::*val)(Args...) const ) noexcept;
    /// \}

    /// \brief Calculates a hash of the given member pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename R, typename C>
    hash_t hash_value( R C::* val ) noexcept;

    /// \{
    /// \brief Calculates a hash of the given T array
    ///
    /// \param val the value to hash
    /// \return the hash of the supplied value
    template<typename T, std::size_t N>
    constexpr hash_t hash_value( T (&val)[N] );
    template<typename T, std::size_t N>
    constexpr hash_t hash_value( const T (&val)[N] );
    /// \}

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
    constexpr hash_t hash_value( Enum val ) noexcept;

    //-------------------------------------------------------------------------
    // Hashing Utilities
    //-------------------------------------------------------------------------

    namespace detail {

      template<typename T, typename = void>
      struct is_hashable_impl
        : std::false_type{};

      template<typename T>
      struct is_hashable_impl<T,void_t<decltype( std::declval<::bit::stl::hash_t&>() = hash_value(std::declval<T>()) )>>
        : std::true_type{};

      template<typename T, typename = void>
      struct is_nothrow_hashable_impl
        : std::false_type{};

      template<typename T>
      struct is_nothrow_hashable_impl<T,void_t<decltype( std::declval<::bit::stl::hash_t&>() = hash_value(std::declval<T>()) )>>
        : bool_constant<noexcept( std::declval<::bit::stl::hash_t&>() = hash_value(std::declval<T>()) )>{};

    } // namespace detail

    /// \brief Trait determining whether \p T is hashable by an ADL call to
    ///        \c hash_value
    ///
    /// The result is accessible by \c ::value
    ///
    /// \tparam T the type to check
    template<typename T>
    struct is_hashable : detail::is_hashable_impl<T>{};

    /// \brief Convenience utility for extracting \c ::value from
    ///        \c is_hashable
    template<typename T>
    constexpr bool is_hashable_v = is_hashable<T>::value;

    //-------------------------------------------------------------------------

    /// \brief Trait determining whether \p T is nothrow hashable by an ADL
    ///        call to \c hash_value
    ///
    /// The result is accessible by \c ::value
    ///
    /// \tparam T the type to check
    template<typename T>
    struct is_nothrow_hashable : detail::is_nothrow_hashable_impl<T>{};

    /// \brief Convenience utility for extracting \c ::value from
    ///        \c is_nothrow_hashable
    template<typename T>
    constexpr bool is_nothrow_hashable_v = is_nothrow_hashable<T>::value;

    //-------------------------------------------------------------------------
    // Composite Hashing Functions
    //-------------------------------------------------------------------------

    /// \brief Combines two hash values
    ///
    /// \param seed the seed to combine
    /// \param hash the hash to combine with the seed
    /// \return the result of the combination
    constexpr hash_t hash_combine( hash_t seed, hash_t hash ) noexcept;

    /// \brief Combines n hash values
    ///
    /// \param seed the seed to begin combination with
    /// \param hash0 the first hash to comnbine with the seed
    /// \param hashes the rest of the hashes to combine with the combined seed/hashes
    /// \return the result of the combinations
    template<typename...Hashes,
             typename=std::enable_if<(sizeof...(Hashes)>0) &&
                                     conjunction<std::is_same<Hashes,hash_t>...>::value>>
    constexpr hash_t hash_combine( hash_t seed,
                                   hash_t hash0,
                                   Hashes...hashes ) noexcept;

    //-------------------------------------------------------------------------

    /// \brief Hashes a range of entries, returning the result
    ///
    /// This is equivalent to combining hashes of all entries within the range
    ///
    /// \param first The beginning of the range to hash
    /// \param last The end of the range to hash
    /// \return the hashed value
    template<typename InputIterator>
    constexpr hash_t hash_range( InputIterator first, InputIterator last )
      noexcept( is_nothrow_hashable<std::decay_t<decltype(std::declval<InputIterator>())>>::value );

    //-------------------------------------------------------------------------

    /// \brief Hashes all the specified \p args and combines the results
    ///
    /// The computation for each of the \p args is determined by using ADL to
    /// determine the appropriate \c hash_value function to call
    ///
    /// \param args the arguments to hash
    /// \return the hash result
    template<typename...Args>
    constexpr hash_t hash_values( Args&&...args );

    //-------------------------------------------------------------------------

    /// \brief Hashes a segment of a given string
    ///
    /// \param str the pointer to the start of the string
    /// \param count the length of the string
    /// \return the hash of the string segment
    template<typename CharT>
    constexpr hash_t hash_string_segment( const CharT* str,
                                          std::size_t count ) noexcept;

    /// \brief Hashes the raw memory from a given type
    ///
    /// \param data the data to hash
    /// \return the hash of the raw data
    template<typename T>
    hash_t hash_raw( const T& data ) noexcept;

    //=========================================================================
    // class hash
    //=========================================================================

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
      constexpr hash_t operator()( const Key& val );
    };

  } // namespace stl
} // namespace bit

#include "detail/hash.inl"

#endif /* BIT_STL_UTILITIES_HASH_HPP */
