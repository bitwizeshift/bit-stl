#ifndef BIT_STL_DETAIL_ITERATOR_RANGE_INL
#define BIT_STL_DETAIL_ITERATOR_RANGE_INL

//------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------

template<typename I, typename S>
constexpr bit::stl::range<I,S>::range( I iterator, S sentinel )
  noexcept
  : m_first(std::move(iterator)),
    m_last(std::move(sentinel))
{

}

//------------------------------------------------------------------------
// Iterators
//------------------------------------------------------------------------

template<typename I, typename S>
constexpr typename bit::stl::range<I,S>::iterator
  bit::stl::range<I,S>::begin()
{
  return m_first;
}

template<typename I, typename S>
constexpr typename bit::stl::range<I,S>::sentinel
  bit::stl::range<I,S>::end()
{
  return m_last;
}

#endif /* BIT_STL_DETAIL_ITERATOR_RANGE_INL */
