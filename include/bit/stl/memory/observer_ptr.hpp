/**
 * \file observer_ptr.hpp
 *
 * \brief This header contains a dummy smart-pointer, whose sole purpose
 *        is to behave like a well-defined raw-pointer.
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
#ifndef BIT_STL_MEMORY_OBSERVER_PTR_HPP
#define BIT_STL_MEMORY_OBSERVER_PTR_HPP

#include <cstddef>     // std::nullptr_t, std::size_t
#include <type_traits> // std::true_type, std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T>
      struct is_ptr_observable
      {
        template<typename U>
        static auto test( U* t )
          -> decltype(std::declval<const void*>() = t->get(), std::true_type{});

        static auto test(...) -> std::false_type;

        static constexpr bool value = decltype(test( std::declval<T*>() ))::value;
      };

      template<typename T>
      using make_observer_element_type_t
        = std::remove_pointer_t<std::decay_t<decltype(std::declval<T>().get())>>;

    } // namespace detail

    //////////////////////////////////////////////////////////////////////////
    /// \brief A lightweight wrapper around a pointer type
    ///
    /// This is essentially a 'dumb' smart pointer, in that it behaves
    /// identically to a raw pointer, but exposes a smart-pointer API with
    /// raw-pointer semantics.
    ///
    /// \tparam the underlying pointer type
    /// \satisfies{NullablePointer}
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class observer_ptr
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using pointer      = T*; ///< The underlying pointer type
      using element_type = T;  ///< The element type

      //----------------------------------------------------------------------
      // Constructors / Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs an observer_ptr to \c nullptr
      constexpr observer_ptr() noexcept;

      /// \brief Constructs an observer_ptr pointing to \c nullptr
      constexpr observer_ptr( std::nullptr_t ) noexcept;

      /// \brief Constructs an observer_ptr that points to \p ptr
      ///
      /// \param ptr the pointer value
      constexpr explicit observer_ptr( pointer ptr ) noexcept;

      /// \brief Copy-converts an observer_ptr from another one that points
      ///        to U
      ///
      /// \param other the other pointer to copy convert
      template<typename U, std::enable_if<std::is_convertible<U*,T*>::value>* = nullptr>
      constexpr observer_ptr( const observer_ptr<U>& other ) noexcept;

      /// \brief Move-converts an observer_ptr from another one that points
      ///        to U
      ///
      /// \param other the other pointer to move convert
      template<typename U, std::enable_if<std::is_convertible<U*,T*>::value>* = nullptr>
      observer_ptr( observer_ptr<U>&& other ) noexcept;

      /// \brief Copy-constructs an observer_ptr from another one
      ///
      /// \param other the other observer_ptr to copy
      constexpr observer_ptr( const observer_ptr& other ) noexcept = default;

      /// \brief Move-constructs an observer_ptr from another one
      ///
      /// \param other the other observer_ptr to move
      observer_ptr( observer_ptr&& other ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Assigns this observer_ptr to \c nullptr
      ///
      /// \return reference to \c (*this)
      observer_ptr& operator=( std::nullptr_t ) noexcept;

      /// \brief Copy-assigns an observer_ptr from another one
      ///
      /// \param other the other observer_ptr to copy
      /// \return reference to \c (*this)
      observer_ptr& operator=( const observer_ptr& other ) noexcept = default;

      /// \brief Move-assigns an observer_ptr from another one
      ///
      /// \param other the other observer_ptr to move
      /// \return reference to \c (*this)
      observer_ptr& operator=( observer_ptr&& other ) noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Resets this observer_ptr to point to \p ptr
      ///
      /// \param ptr the pointer to reset to
      void reset( pointer ptr = pointer() ) noexcept;

      /// \brief Resets this observer_ptr to \c nullptr
      void reset( std::nullptr_t ) noexcept;

      /// \brief Swaps this observer_ptr with another observer_ptr
      ///
      /// \param other the other observer_ptr
      void swap( observer_ptr& other ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the underlying pointer
      ///
      /// \return the underlying pointer
      constexpr pointer get() const noexcept;

      /// \brief Explicitly convertible to bool. This is \c true when the
      ///        underlying pointer is non-null
      constexpr explicit operator bool() const noexcept;

      /// \brief Dereferences the observer_ptr
      ///
      /// \return the underlying pointer
      constexpr pointer operator->() const noexcept;

      /// \brief Dereferences the observer_ptr
      ///
      /// \return the underlying reference
      constexpr std::add_lvalue_reference_t<T> operator*() const noexcept;

      //----------------------------------------------------------------------
      // Conversions
      //----------------------------------------------------------------------
    public:

      /// \brief Explicitly convertible to pointer type
      constexpr explicit operator element_type*() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      T* m_ptr; ///< The underlying pointer
    };

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps the observer_ptr \p lhs with \p rhs
    ///
    /// \param lhs the left one to swap
    /// \param rhs the right one to swap
    template<typename T>
    void swap( observer_ptr<T>& lhs, observer_ptr<T>& rhs ) noexcept;

    /// \brief Hashes this observer_ptr
    ///
    /// \param val the value to hash
    /// \return the hash of the underlying pointer
    template<typename T>
    std::size_t hash_value( const observer_ptr<T>& val ) noexcept;

    /// \brief Makes an observer_ptr from a raw pointer
    ///
    /// \param ptr the pointer
    /// \return an observer_ptr
    template<typename T>
    constexpr observer_ptr<T> make_observer( T* ptr ) noexcept;

    /// \brief Makes an observer_ptr from a raw pointer, and coerces it to
    ///        the specified type
    ///
    /// \tparam T the type to convert to
    /// \param ptr the pointer
    /// \return an observer_ptr
    template<typename T, typename U, std::enable_if_t<!std::is_same<T,U>::value && std::is_convertible<U*,T*>::value>* = nullptr>
    constexpr observer_ptr<T> make_observer( U* ptr ) noexcept;

    /// \brief Makes an observer_ptr from a smart pointer
    ///
    /// \param ptr the pointer
    /// \return an observer_ptr
    template<typename Pointer>
    constexpr auto make_observer( const Pointer& ptr ) noexcept
      -> decltype( make_observer( ptr.get() ) );

    /// \brief Makes an observer_ptr from a smart pointer
    ///
    /// \tparam T explicit type of the pointer
    /// \param ptr the pointer
    /// \return an observer_ptr
    template<typename T, typename Pointer, std::enable_if<detail::is_ptr_observable<Pointer>::value>* = nullptr>
    constexpr observer_ptr<T> make_observer( const Pointer& ptr ) noexcept;

    inline namespace casts {

      /// \brief Creates a new instance of observer_ptr whose stored pointer
      ///        is the result of a static_cast
      ///
      /// \param ptr the pointer to static_cast
      /// \return the result of a static_cast
      template<typename T, typename U>
      constexpr observer_ptr<T> static_pointer_cast( const observer_ptr<U>& ptr ) noexcept;

      template<typename T, typename U>
      constexpr observer_ptr<T> dynamic_pointer_cast( const observer_ptr<U>& ptr ) noexcept;

      template<typename T, typename U>
      constexpr observer_ptr<T> const_pointer_cast( const observer_ptr<U>& ptr ) noexcept;

      template<typename T, typename U>
      constexpr observer_ptr<T> reinterpret_pointer_cast( const observer_ptr<T>& ptr ) noexcept;

    } // inline namespace casts

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr bool operator==( const observer_ptr<T>& lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U>
    constexpr bool operator!=( const observer_ptr<T>& lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U>
    constexpr bool operator<( const observer_ptr<T>& lhs,
                              const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U>
    constexpr bool operator>( const observer_ptr<T>& lhs,
                              const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U>
    constexpr bool operator<=( const observer_ptr<T>& lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U>
    constexpr bool operator>=( const observer_ptr<T>& lhs,
                               const observer_ptr<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator==( std::nullptr_t,
                               const observer_ptr<T>& rhs ) noexcept;
    template<typename T>
    constexpr bool operator==( const observer_ptr<T>& lhs,
                               std::nullptr_t ) noexcept;

    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
    constexpr bool operator==( const T* lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
    constexpr bool operator==( const observer_ptr<T>& lhs,
                               const U* rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator!=( std::nullptr_t,
                               const observer_ptr<T>& rhs ) noexcept;
    template<typename T>
    constexpr bool operator!=( const observer_ptr<T>& lhs,
                               std::nullptr_t ) noexcept;

    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
    constexpr bool operator!=( const T* lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
    constexpr bool operator!=( const observer_ptr<T>& lhs,
                               const U* rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator<( std::nullptr_t,
                              const observer_ptr<T>& rhs ) noexcept;
    template<typename T>
    constexpr bool operator<( const observer_ptr<T>& lhs,
                              std::nullptr_t ) noexcept;

    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
    constexpr bool operator<( const T* lhs,
                              const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
    constexpr bool operator<( const observer_ptr<T>& lhs,
                              const U* rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator>( std::nullptr_t,
                              const observer_ptr<T>& rhs ) noexcept;
    template<typename T>
    constexpr bool operator>( const observer_ptr<T>& lhs,
                              std::nullptr_t ) noexcept;

    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
    constexpr bool operator>( const T* lhs,
                              const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
    constexpr bool operator>( const observer_ptr<T>& lhs,
                              const U* rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator<=( std::nullptr_t,
                               const observer_ptr<T>& rhs ) noexcept;
    template<typename T>
    constexpr bool operator<=( const observer_ptr<T>& lhs,
                               std::nullptr_t ) noexcept;

    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
    constexpr bool operator<=( const T* lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
    constexpr bool operator<=( const observer_ptr<T>& lhs,
                               const U* rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator>=( std::nullptr_t,
                               const observer_ptr<T>& rhs ) noexcept;
    template<typename T>
    constexpr bool operator>=( const observer_ptr<T>& lhs,
                               std::nullptr_t ) noexcept;

    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<T*,U*>::value>>
    constexpr bool operator>=( const T* lhs,
                               const observer_ptr<U>& rhs ) noexcept;
    template<typename T, typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
    constexpr bool operator>=( const observer_ptr<T>& lhs,
                               const U* rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/observer_ptr.inl"

#endif /* BIT_STL_MEMORY_OBSERVER_PTR_HPP */
