#ifndef BIT_STL_INTERNAL_MEMORY_OBSERVER_PTR_HPP
#define BIT_STL_INTERNAL_MEMORY_OBSERVER_PTR_HPP

namespace bit {
  inline namespace stl {

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
      constexpr observer_ptr() = default;

      /// \brief Constructs an observer_ptr that has no corresponding watched
      ///        object
      ///
      /// \param null a nullptr
      constexpr observer_ptr( std::nullptr_t null );

      constexpr observer_ptr( element_type* ptr );

      template<typename U>
      constexpr observer_ptr( observer_ptr<U> ptr );

      constexpr observer_ptr( const observer_ptr& ) = default;

      constexpr observer_ptr( observer_ptr&& ) = default;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      constexpr void release() noexcept;

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

    template<typename T>
    void swap( observer_ptr<T>& lhs, observer_ptr<T>& rhs ) noexcept;


    template<typename T>
    std::size_t hash_value( const observer_ptr<T>& val ) noexcept;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_MEMORY_OBSERVER_PTR_HPP */
