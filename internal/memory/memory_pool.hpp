/**
 * \file memory_pool.inl
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_INTERNAL_MEMORY_MEMORY_POOL_HPP
#define BIT_INTERNAL_MEMORY_MEMORY_POOL_HPP

namespace bit {
  inline namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \class bit::memory_pool
    ///
    /// \brief This class acts as a thin wrapper around memory, allowing it to
    ///        know its own size and boundary
    //////////////////////////////////////////////////////////////////////////
    class memory_pool
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type  = byte;                ///< The type of data in this memory pool
      using pointer       = element_type*;        ///< Pointers of the memory type
      using const_pointer = const element_type*;  ///< Constant pointer of the memory type
      using void_pointer       = void*;           ///< Pointer to void
      using const_void_pointer = const void*;     ///< Constant pointer to void

      using size_type     = std::size_t;          ///< Type representing the size

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default memory pool constructing a null pool
      constexpr memory_pool() noexcept;

      /// \brief Default memory pool constructing a null pool
      constexpr memory_pool( std::nullptr_t ) noexcept;

      /// \brief Copies the \p other memory_pool
      constexpr memory_pool( const memory_pool& other ) noexcept;

      /// \brief Moves the \p other memory_pool
      constexpr memory_pool( memory_pool&& other ) noexcept;

      /// \brief Constructs a memory_pool by providing the memory location and
      ///        size
      ///
      /// \param ptr  the pointer to the memory location
      /// \param size the size of the memory pool
      memory_pool( void_pointer ptr, size_type size ) noexcept;

      /// \brief Constructs a memory_pool out of any other type of pool
      ///
      /// \param pool the memory pool
      template<class Pool>
      constexpr memory_pool( Pool&& pool ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copies the \p other memory_pool
      memory_pool& operator = ( const memory_pool& other ) noexcept;

      /// \brief Moves the \p other memory_pool
      memory_pool& operator = ( memory_pool&& other ) noexcept;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the size of this \a memory_pool
      ///
      /// \return the size of this pool
      constexpr size_type size() const noexcept;

      /// \brief  Gets the alignment of this \a memory_pool
      ///
      /// \return the alignment of this pool
      constexpr size_type align() const noexcept;

      //----------------------------------------------------------------------
      // Member Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the starting address of this memory_pool's memory
      ///
      /// \return the starting address
      constexpr const_pointer start_address() const noexcept;

      /// \brief Gets the ending address of this memory_pool's memory
      ///
      /// \note The ending address is 1-past the end of the accessible memory
      ///
      /// \return the ending address
      constexpr const_pointer end_address() const noexcept;

      /// \brief Checks if a pointer is in range of this memory_pool
      ///
      /// This function works as if by calling:
      /// \code
      /// in_range( address, pool.start_address(), pool.end_address() )
      /// \endcode
      ///
      /// \return true if the pointer is in range, false otherwise
      constexpr bool contains( const void_pointer address ) const noexcept;

      /// \brief Returns a constant pointer to the memory mapped to this memory_pool
      ///
      /// \return a constant pointer to the memory
      constexpr void_pointer ptr() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      element_type* m_memory; ///< The address of this memory
      size_type     m_size;   ///< The size of this memory pool
      size_type     m_align;  ///< The alignment of this memory pool
    };

    //========================================================================
    // Inline Definitions
    //========================================================================

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------

    inline constexpr memory_pool::memory_pool()
      noexcept
      : m_memory( nullptr ),
        m_size( 0 ),
        m_align( 0 )
    {

    }

    inline constexpr memory_pool::memory_pool( std::nullptr_t )
      noexcept
      : memory_pool()
    {

    }

    inline constexpr memory_pool::memory_pool( const memory_pool& other )
      noexcept
      : m_memory( other.m_memory ),
        m_size( other.m_size ),
        m_align( other.m_align )
    {

    }

    inline constexpr memory_pool::memory_pool( memory_pool&& other )
      noexcept
      : m_memory( std::move(other.m_memory) ),
        m_size( other.m_size ),
        m_align( other.m_align )
    {
      other.m_memory = nullptr;
      other.m_size   = 0;
      other.m_align  = 0;
    }

    inline memory_pool::memory_pool( void_pointer ptr, size_type size )
      noexcept
      : m_memory( static_cast<byte*>( ptr ) ),
        m_size( size ),
        m_align( align_of(ptr) )
    {

    }

    template<class Pool>
    inline constexpr memory_pool::memory_pool( Pool&& pool )
      noexcept
      : m_memory( static_cast<bit::byte*>( pool.ptr()) ),
        m_size( pool.size() ),
        m_align( pool.align() )
    {

    }

    //------------------------------------------------------------------------
    // Assignment
    //------------------------------------------------------------------------

    memory_pool& memory_pool::operator = ( const memory_pool& other )
      noexcept
    {
      m_memory = other.m_memory;
      m_size   = other.m_size;
      m_align  = other.m_align;
      return (*this);
    }

    memory_pool& memory_pool::operator = ( memory_pool&& other )
      noexcept
    {
      m_memory = std::move(other.m_memory);
      m_size   = std::move(other.m_size);
      m_align  = std::move(other.m_align);

      other.m_memory = nullptr;
      other.m_size   = 0;
      other.m_align  = 0;
      return (*this);
    }


    //------------------------------------------------------------------------
    // Capacity
    //------------------------------------------------------------------------

    inline constexpr memory_pool::size_type memory_pool::size()
      const noexcept
    {
      return m_size;
    }

    inline constexpr memory_pool::size_type memory_pool::align()
      const noexcept
    {
      return m_align;
    }

    //------------------------------------------------------------------------
    // Member Access
    //------------------------------------------------------------------------

    inline constexpr memory_pool::const_pointer memory_pool::start_address()
      const noexcept
    {
      return (const_pointer) (m_memory);
    }

    inline constexpr memory_pool::const_pointer memory_pool::end_address()
      const noexcept
    {
      return (const_pointer) (m_memory + m_size);
    }

    inline constexpr bool memory_pool::contains( const void_pointer address )
      const noexcept
    {
      return in_region( address, start_address(), end_address() );
    }

    inline constexpr memory_pool::void_pointer memory_pool::ptr()
      const noexcept
    {
      return static_cast<void*>(m_memory);
    }
  } // inline namespace stl
} // namespace bit

#endif /* BIT_INTERNAL_MEMORY_MEMORY_POOL_HPP */
