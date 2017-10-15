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

#endif /* BIT_STL_DETAIL_ITERATOR_INL */
