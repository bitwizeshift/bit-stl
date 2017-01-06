#ifndef BIT_INTERNAL_MEMORY_STD_ALLOCATOR_INL
#define BIT_INTERNAL_MEMORY_STD_ALLOCATOR_INL

namespace bit {
  namespace stl {

    //---------------------------------------------------------------------------
    // Constructors
    //---------------------------------------------------------------------------

    template<typename T, typename Allocator>
    std_allocator<T,Allocator>::std_allocator( Allocator& alloc )
      noexcept
      : m_allocator(alloc)
    {

    }

    // --------------------------------------------------------------------------

    template<typename T, typename Allocator>
    template<typename U, typename Alloc2>
    std_allocator<T,Allocator>::std_allocator( const std_allocator<U,Alloc2>& alloc )
      noexcept
      : m_allocator( alloc.m_allocator )
    {

    }

    //---------------------------------------------------------------------------
    // Allocation / Deallocation
    //---------------------------------------------------------------------------

    template<typename T, typename Allocator>
    typename std_allocator<T,Allocator>::pointer
    std_allocator<T,Allocator>::allocate( size_type n )
    {
      pointer ptr = static_cast<pointer>( m_allocator.alloc( sizeof(T)*n, alignof(T), 0 ) );
#if BIT_COMPILER_EXCEPTIONS_ENABLED
      if(!ptr) throw std::bad_alloc();
#endif
      return ptr;
    }

    //---------------------------------------------------------------------------

    template<typename T, typename Allocator>
    void std_allocator<T,Allocator>::deallocate( pointer p, size_type n )
    {
      m_allocator.deallocate( p );
    }

    //---------------------------------------------------------------------------
    // Construction / Destruction
    //---------------------------------------------------------------------------

    template<typename T, typename Allocator>
    void std_allocator<T,Allocator>::construct( pointer p, const_reference val )
    {
      // Call placement new to construct it
      ::new(static_cast<void*>(p)) T(val);
    }

    template<typename T, typename Allocator>
    template<typename U, typename... Args>
    void std_allocator<T,Allocator>::construct( U* p, Args&&... args )
    {
      // Call placement new to construct it
      ::new(static_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    //---------------------------------------------------------------------------

    template<typename T, typename Allocator>
    void std_allocator<T,Allocator>::destroy( pointer p )
    {
      // Explicitly call the destructor
      (static_cast<T*>(p))->~T();
    }

    template<typename T, typename Allocator>
    template<typename U>
    void std_allocator<T,Allocator>::destroy( U* p )
    {
      // Explicitly call the destructor
      p->~U();
    }

    template<typename T, typename Allocator>
    inline typename std_allocator<T,Allocator>::size_type
       std_allocator<T,Allocator>::max_size()
      const noexcept
    {
      return std::numeric_limits<size_type>::max();
    }

    template<typename T, typename Allocator>
    inline typename std_allocator<T,Allocator>::pointer
      std_allocator<T,Allocator>::address(reference x)
      const
    {
      return std::addressof(x);
    }

    template<typename T, typename Allocator>
    inline typename std_allocator<T,Allocator>::const_pointer
      std_allocator<T,Allocator>::address(const_reference x)
      const
    {
      return std::addressof(x);
    }

    //---------------------------------------------------------------------------
    // Global Operators
    //---------------------------------------------------------------------------

    template <typename T, typename U, typename Allocator>
    inline bool operator==( const std_allocator<T,Allocator>& lhs,
                            const std_allocator<U,Allocator>& rhs)
    {
      return (&lhs.m_allocator)==(&rhs.m_allocator);
    }

    template<typename T, typename U, typename Allocator1, typename Allocator2>
    inline bool operator!=( const std_allocator<T,Allocator1>& lhs,
                            const std_allocator<U,Allocator2>& rhs )
    {
      return (&lhs.m_allocator)!=(&rhs.m_allocator);
    }


  }  // namespace stl
}  // namespace bit

#endif /* BIT_INTERNAL_MEMORY_STD_ALLOCATOR_INL */
