#ifndef BIT_STL_UTILITIES_DETAIL_UTILITY_INL
#define BIT_STL_UTILITIES_DETAIL_UTILITY_INL

//----------------------------------------------------------------------------
// Indexing
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
constexpr T& bit::stl::at( T (&array)[N], std::size_t n )
{
  BIT_ASSERT_OR_THROW( n < N, std::out_of_range, "at: index out of range" );
  return array[n];
}

template<typename Container, typename Key, typename>
constexpr decltype(auto) bit::stl::at( Container& container, Key&& key )
{
  return container.at( std::forward<Key>(key) );
}

template<typename Container, bit::stl::underlying_container_type_t<Container>*>
bit::stl::underlying_container_type_t<Container>&
  bit::stl::get_underlying_container( Container& container )
{
  struct I : private Container {
    static decltype(auto) get( Container& container )
    {
      return (container.*&I::c);
    }
  };

  return I::get( container );
}

#endif /* BIT_STL_UTILITIES_DETAIL_UTILITY_INL */
