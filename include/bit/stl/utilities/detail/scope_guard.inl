#ifndef BIT_STL_UTILITIES_DETAIL_SCOPE_GUARD_INL
#define BIT_STL_UTILITIES_DETAIL_SCOPE_GUARD_INL

//-----------------------------------------------------------------------------
// Scope Guard
//-----------------------------------------------------------------------------

template<typename Fn>
inline constexpr bit::stl::scope_guard<Fn>::scope_guard( scope scope,
                                                         Fn function )
  noexcept( std::is_nothrow_move_constructible<Fn>::value )
  : m_action(std::move(function)),
    m_scope(scope)
{

}

template<typename Fn>
inline constexpr bit::stl::scope_guard<Fn>::scope_guard( scope_guard&& other )
  noexcept( std::is_nothrow_move_constructible<Fn>::value )
  : m_action(std::move(other.m_action)),
    m_scope(other.m_scope)
{
  other.m_scope = scope::cancelled;
}

//-----------------------------------------------------------------------------

template<typename Fn>
inline bit::stl::scope_guard<Fn>::~scope_guard()
{
  if( m_scope == scope::cancelled ) return;
#if __cplusplus >= 201703L
  auto has_exceptions = (std::uncaught_exceptions() > 0);
#else
  auto has_exceptions = std::uncaught_exception();
#endif
  if( (m_scope == scope::on_exit) ||
      ((m_scope == scope::on_clean_exit) && !has_exceptions) ||
      ((m_scope == scope::on_error_exit) && has_exceptions) )
  {
    m_action();
  }
}

//-----------------------------------------------------------------------------

template<typename Fn>
inline bit::stl::scope_guard<Fn>&
  bit::stl::scope_guard<Fn>::operator = ( scope_guard&& other )
  noexcept( std::is_nothrow_move_assignable<Fn>::value )
{
  m_action = std::move(other.m_action);
  m_scope  = other.m_scope;

  other.m_scope = scope::cancelled;
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename Fn>
inline void bit::stl::scope_guard<Fn>::cancel() noexcept
{
  m_scope = scope::cancelled;
}

//=============================================================================
// Free Functions
//=============================================================================

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename Fn>
inline constexpr bit::stl::scope_guard<std::decay_t<Fn>>
  bit::stl::on_scope_exit( Fn&& function )
{
  using scope = typename scope_guard<std::decay_t<Fn>>::scope;
  return { scope::on_exit, std::forward<Fn>(function) };
}

template<typename Fn>
inline constexpr bit::stl::scope_guard<std::decay_t<Fn>>
  bit::stl::on_scope_error_exit( Fn&& function )
{
  using scope = typename scope_guard<std::decay_t<Fn>>::scope;
  return { scope::on_error_exit, std::forward<Fn>(function) };
}

template<typename Fn>
inline constexpr bit::stl::scope_guard<std::decay_t<Fn>>
  bit::stl::on_scope_clean_exit( Fn&& function )
{
  using scope = typename scope_guard<std::decay_t<Fn>>::scope;
  return { scope::on_clean_exit, std::forward<Fn>(function) };
}


#endif /* BIT_STL_UTILITIES_DETAIL_SCOPE_GUARD_INL */
