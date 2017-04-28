#ifndef BIT_STL_DETAIL_CIRCULAR_BUFFER_INL
#define BIT_STL_DETAIL_CIRCULAR_BUFFER_INL

//============================================================================
// circular_buffer_iterator
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename C, typename T>
inline bit::stl::detail::circular_buffer_iterator<C,T>
  ::circular_buffer_iterator( C& container, T* ptr, bool is_full )
  : m_ptr(ptr),
    m_container(&container),
    m_is_full(is_full)
{

}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

template<typename C, typename T>
inline bit::stl::detail::circular_buffer_iterator<C,T>&
  bit::stl::detail::circular_buffer_iterator<C,T>::operator++()
  noexcept
{
  m_is_full = false;
  m_container->increment( m_ptr );
  return (*this);
}

template<typename C, typename T>
inline bit::stl::detail::circular_buffer_iterator<C,T>
  bit::stl::detail::circular_buffer_iterator<C,T>::operator++(int)
  noexcept
{
  auto iter = (*this);
  m_is_full = false;
  m_container->increment( m_ptr );
  return iter;
}

//----------------------------------------------------------------------------

template<typename C, typename T>
inline bit::stl::detail::circular_buffer_iterator<C,T>&
  bit::stl::detail::circular_buffer_iterator<C,T>::operator--()
  noexcept
{
  m_is_full = false;
  m_container->decrement( m_ptr );
  return (*this);
}

template<typename C, typename T>
inline bit::stl::detail::circular_buffer_iterator<C,T>
  bit::stl::detail::circular_buffer_iterator<C,T>::operator--(int)
  noexcept
{
  auto iter = (*this);
  m_is_full = false;
  m_container->decrement( m_ptr );
  return iter;
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename C, typename T>
inline typename bit::stl::detail::circular_buffer_iterator<C,T>::reference
  bit::stl::detail::circular_buffer_iterator<C,T>::operator*()
  noexcept
{
  return *m_ptr;
}

template<typename C, typename T>
inline typename bit::stl::detail::circular_buffer_iterator<C,T>::pointer
  bit::stl::detail::circular_buffer_iterator<C,T>::operator->()
  noexcept
{
  return m_ptr;
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename C, typename T>
inline bool
  bit::stl::detail::operator==( const circular_buffer_iterator<C,T>& lhs,
                                const circular_buffer_iterator<C,T>& rhs )
  noexcept
{
  return lhs.m_is_full == rhs.m_is_full && lhs.m_ptr == rhs.m_ptr;
}

template<typename C, typename T>
inline bool
  bit::stl::detail::operator!=( const circular_buffer_iterator<C,T>& lhs,
                                const circular_buffer_iterator<C,T>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//============================================================================
// circular_buffer
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::circular_buffer<T>::circular_buffer( void* buffer,
                                                      std::size_t size )
  noexcept
  : m_buffer(static_cast<T*>(buffer)),
    m_begin(m_buffer),
    m_end(m_buffer),
    m_capacity(size),
    m_size(0)
{

}

template<typename T>
inline bit::stl::circular_buffer<T>
  ::circular_buffer( circular_buffer&& other )
  noexcept
  : m_buffer( other.m_buffer ),
    m_begin( other.m_begin ),
    m_end( other.m_end ),
    m_capacity( other.m_capacity ),
    m_size( other.m_size )
{
  other.m_size = 0;
  other.m_buffer = nullptr;
}

template<typename T>
inline bit::stl::circular_buffer<T>::~circular_buffer()
{
  clear();
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
template<typename...Args>
inline void bit::stl::circular_buffer<T>::emplace_back( Args&&...args )
{
  if(full()) {
    stl::destroy_at( m_begin );
    increment( m_begin );
  } else {
    ++m_size;
  }

#ifdef BIT_COMPILER_EXCEPTIONS_ENABLED
  try {
#endif
    new (m_end) T( std::forward<Args>(args)... );
#ifdef BIT_COMPILER_EXCEPTIONS_ENABLED
  } catch (...) {
    decrement( m_end );
    --m_size;
    throw;
  }
#endif
  increment( m_end );
}

template<typename T>
template<typename...Args>
inline void bit::stl::circular_buffer<T>::emplace_front( Args&&...args )
{
  if(full()) {
    decrement( m_end );
    stl::destroy_at( m_end );
  } else {
    ++m_size;
  }
  decrement( m_begin );

#ifdef BIT_COMPILER_EXCEPTIONS_ENABLED
  try {
#endif
    new (m_begin) T( std::forward<Args>(args)... );
#ifdef BIT_COMPILER_EXCEPTIONS_ENABLED
  } catch (...) {
    increment( m_begin );
    --m_size;
    throw;
  }
#endif
}

//----------------------------------------------------------------------

template<typename T>
inline void bit::stl::circular_buffer<T>::push_back( const T& value )
{
  emplace_back( value );
}

template<typename T>
inline void bit::stl::circular_buffer<T>::push_back( T&& value )
{
  emplace_back( std::move(value) );
}

//----------------------------------------------------------------------

template<typename T>
inline void bit::stl::circular_buffer<T>::push_front( const T& value )
{
  emplace_front( value );
}

template<typename T>
inline void bit::stl::circular_buffer<T>::push_front( T&& value )
{
  emplace_front( std::move(value) );
}

//----------------------------------------------------------------------

template<typename T>
inline void bit::stl::circular_buffer<T>::pop_front()
{
  stl::destroy_at( m_begin );
  increment( m_begin );
  --m_size;
}

template<typename T>
inline void bit::stl::circular_buffer<T>::pop_back()
{
  stl::destroy_at( m_end );
  decrement( m_end );
  --m_size;
}

//----------------------------------------------------------------------

template<typename T>
inline void bit::stl::circular_buffer<T>::clear()
{
  while( !empty() ) {
    pop_back();
  }
}

template<typename T>
inline void bit::stl::circular_buffer<T>::swap( circular_buffer& other )
  noexcept
{
  using std::swap;

  swap(m_buffer, other.m_buffer);
  swap(m_begin, other.m_begin);
  swap(m_end, other.m_end);
  swap(m_capacity, other.m_capacity);
  swap(m_size, other.m_size);
}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename T>
inline bool bit::stl::circular_buffer<T>::empty()
  const noexcept
{
  return m_size == 0;
}

template<typename T>
inline bool bit::stl::circular_buffer<T>::full()
  const noexcept
{
  return m_size == m_capacity;
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::size_type
  bit::stl::circular_buffer<T>::size()
  const noexcept
{
  return m_size;
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::size_type
  bit::stl::circular_buffer<T>::max_size()
  const noexcept
{
  return m_capacity;
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::size_type
  bit::stl::circular_buffer<T>::capacity()
  const noexcept
{
  return m_capacity;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::reference
  bit::stl::circular_buffer<T>::front()
  noexcept
{
  return *m_begin;
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_reference
  bit::stl::circular_buffer<T>::front()
  const noexcept
{
  return *m_begin;
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::reference
  bit::stl::circular_buffer<T>::back()
  noexcept
{
  auto ptr = m_end;
  return *decrement( ptr );
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_reference
  bit::stl::circular_buffer<T>::back()
  const noexcept
{
  auto ptr = m_end;
  return *decrement( ptr );
}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::iterator
  bit::stl::circular_buffer<T>::begin()
  noexcept
{
  return iterator{ (*this), m_begin, full() };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_iterator
  bit::stl::circular_buffer<T>::begin()
  const noexcept
{
  return const_iterator{ (*this), m_begin, full() };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_iterator
  bit::stl::circular_buffer<T>::cbegin()
  const noexcept
{
  return const_iterator{ (*this), m_begin, full() };
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::iterator
  bit::stl::circular_buffer<T>::end()
  noexcept
{
  return iterator{ (*this), m_end, 0 };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_iterator
  bit::stl::circular_buffer<T>::end()
  const noexcept
{
  return const_iterator{ (*this), m_end, 0 };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_iterator
  bit::stl::circular_buffer<T>::cend()
  const noexcept
{
  return const_iterator{ (*this), m_end, 0 };
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::reverse_iterator
  bit::stl::circular_buffer<T>::rbegin()
  noexcept
{
  return reverse_iterator{ iterator{(*this), m_end, full()} };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_reverse_iterator
  bit::stl::circular_buffer<T>::rbegin()
  const noexcept
{
  return const_reverse_iterator{ const_iterator{(*this), m_end, full()} };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_reverse_iterator
  bit::stl::circular_buffer<T>::crbegin()
  const noexcept
{
  return const_reverse_iterator{ const_iterator{(*this), m_end, full()} };
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::circular_buffer<T>::reverse_iterator
  bit::stl::circular_buffer<T>::rend()
  noexcept
{
  return reverse_iterator{ iterator{(*this), m_begin, 0} };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_reverse_iterator
  bit::stl::circular_buffer<T>::rend()
  const noexcept
{
  return const_reverse_iterator{ const_iterator{(*this), m_begin, 0} };
}

template<typename T>
inline typename bit::stl::circular_buffer<T>::const_reverse_iterator
  bit::stl::circular_buffer<T>::crend()
  const noexcept
{
  return const_reverse_iterator{ const_iterator{(*this), m_begin, 0} };
}
//----------------------------------------------------------------------------
// Private Members
//----------------------------------------------------------------------------

template<typename T>
inline T*& bit::stl::circular_buffer<T>::increment( T*& iter )
  noexcept
{
  if( iter == &m_buffer[m_capacity-1] ) {
    return (iter = &m_buffer[0]);
  }
  return ++iter;
}

template<typename T>
inline T*& bit::stl::circular_buffer<T>::decrement( T*& iter )
  noexcept
{
  if( iter == &m_buffer[0] ) {
    return (iter = &m_buffer[m_capacity-1]);
  }
  return --iter;
}

#endif /* BIT_STL_DETAIL_CIRCULAR_BUFFER_INL */
