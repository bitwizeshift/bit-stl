#ifndef BIT_STL_DETAIL_ITERATOR_INL
#define BIT_STL_DETAIL_ITERATOR_INL

//------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------

template<typename Container>
constexpr bit::stl::range<Container>::range( Container& container )
  noexcept
  : m_container(container)
{

}

//------------------------------------------------------------------------
// Iterators
//------------------------------------------------------------------------

template<typename Container>
constexpr typename bit::stl::range<Container>::iterator
  bit::stl::range<Container>::begin()
{
  return m_container.begin();
}

template<typename Container>
constexpr typename bit::stl::range<Container>::sentinel
  bit::stl::range<Container>::end()
{
  return m_container.end();
}

//------------------------------------------------------------------------

template<typename Container>
constexpr typename bit::stl::range<Container>::const_iterator
  bit::stl::range<Container>::begin() const
{
  return m_container.begin();
}

template<typename Container>
constexpr typename bit::stl::range<Container>::const_sentinel
  bit::stl::range<Container>::end() const
{
  return m_container.end();
}

//------------------------------------------------------------------------

template<typename Container>
constexpr typename bit::stl::range<Container>::const_iterator
  bit::stl::range<Container>::cbegin() const
{
  return m_container.begin();
}

template<typename Container>
constexpr typename bit::stl::range<Container>::const_sentinel
  bit::stl::range<Container>::cend() const
{
  return m_container.end();
}

#endif /* BIT_STL_DETAIL_ITERATOR_INL */
