#ifndef BIT_STL_RANGES_DETAIL_REVERSE_RANGE_INL
#define BIT_STL_RANGES_DETAIL_REVERSE_RANGE_INL


template<typename Range>
inline constexpr bit::stl::detail::reverse_range_t<Range>
  bit::stl::make_reverse_range( Range&& range )
{
  return make_range( std::forward<Range>(range).rbegin(),
                     std::forward<Range>(range).rend() );
}


#endif /* BIT_STL_RANGES_DETAIL_REVERSE_RANGE_INL */
