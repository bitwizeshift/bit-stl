#ifndef BIT_STL_CONTAINERS_DETAIL_CIRCULAR_ARRAY_INL
#define BIT_STL_CONTAINERS_DETAIL_CIRCULAR_ARRAY_INL

//============================================================================
// circular_array
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
bit::stl::circular_array<T,N>::circular_array()
  noexcept
  : m_buffer( &m_storage, N )
{

}

template<typename T, std::size_t N>
bit::stl::circular_array<T,N>::circular_array( T(&&array)[N] )
   noexcept(std::is_nothrow_move_constructible<T>::value)
  : m_buffer( &m_storage, N )
{
  for(auto&& v : array ) {
    m_buffer.push_back( std::move(v) );
  }
}

template<typename T, std::size_t N>
bit::stl::circular_array<T,N>::circular_array( const circular_array& other )
  noexcept(std::is_nothrow_copy_constructible<T>::value)
  : m_buffer( &m_storage, N )
{
  for(auto const& v : other.m_buffer ) {
    m_buffer.push_back( v );
  }
}


template<typename T, std::size_t N>
bit::stl::circular_array<T,N>::circular_array( circular_array&& other )
   noexcept(std::is_nothrow_move_constructible<T>::value)
   : m_buffer( &m_storage, N )
{
  for(auto&& v : other.m_buffer) {
    m_buffer.push_back( std::move(v) );
  }
  other.m_buffer.clear();
}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
bool bit::stl::circular_array<T,N>::empty()
  const noexcept
{
  return m_buffer.empty();
}

template<typename T, std::size_t N>
bool bit::stl::circular_array<T,N>::full()
  const noexcept
{
  return m_buffer.full();
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::size_type
  bit::stl::circular_array<T,N>::size()
  const noexcept
{
  return m_buffer.size();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::size_type
  bit::stl::circular_array<T,N>::max_size()
  const noexcept
{
  return m_buffer.max_size();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::size_type
  bit::stl::circular_array<T,N>::capacity()
  const noexcept
{
  return m_buffer.capacity();
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::reference
  bit::stl::circular_array<T,N>::front()
  noexcept
{
  return m_buffer.front();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_reference
  bit::stl::circular_array<T,N>::front()
  const noexcept
{
  return m_buffer.front();
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::reference
  bit::stl::circular_array<T,N>::back()
  noexcept
{
  return m_buffer.back();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_reference
  bit::stl::circular_array<T,N>::back()
  const noexcept
{
  return m_buffer.back();
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
template<typename...Args>
typename bit::stl::circular_array<T,N>::reference
  bit::stl::circular_array<T,N>::emplace_back( Args&&...args )
{
  return m_buffer.emplace_back( std::forward<Args>(args)... );
}

template<typename T, std::size_t N>
template<typename...Args>
typename bit::stl::circular_array<T,N>::reference
  bit::stl::circular_array<T,N>::emplace_front( Args&&...args )
{
  return m_buffer.emplace_front( std::forward<Args>(args)... );
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::push_back( const value_type& value )
{
  m_buffer.push_back(value);
}

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::push_back( value_type&& value )
{
  m_buffer.push_back( std::move(value) );
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::push_front( const value_type& value )
{
  m_buffer.push_front(value);
}

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::push_front( value_type&& value )
{
  m_buffer.push_front( std::move(value) );
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::pop_front()
{
  m_buffer.pop_front();
}

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::pop_back()
{
  m_buffer.pop_front();
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
void bit::stl::circular_array<T,N>::swap( circular_array& other )
  noexcept
{
  using std::swap;

  swap( m_storage, other.m_storage );
  swap( m_buffer, other.m_buffer );
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::iterator
  bit::stl::circular_array<T,N>::begin()
  noexcept
{
  return m_buffer.begin();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_iterator
  bit::stl::circular_array<T,N>::begin()
  const noexcept
{
  return m_buffer.begin();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_iterator
  bit::stl::circular_array<T,N>::cbegin()
  const noexcept
{
  return m_buffer.cbegin();
}

//----------------------------------------------------------------------------


template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::iterator
  bit::stl::circular_array<T,N>::end()
  noexcept
{
  return m_buffer.end();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_iterator
  bit::stl::circular_array<T,N>::end()
  const noexcept
{
  return m_buffer.end();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_iterator
  bit::stl::circular_array<T,N>::cend()
  const noexcept
{
  return m_buffer.cend();
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::reverse_iterator
  bit::stl::circular_array<T,N>::rbegin()
  noexcept
{
  return m_buffer.rbegin();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_reverse_iterator
  bit::stl::circular_array<T,N>::rbegin()
  const noexcept
{
  return m_buffer.rbegin();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_reverse_iterator
  bit::stl::circular_array<T,N>::crbegin()
  const noexcept
{
  return m_buffer.crbegin();
}

//----------------------------------------------------------------------------

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::reverse_iterator
  bit::stl::circular_array<T,N>::rend()
  noexcept
{
  return m_buffer.rend();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_reverse_iterator
  bit::stl::circular_array<T,N>::rend()
  const noexcept
{
  return m_buffer.rend();
}

template<typename T, std::size_t N>
typename bit::stl::circular_array<T,N>::const_reverse_iterator
  bit::stl::circular_array<T,N>::crend()
  const noexcept
{
  return m_buffer.crend();
}

#endif /* BIT_STL_CONTAINERS_DETAIL_CIRCULAR_ARRAY_INL */
