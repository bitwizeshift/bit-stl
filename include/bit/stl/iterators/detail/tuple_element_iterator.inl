#ifndef BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_INL
#define BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_INL


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<std::size_t N,typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>
  ::tuple_element_iterator( Iter iter )
  : m_iter(iter)
{

}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

template<std::size_t N, typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>&
  bit::stl::tuple_element_iterator<N,Iter>::operator++()
  noexcept
{
  ++m_iter;
  return (*this);
}

template<std::size_t N, typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>
  bit::stl::tuple_element_iterator<N,Iter>::operator++(int)
  noexcept
{
  return tuple_element_iterator(m_iter++);
}

//----------------------------------------------------------------------------

template<std::size_t N, typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>&
  bit::stl::tuple_element_iterator<N,Iter>::operator--()
  noexcept
{
  --m_iter;
  return (*this);
}

template<std::size_t N, typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>
  bit::stl::tuple_element_iterator<N,Iter>::operator--(int)
  noexcept
{
  return tuple_element_iterator(m_iter--);
}

//----------------------------------------------------------------------------
// Random Access
//----------------------------------------------------------------------------

template<std::size_t N, typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>&
  bit::stl::tuple_element_iterator<N,Iter>::operator+=( difference_type n )
  noexcept
{
  m_iter += n;
  return (*this);
}
template<std::size_t N, typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>&
  bit::stl::tuple_element_iterator<N,Iter>::operator-=( difference_type n )
  noexcept
{
  m_iter -= n;
  return (*this);
}

template<std::size_t N, typename Iter>
inline constexpr typename bit::stl::tuple_element_iterator<N,Iter>::difference_type
  bit::stl::tuple_element_iterator<N,Iter>::operator-( const tuple_element_iterator& rhs )
  const noexcept
{
  return (tuple_element_iterator(m_iter)-rhs);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<std::size_t N, typename Iter>
inline constexpr typename bit::stl::tuple_element_iterator<N,Iter>::pointer
  bit::stl::tuple_element_iterator<N,Iter>::operator->()
  const noexcept
{
  return std::addressof( std::get<N>(*m_iter) );
}

template<std::size_t N, typename Iter>
inline constexpr typename bit::stl::tuple_element_iterator<N,Iter>::reference
  bit::stl::tuple_element_iterator<N,Iter>::operator*()
  const noexcept
{
  return std::get<N>(*m_iter);
}

//----------------------------------------------------------------------------
// Comparison
//----------------------------------------------------------------------------

template<std::size_t N, typename Iter>
inline constexpr bool
  bit::stl::tuple_element_iterator<N,Iter>::operator==( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter == rhs.m_iter;
}

template<std::size_t N, typename Iter>
inline constexpr bool
  bit::stl::tuple_element_iterator<N,Iter>::operator!=( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter != rhs.m_iter;
}

template<std::size_t N, typename Iter>
inline constexpr bool
  bit::stl::tuple_element_iterator<N,Iter>::operator<( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter < rhs.m_iter;
}

template<std::size_t N, typename Iter>
inline constexpr bool
  bit::stl::tuple_element_iterator<N,Iter>::operator<=( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter <= rhs.m_iter;
}

template<std::size_t N, typename Iter>
inline constexpr bool
  bit::stl::tuple_element_iterator<N,Iter>::operator>( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter > rhs.m_iter;
}

template<std::size_t N, typename Iter>
inline constexpr bool
  bit::stl::tuple_element_iterator<N,Iter>::operator>=( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter >= rhs.m_iter;
}

#endif /* BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_INL */
