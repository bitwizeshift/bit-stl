/**
 * \file set_view.hpp
 *
 * \brief This header contains an implementation of a type-erased set
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

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
#ifndef BIT_STL_CONTAINERS_SET_VIEW_HPP
#define BIT_STL_CONTAINERS_SET_VIEW_HPP

#include "detail/associative_vtables.hpp" // IWYU pragma: export

#include <type_traits>

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A lightweight, non-owning wrapper around set operations
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class set_view
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type      = std::decay_t<T>;
      using pointer         = value_type*;
      using const_pointer   = const value_type*;
      using reference       = value_type&;
      using const_reference = const value_type&;

      using size_type       = std::size_t;

      //----------------------------------------------------------------------
      // Constructor / Destructor / Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an empty set_view
      constexpr set_view() noexcept;

      /// \brief Constructs a set_view from a given set
      ///
      /// \note This constructor does not participate in overload resolution
      ///       if Set is a set_view
      ///
      /// \param other the set-like type to view
#ifndef BIT_DOXYGEN_BUILD
      template<typename Set,
               typename = std::enable_if_t<!std::is_same<set_view,std::decay_t<Set>>::value> >
#else
      template<typename Set>
#endif
      constexpr set_view( Set&& other ) noexcept;

      /// \brief Constructs a set_view by copying another set_view
      ///
      /// \param other the set view to copy
      constexpr set_view( const set_view& other ) noexcept = default;

      /// \brief Constructs a set_view by moving another set_view
      ///
      /// \param other the set_view to move
      constexpr set_view( set_view&& other ) noexcept = default;

      /// \brief Destructs the set_view
      ~set_view() noexcept = default;

      //----------------------------------------------------------------------
      // Assignment Operators
      //----------------------------------------------------------------------
    public:

      set_view& operator=( const set_view& other ) noexcept = default;

      set_view& operator=( set_view&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Checks if this set_view is empty
      ///
      /// \return \c true if this set_view is empty
      bool empty() const noexcept;

      /// \brief Gets the size of this set_view
      ///
      /// \return the number of entries in this set_view
      size_type size() const noexcept;

      //----------------------------------------------------------------------
      // Lookup
      //----------------------------------------------------------------------
    public:

      /// \brief Counts the number of entries in this set_view
      ///
      /// \param key the key to count
      /// \return the number of entries in this set_view
      size_type count( const value_type& key ) const noexcept;

      /// \brief Checks the contents of this set_view
      ///
      /// \param key the key to find
      /// \return \c true if this set_view contains
      bool contains( const value_type& key ) const noexcept;

      /// \brief This operator determines whether this set_view is currently
      ///        viewing a set type
      explicit operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using vtable_type = detail::set_vtable<T>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      const vtable_type* m_vtable;
      const void*        m_instance;

    };

  } // namespace stl
} // namespace bit

#include "detail/set_view.inl"

#endif /* BIT_STL_CONTAINERS_SET_VIEW_HPP */
