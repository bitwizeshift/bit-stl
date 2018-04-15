#ifndef BIT_STL_UTILITIES_DETAIL_TRIBOOL_INL
#define BIT_STL_UTILITIES_DETAIL_TRIBOOL_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::stl::tribool::tribool()
  : m_state(state::e_indeterminate)
{

}

inline constexpr bit::stl::tribool::tribool( bool b )
  : m_state(b ? state::e_true : state::e_false)
{

}

inline constexpr bit::stl::tribool::tribool( indeterminate_t )
  : m_state(state::e_indeterminate)
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::stl::tribool::operator bool()
  const noexcept
{
  return m_state == state::e_true;
}

inline constexpr bit::stl::tribool bit::stl::tribool::operator !()
  const noexcept
{
  return m_state == state::e_indeterminate ? (*this) : tribool(!bool(*this));
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

inline constexpr bool
  bit::stl::indeterminate( const tribool& t, detail::tribool_t )
  noexcept
{
  return t.m_state == tribool::state::e_indeterminate;
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( tribool t )
  noexcept
{
  if( t ) return static_cast<hash_t>(1);
  else if( !t ) return static_cast<hash_t>(2);
  return static_cast<hash_t>(0);
}

//----------------------------------------------------------------------------
// Equality Comparisons
//----------------------------------------------------------------------------

inline constexpr bool
  bit::stl::operator==( const tribool& lhs, const tribool& rhs )
  noexcept
{
  return lhs.m_state == rhs.m_state;
}

inline constexpr bool
  bit::stl::operator==( indeterminate_t, const tribool& rhs )
  noexcept
{
  return tribool(indeterminate) == rhs;
}

inline constexpr bool
  bit::stl::operator==( const tribool& lhs, indeterminate_t )
  noexcept
{
  return lhs == tribool(indeterminate);
}

inline constexpr bool bit::stl::operator==( const tribool& lhs, bool rhs )
  noexcept
{
  return lhs == tribool(rhs);
}

inline constexpr bool bit::stl::operator==( bool lhs, const tribool& rhs )
  noexcept
{
  return tribool(lhs) == rhs;
}

//----------------------------------------------------------------------------

inline constexpr bool
  bit::stl::operator!=( const tribool& lhs, const tribool& rhs )
  noexcept
{
  return !(lhs==rhs);
}

inline constexpr bool
  bit::stl::operator!=( indeterminate_t, const tribool& rhs )
  noexcept
{
  return tribool(indeterminate) != rhs;
}

inline constexpr bool
  bit::stl::operator!=( const tribool& lhs, indeterminate_t )
  noexcept
{
  return lhs != tribool(indeterminate);
}

inline constexpr bool bit::stl::operator!=( const tribool& lhs, bool rhs )
  noexcept
{
  return lhs != tribool(rhs);
}

inline constexpr bool bit::stl::operator!=( bool lhs, const tribool& rhs )
  noexcept
{
  return tribool(lhs) != rhs;
}

//----------------------------------------------------------------------------
// Triboolean Binary Operations
//----------------------------------------------------------------------------

inline constexpr bit::stl::tribool
  bit::stl::operator&&( const tribool& lhs, const tribool& rhs )
  noexcept
{
  if(lhs.m_state == tribool::state::e_indeterminate || rhs.m_state == tribool::state::e_indeterminate) {
    return tribool(indeterminate);
  }

  return tribool( bool(lhs.m_state) && bool(rhs.m_state));
}

inline constexpr bit::stl::tribool
  bit::stl::operator||( const tribool& lhs, const tribool& rhs )
  noexcept
{
  if(lhs.m_state == rhs.m_state ) return lhs;

  if(lhs.m_state == tribool::state::e_true) return tribool(true);
  if(rhs.m_state == tribool::state::e_true) return tribool(true);

  return tribool(indeterminate);
}

#endif /* BIT_STL_UTILITIES_DETAIL_TRIBOOL_INL */
