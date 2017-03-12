#ifndef BIT_STL_INTERNAL_MEMORY_OBSERVER_PTR_HPP
#define BIT_STL_INTERNAL_MEMORY_OBSERVER_PTR_HPP

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An observer pointer is a vocabulary type intended to be a
    ///        drop-in replacement for non-owning raw pointers.
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class observer_ptr
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = T;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an observer_ptr that has no corresponding watched
      ///        object
      constexpr observer_ptr();

      /// \brief Constructs an observer_ptr that has no corresponding watched
      ///        object
      ///
      /// \param null a nullptr
      constexpr observer_ptr( std::nullptr_t null );

      /// \brief Constructs an observer_ptr from a given pointer
      ///
      /// \param ptr the pointer
      constexpr observer_ptr( element_type* ptr );

      /// \brief Constructs an observer_ptr from another, convertible
      ///        observer_ptr
      ///
      /// \param ptr the observer_ptr to convert
      template<typename U>
      constexpr observer_ptr( observer_ptr<U> ptr );

      /// \brief Copy-constructs this observer_ptr from another
      ///
      /// \param other the other observer_ptr to copy
      constexpr observer_ptr( const observer_ptr& other ) = default;

      /// \brief Move-constructs this observer_ptr from another
      ///
      /// \param other the other observer_ptr to move
      constexpr observer_ptr( observer_ptr&& other ) = default;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      constexpr void reset(element_type* p = nullptr) noexcept;

      constexpr void swap(observer_ptr& other) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      constexpr element_type* get() const noexcept;

      constexpr explicit operator bool() const noexcept;

      constexpr element_type& operator*() const;

      constexpr element_type* operator->() const noexcept;

      //----------------------------------------------------------------------
      // Conversions
      //----------------------------------------------------------------------
    public:

      constexpr explicit operator element_type*() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      element_type* m_ptr;
    };

    /// \brief Makes an observer pointer from another pointer
    ///
    /// \param ptr the pointer to make an observer
    /// \return an observer pointer
    template<typename T>
    constexpr observer_ptr<T> make_observer( T* ptr ) noexcept;

    /// \brief Swaps two observer_ptr
    ///
    /// \param lhs the left observer_ptr
    /// \param rhs the right observer_ptr
    template<typename T>
    void swap( observer_ptr<T>& lhs, observer_ptr<T>& rhs ) noexcept;

    /// \brief Hashes the current observer pointer
    ///
    /// \param val the value to hash
    /// \return the hash of the observer_ptr
    template<typename T>
    std::size_t hash_value( const observer_ptr<T>& val ) noexcept;

  } // namespace stl
} // namespace bit

#include "observer_ptr.inl"

#endif /* BIT_STL_INTERNAL_MEMORY_OBSERVER_PTR_HPP */
