#ifndef BIT_STL_RANGES_DETAIL_TUPLE_ELEMENT_RANGE_INL
#define BIT_STL_RANGES_DETAIL_TUPLE_ELEMENT_RANGE_INL

template<std::size_t N, typename Iterator, typename Sentinel>
inline constexpr bit::stl::tuple_element_range<N,Iterator,Sentinel>
  bit::stl::make_tuple_element_range( Iterator iterator, Sentinel sentinel )
{
  return { make_tuple_element_iterator<N,Iterator>( iterator ),
           make_tuple_element_iterator<N,Sentinel>( sentinel ) };
}

template<std::size_t N, typename Range>
inline constexpr auto bit::stl::make_tuple_element_range( Range&& r )
  -> decltype(make_tuple_element_range<N>( r.begin(), r.end()))
{
  return make_tuple_element_range<N>( std::forward<Range>(r).begin(),
                                      std::forward<Range>(r).end() );
}

//------------------------------------------------------------------------

template<typename Iterator, typename Sentinel>
inline constexpr bit::stl::tuple_element_range<0,Iterator,Sentinel>
  bit::stl::make_key_range( Iterator iterator, Sentinel sentinel )
{
  return make_tuple_element_iterator<0>( iterator, sentinel );
}

template<typename Range>
inline constexpr auto bit::stl::make_key_range( Range&& r )
  -> decltype(make_key_range( r.begin(), r.end()))
{
  return make_key_range<0>( std::forward<Range>(r).begin(),
                            std::forward<Range>(r).end() );
}

//------------------------------------------------------------------------

template<typename Iterator, typename Sentinel>
inline constexpr bit::stl::tuple_element_range<1,Iterator,Sentinel>
  bit::stl::make_value_range( Iterator iterator, Sentinel sentinel )
{
  return make_tuple_element_iterator<1>( iterator, sentinel );
}

template<typename Range>
inline constexpr auto bit::stl::make_value_range( Range&& r )
  -> decltype(make_value_range( r.begin(), r.end()))
{
  return make_value_range<1>( std::forward<Range>(r).begin(),
                              std::forward<Range>(r).end() );
}

#endif /* BIT_STL_RANGES_DETAIL_TUPLE_ELEMENT_RANGE_INL */
