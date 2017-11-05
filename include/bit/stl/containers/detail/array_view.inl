#ifndef BIT_STL_CONTAINERS_DETAIL_ARRAY_VIEW_INL
#define BIT_STL_CONTAINERS_DETAIL_ARRAY_VIEW_INL

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::array_view<T>::array_view()
  noexcept
  : m_ptr(nullptr),
    m_size(0)
{

}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::array_view<T>::array_view( const array_view& other )
  noexcept
  : m_ptr(other.m_ptr),
    m_size(other.m_size)
{

}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::array_view<T>::array_view( array_view&& other )
  noexcept
  : m_ptr(other.m_ptr),
    m_size(other.m_size)
{
  other.m_ptr  = nullptr;
  other.m_size = 0;
}

//-----------------------------------------------------------------------------

template<typename T>
template<std::size_t N>
inline constexpr bit::stl::array_view<T>::array_view( value_type (&array)[N] )
  noexcept
  : m_ptr(array),
    m_size(N)
{

}

//-----------------------------------------------------------------------------

template<typename T>
template<std::size_t N>
inline constexpr bit::stl::array_view<T>::
  array_view( const value_type (&array)[N] )
  noexcept
  : m_ptr(array),
    m_size(N)
{

}

template<typename T>
inline constexpr bit::stl::array_view<T>::
  array_view( std::initializer_list<value_type> ilist )
  noexcept
  : m_ptr(ilist.begin()),
    m_size(ilist.end() - ilist.begin())
{

}

//-----------------------------------------------------------------------------

template<typename T>
template<typename Container,typename>
inline constexpr bit::stl::array_view<T>::
  array_view( const Container& container )
  noexcept
  : m_ptr(container.data()),
    m_size(container.size())
{

}

//-----------------------------------------------------------------------------
// Capacity
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::size_type
  bit::stl::array_view<T>::size()
  const noexcept
{
  return m_size;
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::array_view<T>::empty()
  const noexcept
{
  return m_size == 0;
}

//-----------------------------------------------------------------------------
// Element Access
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr const typename bit::stl::array_view<T>::value_type*
  bit::stl::array_view<T>::data()
  const noexcept
{
  return m_ptr;
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reference
  bit::stl::array_view<T>::operator[]( std::size_t n )
  const noexcept
{
  return m_ptr[n];
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reference
  bit::stl::array_view<T>::at( std::size_t n )
  const
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( n >= m_size) throw std::out_of_range("array_view::at: input out of range");
#endif
  return m_ptr[n];
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reference
  bit::stl::array_view<T>::front()
  const noexcept
{
  return m_ptr[0];
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reference
  bit::stl::array_view<T>::back()
  const noexcept
{
  return m_ptr[m_size-1];
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::array_view<T>::remove_front( size_type n )
  noexcept
{
  m_ptr += n;
  m_size -= n;
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::array_view<T>::remove_back( size_type n )
  noexcept
{
  m_size -= n;
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::array_view<T>::swap( array_view<T>& rhs )
  noexcept
{
  using std::swap;

  swap(m_size,rhs.m_size);
  swap(m_ptr,rhs.m_ptr);
}

//-----------------------------------------------------------------------------
// Operations
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::array_view<T>
  bit::stl::array_view<T>::subarray( size_type offset, size_type count )
  const
{
  const size_type max_length = offset > m_size ? 0 : m_size - offset;

#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( offset >= m_size ) throw std::out_of_range("array_view::subarray: index out of range");
#endif
  return array_view<T>( m_ptr + offset, count > max_length ? max_length : count );
}

//-----------------------------------------------------------------------------
// Iterators
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_iterator
  bit::stl::array_view<T>::begin()
  const noexcept
{
  return iterator(m_ptr);
}


template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_iterator
  bit::stl::array_view<T>::end()
  const noexcept
{
  return iterator(m_ptr + m_size);
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_iterator
  bit::stl::array_view<T>::cbegin()
  const noexcept
{
  return const_iterator(m_ptr);
}


template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_iterator
  bit::stl::array_view<T>::cend()
  const noexcept
{
  return const_iterator(m_ptr + m_size);
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reverse_iterator
  bit::stl::array_view<T>::rbegin()
  const noexcept
{
  return reverse_iterator(m_ptr + (m_size-1));
}


template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reverse_iterator
  bit::stl::array_view<T>::rend()
  const noexcept
{
  return reverse_iterator(m_ptr - 1);
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reverse_iterator
  bit::stl::array_view<T>::crbegin()
  const noexcept
{
  return const_reverse_iterator(m_ptr + (m_size - 1));
}


template<typename T>
inline constexpr typename bit::stl::array_view<T>::const_reverse_iterator
  bit::stl::array_view<T>::crend()
  const noexcept
{
  return const_reverse_iterator(m_ptr - 1);
}

//-----------------------------------------------------------------------------
// Private Constructors
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::array_view<T>::
  array_view( const value_type* ptr, size_type size )
  noexcept
  : m_ptr(ptr),
    m_size(size)
{

}

//=============================================================================
// Free Functions
//=============================================================================

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::swap( array_view<T>& lhs,
                                      array_view<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//-----------------------------------------------------------------------------
// Comparison
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator==( const array_view<T>& lhs,
                                            const array_view<T>& rhs )
{
  return std::equal(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

template<typename T>
inline constexpr bool bit::stl::operator!=( const array_view<T>& lhs,
                                            const array_view<T>& rhs )
{
  return !(lhs==rhs);
}

template<typename T>
inline constexpr bool bit::stl::operator<( const array_view<T>& lhs,
                                           const array_view<T>& rhs )
{
  return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

template<typename T>
inline constexpr bool bit::stl::operator>( const array_view<T>& lhs,
                                           const array_view<T>& rhs )
{
  return (rhs < lhs);
}

template<typename T>
inline constexpr bool bit::stl::operator<=( const array_view<T>& lhs,
                                            const array_view<T>& rhs )
{
  return !(lhs > rhs);
}

template<typename T>
constexpr bool bit::stl::operator>=(const array_view<T>& lhs, const array_view<T>& rhs)
{
  return !(lhs < rhs);
}

#endif /* BIT_STL_CONTAINERS_DETAIL_ARRAY_VIEW_INL */
