#ifndef BIT_STL_UTILITIES_DETAIL_DYNAMIC_INDEX_CONSTANT_INL
#define BIT_STL_UTILITIES_DETAIL_DYNAMIC_INDEX_CONSTANT_INL

//=============================================================================
// dynamic_index_constant
//=============================================================================

//-----------------------------------------------------------------------------
// Observer
//-----------------------------------------------------------------------------

template<std::ptrdiff_t Value, std::size_t Idx>
inline constexpr std::ptrdiff_t
  bit::stl::dynamic_index_constant<Value,Idx>::value()
  const noexcept
{
  return Value;
}

//=============================================================================
// dynamic_index_constant<dynamic_index>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline constexpr bit::stl::dynamic_index_constant<bit::stl::dynamic_index,Idx>
  ::dynamic_index_constant( std::ptrdiff_t value )
  : m_value(value)
{

}

//-----------------------------------------------------------------------------
// Observer
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline constexpr std::ptrdiff_t
  bit::stl::dynamic_index_constant<bit::stl::dynamic_index,Idx>::value()
  const noexcept
{
  return m_value;
}

#endif /* BIT_STL_UTILITIES_DETAIL_DYNAMIC_INDEX_CONSTANT_INL */
