#ifndef BIT_STL_CONTAINERS_DETAIL_CIRCULAR_QUEUE_INL
#define BIT_STL_CONTAINERS_DETAIL_CIRCULAR_QUEUE_INL

//============================================================================
// circular_queue
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>::circular_queue()
  : circular_queue( Allocator() )
{

}

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( const Allocator& alloc )
  : circular_queue( 0, alloc )
{

}

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( size_type count, const T& value, const Allocator& alloc )
  : circular_queue( count, alloc )
{
  while(!full()) {
    m_storage.buffer().emplace_back(value);
  }
}

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( size_type count, const Allocator& alloc )
  : m_storage( count, alloc )
{

}

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( const circular_queue& other )
  : circular_queue( other.capacity(), other.get_allocator() )
{
  for(auto const& v : other.m_storage.buffer() ) {
    m_storage.buffer().emplace_back(v);
  }
}


template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( const circular_queue& other, const Allocator& alloc )
  : circular_queue( other.capacity(), alloc )
{
  for(auto const& v : other.m_storage.buffer() ) {
    m_storage.buffer().emplace_back(v);
  }
}


template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( circular_queue&& other )
  : circular_queue( std::move(other), other.get_allocator() )
{

}

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>
  ::circular_queue( circular_queue&& other, const Allocator& alloc )
  : m_storage( std::move(other.m_storage), alloc )
{

}

//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline bit::stl::circular_queue<T,Allocator>&
  bit::stl::circular_queue<T,Allocator>::operator=( circular_queue other )
  noexcept
{
  swap(*this,other);

  return (*this);
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::allocator_type
  bit::stl::circular_queue<T,Allocator>::get_allocator()
  const
{
  return m_storage.get_allocator();
}

//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::reference
  bit::stl::circular_queue<T,Allocator>::front()
  noexcept
{
  return m_storage.buffer().front();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_reference
  bit::stl::circular_queue<T,Allocator>::front()
  const noexcept
{
  return m_storage.buffer().front();
}

//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::reference
  bit::stl::circular_queue<T,Allocator>::back()
  noexcept
{
  return m_storage.buffer().back();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_reference
  bit::stl::circular_queue<T,Allocator>::back()
  const noexcept
{
  return m_storage.buffer().back();
}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline bool bit::stl::circular_queue<T,Allocator>::empty()
  const noexcept
{
  return m_storage.buffer().empty();
}

template<typename T, typename Allocator>
inline bool bit::stl::circular_queue<T,Allocator>::full()
  const noexcept
{
  return m_storage.buffer().full();
}

//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::size_type
  bit::stl::circular_queue<T,Allocator>::size()
  const noexcept
{
  return m_storage.buffer().size();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::size_type
  bit::stl::circular_queue<T,Allocator>::max_size()
  const noexcept
{
  return m_storage.buffer().max_size();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::size_type
  bit::stl::circular_queue<T,Allocator>::capacity()
  const noexcept
{
  return m_storage.buffer().capacity();
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline void bit::stl::circular_queue<T,Allocator>::resize( size_type n )
{
  if( m_storage.buffer().capacity() > n ) {
    return;
  }

  resize( std::is_nothrow_move_constructible<T>{}, n );
}

template<typename T, typename Allocator>
template<typename,typename>
inline void bit::stl::circular_queue<T,Allocator>
  ::push( const value_type& value )
{
  m_storage.buffer().push_back(value);
}

template<typename T, typename Allocator>
template<typename,typename>
inline void bit::stl::circular_queue<T,Allocator>::push( value_type&& value )
{
  m_storage.buffer().push_back( std::move(value) );
}

template<typename T, typename Allocator>
template<typename...Args, typename>
inline typename bit::stl::circular_queue<T,Allocator>::reference
  bit::stl::circular_queue<T,Allocator>::emplace( Args&&...args )
{
  return m_storage.buffer().emplace_back( std::forward<Args>(args)... );
}

template<typename T, typename Allocator>
inline void bit::stl::circular_queue<T,Allocator>::pop()
{
  m_storage.buffer().pop_front();
}

template<typename T, typename Allocator>
inline void bit::stl::circular_queue<T,Allocator>::swap( circular_queue& other )
  noexcept
{
  m_storage.swap(other.m_storage);
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::iterator
  bit::stl::circular_queue<T,Allocator>::begin()
  noexcept
{
  return m_storage.buffer().begin();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_iterator
  bit::stl::circular_queue<T,Allocator>::begin()
  const noexcept
{
  return m_storage.buffer().begin();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_iterator
  bit::stl::circular_queue<T,Allocator>::cbegin()
  const noexcept
{
  return m_storage.buffer().cbegin();
}

//----------------------------------------------------------------------------


template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::iterator
  bit::stl::circular_queue<T,Allocator>::end()
  noexcept
{
  return m_storage.buffer().end();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_iterator
  bit::stl::circular_queue<T,Allocator>::end()
  const noexcept
{
  return m_storage.buffer().end();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_iterator
  bit::stl::circular_queue<T,Allocator>::cend()
  const noexcept
{
  return m_storage.buffer().cend();
}

//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::reverse_iterator
  bit::stl::circular_queue<T,Allocator>::rbegin()
  noexcept
{
  return m_storage.buffer().rbegin();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_reverse_iterator
  bit::stl::circular_queue<T,Allocator>::rbegin()
  const noexcept
{
  return m_storage.buffer().rbegin();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_reverse_iterator
  bit::stl::circular_queue<T,Allocator>::crbegin()
  const noexcept
{
  return m_storage.buffer().crbegin();
}

//----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::reverse_iterator
  bit::stl::circular_queue<T,Allocator>::rend()
  noexcept
{
  return m_storage.buffer().rend();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_reverse_iterator
  bit::stl::circular_queue<T,Allocator>::rend()
  const noexcept
{
  return m_storage.buffer().rend();
}

template<typename T, typename Allocator>
inline typename bit::stl::circular_queue<T,Allocator>::const_reverse_iterator
  bit::stl::circular_queue<T,Allocator>::crend()
  const noexcept
{
  return m_storage.buffer().crend();
}

//-----------------------------------------------------------------------------
// Private Modifiers
//-----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline void bit::stl::circular_queue<T,Allocator>::resize( std::true_type,
                                                           size_type n )
{
  auto storage = storage_type{ n, m_storage.get_allocator() };

  for( auto&& v : m_storage.buffer() ) {
    storage.buffer().emplace_back( std::move(v) );
  }

  // Swap the active storage
  m_storage.buffer().swap(storage.buffer());
}

template<typename T, typename Allocator>
inline void bit::stl::circular_queue<T,Allocator>::resize( std::false_type,
                                                           size_type n )
{
  auto storage = storage_type{ n, m_storage.get_allocator() };

  for( const auto& v : m_storage.buffer() ) {
    storage.buffer().emplace_back( v );
  }

  // Swap the active storage
  m_storage.buffer().swap(storage.buffer());
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline void bit::stl::swap( circular_queue<T,Allocator>& lhs,
                            circular_queue<T,Allocator>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//-----------------------------------------------------------------------------
// Equality
//-----------------------------------------------------------------------------

template<typename T, typename Allocator>
inline bool bit::stl::operator==( const circular_queue<T,Allocator>& lhs,
                                  const circular_queue<T,Allocator>& rhs )
  noexcept
{
  return std::equal(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

template<typename T, typename Allocator>
inline bool bit::stl::operator!=( const circular_queue<T,Allocator>& lhs,
                                  const circular_queue<T,Allocator>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

#endif /* BIT_STL_CONTAINERS_DETAIL_CIRCULAR_QUEUE_INL */
