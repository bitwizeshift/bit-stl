#ifndef BIT_STL_DETAIL_MAP_VIEW_INL
#define BIT_STL_DETAIL_MAP_VIEW_INL

//------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------

template<typename Key, typename T>
constexpr bit::stl::map_view<Key,T>::map_view()
  noexcept
  : m_vtable(nullptr),
    m_instance(nullptr)
{

}

template<typename Key, typename T>
template<typename Map, typename>
constexpr bit::stl::map_view<Key,T>::map_view( Map&& other )
  noexcept
  : m_vtable( detail::map_vtable<Key,T>::template get_vtable<std::decay_t<Map>>() ),
    m_instance( std::addressof(other) )
{

}

//------------------------------------------------------------------------
// Elemental Access
//------------------------------------------------------------------------

template<typename Key, typename T>
const typename bit::stl::map_view<Key,T>::mapped_type&
  bit::stl::map_view<Key,T>::at( const key_type& key )
  const
{
  return m_vtable->get_ptr( m_instance, key );
}

//------------------------------------------------------------------------
// Capacity
//------------------------------------------------------------------------

template<typename Key, typename T>
bool bit::stl::map_view<Key,T>::empty()
  const noexcept
{
  return size() == 0;
}

template<typename Key, typename T>
typename bit::stl::map_view<Key,T>::size_type
  bit::stl::map_view<Key,T>::size()
  const noexcept
{
  return size();
}

//------------------------------------------------------------------------
// Lookup
//------------------------------------------------------------------------


template<typename Key, typename T>
typename bit::stl::map_view<Key,T>::size_type
  bit::stl::map_view<Key,T>::count( const key_type& key )
  const noexcept
{
  if(m_vtable) m_vtable->count_ptr( m_instance, key );
  return 0;
}

template<typename Key, typename T>
bool bit::stl::map_view<Key,T>::contains( const key_type& key )
  const noexcept
{
  return count( key ) >= 1;
}

template<typename Key, typename T>
constexpr bit::stl::map_view<Key,T>::operator bool()
  const noexcept
{
  return m_vtable;
}

#endif /* BIT_STL_DETAIL_MAP_VIEW_INL */
