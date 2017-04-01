#ifndef BIT_STL_DETAIL_ITERATOR_INL
#define BIT_STL_DETAIL_ITERATOR_INL

//------------------------------------------------------------------------
// Iterator Adapters : make utilities
//------------------------------------------------------------------------

template<std::size_t N,typename Iter>
inline constexpr bit::stl::tuple_element_iterator<N,Iter>
  bit::stl::make_tuple_element_iterator( Iter iter )
{
  return tuple_element_iterator<N,std::decay_t<Iter>>( iter );
}

template<typename Iter>
inline constexpr bit::stl::tuple_element_iterator<0,Iter>
  bit::stl::make_key_iterator( Iter iter )
{
  return tuple_element_iterator<0,Iter>( iter );
}

template<typename Iter>
inline constexpr bit::stl::tuple_element_iterator<1,Iter>
  bit::stl::make_value_iterator( Iter iter )
{
  return tuple_element_iterator<1,Iter>( iter );
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

template<std::size_t N, typename I, typename S>
inline constexpr auto bit::stl::make_tuple_element_range( I iterator, S sentinel )
  -> bit::stl::range<bit::stl::tuple_element_iterator<N,I>,
                     bit::stl::tuple_element_iterator<N,S>>
{
  return { make_tuple_element_iterator<N,I>( iterator ),
           make_tuple_element_iterator<N,S>( sentinel ) };
}

template<std::size_t N, typename Range>
inline constexpr auto bit::stl::make_tuple_element_range( Range&& r )
  -> decltype(make_tuple_element_range( r.begin(), r.end()))
{
  return make_tuple_element_range<N>( std::forward<Range>(r).begin(),
                                      std::forward<Range>(r).end() );
}

//------------------------------------------------------------------------

template<typename I, typename S>
constexpr auto bit::stl::make_key_range( I iterator, S sentinel )
  -> bit::stl::range<bit::stl::tuple_element_iterator<0,I>,
                     bit::stl::tuple_element_iterator<0,S>>
{
  return make_tuple_element_iterator<0>( iterator, sentinel );
}

template<typename Range>
constexpr auto bit::stl::make_key_range( Range&& r )
  -> decltype(make_key_range( r.begin(), r.end()))
{
  return make_tuple_element_iterator<0>( std::forward<Range>(r).begin(),
                                         std::forward<Range>(r).end() );
}

//------------------------------------------------------------------------

template<typename I, typename S>
constexpr auto bit::stl::make_value_range( I iterator, S sentinel )
  -> bit::stl::range<bit::stl::tuple_element_iterator<1,I>,
                     bit::stl::tuple_element_iterator<1,S>>
{
  return make_tuple_element_iterator<1>( iterator, sentinel );
}

template<typename Range>
constexpr auto bit::stl::make_value_range( Range&& r )
  -> decltype(make_value_range( r.begin(), r.end()))
{
  return make_tuple_element_iterator<1>( std::forward<Range>(r).begin(),
                                         std::forward<Range>(r).end() );
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
  return { std::make_reverse_iterator(iterator),
           std::make_reverse_iterator(sentinel) };
}

template<typename Range>
inline constexpr auto
  bit::stl::make_reverse_range( Range&& r )
  -> decltype(make_reverse_range( r.begin(), r.end() ))
{
  return make_reverse_range( std::forward<Range>(r).begin(),
                             std::forward<Range>(r).end() );
}

//------------------------------------------------------------------------

#endif /* BIT_STL_DETAIL_ITERATOR_INL */
