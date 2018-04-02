/*****************************************************************************
 * \file
 * \brief This header contains a type-erased version of the unique_ptr
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
#ifndef BIT_STL_MEMORY_EXCLUSIVE_PTR_HPP
#define BIT_STL_MEMORY_EXCLUSIVE_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../utilities/compressed_tuple.hpp"
#include "allocator_deleter.hpp"

#include <cstdint>     // std::uintptr_t
#include <memory>      // std::default_delete
#include <tuple>       // std::forward_as_tuple
#include <type_traits> // std::add_lvalue_reference_t
#include <utility>     // std::piecewise_construct, std::move, std::forward

namespace bit {
  namespace stl {
    template<typename> class exclusive_ptr;

    namespace detail {
      class exclusive_ptr_control_block;
      template<typename,typename> class exclusive_ptr_emplace;
      template<typename,typename,typename> class exclusive_ptr_pointer;
      template<typename T, typename U>
      exclusive_ptr<T> static_pointer_cast( exclusive_ptr<U>&& other );
      template<typename T, typename U>
      exclusive_ptr<T> dynamic_pointer_cast( exclusive_ptr<U>&& other );
      template<typename T, typename U>
      exclusive_ptr<T> const_pointer_cast( exclusive_ptr<U>&& other );
      template<typename T, typename U>
      exclusive_ptr<T> reinterpret_pointer_cast( exclusive_ptr<U>&& other );
    } // namespace detail

    //=========================================================================
    // X.Y.1 : exclusive_ptr
    //=========================================================================

    ///////////////////////////////////////////////////////////////////////////
    /// \brief An RAII wrapper around an allocated piece of memory with unique
    ///        ownership semantics.
    ///
    /// Unlike unique_ptr, this type type-erases the allocator and deleter.
    /// This provides flexibility at the cost of a virtual call for destructor,
    /// and some possible spacial overhead of 1 extra pointer along with any
    /// additional storage required by Deleter and Allocator types.
    ///
    /// In the  case where Deleter and Allocator are both stateless, and
    /// this type is allocated by a call to 'make_exclusive' or
    /// 'allocate_exclusive', then the additional storage is fixed at
    /// 2 pointers on the stack, and no additional heap memory.
    ///
    /// This is useful for classes that require unique ownership semantics,
    /// but offer flexibility on the underlying allocator type that can be
    /// used without wanting to expose the entire class as a template.
    ///
    /// \tparam T The type pointed to by this exclusive_ptr
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    class exclusive_ptr
    {
      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using element_type = std::remove_extent_t<T>;

      //-----------------------------------------------------------------------
      // Constructors / Destructor / Assignment
      //-----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Constructs an exclusive_ptr that points to nullptr
      ///
      /// \post \c get() returns \c nullptr
      constexpr exclusive_ptr() noexcept;
      constexpr exclusive_ptr( std::nullptr_t ) noexcept;
      /// \}

      /// \brief Constructs an exclusive_ptr that points to \p ptr
      ///
      /// \note This function only participates in overload resolution if \c Y*
      ///       is convertible to T*
      ///
      /// Use of this particular constructor is discouraged with exclusive_ptr
      /// since it allocates additional heap memory. Prefer 'make_exclusive' or
      /// 'allocate_exclusive' whenever possible
      ///
      /// \post \c get() returns \p ptr
      ///
      /// \param ptr the pointer to point to
      template<typename Y,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      explicit exclusive_ptr( Y* ptr );

      /// \brief Constructs an exclusive_ptr that points to \p ptr and is
      ///        deleted by \p deleter
      ///
      /// \note This function only participates in overload resolution if \c Y*
      ///       is convertible to T*
      ///
      /// Use of this particular constructor is discouraged with exclusive_ptr
      /// since it allocates additional heap memory. Prefer 'make_exclusive' or
      /// 'allocate_exclusive' whenever possible
      ///
      /// \post \c get() returns \p ptr
      ///
      /// \param ptr the pointer to point to
      /// \param deleter the deleter to use to deleter \p ptr
      template<typename Y, typename Deleter,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      explicit exclusive_ptr( Y* ptr, Deleter deleter );

      /// \brief Constructs an exclusive_ptr that points to nullptr
      ///
      /// \post \c get() returns \c nullptr
      ///
      /// \param deleter the deleter to use to deleter \p ptr
      template<typename Deleter>
      exclusive_ptr( std::nullptr_t, Deleter deleter );

      /// \brief Constructs an exclusive_ptr that points to \p ptr,
      ///        uses \p deleter to delete the allocated memory, and
      ///        uses \p alloc to allocate the node
      ///
      /// \note This function only participates in overload resolution if \c Y*
      ///       is convertible to T*
      ///
      /// \post \c get() returns \p ptr
      ///
      /// \param ptr the pointer to point to
      /// \param deleter the deleter to use to deleter \p ptr
      /// \param alloc the allocator to allocate the node
      template<typename Y, typename Deleter, typename Allocator,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      exclusive_ptr( Y* ptr, Deleter deleter, Allocator alloc );

      /// \brief Constructs an exclusive_ptr that points to nullptr
      ///
      /// \post \c get() returns \c nullptr
      ///
      /// \param deleter the deleter to use to deleter \p ptr
      /// \param alloc the allocator to allocate the node
      template<typename Deleter, typename Allocator>
      exclusive_ptr( std::nullptr_t, Deleter deleter, Allocator alloc );

      /// \brief Move-constructs this exclusive_ptr from an existing one
      ///
      /// \post \c other.get() returns \c nullptr
      ///
      /// \post \c get() returns the old value of \c other.get()
      ///
      /// \param other the other exclusive_ptr to move
      exclusive_ptr( exclusive_ptr&& other ) noexcept;

      // Deleted copy constructor
      exclusive_ptr( const exclusive_ptr& other ) = delete;

      /// \brief Move-converts this exclusive_ptr from an existing one
      ///
      /// \note This function only participates in overload resolution if \c Y*
      ///       is convertible to T*
      ///
      /// \post \c other.get() returns \c nullptr
      ///
      /// \post \c get() returns the old value of \c other.get()
      ///
      /// \param other the other exclusive_ptr to c
      template<typename Y,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      exclusive_ptr( exclusive_ptr<Y>&& other ) noexcept;

      // Deleted copy converting constructor
      template<typename Y,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      exclusive_ptr( const exclusive_ptr<Y>& other ) = delete;

      //-----------------------------------------------------------------------

      /// \brief Destroys this exclusive_ptr, freeing up any resources
      ~exclusive_ptr();

      //-----------------------------------------------------------------------

      /// \brief Move-assigns an exclusive_ptr to this \p exclusive_ptr
      ///
      /// \post \c other.get() returns \c nullptr
      ///
      /// \post \c get() returns the old pointer from \c other.get()
      ///
      /// \param other the other exclusive_ptr to move
      /// \return reference to \c (*this)
      exclusive_ptr& operator=( exclusive_ptr&& other ) noexcept;

      /// \brief Move-assigns an exclusive_ptr to this \p exclusive_ptr
      ///
      /// \note This function only participates in overload resolution if \c Y*
      ///       is convertible to T*
      ///
      /// \post \c other.get() returns \c nullptr
      ///
      /// \post \c get() returns the old pointer from \c other.get()
      ///
      /// \param other the other exclusive_ptr to move
      /// \return reference to \c (*this)
      template<typename Y,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      exclusive_ptr& operator=( exclusive_ptr<Y>&& other ) noexcept;

      /// \brief Assigns \c nullptr to this \c exclusive_ptr
      ///
      /// \post \c get() returns \c nullptr
      ///
      /// \return reference to \c (*this)
      exclusive_ptr& operator=( std::nullptr_t ) noexcept;

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------

      /// \brief Resets this exclusive_ptr to \c nullptr, freeing any resources
      ///
      /// \post \c get() returns \c nullptr
      void reset() noexcept;

      /// \{
      /// \brief Resets this exclusive_ptr to the specified \p ptr
      ///
      /// \note This function only participates in overload resolution if \c Y*
      ///       is convertible to T*
      ///
      /// \param ptr the pointer to watch
      /// \param deleter the deleter to free \p ptr with
      /// \param alloc the allocator to allocate the new node with
      template<typename Y,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      void reset( Y* ptr );
      template<typename Y, typename Deleter,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      void reset( Y* ptr, Deleter deleter );
      template<typename Y, typename Deleter, typename Allocator,
               typename=std::enable_if_t<std::is_convertible<Y*,T*>::value>>
      void reset( Y* ptr, Deleter deleter, Allocator alloc );
      /// \}

      //-----------------------------------------------------------------------

      /// \brief Swaps the contents of \c this with \p other
      ///
      /// \post \p other contains the old contents of \c this, and \c this
      ///       contains the old contents of \p other
      ///
      /// \param other the other pointer to swap with
      void swap( exclusive_ptr& other ) noexcept;

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------

      /// \brief Gets a pointer to the underlying element
      ///
      /// \return pointer to the element
      element_type* get() const noexcept;

      /// \brief Indexes into the array pointed to by this exclusive_ptr
      ///
      /// \note This function only partiicpates in overload resolution if
      ///       \c T is an array type
      ///
      /// \param i the index entry to point to
      /// \return reference to \c the indexed entry
      template<typename U=T,
               typename=std::enable_if_t<std::is_array<U>::value>>
      std::add_lvalue_reference_t<element_type>
        operator[]( std::ptrdiff_t i ) noexcept;

      /// \brief Dereferences the exclusive_ptr
      ///
      /// \pre \c get() returns non-null
      ///
      /// \return reference to the pointed-to element
      std::add_lvalue_reference_t<element_type>
        operator*() const noexcept;

      /// \brief Dereferences the exclusive_ptr
      ///
      /// \pre \c get() returns non-null
      ///
      /// \return pointer to the element
      element_type* operator->() const noexcept;

      /// \brief Returns \c true if this pointer is non-null
      ///
      /// \return \c true if this pointer is non-null
      explicit operator bool() const noexcept;

      //-----------------------------------------------------------------------
      // Private Member Types
      //-----------------------------------------------------------------------
    private:

      struct ctor_tag{};
      using control_block_type = detail::exclusive_ptr_control_block;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      control_block_type* m_control_block;
      element_type*       m_ptr;

      template<typename> friend class exclusive_ptr;

      //-----------------------------------------------------------------------
      // Private Constructors
      //-----------------------------------------------------------------------
    private:

      /// \brief Constructs this exclusive_ptr from the given control block and
      ///        pointer
      ///
      /// \param block the control block
      /// \param ptr the pointer to the managed element
      exclusive_ptr( ctor_tag,
                     control_block_type* block,
                     T* ptr ) noexcept;

      //-----------------------------------------------------------------------
      // Friendships
      //-----------------------------------------------------------------------
    private:

      template<typename Deleter, typename U>
      friend Deleter* get_deleter( const exclusive_ptr<U>& );

      template<typename U, typename...Args>
      friend exclusive_ptr<U> make_exclusive( Args&&...args );

      template<typename U, typename Allocator, typename...Args>
      friend exclusive_ptr<U> allocate_exclusive( const Allocator& allocator, Args&&...args );

      template<typename Y, typename U>
      friend exclusive_ptr<Y> detail::static_pointer_cast( exclusive_ptr<U>&& other );
      template<typename Y, typename U>
      friend exclusive_ptr<Y> detail::dynamic_pointer_cast( exclusive_ptr<U>&& other );
      template<typename Y, typename U>
      friend exclusive_ptr<Y> detail::const_pointer_cast( exclusive_ptr<U>&& other );
      template<typename Y, typename U>
      friend exclusive_ptr<Y> detail::reinterpret_pointer_cast( exclusive_ptr<U>&& other );

    };

    //-------------------------------------------------------------------------
    // Comparison
    //-------------------------------------------------------------------------

    template<typename T>
    bool operator==( const exclusive_ptr<T>& lhs, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator!=( const exclusive_ptr<T>& lhs, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator<( const exclusive_ptr<T>& lhs, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator>( const exclusive_ptr<T>& lhs, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator<=( const exclusive_ptr<T>& lhs, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator>=( const exclusive_ptr<T>& lhs, const exclusive_ptr<T>& rhs ) noexcept;

    template<typename T>
    bool operator==( const exclusive_ptr<T>& lhs, std::nullptr_t ) noexcept;
    template<typename T>
    bool operator==( std::nullptr_t, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator!=( const exclusive_ptr<T>& lhs, std::nullptr_t ) noexcept;
    template<typename T>
    bool operator!=( std::nullptr_t, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator<( const exclusive_ptr<T>& lhs, std::nullptr_t ) noexcept;
    template<typename T>
    bool operator<( std::nullptr_t, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator>( const exclusive_ptr<T>& lhs, std::nullptr_t ) noexcept;
    template<typename T>
    bool operator>( std::nullptr_t, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator<=( const exclusive_ptr<T>& lhs, std::nullptr_t ) noexcept;
    template<typename T>
    bool operator<=( std::nullptr_t, const exclusive_ptr<T>& rhs ) noexcept;
    template<typename T>
    bool operator>=( const exclusive_ptr<T>& lhs, std::nullptr_t ) noexcept;
    template<typename T>
    bool operator>=( std::nullptr_t, const exclusive_ptr<T>& rhs ) noexcept;

    //=========================================================================
    // X.Y.2 : exclusive_ptr utilities
    //=========================================================================

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Swaps the contents of \p lhs with \p rhs
    ///
    /// \post the old contents of \p lhs are in \p rhs and the old contents of
    ///       \p rhs are in \p lhs
    ///
    /// \param lhs the left exclusive_ptr to swap
    /// \param rhs the right exclusive_ptr to swap
    template<typename T>
    void swap( exclusive_ptr<T>& lhs, exclusive_ptr<T>& rhs ) noexcept;

    //-------------------------------------------------------------------------

    /// \brief Hashes this exclusive_ptr
    ///
    /// \param val the value to hash
    /// \return the hash of the underlying pointer
    template<typename T>
    std::size_t hash_value( const exclusive_ptr<T>& val ) noexcept;

    //-------------------------------------------------------------------------

    /// \brief Gets the deleter from \p ptr
    ///
    /// \tparam Deleter the type of the deleter to retrieve
    /// \param ptr the exclusive_ptr to get the deleter from
    /// \return the deleter
    template<typename Deleter, typename T>
    Deleter* get_deleter( const exclusive_ptr<T>& ptr );

    //-------------------------------------------------------------------------

    /// \brief Makes an exclusive_ptr from the given \p args
    ///
    /// \tparam T the type of the exclusive_ptr
    /// \param args the arguments to forward for the underlying constructor
    /// \return an allocated exclusive_ptr
    template<typename T, typename...Args>
    exclusive_ptr<T> make_exclusive( Args&&...args );

    /// \brief Allocates an exclusive_ptr, forwarding \p args to the underyling
    ///        constructor
    ///
    /// \param allocator the allocator to allocate the exclusive_ptr
    /// \param args the arguments to forward for the underlying constructor
    /// \return an allocated exclusive_ptr
    template<typename T, typename Allocator, typename...Args>
    exclusive_ptr<T> allocate_exclusive( const Allocator& allocator, Args&&...args );

    //-------------------------------------------------------------------------
    // Casts
    //-------------------------------------------------------------------------

    inline namespace casts {
      /// \brief Statically casts an exclusive_ptr of type \c U to type \c T
      ///
      /// \tparam T the type to cast to
      /// \param other the exclusive_ptr to cast
      /// \return the statically casted exclusive_ptr
      template<typename T, typename U>
      exclusive_ptr<T> static_pointer_cast( exclusive_ptr<U>&& other );

      /// \brief Dynamically casts an exclusive_ptr of type \c U to type \c T
      ///
      /// If the expression \c dynamic_cast<T*>(other.get()) returns \c nullptr
      /// then \p other remains unchanged
      ///
      /// \tparam T the type to cast to
      /// \param other the exclusive_ptr to cast
      /// \return the dynamically casted exclusive_ptr
      template<typename T, typename U>
      exclusive_ptr<T> dynamic_pointer_cast( exclusive_ptr<U>&& other );

      /// \brief Const casts an exclusive_ptr of type \c U to type \c T
      ///
      /// \tparam T the type to cast to
      /// \param other the exclusive_ptr to cast
      /// \return the const casted exclusive_ptr
      template<typename T, typename U>
      exclusive_ptr<T> const_pointer_cast( exclusive_ptr<U>&& other );

      /// \brief Reinterpret casts an exclusive_ptr of type \c U to type \c T
      ///
      /// \tparam T the type to cast to
      /// \param other the exclusive_ptr to cast
      /// \return the reinterpret casted exclusive_ptr
      template<typename T, typename U>
      exclusive_ptr<T> reinterpret_pointer_cast( exclusive_ptr<U>&& other );
    } // inline namespace casts
  } // namespace stl
} // namespace bit

#include "detail/exclusive_ptr.inl"

#endif // BIT_STL_MEMORY_EXCLUSIVE_PTR_HPP
