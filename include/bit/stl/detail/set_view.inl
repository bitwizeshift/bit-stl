#ifndef BIT_STL_DETAIL_SET_VIEW_INL
#define BIT_STL_DETAIL_SET_VIEW_INL

//------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::set_view<T>::set_view()
  noexcept
  : m_vtable(nullptr),
    m_instance(nullptr)
{

}

template<typename T>
template<typename Set, typename>
inline constexpr bit::stl::set_view<T>::set_view( Set&& other )
  noexcept
  : m_vtable( detail::set_vtable<T>::template get_vtable<std::decay_t<Set>>() ),
    m_instance( std::addressof(other) )
{

}

//------------------------------------------------------------------------
// Capacity
//------------------------------------------------------------------------

template<typename T>
inline bool bit::stl::set_view<T>::empty()
  const noexcept
{
  return size() == 0;
}

template<typename T>
inline typename bit::stl::set_view<T>::size_type
  bit::stl::set_view<T>::size()
  const noexcept
{
  if( m_vtable ) return m_vtable->size_ptr( m_instance );
  return 0;
}

//------------------------------------------------------------------------
// Lookup
//------------------------------------------------------------------------

template<typename T>
inline typename bit::stl::set_view<T>::size_type
  bit::stl::set_view<T>::count( const value_type& key )
  const noexcept
{
  if( m_vtable ) return m_vtable->count_ptr( m_instance );
  return 0;
}

template<typename T>
inline bool bit::stl::set_view<T>::contains( const value_type& key )
  const noexcept
{
  return count( key ) != 0;
}

template<typename T>
inline bit::stl::set_view<T>::operator bool()
  const noexcept
{
  return m_vtable;
}

#endif /* BIT_STL_DETAIL_SET_VIEW_INL */
