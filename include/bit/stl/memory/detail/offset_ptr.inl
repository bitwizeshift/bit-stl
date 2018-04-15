#ifndef BIT_STL_MEMORY_DETAIL_OFFSET_PTR_INL
#define BIT_STL_MEMORY_DETAIL_OFFSET_PTR_INL

//=============================================================================
// offset_ptr
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors / Assignments
//-----------------------------------------------------------------------------

template<typename T>
bit::stl::offset_ptr<T>::offset_ptr()
  noexcept
  : offset_ptr(nullptr)
{

}

template<typename T>
bit::stl::offset_ptr<T>::offset_ptr( std::nullptr_t )
  noexcept
  : m_offset(1)
{

}

template<typename T>
bit::stl::offset_ptr<T>::offset_ptr( pointer p )
  noexcept
  : m_offset( calculate_offset(this,p) )
{

}

template<typename T>
template<typename U, typename>
bit::stl::offset_ptr<T>::offset_ptr( U* p )
  noexcept
  : m_offset( calculate_offset(this,p) )
{

}

template<typename T>
bit::stl::offset_ptr<T>::offset_ptr( offset_ptr&& other )
  noexcept
  : m_offset(other.m_offset)
{
  other.reset();
}

template<typename T>
template<typename U, typename>
bit::stl::offset_ptr<T>::offset_ptr( const offset_ptr<U>& other )
  noexcept
  : m_offset( calculate_offset(this,other.get()) )
{

}

template<typename T>
template<typename U, typename>
bit::stl::offset_ptr<T>::offset_ptr( offset_ptr<U>&& other )
  noexcept
  : m_offset( calculate_offset(this,other.get()) )
{
  other.reset();
}

//-----------------------------------------------------------------------------

template<typename T>
bit::stl::offset_ptr<T>& bit::stl::offset_ptr<T>::operator=( pointer p )
  noexcept
{
  reset( p );
  return (*this);
}

template<typename T>
template<typename U, typename>
bit::stl::offset_ptr<T>& bit::stl::offset_ptr<T>::operator=( U* p )
  noexcept
{
  reset( p );
  return (*this);
}

template<typename T>
bit::stl::offset_ptr<T>& bit::stl::offset_ptr<T>::operator=( offset_ptr&& other )
  noexcept
{
  m_offset = other.m_offset;
  other.reset();
  return (*this);
}

template<typename T>
template<typename U, typename>
bit::stl::offset_ptr<T>& bit::stl::offset_ptr<T>::operator=( const offset_ptr<U>& other )
  noexcept
{
  m_offset = calculate_offset(this,other.get());
  return (*this);
}

template<typename T>
template<typename U, typename>
bit::stl::offset_ptr<T>& bit::stl::offset_ptr<T>::operator=( offset_ptr<U>&& other )
  noexcept
{
  m_offset = calculate_offset(this,other.get());
  other.reset();
  return (*this);
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T>
void bit::stl::offset_ptr<T>::reset()
  noexcept
{
  m_offset = 1;
}

template<typename T>
template<typename U, typename>
void bit::stl::offset_ptr<T>::reset(U *p)
  noexcept
{
  m_offset = calculate_offset(this,p);
}

template<typename T>
void bit::stl::offset_ptr<T>::swap( offset_ptr& other )
  noexcept
{
  using std::swap;

  swap(m_offset, other.m_offset);
}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename T>
typename bit::stl::offset_ptr<T>::element_type*
  bit::stl::offset_ptr<T>::get()
  const noexcept
{
  return calculate_address( std::is_const<T>{} );
}

template<typename T>
typename bit::stl::offset_ptr<T>::element_type&
  bit::stl::offset_ptr<T>::operator*()
  const noexcept
{
  return *get();
}

template<typename T>
typename bit::stl::offset_ptr<T>::element_type*
  bit::stl::offset_ptr<T>::operator->()
  const noexcept
{
  return get();
}

template<typename T>
bit::stl::offset_ptr<T>::operator bool()
  const noexcept
{
  return m_offset != 1;
}

template<typename T>
std::ptrdiff_t bit::stl::offset_ptr<T>::offset()
  const noexcept
{
  return m_offset;
}

//-----------------------------------------------------------------------------
// Private Utilities
//-----------------------------------------------------------------------------

template<typename T>
template<typename U, typename V>
std::ptrdiff_t bit::stl::offset_ptr<T>::calculate_offset( U* lhs, V* rhs )
  noexcept
{
  using byte_t = const unsigned char;
  auto offset = reinterpret_cast<byte_t*>(lhs) - reinterpret_cast<byte_t*>(rhs);
  return offset ? offset : 1;
}

template<typename T>
T* bit::stl::offset_ptr<T>::calculate_address( std::true_type )
  const noexcept
{
  using byte_t = const unsigned char;

  return reinterpret_cast<T*>(reinterpret_cast<byte_t*>(this) + m_offset);
}

template<typename T>
T* bit::stl::offset_ptr<T>::calculate_address( std::false_type )
  const noexcept
{
  using byte_t = unsigned char;

  return reinterpret_cast<T*>(reinterpret_cast<byte_t*>(this) + m_offset);
}

//-----------------------------------------------------------------------------
// Comparisons
//-----------------------------------------------------------------------------

template<typename T, typename U>
inline bool bit::stl::operator==( const offset_ptr<T>& lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}
template<typename T, typename U>
inline bool bit::stl::operator!=( const offset_ptr<T>& lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs.get() != rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator<( const offset_ptr<T>& lhs,
                                 const offset_ptr<U>& rhs )
  noexcept
{
  return lhs.get() < rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator>( const offset_ptr<T>& lhs,
                                 const offset_ptr<U>& rhs )
  noexcept
{
  return lhs.get() > rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator<=( const offset_ptr<T>& lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs.get() <= rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator>=( const offset_ptr<T>& lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs.get() >= rhs.get();
}

//-----------------------------------------------------------------------------

template<typename T, typename U>
inline bool bit::stl::operator==( const offset_ptr<T>& lhs,
                                  const U* rhs )
  noexcept
{
  return lhs.get() == rhs;
}

template<typename T, typename U>
inline bool bit::stl::operator==( const T* lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs == rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator!=( const offset_ptr<T>& lhs,
                                  const U* rhs )
  noexcept
{
  return lhs.get() != rhs;
}

template<typename T, typename U>
inline bool bit::stl::operator!=( const T* lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs != rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator<( const offset_ptr<T>& lhs,
                                 const U* rhs )
  noexcept
{
  return lhs.get() < rhs;
}

template<typename T, typename U>
inline bool bit::stl::operator<( const T* lhs,
                                 const offset_ptr<U>& rhs )
  noexcept
{
  return lhs < rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator>( const offset_ptr<T>& lhs,
                                 const U* rhs )
  noexcept
{
  return lhs.get() > rhs;
}

template<typename T, typename U>
inline bool bit::stl::operator>( const T* lhs,
                                 const offset_ptr<U>& rhs )
  noexcept
{
  return lhs > rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator<=( const offset_ptr<T>& lhs,
                                  const U* rhs )
  noexcept
{
  return lhs.get() <= rhs;
}

template<typename T, typename U>
inline bool bit::stl::operator<=( const T* lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs <= rhs.get();
}

template<typename T, typename U>
inline bool bit::stl::operator>=( const offset_ptr<T>& lhs,
                                  const U* rhs )
  noexcept
{
  return lhs.get() >= rhs;
}

template<typename T, typename U>
inline bool bit::stl::operator>=( const T* lhs,
                                  const offset_ptr<U>& rhs )
  noexcept
{
  return lhs >= rhs.get();
}


//-----------------------------------------------------------------------------

template<typename T>
inline bool bit::stl::operator==( const offset_ptr<T>& lhs,
                                  std::nullptr_t )
  noexcept
{
  return lhs.get() == nullptr;
}

template<typename T>
inline bool bit::stl::operator==( std::nullptr_t,
                                  const offset_ptr<T>& rhs )
  noexcept
{
  return rhs.get() == nullptr;
}

template<typename T>
inline bool bit::stl::operator!=( const offset_ptr<T>& lhs,
                                  std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator!=( std::nullptr_t,
                                  const offset_ptr<T>& rhs )
  noexcept
{
  return rhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator<( const offset_ptr<T>& lhs,
                                 std::nullptr_t )
  noexcept
{
  return false;
}

template<typename T>
inline bool bit::stl::operator<( std::nullptr_t,
                                 const offset_ptr<T>& rhs )
  noexcept
{
  return rhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator>( const offset_ptr<T>& lhs,
                                 std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator>( std::nullptr_t,
                                 const offset_ptr<T>& rhs )
  noexcept
{
  return false;
}

template<typename T>
inline bool bit::stl::operator<=( const offset_ptr<T>& lhs,
                                  std::nullptr_t )
  noexcept
{
  return lhs.get() == nullptr;
}

template<typename T>
inline bool bit::stl::operator<=( std::nullptr_t,
                                  const offset_ptr<T>& rhs )
  noexcept
{
  return true;
}

template<typename T>
inline bool bit::stl::operator>=( const offset_ptr<T>&,
                                  std::nullptr_t )
  noexcept
{
  return true;
}

template<typename T>
inline bool bit::stl::operator>=( std::nullptr_t,
                                  const offset_ptr<T>& rhs )
  noexcept
{
  return rhs.get() == nullptr;
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::swap( offset_ptr<T>& lhs, offset_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

template<typename T>
inline bit::stl::hash_t bit::stl::hash_value( const offset_ptr<T>& val )
  noexcept
{
  return hash_value( val.offset() );
}

//-----------------------------------------------------------------------------
// Casts
//-----------------------------------------------------------------------------

template<typename To, typename From>
inline bit::stl::offset_ptr<To>
  bit::stl::casts::static_pointer_cast( const offset_ptr<From>& other )
  noexcept
{
  return offset_ptr<To>( static_cast<To*>( other.get() ) );
}

template<typename To, typename From>
inline bit::stl::offset_ptr<To>
  bit::stl::casts::dynamic_pointer_cast( const offset_ptr<From>& other )
  noexcept
{
  return offset_ptr<To>( dynamic_cast<To*>( other.get() ) );
}

template<typename To, typename From>
inline bit::stl::offset_ptr<To>
  bit::stl::casts::const_pointer_cast( const offset_ptr<From>& other )
  noexcept
{
  return offset_ptr<To>( const_cast<To*>( other.get() ) );
}

template<typename To, typename From>
inline bit::stl::offset_ptr<To>
  bit::stl::casts::reinterpret_pointer_cast( const offset_ptr<From>& other )
  noexcept
{
  return offset_ptr<To>( reinterpret_cast<To*>( other.get() ) );
}

#endif // BIT_STL_MEMORY_DETAIL_OFFSET_PTR_INL
