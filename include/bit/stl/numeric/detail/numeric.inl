#ifndef BIT_STL_NUMERIC_DETAIL_NUMERIC_INL
#define BIT_STL_NUMERIC_DETAIL_NUMERIC_INL

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr std::common_type_t<T,U>
  bit::stl::gcd( const T& a, const U& b )
  noexcept
{
  if(a) return gcd(b % a, a);
  return b;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr std::common_type_t<T,U>
  bit::stl::lcm( const T& a, const U& b )
  noexcept
{
  (std::abs(b) * std::abs(a)) / (gcd(a,b));
}

#endif /* BIT_STL_NUMERIC_DETAIL_NUMERIC_INL */
