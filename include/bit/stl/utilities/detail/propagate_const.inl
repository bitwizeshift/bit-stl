#ifndef BIT_STL_UTILITIES_DETAIL_PROPAGATE_CONST_INL
#define BIT_STL_UTILITIES_DETAIL_PROPAGATE_CONST_INL

//-----------------------------------------------------------------------------
// Constructors / Assignment
//-----------------------------------------------------------------------------

// (3)
template<typename T>
template<typename U, std::enable_if_t<bit::stl::is_explicitly_convertible<U&&,T>::value>*>
inline constexpr bit::stl::propagate_const<T>
  ::propagate_const( propagate_const<U>&& pu )
  : m_pointer( std::move(pu.m_pointer) )
{

}

template<typename T>
template<typename U, std::enable_if_t<!bit::stl::is_explicitly_convertible<U&&,T>::value>*>
inline constexpr bit::stl::propagate_const<T>
  ::propagate_const( propagate_const<U>&& pu )
  : m_pointer( std::move(pu.m_pointer) )
{

}

// (4)
template<typename T>
template<typename U, std::enable_if_t<bit::stl::is_explicitly_convertible<U&&,T>::value && !std::is_same<std::decay_t<U>,bit::stl::propagate_const<T>>::value>*>
inline constexpr bit::stl::propagate_const<T>::propagate_const( U&& u )
  : m_pointer( std::forward<U>(u) )
{

}

template<typename T>
template<typename U, std::enable_if_t<!bit::stl::is_explicitly_convertible<U&&,T>::value && !std::is_same<std::decay_t<U>,bit::stl::propagate_const<T>>::value>*>
inline constexpr bit::stl::propagate_const<T>::propagate_const( U&& u )
  : m_pointer( std::forward<U>(u) )
{

}

//-----------------------------------------------------------------------------

// (2)
template<typename T>
template<typename U, typename>
inline bit::stl::propagate_const<T>&
  bit::stl::propagate_const<T>::operator=( propagate_const<U>&& pu )
{
  m_pointer = std::move(pu);

  return (*this);
}

// (3)
template<typename T>
template<typename U, typename>
inline bit::stl::propagate_const<T>&
  bit::stl::propagate_const<T>::operator=( U&& u )
{
  m_pointer = std::forward<U>(u);

  return (*this);
}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::get()
{
  return get_impl( std::is_pointer<T>{} );
}

template<typename T>
inline constexpr const typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::get()
  const
{
  return get_impl( std::is_pointer<T>{} );
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::propagate_const<T>::operator bool() const
{
  return static_cast<bool>(m_pointer);
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::propagate_const<T>::element_type&
  bit::stl::propagate_const<T>::operator*()
{
  return get();
}

template<typename T>
inline constexpr const typename bit::stl::propagate_const<T>::element_type&
  bit::stl::propagate_const<T>::operator*()
  const
{
  return get();
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::operator->()
{
  return *get();
}

template<typename T>
inline constexpr const typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::operator->()
  const
{
  return *get();
}

//-----------------------------------------------------------------------------
// Private Implementation
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::get_impl( std::true_type )
{
  return m_pointer;
}

template<typename T>
inline constexpr const typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::get_impl( std::true_type )
  const
{
  return m_pointer;
}

template<typename T>
inline constexpr typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::get_impl( std::false_type )
{
  return m_pointer.get();
}

template<typename T>
inline constexpr const typename bit::stl::propagate_const<T>::element_type*
  bit::stl::propagate_const<T>::get_impl( std::false_type )
  const
{
  return m_pointer.get();
}

//=============================================================================
// Free Functions
//=============================================================================

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::swap( propagate_const<T>& lhs,
                                      propagate_const<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

template<typename T>
inline constexpr bit::stl::hash_t bit::stl::hash_value( const propagate_const<T>& v )
  noexcept
{
  return hash_value( v.m_pointer );
}

#endif /* BIT_STL_UTILITIES_DETAIL_PROPAGATE_CONST_INL */
