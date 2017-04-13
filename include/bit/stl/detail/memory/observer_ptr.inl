#ifndef BIT_STL_DETAIL_MEMORY_OBSERVER_PTR_INL
#define BIT_STL_DETAIL_MEMORY_OBSERVER_PTR_INL

//----------------------------------------------------------------------------
// Constructors / Assignment
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::observer_ptr<T>::observer_ptr()
  noexcept
  : observer_ptr(nullptr)
{

}

template<typename T>
inline constexpr bit::stl::observer_ptr<T>::observer_ptr( std::nullptr_t )
  noexcept
  : m_ptr(nullptr)
{

}

template<typename T>
inline constexpr bit::stl::observer_ptr<T>::observer_ptr( pointer ptr )
  noexcept
  : m_ptr(ptr)
{

}

template<typename T>
template<typename U, std::enable_if<std::is_convertible<U*,T*>::value>*>
inline constexpr bit::stl::observer_ptr<T>::observer_ptr( const observer_ptr<U>& other )
  noexcept
  : observer_ptr( other.get() )
{

}

template<typename T>
template<typename U, std::enable_if<std::is_convertible<U*,T*>::value>*>
inline bit::stl::observer_ptr<T>::observer_ptr( observer_ptr<U>&& other )
  noexcept
  : observer_ptr( other.get() )
{
  other.reset();
}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::observer_ptr<T>&
  bit::stl::observer_ptr<T>::operator=( std::nullptr_t )
  noexcept
{
  m_ptr = nullptr;

  return (*this);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::observer_ptr<T>::reset( pointer ptr )
  noexcept
{
  m_ptr = ptr;
}

template<typename T>
inline void bit::stl::observer_ptr<T>::reset( std::nullptr_t )
  noexcept
{
  m_ptr = nullptr;
}

template<typename T>
inline void bit::stl::observer_ptr<T>::swap( observer_ptr& other )
  noexcept
{
  using std::swap;
  swap(m_ptr, other.m_ptr);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::observer_ptr<T>::pointer
  bit::stl::observer_ptr<T>::get()
  const noexcept
{
  return m_ptr;
}

template<typename T>
inline constexpr bit::stl::observer_ptr<T>::operator bool()
  const noexcept
{
  return (bool) m_ptr;
}

template<typename T>
inline constexpr typename bit::stl::observer_ptr<T>::pointer
  bit::stl::observer_ptr<T>::operator->()
  const noexcept
{
  return m_ptr;
}

template<typename T>
inline constexpr std::add_lvalue_reference_t<T>
  bit::stl::observer_ptr<T>::operator*()
  const noexcept
{
  return *m_ptr;
}

//----------------------------------------------------------------------------
// Conversions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::observer_ptr<T>::operator element_type*()
  const noexcept
{
  return m_ptr;
}


//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::swap( observer_ptr<T>& lhs, observer_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

template<typename T>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::make_observer( T* ptr )
  noexcept
{
  return observer_ptr<T>( ptr );
}

template<typename T, typename U, std::enable_if_t<!std::is_same<T,U>::value && std::is_convertible<U*,T*>::value>*>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::make_observer( U* ptr )
  noexcept
{
  return observer_ptr<T>( ptr );
}


template<typename Pointer>
inline constexpr auto bit::stl::make_observer( const Pointer& ptr )
  noexcept -> decltype( make_observer( ptr.get() ) )
{
  return make_observer( ptr.get() );
}

template<typename T, typename Pointer, std::enable_if<bit::stl::detail::is_ptr_observable<Pointer>::value>*>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::make_observer( const Pointer& ptr )
  noexcept
{
  return observer_ptr<T>( ptr.get() );
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::stl::operator==( const observer_ptr<T>& lhs,
                                            const observer_ptr<U>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator!=( const observer_ptr<T>& lhs,
                                            const observer_ptr<U>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator<( const observer_ptr<T>& lhs,
                                           const observer_ptr<U>& rhs )
  noexcept
{
  return lhs.get() < rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator>( const observer_ptr<T>& lhs,
                                           const observer_ptr<U>& rhs )
  noexcept
{
  return lhs.get() > rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator<=( const observer_ptr<T>& lhs,
                                            const observer_ptr<U>& rhs )
  noexcept
{
  return lhs.get() <= rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator>=( const observer_ptr<T>& lhs,
                                            const observer_ptr<U>& rhs )
  noexcept
{
  return lhs.get() >= rhs.get();
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator==( std::nullptr_t,
                                            const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr == rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator==( const observer_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() == nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator!=( std::nullptr_t,
                                            const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr != rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator!=( const observer_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator<( std::nullptr_t,
                                           const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr < rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator<( const observer_ptr<T>& lhs,
                                           std::nullptr_t )
  noexcept
{
  return lhs.get() < nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator>( std::nullptr_t,
                                           const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr > rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator>( const observer_ptr<T>& lhs,
                                           std::nullptr_t )
  noexcept
{
  return lhs.get() > nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator<=( std::nullptr_t,
                                            const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr <= rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator<=( const observer_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() <= nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator>=( std::nullptr_t,
                                            const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr >= rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator>=( const observer_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() >= nullptr;
}

#endif /* BIT_STL_DETAIL_MEMORY_OBSERVER_PTR_INL */
