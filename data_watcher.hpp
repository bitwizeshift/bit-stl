/**
 * \file const_data_watcher.hpp
 *
 * \brief Debug methods for the rest of the system
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_CONST_DATA_WATCHER_HPP
#define BIT_CONST_DATA_WATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "config.hpp"
#include "type_traits.hpp"

namespace bit {

  /////////////////////////////////////////////////////////////////////////////
  /// \class bfg::data_watcher
  ///
  /// \brief A wrapper class around fundamental types that causes a breakpoint
  ///        any time the variable is set.
  ///
  /// \note In non-debug builds, const_data_watcher is not defined so that it
  ///       cannot exist in release.
  /////////////////////////////////////////////////////////////////////////////
#ifdef BIT_DEBUG
  template<typename T>
  class data_watcher final
  {
    //-------------------------------------------------------------------------
    // Public Members
    //-------------------------------------------------------------------------
  public:

    typedef data_watcher<T> this_type;

    typedef T        value_type;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef T*       pointer;
    typedef const T* const_pointer;

    //-------------------------------------------------------------------------
    // Assignment
    //-------------------------------------------------------------------------
  public:

    /// \brief Assign a value to this data watcher
    ///
    /// \param val the value to assign
    /// \return reference to the newly changed value
    inline const T& operator=( const value_type& val )
      noexcept
    {
      return set( val );
    }

    /// \brief Assign a value to this data watcher
    ///
    /// \param x the value to assign
    /// \return reference to the newly changed value
    inline const T& operator=( const data_watcher<T>& x )
      noexcept
    {
      return set( x.get() );
    }

    /// \brief Assign a value to this data watcher
    ///
    /// \param x the value to assign
    /// \return reference to the newly changed value
    template<typename U>
    inline const T& operator=( const data_watcher<U>& x )
      noexcept
    {
      return set( x.get() );
    }

    //-------------------------------------------------------------------------
    // Get/Set
    //-------------------------------------------------------------------------
  public:

    /// \brief Sets the variable, setting a breakpoint before the value changes
    ///
    /// \return reference to the data
    inline const reference set( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data = val;
      return m_data;
    }

    /// \brief Gets the variable being watched
    ///
    /// \return reference to the data
    inline const reference get() const
      noexcept
    {
      return m_data;
    }

    //-------------------------------------------------------------------------
    // Operators
    //-------------------------------------------------------------------------
  public:

    inline const reference operator+=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data+=val;
      return (*this);
    }

    inline const reference operator-=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data-=val;
      return (*this);
    }

    inline const reference operator/=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data/=val;
      return (*this);
    }

    inline const reference operator*=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data*=val;
      return (*this);
    }

    inline const reference operator%=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data%=val;
      return (*this);
    }

    //-------------------------------------------------------------------------

    inline const reference operator&=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data&=val;
      return (*this);
    }

    inline const reference operator^=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data^=val;
      return (*this);
    }

    inline const reference operator|=( const value_type& val )
    {
      BIT_BREAKPOINT();
      m_data|=val;
      return (*this);
    }

    //-------------------------------------------------------------------------

    inline const reference operator++()
    {
      BIT_BREAKPOINT();
      m_data++;
      return (*this);
    }

    inline const reference operator--()
    {
      BIT_BREAKPOINT();
      m_data--;
      return (*this);
    }

    inline value_type operator++( int )
    {
      BIT_BREAKPOINT();
      ++m_data;
      return (*this);
    }

    inline value_type operator--( int )
    {
      BIT_BREAKPOINT();
      --m_data;
      return (*this);
    }

    //-------------------------------------------------------------------------

    inline operator const value_type&()
      const noexcept
    {
      return m_data;
    }

    inline const pointer operator->()
      const noexcept
    {
      return &m_data;
    }

    inline const reference operator*()
      const noexcept
    {
      return m_data;
    }

    //-------------------------------------------------------------------------
    // Private Members
    //-------------------------------------------------------------------------
  private:

    value_type m_data; ///< Internal data to be watched
  };

#else

  template<typename T>
  class const_data_watcher
  {
    const_data_watcher() = delete; // refuse to compile in non-debug builds
  };

#endif

}  // namespace bit



#endif /* BIT_CONST_DATA_WATCHER_HPP */
