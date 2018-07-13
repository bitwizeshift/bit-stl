#ifndef BIT_STL_UTILITIES_DETAIL_BYTE_INL
#define BIT_STL_UTILITIES_DETAIL_BYTE_INL

//=============================================================================
// definitions : non-member operators : enum class : byte
//=============================================================================

//-----------------------------------------------------------------------------
// Operators
//-----------------------------------------------------------------------------

template<typename IntT, typename>
inline constexpr bit::stl::byte bit::stl::operator<<( byte lhs, IntT shift )
  noexcept
{
  return byte(static_cast<unsigned char>(lhs) << shift);
}

template<typename IntT, typename>
inline constexpr bit::stl::byte bit::stl::operator>>( byte lhs, IntT shift )
  noexcept
{
  return byte(static_cast<unsigned char>(lhs) >> shift);
}

//-----------------------------------------------------------------------------

inline constexpr bit::stl::byte bit::stl::operator|( byte lhs, byte rhs )
  noexcept
{
  return byte(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
}

inline constexpr bit::stl::byte bit::stl::operator&( byte lhs, byte rhs )
  noexcept
{
  return byte(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
}

inline constexpr bit::stl::byte bit::stl::operator^( byte lhs, byte rhs )
  noexcept
{
  return byte(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
}

//-----------------------------------------------------------------------------

inline constexpr bit::stl::byte bit::stl::operator~( byte lhs )
  noexcept
{
  return byte(~static_cast<unsigned char>(lhs));
}

//-----------------------------------------------------------------------------
// Compound Assignment Operators
//-----------------------------------------------------------------------------

template<typename IntT, typename>
inline constexpr bit::stl::byte& bit::stl::operator<<=( byte& lhs, IntT shift )
  noexcept
{
  return lhs = byte(static_cast<unsigned char>(lhs) << shift);
}

template<typename IntT, typename>
inline constexpr bit::stl::byte& bit::stl::operator>>=( byte& lhs, IntT shift )
  noexcept
{
  return lhs = byte(static_cast<unsigned char>(lhs) >> shift);
}

//-----------------------------------------------------------------------------

inline bit::stl::byte& bit::stl::operator|=( byte& lhs, byte rhs )
  noexcept
{
  return lhs = byte(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
}

inline bit::stl::byte& bit::stl::operator&=( byte& lhs, byte rhs )
  noexcept
{
  return lhs = byte(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
}

inline bit::stl::byte& bit::stl::operator^=( byte& lhs, byte rhs )
  noexcept
{
  return lhs = byte(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
}

#endif /* BIT_STL_UTILITIES_DETAIL_BYTE_INL */
