#ifndef BIT_STL_MEMORY_DETAIL_ALLOCATOR_DESTRUCTOR_INL
#define BIT_STL_MEMORY_DETAIL_ALLOCATOR_DESTRUCTOR_INL

//=============================================================================
// allocator_destructor
//=============================================================================

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

template<typename Allocator>
bit::stl::allocator_deleter<Allocator>
  ::allocator_deleter( Allocator& alloc, size_type size )
  noexcept
  : m_allocator(alloc),
    m_size(size)
{

}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename Allocator>
void bit::stl::allocator_deleter<Allocator>::operator()( pointer p )
  noexcept
{
  alloc_traits::destroy( m_allocator, p );
  alloc_traits::deallocate( m_allocator, p, m_size );
}

#endif /* BIT_STL_MEMORY_DETAIL_ALLOCATOR_DESTRUCTOR_INL */
