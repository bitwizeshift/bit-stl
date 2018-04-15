#ifndef BIT_STL_UTILITIES_DETAIL_MONOSTATE_INL
#define BIT_STL_UTILITIES_DETAIL_MONOSTATE_INL

//-----------------------------------------------------------------------------
// Comparisons
//-----------------------------------------------------------------------------

inline constexpr bool bit::stl::operator<(monostate, monostate)
  noexcept
{
  return false;
}

inline constexpr bool bit::stl::operator>(monostate, monostate)
  noexcept
{
  return false;
}

inline constexpr bool bit::stl::operator<=(monostate, monostate)
  noexcept
{
  return true;
}

inline constexpr bool bit::stl::operator>=(monostate, monostate)
  noexcept
{
  return true;
}

inline constexpr bool bit::stl::operator==(monostate, monostate)
  noexcept
{
  return true;
}

inline constexpr bool bit::stl::operator!=(monostate, monostate)
  noexcept
{
  return false;
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

inline constexpr bit::stl::hash_t bit::stl::hash_value( const monostate& )
{
  return static_cast<hash_t>(0);
}

#endif /* BIT_STL_UTILITIES_DETAIL_MONOSTATE_INL */
