/**
 * \file const_data_watcher.hpp
 *
 * \brief This header contains debug methods for the rest of the system
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_DATA_WATCHER_HPP
#define BIT_STL_DATA_WATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl local libraries
#include "stddef.hpp"
#include "type_traits.hpp"

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper class around fundamental types that causes a
    ///        breakpoint any time the variable is set.
    ///
    /// \note In non-debug builds, const_data_watcher is not defined so that
    ///       it cannot exist in release.
    ///
    /// \tparam T the type of this debug_watcher to watch
    //////////////////////////////////////////////////////////////////////////
#ifdef BIT_DEBUG
    template<typename T>
    class data_watcher final
    {
      //----------------------------------------------------------------------
      // Public Members
      //----------------------------------------------------------------------
    public:

      using value_type = T;
      using deref_type = decltype(*std::declval<T>());

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      template<typename...Args, std::enable_if_t<std::is_constructible<T,Args...>::value>* = nullptr>
      data_watcher( Args&&...args );

      data_watcher( const data_watcher& other );

      data_watcher( data_watcher&& other );

      template<typename U, std::enable_if_t<std::is_constructible<T,U&&>::value>* = nullptr>
      data_watcher( const data_watcher<U>& other );

      template<typename U, std::enable_if_t<std::is_constructible<T,U&&>::value>* = nullptr>
      data_watcher( data_watcher<U>&& other );

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Assign a value to this data watcher
      ///
      /// \param val the value to assign
      /// \return reference to the newly changed value
      data_watcher& operator=( const value_type& value );

      data_watcher& operator=( value_type&& value );

      data_watcher& operator=( const data_watcher& other ) = default;

      data_watcher& operator=( data_watcher&& other ) = default;

      template<typename U>
      data_watcher& operator=( const data_watcher<U>& other );

      template<typename U>
      data_watcher& operator=( data_watcher<U>&& other );

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      operator value_type&() &;

      operator value_type&&() &&;

      value_type& operator->();

      const value_type& operator->() const;

      deref_type& operator*() &;

      const deref_type& operator*() const &;

      deref_type&& operator*() &&;

      const deref_type&& operator*() const &&;

      //----------------------------------------------------------------------
      // Operators
      //----------------------------------------------------------------------
    public:

      data_watcher& operator+=( const value_type& val );

      data_watcher& operator-=( const value_type& val );

      data_watcher& operator/=( const value_type& val );

      data_watcher& operator*=( const value_type& val );

      data_watcher& operator%=( const value_type& val );

      //----------------------------------------------------------------------

      data_watcher& operator&=( const value_type& val );

      data_watcher& operator^=( const value_type& val );

      data_watcher& operator|=( const value_type& val );

      //----------------------------------------------------------------------

      data_watcher& operator++();

      data_watcher& operator--();

      data_watcher& operator++( int );

      data_watcher& operator--( int );

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
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

  } // namespace stl
}  // namespace bit

#endif /* BIT_STL_DATA_WATCHER_HPP */
