/**
 * \file tribool.inl
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_DETAIL_TRIBOOL_INL
#define BIT_STL_DETAIL_TRIBOOL_INL

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------

    inline constexpr tribool::tribool()
      : m_state(state::e_indeterminate)
    {

    }

    inline constexpr tribool::tribool( bool b )
      : m_state(b ? state::e_true : state::e_false)
    {

    }

    inline constexpr tribool::tribool( indeterminate_t )
      : m_state(state::e_indeterminate)
    {

    }

    //------------------------------------------------------------------------
    // Observers
    //------------------------------------------------------------------------

    inline constexpr tribool::operator bool()
      const noexcept
    {
      return m_state == state::e_true;
    }

    inline constexpr tribool tribool::operator !()
      const noexcept
    {
      return m_state == state::e_indeterminate ? (*this) : tribool(!bool(*this));
    }

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    constexpr bool indeterminate( const tribool& t, detail::tribool_t )
      noexcept
    {
      return t.m_state == tribool::state::e_indeterminate;
    }

    //------------------------------------------------------------------------
    // Equality Comparisons
    //------------------------------------------------------------------------

    inline constexpr bool operator==( const tribool& lhs, const tribool& rhs )
    {
      return lhs.m_state == rhs.m_state;
    }

    inline constexpr bool operator==( indeterminate_t, const tribool& rhs )
    {
      return tribool(indeterminate) == rhs;
    }

    inline constexpr bool operator==( const tribool& lhs, indeterminate_t )
    {
      return lhs == tribool(indeterminate);
    }

    inline constexpr bool operator!=( const tribool& lhs, const tribool& rhs )
    {
      return !(lhs==rhs);
    }

    inline constexpr bool operator!=( indeterminate_t, const tribool& rhs )
    {
      return tribool(indeterminate) != rhs;
    }

    inline constexpr bool operator!=( const tribool& lhs, indeterminate_t )
    {
      return lhs != tribool(indeterminate);
    }

    //------------------------------------------------------------------------
    // Triboolean Binary Operations
    //------------------------------------------------------------------------

    inline constexpr tribool operator&&( const tribool& lhs, const tribool& rhs )
    {
      if(lhs.m_state == tribool::state::e_indeterminate || rhs.m_state == tribool::state::e_indeterminate) {
        return tribool(indeterminate);
      }

      return tribool( bool(lhs.m_state) && bool(rhs.m_state));
    }

    inline constexpr tribool operator||( const tribool& lhs, const tribool& rhs )
    {
      if(lhs.m_state == rhs.m_state ) return lhs;

      if(lhs.m_state == tribool::state::e_true) return tribool(true);
      if(rhs.m_state == tribool::state::e_true) return tribool(true);

      return tribool(indeterminate);
    }

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_TRIBOOL_INL */
