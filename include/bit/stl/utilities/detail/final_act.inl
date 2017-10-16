#ifndef BIT_STL_UTILITIES_DETAIL_FINAL_ACT_INL
#define BIT_STL_UTILITIES_DETAIL_FINAL_ACT_INL

//-----------------------------------------------------------------------------
// Final Act
//-----------------------------------------------------------------------------

template<typename Func>
inline constexpr bit::stl::final_act<Func>::final_act( Func&& function )
  : m_action( std::forward<Func>(function) ),
    m_will_invoke(true)
{

}

template<typename Func>
inline constexpr bit::stl::final_act<Func>::final_act( final_act&& other )
  : m_action( std::move(other.m_action) ),
    m_will_invoke(other.m_will_invoke)
{
  other.m_will_invoke = false;
}

template<typename Func>
inline bit::stl::final_act<Func>&
  bit::stl::final_act<Func>::operator = ( final_act&& other )
{
  m_action      = std::move(other.m_action);
  m_will_invoke = other.m_will_invoke;

  other.m_will_invoke = false;
}

template<typename Func>
inline bit::stl::final_act<Func>::~final_act()
{
  if(m_will_invoke)
  {
    m_action();
  }
}

template<typename Func>
void bit::stl::final_act<Func>::cancel() noexcept
{
  m_will_invoke = false;
}

//-----------------------------------------------------------------------------

template<typename Func>
inline constexpr bit::stl::final_act<Func>
  bit::stl::finally( Func&& function )
  noexcept
{
  return final_act<Func>( std::forward<Func>(function) );
}

#endif /* BIT_STL_UTILITIES_DETAIL_FINAL_ACT_INL */
