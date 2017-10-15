#ifndef BIT_STL_DETAIL_POINTER_WRAPPER_INL
#define BIT_STL_DETAIL_POINTER_WRAPPER_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
template<typename...Args,std::enable_if_t<std::is_constructible<T,Args...>::value>*>
bit::stl::pointer_wrapper<T>::pointer_wrapper( in_place_t, Args&&...args )
  noexcept(std::is_nothrow_constructible<T,Args...>::value)
  : m_instance( std::forward<Args>(args)... )
{

}

template<typename T>
template<typename U>
bit::stl::pointer_wrapper<T>::pointer_wrapper( const pointer_wrapper<U>& other )
  : m_instance(other.m_instance)
{

}

template<typename T>
template<typename U>
bit::stl::pointer_wrapper<T>::pointer_wrapper( pointer_wrapper<U>&& other )
  : m_instance( std::move(other.m_instance) )
{

}

//----------------------------------------------------------------------------
// Assignment Operators
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::stl::pointer_wrapper<T>&
  bit::stl::pointer_wrapper<T>::operator=( const pointer_wrapper<U>& other )
{
  m_instance = element_type(other.m_instance);

  return (*this);
}

template<typename T>
template<typename U>
bit::stl::pointer_wrapper<T>&
  bit::stl::pointer_wrapper<T>::operator=( pointer_wrapper<U>&& other )
{
  m_instance = element_type(std::move(other.m_instance));

  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
typename bit::stl::pointer_wrapper<T>::element_type*
  bit::stl::pointer_wrapper<T>::get()
  noexcept
{
  return std::addressof(m_instance);
}

template<typename T>
const typename bit::stl::pointer_wrapper<T>::element_type*
  bit::stl::pointer_wrapper<T>::get()
  const noexcept
{
  return std::addressof(m_instance);
}


template<typename T>
typename bit::stl::pointer_wrapper<T>::element_type*
  bit::stl::pointer_wrapper<T>::operator->()
  noexcept
{
  return std::addressof(m_instance);
}

//----------------------------------------------------------------------------

template<typename T>
const typename bit::stl::pointer_wrapper<T>::element_type*
  bit::stl::pointer_wrapper<T>::operator->()
  const noexcept
{
  return std::addressof(m_instance);
}

//----------------------------------------------------------------------------

template<typename T>
typename bit::stl::pointer_wrapper<T>::element_type&
  bit::stl::pointer_wrapper<T>::operator*()
  noexcept
{
  return m_instance;
}

//----------------------------------------------------------------------------

template<typename T>
const typename bit::stl::pointer_wrapper<T>::element_type&
  bit::stl::pointer_wrapper<T>::operator*()
  const noexcept
{
  return m_instance;
}

template<typename T>
bit::stl::pointer_wrapper<T>::operator bool()
  const noexcept
{
  return true;
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T, typename...Args>
bit::stl::pointer_wrapper<T> bit::stl::make_pointer_wrapper( Args&&...args )
  noexcept( std::is_nothrow_constructible<T,Args...>::value )
{
  return pointer_wrapper<T>( in_place, std::forward<Args>(args)... );
}

#endif /* BIT_STL_DETAIL_POINTER_WRAPPER_INL */
