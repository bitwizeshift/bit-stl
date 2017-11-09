#ifndef BIT_STL_UTILITIES_DETAIL_UUID_INL
#define BIT_STL_UTILITIES_DETAIL_UUID_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::stl::uuid::uuid()
  noexcept
{
  // intentionally uninitialized
}

//----------------------------------------------------------------------------

inline constexpr bit::stl::uuid::uuid( const value_type(&array)[16] )
  noexcept
  : m_storage{array[0],  array[1],  array[2],  array[3], array[4],  array[5],
              array[6],  array[7],  array[8],  array[9], array[10], array[11],
              array[12], array[13], array[14], array[15]}
{

}

//----------------------------------------------------------------------------
// Assignment
//----------------------------------------------------------------------------

bit::stl::uuid& bit::stl::uuid::operator=( const value_type(&array)[16])
  noexcept
{
  for(auto i=0; i<16; ++i) {
    m_storage[i] = array[i];
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

inline constexpr bit::stl::uuid::size_type bit::stl::uuid::size()
  const noexcept
{
  return 16;
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

inline constexpr bit::stl::uuid::iterator bit::stl::uuid::begin()
  const noexcept
{
  return iterator(&m_storage[0]);
}

inline constexpr bit::stl::uuid::iterator bit::stl::uuid::end()
  const noexcept
{
  return iterator(&m_storage[16]);
}

//----------------------------------------------------------------------------

inline constexpr bit::stl::uuid::iterator bit::stl::uuid::cbegin()
  const noexcept
{
  return iterator(&m_storage[0]);
}

inline constexpr bit::stl::uuid::iterator bit::stl::uuid::cend()
  const noexcept
{
  return iterator(&m_storage[16]);
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

inline bool bit::stl::operator==( const uuid& lhs, const uuid& rhs )
  noexcept
{
  return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
}

inline bool bit::stl::operator!=( const uuid& lhs, const uuid& rhs )
  noexcept
{
  return !(lhs==rhs);
}

inline bool bit::stl::operator<( const uuid& lhs, const uuid& rhs )
  noexcept
{
  return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

inline bool bit::stl::operator>( const uuid& lhs, const uuid& rhs )
  noexcept
{
  return (rhs < lhs);
}

inline bool bit::stl::operator<=( const uuid& lhs, const uuid& rhs )
  noexcept
{
  return !(rhs < lhs);
}

inline bool bit::stl::operator>=( const uuid& lhs, const uuid& rhs )
  noexcept
{
  return !(lhs < rhs);
}

#endif /* BIT_STL_UTILITIES_DETAIL_UUID_INL */
