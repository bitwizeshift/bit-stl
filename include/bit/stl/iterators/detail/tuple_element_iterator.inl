#ifndef BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_INL
#define BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<std::size_t N,typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>
  ::tuple_element_iterator( Iterator it )
  : m_iter(it)
{

}

//----------------------------------------------------------------------------
// Iteratoration
//----------------------------------------------------------------------------

template<std::size_t N, typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>&
  bit::stl::tuple_element_iterator<N,Iterator>::operator++()
  noexcept
{
  ++m_iter;
  return (*this);
}

template<std::size_t N, typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>
  bit::stl::tuple_element_iterator<N,Iterator>::operator++(int)
  noexcept
{
  return tuple_element_iterator(m_iter++);
}

//----------------------------------------------------------------------------

template<std::size_t N, typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>&
  bit::stl::tuple_element_iterator<N,Iterator>::operator--()
  noexcept
{
  --m_iter;
  return (*this);
}

template<std::size_t N, typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>
  bit::stl::tuple_element_iterator<N,Iterator>::operator--(int)
  noexcept
{
  return tuple_element_iterator(m_iter--);
}

//----------------------------------------------------------------------------
// Random Access
//----------------------------------------------------------------------------

template<std::size_t N, typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>&
  bit::stl::tuple_element_iterator<N,Iterator>::operator+=( difference_type n )
  noexcept
{
  m_iter += n;
  return (*this);
}
template<std::size_t N, typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>&
  bit::stl::tuple_element_iterator<N,Iterator>::operator-=( difference_type n )
  noexcept
{
  m_iter -= n;
  return (*this);
}

template<std::size_t N, typename Iterator>
inline constexpr typename bit::stl::tuple_element_iterator<N,Iterator>::difference_type
  bit::stl::tuple_element_iterator<N,Iterator>::operator-( const tuple_element_iterator& rhs )
  const noexcept
{
  return (tuple_element_iterator(m_iter)-rhs);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<std::size_t N, typename Iterator>
inline constexpr typename bit::stl::tuple_element_iterator<N,Iterator>::pointer
  bit::stl::tuple_element_iterator<N,Iterator>::operator->()
  const noexcept
{
  return std::addressof( std::get<N>(*m_iter) );
}

template<std::size_t N, typename Iterator>
inline constexpr typename bit::stl::tuple_element_iterator<N,Iterator>::reference
  bit::stl::tuple_element_iterator<N,Iterator>::operator*()
  const noexcept
{
  return std::get<N>(*m_iter);
}

//----------------------------------------------------------------------------
// Comparison
//----------------------------------------------------------------------------

template<std::size_t N, typename Iterator>
inline constexpr bool bit::stl::tuple_element_iterator<N,Iterator>
  ::operator==( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter == rhs.m_iter;
}

template<std::size_t N, typename Iterator>
inline constexpr bool bit::stl::tuple_element_iterator<N,Iterator>
  ::operator!=( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter != rhs.m_iter;
}

template<std::size_t N, typename Iterator>
inline constexpr bool bit::stl::tuple_element_iterator<N,Iterator>
  ::operator<( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter < rhs.m_iter;
}

template<std::size_t N, typename Iterator>
inline constexpr bool bit::stl::tuple_element_iterator<N,Iterator>
  ::operator<=( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter <= rhs.m_iter;
}

template<std::size_t N, typename Iterator>
inline constexpr bool bit::stl::tuple_element_iterator<N,Iterator>
  ::operator>( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter > rhs.m_iter;
}

template<std::size_t N, typename Iterator>
inline constexpr bool bit::stl::tuple_element_iterator<N,Iterator>
  ::operator>=( const tuple_element_iterator& rhs )
  const noexcept
{
  return m_iter >= rhs.m_iter;
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<std::size_t N,typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<N,Iterator>
  bit::stl::make_tuple_element_iterator( Iterator it )
{
  return tuple_element_iterator<N,std::decay_t<Iterator>>( it );
}

template<typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<0,Iterator>
  bit::stl::make_key_iterator( Iterator it )
{
  return tuple_element_iterator<0,Iterator>( it );
}

template<typename Iterator>
inline constexpr bit::stl::tuple_element_iterator<1,Iterator>
  bit::stl::make_value_iterator( Iterator it )
{
  return tuple_element_iterator<1,Iterator>( it );
}


#endif /* BIT_STL_ITERATORS_DETAIL_TUPLE_ELEMENT_ITERATOR_INL */
