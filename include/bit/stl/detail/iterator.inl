#ifndef BIT_STL_DETAIL_ITERATOR_INL
#define BIT_STL_DETAIL_ITERATOR_INL

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

//------------------------------------------------------------------------
// Ranges
//------------------------------------------------------------------------

template<typename I, typename S>
inline constexpr bit::stl::range<I,S>
  bit::stl::make_range( I iterator, S sentinel )
{
  return { iterator, sentinel };
}

template<typename Range>
inline constexpr Range&&
  bit::stl::make_range( Range&& range )
{
  return std::forward<Range>(range);
}

//------------------------------------------------------------------------

template<typename I, typename S>
inline constexpr auto
  bit::stl::make_move_range( I iterator, S sentinel )
  -> range<std::move_iterator<I>,std::move_iterator<S>>
{
  return { std::make_move_iterator(iterator),
           std::make_move_iterator(sentinel) };
}

template<typename Range>
inline constexpr auto
  bit::stl::make_move_range( Range&& r )
  -> decltype(make_move_range( r.begin(), r.end() ))
{
  return make_move_range( std::forward<Range>(r).begin(),
                          std::forward<Range>(r).end() );
}

//------------------------------------------------------------------------

template<typename I, typename S>
inline constexpr auto
  bit::stl::make_reverse_range( I iterator, S sentinel )
  -> range<std::reverse_iterator<I>,std::reverse_iterator<S>>
{
  return { std::make_reverse_iterator(std::move(iterator)),
           std::make_reverse_iterator(std::move(sentinel)) };
}

template<typename Range>
inline constexpr auto
  bit::stl::make_reverse_range( Range&& r )
  -> decltype(make_reverse_range( r.begin(), r.end() ))
{
  return make_reverse_range( std::forward<Range>(r).begin(),
                             std::forward<Range>(r).end() );
}

#endif /* BIT_STL_DETAIL_ITERATOR_INL */
