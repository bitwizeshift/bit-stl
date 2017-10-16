#ifndef BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_INL
#define BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>::
  pointer_iterator( const Ptr& ptr )
  noexcept
  : m_ptr(ptr)
{

}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>&
  bit::stl::pointer_iterator<Ptr,U>::operator++()
  noexcept
{
  ++m_ptr;
  return (*this);
}

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>
  bit::stl::pointer_iterator<Ptr,U>::operator++(int)
  noexcept
{
  return pointer_iterator(m_ptr++);
}

//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>&
  bit::stl::pointer_iterator<Ptr,U>::operator--()
  noexcept
{
  --m_ptr;
  return (*this);
}

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>
  bit::stl::pointer_iterator<Ptr,U>::operator--(int)
  noexcept
{
  return pointer_iterator(m_ptr--);
}

//----------------------------------------------------------------------------
// Random Access
//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>&
  bit::stl::pointer_iterator<Ptr,U>::operator+=( difference_type n )
  noexcept
{
  m_ptr += n;
  return (*this);
}

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>&
  bit::stl::pointer_iterator<Ptr,U>::operator-=( difference_type n )
  noexcept
{
  m_ptr -= n;
  return (*this);
}

template<typename Ptr, typename U>
inline constexpr typename bit::stl::pointer_iterator<Ptr,U>::difference_type
  bit::stl::pointer_iterator<Ptr,U>::operator-( const pointer_iterator<Ptr,U>& rhs )
  const noexcept
{
  return m_ptr - rhs.m_ptr;
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr typename bit::stl::pointer_iterator<Ptr,U>::pointer
  bit::stl::pointer_iterator<Ptr,U>::operator->()
  const noexcept
{
  return m_ptr;
}

template<typename Ptr, typename U>
inline constexpr typename bit::stl::pointer_iterator<Ptr,U>::reference
  bit::stl::pointer_iterator<Ptr,U>::operator*()
  const noexcept
{
  return *m_ptr;
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr bool
  bit::stl::pointer_iterator<Ptr,U>::operator == ( const pointer_iterator& rhs )
  const noexcept
{
  return m_ptr == rhs.m_ptr;
}

template<typename Ptr, typename U>
inline constexpr bool
  bit::stl::pointer_iterator<Ptr,U>::operator != ( const pointer_iterator& rhs )
  const noexcept
{
  return m_ptr != rhs.m_ptr;
}

template<typename Ptr, typename U>
inline constexpr bool
  bit::stl::pointer_iterator<Ptr,U>::operator < ( const pointer_iterator& rhs )
  const noexcept
{
  return m_ptr < rhs.m_ptr;
}

template<typename Ptr, typename U>
inline constexpr bool
  bit::stl::pointer_iterator<Ptr,U>::operator <= ( const pointer_iterator& rhs )
  const noexcept
{
  return m_ptr <= rhs.m_ptr;
}

template<typename Ptr, typename U>
inline constexpr bool
bit::stl::pointer_iterator<Ptr,U>::operator > ( const pointer_iterator& rhs )
  const noexcept
{
  return m_ptr > rhs.m_ptr;
}

template<typename Ptr, typename U>
inline constexpr bool
bit::stl::pointer_iterator<Ptr,U>::operator >= ( const pointer_iterator& rhs )
  const noexcept
{
  return m_ptr >= rhs.m_ptr;
}

//----------------------------------------------------------------------------
// Random Access (free functions)
//----------------------------------------------------------------------------

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>
  bit::stl::operator+( const pointer_iterator<Ptr,U>& lhs,
                       typename pointer_iterator<Ptr,U>::difference_type rhs )
  noexcept
{
  return pointer_iterator<Ptr,U>(lhs) += rhs;
}

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>
  bit::stl::operator+( typename pointer_iterator<Ptr,U>::difference_type rhs,
                       const pointer_iterator<Ptr,U>& lhs )
  noexcept
{
  return pointer_iterator<Ptr,U>(rhs) + lhs;
}

template<typename Ptr, typename U>
inline constexpr bit::stl::pointer_iterator<Ptr,U>
  bit::stl::operator-( const pointer_iterator<Ptr,U>& lhs,
                       typename pointer_iterator<Ptr,U>::difference_type rhs )
  noexcept
{
  return pointer_iterator<Ptr,U>(lhs) -= rhs;
}

#endif /* BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_INL */
