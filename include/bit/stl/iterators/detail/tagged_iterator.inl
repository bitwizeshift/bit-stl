#ifndef BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_INL
#define BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>::
  tagged_iterator( const Iterator& it )
  noexcept
  : m_iter(it)
{

}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>&
  bit::stl::tagged_iterator<Iterator,U>::operator++()
  noexcept
{
  ++m_iter;
  return (*this);
}

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>
  bit::stl::tagged_iterator<Iterator,U>::operator++(int)
  noexcept
{
  return tagged_iterator(m_iter++);
}

//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>&
  bit::stl::tagged_iterator<Iterator,U>::operator--()
  noexcept
{
  --m_iter;
  return (*this);
}

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>
  bit::stl::tagged_iterator<Iterator,U>::operator--(int)
  noexcept
{
  return tagged_iterator(m_iter--);
}

//----------------------------------------------------------------------------
// Random Access
//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>&
  bit::stl::tagged_iterator<Iterator,U>::operator+=( difference_type n )
  noexcept
{
  m_iter += n;
  return (*this);
}

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>&
  bit::stl::tagged_iterator<Iterator,U>::operator-=( difference_type n )
  noexcept
{
  m_iter -= n;
  return (*this);
}

template<typename Iterator, typename U>
inline constexpr typename bit::stl::tagged_iterator<Iterator,U>::difference_type
  bit::stl::tagged_iterator<Iterator,U>::operator-( const tagged_iterator<Iterator,U>& rhs )
  const noexcept
{
  return m_iter - rhs.m_iter;
}

template<typename Iterator, typename U>
inline constexpr typename bit::stl::tagged_iterator<Iterator,U>::reference
  bit::stl::tagged_iterator<Iterator,U>::operator[]( difference_type index )
  noexcept
{
  return m_iter[index];
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr typename bit::stl::tagged_iterator<Iterator,U>::pointer
  bit::stl::tagged_iterator<Iterator,U>::operator->()
  const noexcept
{
  return m_iter;
}

template<typename Iterator, typename U>
inline constexpr typename bit::stl::tagged_iterator<Iterator,U>::reference
  bit::stl::tagged_iterator<Iterator,U>::operator*()
  const noexcept
{
  return *m_iter;
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr bool
  bit::stl::tagged_iterator<Iterator,U>::operator == ( const tagged_iterator& rhs )
  const noexcept
{
  return m_iter == rhs.m_iter;
}

template<typename Iterator, typename U>
inline constexpr bool
  bit::stl::tagged_iterator<Iterator,U>::operator != ( const tagged_iterator& rhs )
  const noexcept
{
  return m_iter != rhs.m_iter;
}

template<typename Iterator, typename U>
inline constexpr bool
  bit::stl::tagged_iterator<Iterator,U>::operator < ( const tagged_iterator& rhs )
  const noexcept
{
  return m_iter < rhs.m_iter;
}

template<typename Iterator, typename U>
inline constexpr bool
  bit::stl::tagged_iterator<Iterator,U>::operator <= ( const tagged_iterator& rhs )
  const noexcept
{
  return m_iter <= rhs.m_iter;
}

template<typename Iterator, typename U>
inline constexpr bool
bit::stl::tagged_iterator<Iterator,U>::operator > ( const tagged_iterator& rhs )
  const noexcept
{
  return m_iter > rhs.m_iter;
}

template<typename Iterator, typename U>
inline constexpr bool
bit::stl::tagged_iterator<Iterator,U>::operator >= ( const tagged_iterator& rhs )
  const noexcept
{
  return m_iter >= rhs.m_iter;
}

//----------------------------------------------------------------------------
// Random Access (free functions)
//----------------------------------------------------------------------------

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>
  bit::stl::operator+( const tagged_iterator<Iterator,U>& lhs,
                       typename tagged_iterator<Iterator,U>::difference_type rhs )
  noexcept
{
  return tagged_iterator<Iterator,U>(lhs) += rhs;
}

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>
  bit::stl::operator+( typename tagged_iterator<Iterator,U>::difference_type lhs,
                       const tagged_iterator<Iterator,U>& rhs )
  noexcept
{
  return tagged_iterator<Iterator,U>(rhs) + lhs;
}

template<typename Iterator, typename U>
inline constexpr bit::stl::tagged_iterator<Iterator,U>
  bit::stl::operator-( const tagged_iterator<Iterator,U>& lhs,
                       typename tagged_iterator<Iterator,U>::difference_type rhs )
  noexcept
{
  return tagged_iterator<Iterator,U>(lhs) -= rhs;
}

#endif /* BIT_STL_ITERATORS_DETAIL_POINTER_ITERATOR_INL */
