#ifndef BIT_STL_MEMORY_DETAIL_OBSERVER_PTR_INL
#define BIT_STL_MEMORY_DETAIL_OBSERVER_PTR_INL

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
template<typename Y, typename>
inline constexpr bit::stl::observer_ptr<T>::observer_ptr( Y* ptr )
  noexcept
  : m_ptr(ptr)
{

}

template<typename T>
template<typename U, typename>
inline bit::stl::observer_ptr<T>::observer_ptr( observer_ptr<U>&& other )
  noexcept
  : observer_ptr( other.get() )
{
  other.reset();
}

template<typename T>
template<typename U, typename>
inline constexpr bit::stl::observer_ptr<T>::observer_ptr( const observer_ptr<U>& other )
  noexcept
  : observer_ptr( other.get() )
{

}

template<typename T>
inline bit::stl::observer_ptr<T>::observer_ptr( observer_ptr&& other )
  noexcept
  : observer_ptr( other.get() )
{
  other.m_ptr = nullptr;
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

template<typename T>
template<typename Y, typename>
inline bit::stl::observer_ptr<T>&
  bit::stl::observer_ptr<T>::operator=( observer_ptr<Y>&& other )
  noexcept
{
  m_ptr = other.m_ptr;
  other.m_ptr = nullptr;

  return (*this);
}

template<typename T>
template<typename Y, typename>
inline bit::stl::observer_ptr<T>&
  bit::stl::observer_ptr<T>::operator=( const observer_ptr<Y>& other )
  noexcept
{
  m_ptr = other.m_ptr;

  return (*this);
}

template<typename T>
inline bit::stl::observer_ptr<T>&
  bit::stl::observer_ptr<T>::operator=( observer_ptr&& other )
  noexcept
{
  m_ptr = other.m_ptr;
  other.m_ptr = nullptr;

  return (*this);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::observer_ptr<T>::reset()
  noexcept
{
  reset(nullptr);
}

template<typename T>
template<typename Y, typename>
inline void bit::stl::observer_ptr<T>::reset( Y* ptr )
  noexcept
{
  m_ptr = ptr;
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
inline constexpr typename bit::stl::observer_ptr<T>::element_type*
  bit::stl::observer_ptr<T>::get()
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

template<typename T>
inline constexpr typename bit::stl::observer_ptr<T>::element_type*
  bit::stl::observer_ptr<T>::operator->()
  const noexcept
{
  return m_ptr;
}

template<typename T>
inline constexpr bit::stl::observer_ptr<T>::operator bool()
  const noexcept
{
  return m_ptr != nullptr;
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

template<typename T, typename U, typename>
constexpr bool bit::stl::operator==( const T* lhs,
                                     const observer_ptr<U>& rhs )
  noexcept
{
  return lhs == rhs.get();
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator==( const observer_ptr<T>& lhs,
                                     const U* rhs )
  noexcept
{
  return lhs.get() == rhs;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator==( std::nullptr_t, const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr == rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator==( const observer_ptr<T>& lhs, std::nullptr_t )
  noexcept
{
  return lhs.get() == nullptr;
}

template<typename T>
inline constexpr bool bit::stl::operator!=( std::nullptr_t, const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr != rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator!=( const observer_ptr<T>& lhs, std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

template<typename T>
inline constexpr bool bit::stl::operator<( std::nullptr_t, const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr < rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator<( const observer_ptr<T>& lhs, std::nullptr_t )
  noexcept
{
  return lhs.get() < nullptr;
}

template<typename T>
inline constexpr bool bit::stl::operator>( std::nullptr_t, const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr > rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator>( const observer_ptr<T>& lhs, std::nullptr_t )
  noexcept
{
  return lhs.get() > nullptr;
}

template<typename T>
inline constexpr bool bit::stl::operator<=( std::nullptr_t, const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr <= rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator<=( const observer_ptr<T>& lhs, std::nullptr_t )
  noexcept
{
  return lhs.get() <= nullptr;
}
template<typename T>
inline constexpr bool bit::stl::operator>=( std::nullptr_t, const observer_ptr<T>& rhs )
  noexcept
{
  return nullptr >= rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator>=( const observer_ptr<T>& lhs, std::nullptr_t )
  noexcept
{
  return lhs.get() >= nullptr;
}

//----------------------------------------------------------------------------

template<typename T, typename U, typename>
constexpr bool bit::stl::operator!=( const T* lhs, const observer_ptr<U>& rhs )
  noexcept
{
  return lhs != rhs.get();
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator!=( const observer_ptr<T>& lhs, const U* rhs )
  noexcept
{
  return lhs.get() != rhs;
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator<( const T* lhs, const observer_ptr<U>& rhs )
  noexcept
{
  return lhs < rhs.get();
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator<( const observer_ptr<T>& lhs, const U* rhs )
  noexcept
{
  return lhs.get() < rhs;
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator>( const T* lhs, const observer_ptr<U>& rhs )
  noexcept
{
  return lhs > rhs.get();
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator>( const observer_ptr<T>& lhs, const U* rhs )
  noexcept
{
  return lhs.get() > rhs;
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator<=( const T* lhs, const observer_ptr<U>& rhs )
  noexcept
{
  return lhs <= rhs.get();
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator<=( const observer_ptr<T>& lhs, const U* rhs )
  noexcept
{
  return lhs.get() <= rhs;
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator>=( const T* lhs, const observer_ptr<U>& rhs )
  noexcept
{
  return lhs >= rhs.get();
}

template<typename T, typename U, typename>
constexpr bool bit::stl::operator>=( const observer_ptr<T>& lhs, const U* rhs )
  noexcept
{
  return lhs.get() >= rhs;
}

//=============================================================================
// X.Y.2 : observer_ptr utilities
//=============================================================================

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::swap( observer_ptr<T>& lhs, observer_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//-----------------------------------------------------------------------------

template<typename T>
inline bit::stl::hash_t bit::stl::hash_value( const observer_ptr<T>& other )
  noexcept
{
  return hash_value( other.get() );
}

//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::make_observer( T* ptr )
  noexcept
{
  return observer_ptr<T>( ptr );
}

template<typename T, typename U, typename>
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

template<typename T, typename Pointer, typename>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::make_observer( const Pointer& ptr )
  noexcept
{
  return observer_ptr<T>( ptr.get() );
}

//----------------------------------------------------------------------------
// Casts
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::casts::static_pointer_cast( const observer_ptr<U>& ptr )
  noexcept
{
  return observer_ptr<T>( static_cast<T*>(ptr.get()) );
}

template<typename T, typename U>
constexpr bit::stl::observer_ptr<T>
  bit::stl::casts::dynamic_pointer_cast( const observer_ptr<U>& ptr )
  noexcept
{
  return observer_ptr<T>( dynamic_cast<T*>(ptr.get()) );
}

template<typename T, typename U>
constexpr bit::stl::observer_ptr<T>
  bit::stl::casts::const_pointer_cast( const observer_ptr<U>& ptr )
  noexcept
{
  return observer_ptr<T>( const_cast<T*>(ptr.get()) );
}

template<typename T, typename U>
constexpr bit::stl::observer_ptr<T>
  bit::stl::casts::reinterpret_pointer_cast( const observer_ptr<T>& ptr )
  noexcept
{
  return observer_ptr<T>( reinterpret_cast<T*>(ptr.get()) );
}

#endif /* BIT_STL_MEMORY_DETAIL_OBSERVER_PTR_INL */
