/**
 * \file safe_enum.hpp
 *
 * \brief This header contains the utility for defining scoped, type-safe enums.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_SAFE_ENUM_HPP
#define BIT_SAFE_ENUM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

namespace bit {

  /////////////////////////////////////////////////////////////////////////////
  /// \class bit::safe_enum
  ///
  /// Implements the Type-Safe Enum c++ idiom, wherein an enum type is safely
  /// encapsulated within a struct, and can only be referred when properly
  /// scoped. This is also known as a Scoped-enum
  ///
  /// \ingroup bit
  /////////////////////////////////////////////////////////////////////////////
  template<
    typename def,
    typename inner = typename def::type
  >
  class safe_enum final : public def
  {

    //-------------------------------------------------------------------------
    // Public Types
    //-------------------------------------------------------------------------
  public:

    typedef safe_enum<def,inner> this_type;
    typedef inner                value_type;

    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
  public:

    inline safe_enum() {}
    inline safe_enum(value_type v) : m_val(v) {}

    //-------------------------------------------------------------------------
    // Comparison Operators
    //-------------------------------------------------------------------------
  public:

    inline value_type underlying() const { return m_val; }

    friend inline bool operator == (const this_type& lhs, const this_type& rhs) { return lhs.m_val == rhs.m_val; }
    friend inline bool operator != (const this_type& lhs, const this_type& rhs) { return lhs.m_val != rhs.m_val; }
    friend inline bool operator <  (const this_type& lhs, const this_type& rhs) { return lhs.m_val <  rhs.m_val; }
    friend inline bool operator <= (const this_type& lhs, const this_type& rhs) { return lhs.m_val <= rhs.m_val; }
    friend inline bool operator >  (const this_type& lhs, const this_type& rhs) { return lhs.m_val >  rhs.m_val; }
    friend inline bool operator >= (const this_type& lhs, const this_type& rhs) { return lhs.m_val >= rhs.m_val; }

    //-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
  private:

    value_type m_val;

  };

  //---------------------------------------------------------------------------

  /////////////////////////////////////////////////////////////////////////////
  /// \class bit::safe_operable_enum
  ///
  /// Like the #safe_enum, this implements the Type Safe Enum c++ idiom, with
  /// the expanded capability of providing mathematical and bitwise operations
  /// on the enums, while still forcing them to be valid enums.
  ///
  /// \ingroup core
  /////////////////////////////////////////////////////////////////////////////
  template<
    typename def,
    typename inner = typename def::type
  >
  class safe_operable_enum final : public def
  {

    //-------------------------------------------------------------------------
    // Public Types
    //-------------------------------------------------------------------------
  public:

    typedef safe_operable_enum<def,inner> this_type;
    typedef inner                         value_type;

    //-------------------------------------------------------------------------
    // Constructor
    //-------------------------------------------------------------------------
  public:

    inline safe_operable_enum() {}
    inline safe_operable_enum(value_type v) : m_val(v) {}

    //-------------------------------------------------------------------------
    // API Operations
    //-------------------------------------------------------------------------
  public:

    inline value_type underlying() const { return m_val; }

    //-------------------------------------------------------------------------
    // Comparison Operators
    //-------------------------------------------------------------------------
  public:

    friend inline bool operator == (const this_type& lhs, const this_type& rhs) { return lhs.m_val == rhs.m_val; }
    friend inline bool operator != (const this_type& lhs, const this_type& rhs) { return lhs.m_val != rhs.m_val; }
    friend inline bool operator <  (const this_type& lhs, const this_type& rhs) { return lhs.m_val <  rhs.m_val; }
    friend inline bool operator <= (const this_type& lhs, const this_type& rhs) { return lhs.m_val <= rhs.m_val; }
    friend inline bool operator >  (const this_type& lhs, const this_type& rhs) { return lhs.m_val >  rhs.m_val; }
    friend inline bool operator >= (const this_type& lhs, const this_type& rhs) { return lhs.m_val >= rhs.m_val; }

    //-------------------------------------------------------------------------
    // Bitwise Operators
    //-------------------------------------------------------------------------
  public:

    friend inline this_type  operator|  ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) | int( rhs.m_val ) ); }
    friend inline this_type  operator&  ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) & int( rhs.m_val ) ); }
    friend inline this_type  operator^  ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) ^ int( rhs.m_val ) ); }
    friend inline this_type  operator<< ( this_type  lhs, int  rhs )      { return value_type( int( lhs.m_val ) << rhs ); }
    friend inline this_type  operator>> ( this_type  lhs, int  rhs )      { return value_type( int( lhs.m_val ) >> rhs ); }
    friend inline this_type& operator|= ( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val |  rhs.m_val); }
    friend inline this_type& operator&= ( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val &  rhs.m_val); }
    friend inline this_type& operator^= ( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val ^  rhs.m_val); }
    friend inline this_type& operator<<=( this_type& lhs, int  rhs ) { return lhs = (lhs.m_val << rhs); }
    friend inline this_type& operator>>=( this_type& lhs, int  rhs ) { return lhs = (lhs.m_val >> rhs); }
    friend inline this_type  operator~  ( this_type  lhs )           { return this_type( ~int( lhs.m_val ) ); }

    //-------------------------------------------------------------------------
    // Arithmetic Operators
    //-------------------------------------------------------------------------
  public:

    friend inline this_type  operator+ ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) + int( rhs.m_val ) ); }
    friend inline this_type  operator- ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) - int( rhs.m_val ) ); }
    friend inline this_type  operator* ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) * int( rhs.m_val ) ); }
    friend inline this_type  operator/ ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) / int( rhs.m_val ) ); }
    friend inline this_type  operator% ( this_type  lhs, this_type rhs ) { return value_type( int( lhs.m_val ) % int( rhs.m_val ) ); }
    friend inline this_type& operator+=( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val + rhs.m_val);   }
    friend inline this_type& operator-=( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val - rhs.m_val);   }
    friend inline this_type& operator*=( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val * rhs.m_val);   }
    friend inline this_type& operator/=( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val / rhs.m_val);   }
    friend inline this_type& operator%=( this_type& lhs, this_type rhs ) { return lhs = (lhs.m_val % rhs.m_val);   }

    //-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
  private:

    value_type m_val;
  };


} // namespace bit

#endif /* BIT_SAFE_ENUM_HPP */
