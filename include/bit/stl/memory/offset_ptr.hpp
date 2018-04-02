/*****************************************************************************
 * \file
 * \brief todo: fill in documentation
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
#ifndef BIT_STL_MEMORY_OFFSET_PTR_HPP
#define BIT_STL_MEMORY_OFFSET_PTR_HPP

#include <cstdlib>     // std::ptrdiff_t
#include <cstdint>     // std::uintptr_t
#include <type_traits> // std::declval

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An offset pointer based on boost::offset_ptr
    ///
    /// \note Like boost::offset_ptr, an offset value of '1' is used to
    ///       represent nullptr internally, since it is unlikely for an offset
    ///       of 1 to ever be valid. 0 is not used, since a self-assignment of
    ///       an offset_ptr is a valid use-case.
    ///       Since 8-bit pointers are exceedingly rare, it should be unlikely
    ///       to ever have an issue with this. An offset of 1 would be pointing
    ///       into the offset_ptr class.
    ///
    /// \tparam T The underlying pointer element
    /// \satisfies NullablePointer
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class offset_ptr
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = T;  ///< The underlying element type
      using pointer      = T*; ///< The pointer type

      //----------------------------------------------------------------------
      // Constructors / Assignment
      //----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Constructs an offset_ptr pointing to nullptr
      offset_ptr() noexcept;
      offset_ptr( std::nullptr_t ) noexcept;
      /// \}

      /// \{
      /// \brief Constructs an offset_ptr pointing to \p p
      ///
      /// \param p the pointer
      offset_ptr( pointer p ) noexcept;
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      offset_ptr( U* p ) noexcept;
      /// \}

      /// \brief Copy-constructs an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to copy
      offset_ptr( const offset_ptr& other ) noexcept = default;

      /// \brief Move-constructs an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to move
      offset_ptr( offset_ptr&& other ) noexcept;

      /// \brief Copy-converts an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to copy
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      offset_ptr( const offset_ptr<U>& other ) noexcept;

      /// \brief Move-converts an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to move
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      offset_ptr( offset_ptr<U>&& other ) noexcept;

      //----------------------------------------------------------------------

      /// \{
      /// \brief Assigns a new pointer \p p to this offset_ptr
      ///
      /// \param p the pointer
      /// \return reference to \c (*this)
      offset_ptr& operator=( pointer p ) noexcept;
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      offset_ptr& operator=( U* p ) noexcept;
      /// \}

      /// \brief Copy-assigns an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to copy
      /// \return reference to \c (*this)
      offset_ptr& operator=( const offset_ptr& other ) noexcept = default;

      /// \brief Move-assigns an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to move
      /// \return reference to \c (*this)
      offset_ptr& operator=( offset_ptr&& other ) noexcept;

      /// \brief Copy-converts an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to copy convert
      /// \return reference to \c (*this)
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      offset_ptr& operator=( const offset_ptr<U>& other ) noexcept;

      /// \brief Move-converts an offset_ptr from another offset_ptr
      ///
      /// \param other the other offset_ptr to move convert
      /// \return reference to \c (*this)
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      offset_ptr& operator=( offset_ptr<U>&& other ) noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Resets this offset_ptr to a nullptr
      void reset() noexcept;

      /// \brief Resets this offset_ptr to point to the new pointer \p p
      ///
      /// \param p the pointer
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* p ) noexcept;

      /// \brief Swaps this offset_ptr with the \p other
      ///
      /// \param other the other offset_ptr to swap
      void swap( offset_ptr& other ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the underlying pointer
      ///
      /// \return the underlying pointer
      element_type* get() const noexcept;

      /// \brief Dereferences the offset_ptr
      ///
      /// \note UB if the pointer is invalid
      ///
      /// \return reference to the pointed element
      element_type& operator*() const noexcept;

      /// \brief Dereferences the offset_ptr
      ///
      /// \note UB if the pointer is invalid
      ///
      /// \return pointer to the element
      element_type* operator->() const noexcept;

      /// \brief Convertible to bool
      ///
      /// \return \c true if this pointer is non-null
      explicit operator bool() const noexcept;

      /// \brief Returns the underlying offset
      ///
      /// \return the offset of this pointer
      std::ptrdiff_t offset() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      std::ptrdiff_t m_offset;

      template<typename> friend class offset_ptr;

      //----------------------------------------------------------------------
      // Private Utilities
      //----------------------------------------------------------------------
    private:

      /// \brief Calculates the offset from \p lhs to \p rhs
      ///
      /// \param lhs the left pointer
      /// \param rhs the right pointer
      /// \return the offset, in bytes
      template<typename U, typename V>
      static std::ptrdiff_t calculate_offset( U* lhs, V* rhs ) noexcept;

      /// \brief Calculates the address from the current offset
      ///
      /// \note This overload is the const variant
      ///
      /// \return the pointer to the entry
      T* calculate_address( std::true_type ) const noexcept;

      /// \brief Calculates the address from the current offset
      ///
      /// \note This overload is the non-const variant
      ///
      /// \return the pointer to the entry
      T* calculate_address( std::false_type ) const noexcept;
    };

    //------------------------------------------------------------------------
    // Utilities
    //------------------------------------------------------------------------

    /// \brief Swaps the instances of two offset_ptr
    ///
    /// \param lhs the left pointer to swap
    /// \param rhs the right pointer to swap
    template<typename T>
    void swap( offset_ptr<T>& lhs, offset_ptr<T>& rhs ) noexcept;

    /// \brief Hashes a offset_ptr
    ///
    /// \param val the ptr to hash
    /// \return the hash of the unique_ptr
    template<typename T>
    std::size_t hash_value( const offset_ptr<T>& val ) noexcept;

    inline namespace casts {

      /// \brief Performs a static_cast on the underlying fat_ptr type
      ///
      /// \param other the other pointer to cast
      /// \return the newly casted pointer
      template<typename To, typename From>
      offset_ptr<To> static_pointer_cast( const offset_ptr<From>& other ) noexcept;

      /// \brief Performs a dynamic_cast on the underlying fat_ptr type
      ///
      /// \param other the other pointer to cast
      /// \return the newly casted pointer
      template<typename To, typename From>
      offset_ptr<To> dynamic_pointer_cast( const offset_ptr<From>& other ) noexcept;

      /// \brief Performs a const_cast on the underlying fat_ptr type
      ///
      /// \param other the other pointer to cast
      /// \return the newly casted pointer
      template<typename To, typename From>
      offset_ptr<To> const_pointer_cast( const offset_ptr<From>& other ) noexcept;

      /// \brief Performs a reinterpret_cast on the underlying fat_ptr type
      ///
      /// \param other the other pointer to cast
      /// \return the newly casted pointer
      template<typename To, typename From>
      offset_ptr<To> reinterpret_pointer_cast( const offset_ptr<From>& other ) noexcept;

    } // inline namespace casts

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    template<typename T, typename U>
    bool operator == ( const offset_ptr<T>& lhs, const offset_ptr<U>& rhs ) noexcept;

    template<typename T, typename U>
    bool operator == ( const offset_ptr<T>& lhs, const U* rhs ) noexcept;

    template<typename T, typename U>
    bool operator == ( const T* lhs, const offset_ptr<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    bool operator != ( const offset_ptr<T>& lhs, const offset_ptr<U>& rhs ) noexcept;

    template<typename T, typename U>
    bool operator != ( const offset_ptr<T>& lhs, const U* rhs ) noexcept;

    template<typename T, typename U>
    bool operator != ( const T* lhs, const offset_ptr<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    bool operator < ( const offset_ptr<T>& lhs, const offset_ptr<U>& rhs ) noexcept;

    template<typename T, typename U>
    bool operator < ( const offset_ptr<T>& lhs, const U* rhs ) noexcept;

    template<typename T, typename U>
    bool operator < ( const T* lhs, const offset_ptr<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    bool operator > ( const offset_ptr<T>& lhs, const offset_ptr<U>& rhs ) noexcept;

    template<typename T, typename U>
    bool operator > ( const offset_ptr<T>& lhs, const U* rhs ) noexcept;

    template<typename T, typename U>
    bool operator > ( const T* lhs, const offset_ptr<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    bool operator <= ( const offset_ptr<T>& lhs, const offset_ptr<U>& rhs ) noexcept;

    template<typename T, typename U>
    bool operator <= ( const offset_ptr<T>& lhs, const U* rhs ) noexcept;

    template<typename T, typename U>
    bool operator <= ( const T* lhs, const offset_ptr<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    bool operator >= ( const offset_ptr<T>& lhs, const offset_ptr<U>& rhs ) noexcept;

    template<typename T, typename U>
    bool operator >= ( const offset_ptr<T>& lhs, const U* rhs ) noexcept;

    template<typename T, typename U>
    bool operator >= ( const T* lhs, const offset_ptr<U>& rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/offset_ptr.inl"

#endif // BIT_STL_MEMORY_OFFSET_PTR_HPP
