/**
 * \file clone_ptr.hpp
 *
 * \brief This header contains an implementation of a smart pointers that
 *        clones pointers on copy.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
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
#ifndef BIT_STL_MEMORY_CLONE_PTR_HPP
#define BIT_STL_MEMORY_CLONE_PTR_HPP

#include "allocator_deleter.hpp"

#include "../utilities/utility.hpp"         //
#include "../utilities/compressed_pair.hpp" // compressed_pair

#include <memory>  // std::allocator, std::allocator_traits
#include <cstddef> // std::size_t

namespace bit {
  namespace stl {
    namespace detail {

      ////////////////////////////////////////////////////////////////////////
      /// \brief
      ///
      ////////////////////////////////////////////////////////////////////////
      class clone_ptr_base
      {
        //--------------------------------------------------------------------
        // Destructor
        //--------------------------------------------------------------------
      public:

        virtual ~clone_ptr_base() = default;

        //--------------------------------------------------------------------
        //
        //--------------------------------------------------------------------
      public:

        virtual void* get_deleter( const std::type_info& info ) noexcept = 0;

        virtual clone_ptr_base* clone() = 0;

        virtual void destroy() = 0;
      };

      ////////////////////////////////////////////////////////////////////////
      /// \brief
      ///
      ////////////////////////////////////////////////////////////////////////
      template<typename T, typename Deleter, typename Allocator>
      class clone_ptr_pointer : public clone_ptr_base
      {
        //--------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------
      public:

        clone_ptr_pointer( T* pointer, const Deleter& deleter, const Allocator& allocator );

        //--------------------------------------------------------------------
        //
        //--------------------------------------------------------------------
      public:

        void* get_deleter( const std::type_info& info ) noexcept override;

        clone_ptr_base* clone() override;

        void destroy() override;

        //--------------------------------------------------------------------
        // Private Member Types
        //--------------------------------------------------------------------
      private:

        using compressed_storage = compressed_pair<compressed_pair<T*,Allocator>,Deleter>;

        //--------------------------------------------------------------------
        // Private Members
        //--------------------------------------------------------------------
      private:

        compressed_storage m_storage;

      };

      ////////////////////////////////////////////////////////////////////////
      /// \brief
      ///
      ////////////////////////////////////////////////////////////////////////
      template<typename T, typename Allocator>
      class clone_ptr_emplace : public clone_ptr_base
      {
        //--------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------
      public:

        template<typename...Args>
        clone_ptr_emplace( Allocator alloc, Args&&...args );

        //--------------------------------------------------------------------
        //
        //--------------------------------------------------------------------
      public:

        void* get_deleter( const std::type_info& info ) noexcept override;

        clone_ptr_base* clone() override;

        void destroy() override;

        T* get() noexcept;

        //--------------------------------------------------------------------
        // Private Member Types
        //--------------------------------------------------------------------
      private:

        using compressed_storage = compressed_pair<Allocator,T>;

        //--------------------------------------------------------------------
        // Private Members
        //--------------------------------------------------------------------
      private:

        compressed_storage m_storage;
      };

    } // namespace detail


    //////////////////////////////////////////////////////////////////////////
    /// \brief clone_ptr is a smart pointer that owns and manages another
    ///        object through a pointer and disposes of that object when the
    ///        clone_ptr goes out of scope
    ///
    /// Like unique_ptr, clone_ptr owns unique instances of objects; no two
    /// clone_ptrs should ever point to the same instance. Unlike unique_ptr,
    /// clone_ptr is copyable -- wherein the underlying type's copy-constructor
    /// is invoked, and the new object is allocated.
    ///
    /// Instead of requiring the Deleter type, this class requires knowledge
    /// of both the allocation *and* deallocation scheme -- and thus requires
    /// the Allocator itself.
    ///
    /// \note No attempt has been made for this class to support the T[]
    ///       specialization, since the \c Allocator concept requires the
    ///       size of the originally allocated array to perform deallocations.
    ///       This would require carrying along an extra size argument to
    ///       properly deallocate, and provides more complications than
    ///       benefits
    ///
    /// \bug Currently this marks functions as 'noexcept', when they should be
    ///      marked 'noexcept(std::is_nothrow_copyable<Allocator>::value)' and
    ///      'noexcept(std::is_nothrow_default_constructible<Allocator>::value)'
    ///
    /// \tparam T the type this clone_ptr manages
     //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class clone_ptr
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type   = T;
      using pointer        = T*;

      //----------------------------------------------------------------------
      // Constructor / Assignment
      //----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Constructs a clone_ptr with no managed object
      clone_ptr() noexcept;
      clone_ptr( std::nullptr_t ) noexcept;
      /// \}

      /// \brief Constructs a clone_ptr that manages \p ptr
      ///
      /// \param ptr the pointer to manage
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      explicit clone_ptr( U* ptr ) noexcept;

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( U* ptr, Deleter deleter );

      template<typename Deleter, typename Allocator>
      clone_ptr( std::nullptr_t, Deleter deleter );

      template<typename U, typename Deleter, typename Allocator, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( U* ptr, Deleter deleter, Allocator alloc );

      template<typename Deleter, typename Allocator>
      clone_ptr( std::nullptr_t, Deleter deleter, Allocator allocator );

      /// \brief Constructs a clone_ptr from an existing clone_ptr
      ///
      /// \param other the other clone_ptr to copy
      clone_ptr( const clone_ptr& other );

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( const clone_ptr<U>& other );

      /// \brief Constructs a clone_ptr from an existing cone_ptr
      ///
      /// \param other the other clone_ptry to copy
      clone_ptr( clone_ptr&& other ) noexcept;

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( clone_ptr<U>&& other ) noexcept;

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( std::unique_ptr<U,Deleter>&& other ) noexcept;


      //----------------------------------------------------------------------

      ~clone_ptr();

      //----------------------------------------------------------------------

      clone_ptr& operator=( const clone_ptr& other );

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr& operator=( const clone_ptr<U>& other );

      clone_ptr& operator=( clone_ptr&& other ) noexcept;

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr& operator=( clone_ptr<U>&& other ) noexcept;

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr& operator=( std::unique_ptr<U,Deleter>&& other );

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      void reset() noexcept;

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* ptr );

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* ptr, Deleter deleter );

      template<typename U, typename Deleter, typename Allocator, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* ptr, Deleter deleter, Allocator alloc );

      void swap( clone_ptr& other ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      pointer get() const noexcept;

      explicit operator bool() const noexcept;

      std::add_lvalue_reference_t<T> operator*() const noexcept;

      pointer operator->() const noexcept;

      //----------------------------------------------------------------------
      // Private Constructors
      //----------------------------------------------------------------------
    private:

      struct ctor_tag{};

      clone_ptr( ctor_tag, detail::clone_ptr_base* control_block, T* ptr ) noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      detail::clone_ptr_base* m_control_block;
      T*                      m_ptr;

      //----------------------------------------------------------------------
      // Private Utilities
      //----------------------------------------------------------------------
    private:

      void* get_deleter( const std::type_info& info ) const noexcept;

      void destroy();

      //----------------------------------------------------------------------
      // Friends
      //----------------------------------------------------------------------
    private:

      template<typename U, typename...Args>
      friend clone_ptr<U> make_clone( Args&&...args );

      template<typename U, typename Allocator, typename...Args>
      friend clone_ptr<U> allocate_clone( const Allocator&, Args&&...args );

      template<typename Deleter, typename U>
      friend Deleter* get_deleter( clone_ptr<U>& p ) noexcept;

      template<typename To, typename From>
      friend clone_ptr<To> static_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      friend clone_ptr<To> dynamic_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      friend clone_ptr<To> const_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      friend clone_ptr<To> reinterpret_pointer_cast( clone_ptr<From>&& other );

      template<typename U>
      friend class clone_ptr;
    };

    //------------------------------------------------------------------------
    // Utilities
    //------------------------------------------------------------------------

    /// \brief Swaps the contents of two clone_ptrs
    ///
    /// \param lhs the left clone_ptr
    /// \param rhs the right clone_ptr
    template<typename T>
    void swap( clone_ptr<T>& lhs, clone_ptr<T>& rhs ) noexcept;

    //------------------------------------------------------------------------


    template<typename T, typename...Args>
    clone_ptr<T> make_clone( Args&&...args );

    template<typename T, typename Allocator, typename...Args>
    clone_ptr<T> allocate_clone( const Allocator&, Args&&...args );

    /// \brief Access to the \c p's deleter.
    ///
    /// If the clone pointer \p p owns a deleter of type cv-unqualified
    /// \p Deleter (e.g. if it was created with one of the constructors that
    /// take a deleter as a parameter), then returns a pointer to the deleter.
    ///
    /// Otherwise, returns a null pointer.
    ///
    /// \param p the pointer
    /// \return the deleter
    template<typename Deleter, typename T>
    Deleter* get_deleter( const clone_ptr<T>& p ) noexcept;

    //------------------------------------------------------------------------
    // Casts
    //------------------------------------------------------------------------

    inline namespace casts {

      template<typename To, typename From>
      clone_ptr<To> static_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      clone_ptr<To> dynamic_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      clone_ptr<To> const_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      clone_ptr<To> reinterpret_pointer_cast( clone_ptr<From>&& other );

    } // inline namespace casts

  } // namespace stl
} // namespace bit

#include "detail/clone_ptr.inl"

#endif /* BIT_STL_MEMORY_CLONE_PTR_HPP */
