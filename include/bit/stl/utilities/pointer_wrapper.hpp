/*****************************************************************************
 * \file
 * \brief This header contains a wrapper that makes a value type act like
 *        a pointer type.
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
#ifndef BIT_STL_UTILITIES_POINTER_WRAPPER_HPP
#define BIT_STL_UTILITIES_POINTER_WRAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "in_place.hpp" // in_place_t

#include <type_traits> // std::remove_extent_t, std::enable_if_t, etc
#include <utility>     // std::move, std::forward
#include <memory>      // std::addressof

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper type around a given type that allows it to be treated
    ///        with pointer-semantics instead of reference-semantics.
    ///
    /// The purpose of this class is to be used in place of 'pointer' types
    /// in containers that use them.
    ///
    /// \tparam T the underlying type
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class pointer_wrapper
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = std::remove_extent_t<T>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs the underlying type of the pointer_wrapper
      pointer_wrapper() = default;

      /// \brief Constructs a pointer wrapper that forwards all arguments to
      ///        the underlying type
      ///
      /// \param args
#ifndef BIT_DOXYGEN_BUILD
      template<typename...Args, std::enable_if_t<std::is_constructible<T,Args...>::value>* = nullptr>
#else
      template<typename...Args>
#endif
      explicit pointer_wrapper( in_place_t, Args&&...args )
        noexcept(std::is_nothrow_constructible<T,Args...>::value);

      /// \brief Copy constructs another pointer_wrapper
      ///
      /// \param other the other pointer_wrapper to copy construct
      pointer_wrapper( const pointer_wrapper& other ) = default;

      /// \brief Move constructs another pointer_wrapper
      ///
      /// \param other the other pointer_wrapper to move construct
      pointer_wrapper( pointer_wrapper&& other ) = default;

      /// \brief Copy converts a pointer_wrapper of a different underlying type
      ///
      /// \param other the other pointer_wrapper to copy
      template<typename U>
      pointer_wrapper( const pointer_wrapper<U>& other );

      /// \brief Move converts a pointer_wrapper of a different underlying type
      ///
      /// \param other the other pointer_wrapper to move
      template<typename U>
      pointer_wrapper( pointer_wrapper<U>&& other );

      //----------------------------------------------------------------------
      // Assignment Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a pointer_wrapper
      ///
      /// \param other the other pointer_wrapper to copy
      pointer_wrapper& operator=( const pointer_wrapper& other ) = default;

      /// \brief Move-assigns a pointer_wrapper
      ///
      /// \param other the other pointer_wrapper to move
      pointer_wrapper& operator=( pointer_wrapper&& other ) = default;

      /// \brief Copy-converts a pointer_wrapper of a different underlying type
      ///
      /// \param other the other pointer_wrapper to copy
      template<typename U>
      pointer_wrapper& operator=( const pointer_wrapper<U>& other );

      /// \brief Move-converts a pointer_wrapper of a different underlying type
      ///
      /// \param other the other pointer_wrapper to move
      template<typename U>
      pointer_wrapper& operator=( pointer_wrapper<U>&& other );

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets a pointer to the underlying type
      ///
      /// \return a pointer to the underlying type
      element_type* get() noexcept;

      /// \copydoc get()
      const element_type* get() const noexcept;

      /// \brief Converts the underlying instance to a pointer
      ///
      /// \return a pointer to the instance
      element_type* operator->() noexcept;

      /// \copydoc operator->()
      const element_type* operator->() const noexcept;

      /// \brief Dereferences the underlying instance
      ///
      /// \return a reference to the instance
      element_type& operator*() noexcept;

      /// \copydoc operator->()
      const element_type& operator*() const noexcept;

      /// \brief Checks if the stored instance is null
      ///
      /// This will never be \c false
      ///
      /// \return \c true
      operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      element_type m_instance; ///< The underlying instance

      template<typename> friend class pointer_wrapper;
    };

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Makes a pointer_wrapper of the underlying type
    ///
    /// \param args... the arguments to forward
    template<typename T, typename...Args>
    pointer_wrapper<T> make_pointer_wrapper( Args&&...args )
      noexcept( std::is_nothrow_constructible<T,Args...>::value );

  } // namespace stl
} // namespace bit

#include "detail/pointer_wrapper.inl"

#endif /* BIT_STL_UTILITIES_POINTER_WRAPPER_HPP */
