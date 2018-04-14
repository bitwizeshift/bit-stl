/*****************************************************************************
 * \file
 * \brief This file defines a type-safe way of defining new integral types
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

#ifndef BIT_STL_UTILITIES_INTEGRAL_TYPE_HPP
#define BIT_STL_UTILITIES_INTEGRAL_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <type_traits>

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief A type-safe wrapper around integers to simplify creating unique
    ///        self-documenting types
    ///
    /// \tparam T the underlying integral type
    /// \tparam Tag the tag type to uniquely differentiate this from other
    ///             integral_types
    ///////////////////////////////////////////////////////////////////////////
    template<typename T, typename Tag=void>
    class integral_type
    {
      static_assert( std::is_integral<T>::value, "T must be an integral type" );
      static_assert( std::is_trivial<T>::value, "T must be trivial type" );

      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using value_type = T; ///< The underlying value type

      //-----------------------------------------------------------------------
      // Constructor / Assignment
      //-----------------------------------------------------------------------
    public:

      /// \brief Default initializes the underlying value type
      constexpr integral_type() noexcept = default;

      /// \brief Constructs the integral type type from the specified \p value
      ///
      /// \param value the value to initialize
      constexpr explicit integral_type( value_type value ) noexcept;

      /// \brief Constructs the integral type type from another integral type
      ///        of the same tag
      ///
      /// \note This constructor only participates in overload resolution if
      ///       U is convertible to T
      ///
      /// \param other the other integral type to copy
      template<typename U,
               typename=std::enable_if_t<std::is_convertible<U,T>::value>>
      constexpr explicit integral_type( integral_type<U,Tag>&& other ) noexcept;

      /// \brief Constructs the integral type type from another integral type
      ///        of the same tag
      ///
      /// \note This constructor only participates in overload resolution if
      ///       U is convertible to T
      ///
      /// \param other the other integral type to copy
      template<typename U,
               typename=std::enable_if_t<std::is_convertible<U,T>::value>>
      constexpr explicit integral_type( const integral_type<U,Tag>& other ) noexcept;

      /// \brief Move-constructs the integral type type from another integral
      ///        type
      ///
      /// \param other the other integral type to move
      constexpr integral_type( integral_type&& other ) noexcept = default;

      /// \brief Copy-constructs the integral type type from another integral
      ///        type
      ///
      /// \param other the other integral type to copy
      constexpr integral_type( const integral_type& other ) noexcept = default;

      //-----------------------------------------------------------------------

      /// \brief Copies the value of \p other
      ///
      /// \param other the other integral type to copy
      /// \return reference to \c (*this)
      integral_type& operator=( const integral_type& other ) noexcept = default;

      /// \brief Copies the value of \p other
      ///
      /// \param other the other integral type to copy
      /// \return reference to \c (*this)
      integral_type& operator=( integral_type&& other ) noexcept = default;

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Retrieves the underlying value of this integral type
      ///
      /// \return the underlying value
      constexpr value_type value() const noexcept;

      //-----------------------------------------------------------------------
      // Arithmetic Operators
      //-----------------------------------------------------------------------
    public:

      integral_type& operator+() const noexcept;
      integral_type operator-() const noexcept;

      //-----------------------------------------------------------------------

      integral_type& operator++() noexcept;
      integral_type operator++(int) noexcept;

      integral_type& operator--() noexcept;
      integral_type operator--(int) noexcept;

      //-----------------------------------------------------------------------

      integral_type& operator+=( integral_type value ) noexcept;
      integral_type& operator-=( integral_type value ) noexcept;
      integral_type& operator*=( integral_type value ) noexcept;
      integral_type& operator/=( integral_type value ) noexcept;
      integral_type& operator%=( integral_type value ) noexcept;

      //-----------------------------------------------------------------------

      integral_type& operator&=( integral_type value ) noexcept;
      integral_type& operator|=( integral_type value ) noexcept;
      integral_type& operator^=( integral_type value ) noexcept;

      //-----------------------------------------------------------------------

      template<typename U,
               typename=std::enable_if_t<std::is_integral<U>::value>>
      integral_type& operator<<=( U value ) noexcept;
      template<typename U,
               typename=std::enable_if_t<std::is_integral<U>::value>>
      integral_type& operator>>=( U value ) noexcept;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      value_type m_value;
    };

    //-------------------------------------------------------------------------
    // Comparison
    //-------------------------------------------------------------------------

    template<typename T, typename U, typename Tag>
    constexpr bool operator==( const integral_type<T,Tag>& lhs,
                               const integral_type<U,Tag>& rhs ) noexcept;
    template<typename T, typename U, typename Tag>
    constexpr bool operator!=( const integral_type<T,Tag>& lhs,
                               const integral_type<U,Tag>& rhs ) noexcept;
    template<typename T, typename U, typename Tag>
    constexpr bool operator<( const integral_type<T,Tag>& lhs,
                              const integral_type<U,Tag>& rhs ) noexcept;
    template<typename T, typename U, typename Tag>
    constexpr bool operator>( const integral_type<T,Tag>& lhs,
                              const integral_type<U,Tag>& rhs ) noexcept;
    template<typename T, typename U, typename Tag>
    constexpr bool operator<=( const integral_type<T,Tag>& lhs,
                               const integral_type<U,Tag>& rhs ) noexcept;
    template<typename T, typename U, typename Tag>
    constexpr bool operator>=( const integral_type<T,Tag>& lhs,
                               const integral_type<U,Tag>& rhs ) noexcept;

    //-------------------------------------------------------------------------
    // Binary Arithmetic Operators
    //-------------------------------------------------------------------------

    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator+( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs ) noexcept;
    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator-( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs ) noexcept;
    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator*( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs ) noexcept;
    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator/( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs ) noexcept;
    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator%( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs ) noexcept;

    //-------------------------------------------------------------------------

    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator&( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs  ) noexcept;
    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator|( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs  ) noexcept;
    template<typename T, typename Tag>
    constexpr integral_type<T,Tag>
      operator^( const integral_type<T,Tag>& lhs,
                 const integral_type<T,Tag>& rhs  ) noexcept;

    //-------------------------------------------------------------------------

    template<typename T, typename Tag, typename U,
             typename=std::enable_if_t<std::is_integral<U>::value>>
    constexpr integral_type<T,Tag>
      operator<<( const integral_type<T,Tag>& lhs, U rhs ) noexcept;
    template<typename T, typename Tag, typename U,
             typename=std::enable_if_t<std::is_integral<U>::value>>
    constexpr integral_type<T,Tag>
      operator>>( const integral_type<T,Tag>& lhs, U rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/integral_type.inl"

#endif /* BIT_STL_UTILITIES_INTEGRAL_TYPE_HPP */
