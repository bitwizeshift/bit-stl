#ifndef BIT_STL_UTILITIES_DETAIL_INTEGRAL_TYPE_INL
#define BIT_STL_UTILITIES_DETAIL_INTEGRAL_TYPE_INL

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  ::integral_type( value_type value )
  noexcept
  : m_value(value)
{

}

//-----------------------------------------------------------------------------

template<typename T, typename Tag>
template<typename U, typename>
inline constexpr bit::stl::integral_type<T,Tag>
  ::integral_type( integral_type<U,Tag>&& other )
  noexcept
  : m_value( other.value() )
{

}

template<typename T, typename Tag>
template<typename U, typename>
inline constexpr bit::stl::integral_type<T,Tag>
  ::integral_type( const integral_type<U,Tag>& other )
  noexcept
  : m_value( other.value() )
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename T, typename Tag>
inline constexpr typename bit::stl::integral_type<T,Tag>::value_type
  bit::stl::integral_type<T,Tag>::value()
  const noexcept
{
  return m_value;
}

//-----------------------------------------------------------------------------
// Arithmetic Operations
//-----------------------------------------------------------------------------

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator+()
  const noexcept
{
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>
  bit::stl::integral_type<T,Tag>::operator-()
  const noexcept
{
  return { -m_value };
}

//-----------------------------------------------------------------------------

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator++()
  noexcept
{
  ++m_value;
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>
  bit::stl::integral_type<T,Tag>::operator++(int)
  noexcept
{
  auto result = (*this);
  ++m_value;
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator--()
  noexcept
{
  --m_value;
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>
  bit::stl::integral_type<T,Tag>::operator--(int)
  noexcept
{
  auto result = (*this);
  --m_value;
  return (*this);
}

//-----------------------------------------------------------------------------

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator+=( integral_type other )
  noexcept
{
  m_value += other.value();
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator-=( integral_type other )
  noexcept
{
  m_value -= other.value();
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator*=( integral_type other )
  noexcept
{
  m_value *= other.value();
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator/=( integral_type other )
  noexcept
{
  m_value /= other.value();
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator%=( integral_type other )
  noexcept
{
  m_value %= other.value();
  return (*this);
}


template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator&=( integral_type other )
  noexcept
{
  m_value &= other.value();
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator|=( integral_type other )
  noexcept
{
  m_value |= other.value();
  return (*this);
}

template<typename T, typename Tag>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator^=( integral_type other )
  noexcept
{
  m_value ^= other.value();
  return (*this);
}

template<typename T, typename Tag>
template<typename U, typename>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator<<=( U value )
  noexcept
{
  m_value <<= value;
  return (*this);
}

template<typename T, typename Tag>
template<typename U, typename>
inline bit::stl::integral_type<T,Tag>&
  bit::stl::integral_type<T,Tag>::operator>>=( U value )
  noexcept
{
  m_value >>= value;
  return (*this);
}

//-----------------------------------------------------------------------------
// Binary Arithmetic Operations
//-----------------------------------------------------------------------------

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator+( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() + rhs.value());
}

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator-( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() - rhs.value());
}

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator*( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() * rhs.value());
}

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator/( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() * rhs.value());
}

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator%( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() % rhs.value());
}

//-------------------------------------------------------------------------

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator&( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() & rhs.value());
}

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator|( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() | rhs.value());
}

template<typename T, typename Tag>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator^( const integral_type<T,Tag>& lhs,
                       const integral_type<T,Tag>& rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() ^ rhs.value());
}

template<typename T, typename Tag, typename U, typename>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator<<( const integral_type<T,Tag>& lhs, U rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() << rhs);
}

template<typename T, typename Tag, typename U, typename>
inline constexpr bit::stl::integral_type<T,Tag>
  bit::stl::operator>>( const integral_type<T,Tag>& lhs, U rhs )
  noexcept
{
  return integral_type<T,Tag>(lhs.value() >> rhs);
}

#endif /* BIT_STL_UTILITIES_DETAIL_INTEGRAL_TYPE_INL */
