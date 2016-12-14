/**
 * \file indirect_ptr.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_INTERNAL_MEMORY_INDIRECT_PTR_HPP
#define BIT_STL_INTERNAL_MEMORY_INDIRECT_PTR_HPP

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An indirect pointer wherein dereferences provide the value
    ///        pointed at by the given pointer
    ///
    ///
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

    //------------------------------------------------------------------------
    // Constructor
    //------------------------------------------------------------------------

    template<typename T>
    inline constexpr indirect_ptr<T>::indirect_ptr()
      noexcept
      : m_ptr(nullptr)
    {

    }

    template<typename T>
    inline constexpr indirect_ptr<T>::indirect_ptr( T* ptr )
      noexcept
      : m_ptr(ptr)
    {

    }

    //------------------------------------------------------------------------
    // Modifiers
    //------------------------------------------------------------------------

    template<typename T>
    inline constexpr void indirect_ptr<T>::swap( indirect_ptr<T>& rhs )
      noexcept
    {
      using std::swap;
      swap(m_ptr,rhs.m_ptr);
    }

    //------------------------------------------------------------------------
    // Observers
    //------------------------------------------------------------------------

    template<typename T>
    inline constexpr typename indirect_ptr<T>::element_type*
      indirect_ptr<T>::get()
      const noexcept
    {
      return m_ptr;
    }

    template<typename T>
    inline constexpr typename indirect_ptr<T>::element_type&
      indirect_ptr<T>::operator*()
      const noexcept
    {
      return dereference(m_ptr);
    }

    template<typename T>
    inline constexpr typename indirect_ptr<T>::element_type*
      indirect_ptr<T>::operator->()
      const noexcept
    {
      return std::addressof(dereference(m_ptr));
    }

    template<typename T>
    inline constexpr typename indirect_ptr<T>::element_type&
      indirect_ptr<T>::operator[]( std::ptrdiff_t n )
      const noexcept
    {
      return m_ptr[n];
    }

    template<typename T>
    inline constexpr indirect_ptr<T>::operator bool()
      const noexcept
    {
      return static_cast<bool>(m_ptr);
    }

    //------------------------------------------------------------------------
    // Mutators
    //------------------------------------------------------------------------

    template<typename T>
    inline constexpr void swap( indirect_ptr<T>& lhs, indirect_ptr<T>& rhs )
      noexcept
    {
      lhs.swap(rhs);
    }

    //------------------------------------------------------------------------
    // Observers
    //------------------------------------------------------------------------

    template<typename T>
    inline constexpr indirect_ptr<T>& indirect_ptr<T>::operator+=( std::ptrdiff_t n )
      noexcept
    {
      m_ptr += n;
      return (*this);
    }

    template<typename T>
    inline constexpr indirect_ptr<T>& indirect_ptr<T>::operator-=( std::ptrdiff_t n )
      noexcept
    {
      m_ptr -= n;
      return (*this);
    }

    template<typename T>
    inline constexpr indirect_ptr<T>& indirect_ptr<T>::operator++()
      noexcept
    {
      ++m_ptr;
      return (*this);
    }

    template<typename T>
    inline constexpr indirect_ptr<T> indirect_ptr<T>::operator++(int)
      noexcept
    {
      return indirect_ptr<T>(m_ptr++);
    }

    template<typename T>
    inline constexpr indirect_ptr<T>& indirect_ptr<T>::operator--()
      noexcept
    {
      --m_ptr;
      return (*this);
    }

    template<typename T>
    inline constexpr indirect_ptr<T> indirect_ptr<T>::operator--(int)
      noexcept
    {
      return indirect_ptr<T>(m_ptr--);
    }

    //------------------------------------------------------------------------
    // Equality
    //------------------------------------------------------------------------

    template<typename T>
    inline bool operator==( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs )
      noexcept
    {
      return lhs.get() == rhs.get();
    }

    template<typename T>
    bool operator!=( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs )
      noexcept
    {
      return lhs.get() != rhs.get();
    }

    template<typename T>
    bool operator< ( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs )
      noexcept
    {
      return lhs.get() < rhs.get();
    }

    template<typename T>
    bool operator<=( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs )
      noexcept
    {
      return lhs.get() <= rhs.get();
    }

    template<typename T>
    bool operator> ( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs )
      noexcept
    {
      return lhs.get() > rhs.get();
    }

    template<typename T>
    bool operator>=( const indirect_ptr<T>& lhs, const indirect_ptr<T>& rhs )
      noexcept
    {
      return lhs.get() >= rhs.get();
    }


  } // inline namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_MEMORY_INDIRECT_PTR_HPP */
