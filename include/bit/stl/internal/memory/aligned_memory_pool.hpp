#ifndef BIT_STL_INTERNAL_MEMORY_ALIGNED_MEMORY_POOL_HPP
#define BIT_STL_INTERNAL_MEMORY_ALIGNED_MEMORY_POOL_HPP

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A type to use as storage for an object of at most \p Len bytes,
    ///        aligned as specified by \p Align.
    ///
    /// The obtained type is aliased by \a AlignedMemoryPool::type
    ///
    /// This class acts as a thin wrapper around memory, allowing it to know
    /// its own size, its own boundaries, and provide std-style iterators in
    /// order to easily iterate through all values in the memory space
    ///
    /// If \p Align is omitted, it is assumed to be alignable to any boundary
    /// (e.g. \p Align = 1)
    ///
    /// bit::AlignedMemoryPool can only be default-constructed or moved, but
    /// once initialized cannot be re-assigned.
    ///
    /// \tparam Size  the size of the aligned_memory_pool
    /// \tparam Align The alignment of the aligned_memory_pool
    ///
    /// \ingroup memory
    //////////////////////////////////////////////////////////////////////////
    template<std::size_t Len, std::size_t Align = alignof(std::max_align_t)>
    class aligned_memory_pool final
    {
      static_assert((Align & (Align-1)) == 0, "Alignment must be power of 2!");

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type       = byte;                 ///< The type of data in this memory pool
      using pointer            = element_type*;        ///< Pointers of the memory type
      using const_pointer      = const element_type*;  ///< Constant pointer of the memory type
      using void_pointer       = void*;                ///< Pointer to void
      using const_void_pointer = const void*;          ///< Constant pointer to void

      using size_type          = std::size_t;          ///< Type representing the size

      //----------------------------------------------------------------------
      // Constructors / Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Allow default-construction of aligned_memory_pool
      constexpr aligned_memory_pool() = default;

      /// \brief Allow moving of aligned_memory_pool
      constexpr aligned_memory_pool( aligned_memory_pool&& ) = default;

      /// \brief Disallow copying of aligned_memory_pool
      constexpr aligned_memory_pool( const aligned_memory_pool& ) = delete;

      /// \brief Disallow copy assignment
      aligned_memory_pool& operator = ( const aligned_memory_pool& ) = delete;

      /// \brief Disallow move assignment
      aligned_memory_pool& operator = ( aligned_memory_pool&& ) = delete;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the size of this \a Aligned_Memory_Pool
      ///
      /// \return the size of this pool
      constexpr size_type size() const noexcept;

      /// \brief  Gets the alignment of this \a Aligned_Memory_Pool
      ///
      /// \return the alignment of this pool
      constexpr size_type align() const noexcept;

      //----------------------------------------------------------------------
      // Member Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the starting address of this Aligned_Memory_Pool's memory
      ///
      /// \return the starting address
      constexpr const_pointer start_address() const noexcept;

      /// \brief Gets the ending address of this Aligned_Memory_Pool's memory
      ///
      /// \return the ending address
      constexpr const_pointer end_address() const noexcept;

      /// \brief Checks if a pointer is in range of this Aligned_Memory_Pool's memory
      ///
      /// \return true if the pointer is in range, false otherwise
      constexpr bool in_region( const void_pointer address ) const noexcept;

      /// \brief Returns a pointer to the memory mapped to this Aligned_Memory_Pool
      ///
      /// \return a pointer to the memory
      constexpr void_pointer ptr() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      alignas(Align) mutable byte m_memory[Len]; ///< The aligned memory
    };

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_MEMORY_ALIGNED_MEMORY_POOL_HPP */
