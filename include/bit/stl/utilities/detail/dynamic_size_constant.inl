#ifndef BIT_STL_UTILITIES_DETAIL_DYNAMIC_SIZE_CONSTANT_INL
#define BIT_STL_UTILITIES_DETAIL_DYNAMIC_SIZE_CONSTANT_INL

//=============================================================================
// dynamic_size_constant
//=============================================================================

//-----------------------------------------------------------------------------
// Observer
//-----------------------------------------------------------------------------

template<std::size_t Value, std::size_t Idx>
inline constexpr std::size_t
  bit::stl::dynamic_size_constant<Value,Idx>::value()
  const noexcept
{
  return Value;
}

//=============================================================================
// dynamic_size_constant<dynamic_size>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline constexpr bit::stl::dynamic_size_constant<bit::stl::dynamic_size,Idx>
  ::dynamic_size_constant( std::size_t value )
  : m_value(value)
{

}

//-----------------------------------------------------------------------------
// Observer
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline constexpr std::size_t
  bit::stl::dynamic_size_constant<bit::stl::dynamic_size,Idx>::value()
  const noexcept
{
  return m_value;
}

#endif /* BIT_STL_UTILITIES_DETAIL_DYNAMIC_SIZE_CONSTANT_INL */
