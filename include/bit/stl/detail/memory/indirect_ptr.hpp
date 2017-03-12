/**
 * \file indirect_ptr.hpp
 *
 * \brief This header contains a pointer used for multiple levels of
 *        indirection
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_STL_DETAIL_MEMORY_INDIRECT_PTR_HPP
#define BIT_STL_DETAIL_MEMORY_INDIRECT_PTR_HPP

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An indirect pointer wherein dereferences provide the value
    ///        pointed at by the given pointer
    ///
    /// \tparam T the underlying pointer type
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class indirect_ptr
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = std::remove_extent_t<T>;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a null indirect_ptr
      constexpr indirect_ptr() noexcept;

      /// \brief Constructs an indirect_ptr from a given pointer
      ///
      /// \param ptr the pointer to use for indirection
      constexpr indirect_ptr( T* ptr ) noexcept;

      /// \brief Copy-constructs an indirect_ptr
      ///
      /// \param other the other pointer to copy
      constexpr indirect_ptr( const indirect_ptr& other ) noexcept = default;

      /// \brief Move-constructs an indirect_ptr
      ///
      /// \param other the other pointer to move
      constexpr indirect_ptr( indirect_ptr&& other ) noexcept = default;

      /// \brief Copy-assigns an indirect_ptr
      ///
      /// \param other the other pointer to copy
      indirect_ptr& operator=( const indirect_ptr& other ) noexcept = default;

      /// \brief Move-assigns an indirect_ptr
      ///
      /// \param other the other pointer to move
      indirect_ptr& operator=( indirect_ptr&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this pointer with \p rhs
      ///
      /// \param rhs the pointer to swap with
      constexpr void swap( indirect_ptr& rhs ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      constexpr element_type* get() const noexcept;

      constexpr element_type& operator*() const noexcept;
      constexpr element_type* operator->() const noexcept;

      constexpr element_type& operator[]( std::ptrdiff_t n ) const noexcept;

      constexpr operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Arithmetic
      //----------------------------------------------------------------------
    public:

      constexpr indirect_ptr& operator+=( std::ptrdiff_t n ) noexcept;
      constexpr indirect_ptr& operator-=( std::ptrdiff_t n ) noexcept;

      constexpr indirect_ptr& operator++() noexcept;
      constexpr indirect_ptr operator++(int) noexcept;

      constexpr indirect_ptr& operator--() noexcept;
      constexpr indirect_ptr operator--(int) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      T* m_ptr;

    };

    //------------------------------------------------------------------------
    // Mutators
    //------------------------------------------------------------------------

    template<typename T>
    constexpr void swap( indirect_ptr<T>& lhs, indirect_ptr<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Observers
    //------------------------------------------------------------------------

    template<typename T>
    indirect_ptr<T> operator + ( const indirect_ptr<T>& lhs, std::ptrdiff_t rhs ) noexcept;

    template<typename T>
    indirect_ptr<T> operator + ( std::ptrdiff_t lhs, const indirect_ptr<T>& rhs ) noexcept;

    template<typename T>
    indirect_ptr<T> operator - ( const indirect_ptr<T>& lhs, std::ptrdiff_t rhs ) noexcept;

    //------------------------------------------------------------------------
    // Equality
    //------------------------------------------------------------------------

    template<typename T>
    bool operator==( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs ) noexcept;

    template<typename T>
    bool operator!=( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs ) noexcept;

    template<typename T>
    bool operator< ( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs ) noexcept;

    template<typename T>
    bool operator<=( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs ) noexcept;

    template<typename T>
    bool operator> ( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs ) noexcept;

    template<typename T>
    bool operator>=( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs ) noexcept;

  } // inline namespace stl
} // namespace bit

#include "indirect_ptr.inl"

#endif /* BIT_STL_DETAIL_MEMORY_INDIRECT_PTR_HPP */
