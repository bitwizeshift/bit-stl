#ifndef BIT_STL_MEMORY_DETAIL_SCOPED_PTR_INL
#define BIT_STL_MEMORY_DETAIL_SCOPED_PTR_INL

//============================================================================
// scoped_ptr<T>
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T,Deleter>::scoped_ptr()
  noexcept
  : scoped_ptr(nullptr)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T,Deleter>
  ::scoped_ptr( std::nullptr_t )
  noexcept
  : m_storage(nullptr)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T,Deleter>::scoped_ptr( pointer ptr )
  noexcept
  : m_storage(ptr)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T,Deleter>
  ::scoped_ptr( pointer ptr, const Deleter& deleter )
  noexcept
  : m_storage(ptr, deleter)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T,Deleter>
  ::scoped_ptr( pointer ptr, Deleter&& deleter )
  noexcept
  : m_storage(ptr, std::move(deleter))
{

}

//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline bit::stl::scoped_ptr<T,Deleter>::~scoped_ptr()
{
  reset();
}

//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline bit::stl::scoped_ptr<T,Deleter>&
  bit::stl::scoped_ptr<T,Deleter>::operator=( std::nullptr_t )
{
  reset();

  return (*this);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline void bit::stl::scoped_ptr<T,Deleter>::reset( pointer ptr )
{
  if( m_storage.ptr ) {
    m_storage( m_storage.ptr );
  }
  m_storage.ptr = ptr;
}

template<typename T, typename Deleter>
inline void bit::stl::scoped_ptr<T,Deleter>::reset( std::nullptr_t )
{
  if( m_storage.ptr ) {
    m_storage( m_storage.ptr );
  }
  m_storage.ptr = nullptr;
}

template<typename T, typename Deleter>
inline void bit::stl::scoped_ptr<T,Deleter>::swap( scoped_ptr& other )
  noexcept
{
  using std::swap;

  swap(m_storage, other.m_storage);
}

template<typename T, typename Deleter>
inline typename bit::stl::scoped_ptr<T,Deleter>::pointer
  bit::stl::scoped_ptr<T,Deleter>::release()
  noexcept
{
  auto ptr = m_storage.ptr;
  m_storage.ptr = nullptr;
  return ptr;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline constexpr typename bit::stl::scoped_ptr<T,Deleter>::pointer
  bit::stl::scoped_ptr<T,Deleter>::get()
  const noexcept
{
  return m_storage.ptr;
}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T,Deleter>::operator bool()
  const noexcept
{
  return m_storage.ptr;
}

template<typename T, typename Deleter>
inline constexpr typename bit::stl::scoped_ptr<T,Deleter>::element_type*
  bit::stl::scoped_ptr<T,Deleter>::operator->()
  const noexcept
{
  return m_storage.ptr;
}

template<typename T, typename Deleter>
constexpr typename bit::stl::scoped_ptr<T,Deleter>::element_type&
  bit::stl::scoped_ptr<T,Deleter>::operator*()
  const noexcept
{
  return *m_storage.ptr;
}

template<typename T, typename Deleter>
Deleter& bit::stl::scoped_ptr<T,Deleter>::get_deleter()
  noexcept
{
  return m_storage;
}

template<typename T, typename Deleter>
const Deleter& bit::stl::scoped_ptr<T,Deleter>::get_deleter()
  const noexcept
{
  return m_storage;
}

//============================================================================
// scoped_ptr<T[]>
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T[],Deleter>::scoped_ptr()
  noexcept
  : scoped_ptr(nullptr)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T[],Deleter>
  ::scoped_ptr( std::nullptr_t )
  noexcept
  : m_storage(nullptr)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T[],Deleter>::scoped_ptr( pointer ptr )
  noexcept
  : m_storage(ptr)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T[],Deleter>
  ::scoped_ptr( pointer ptr, const Deleter& deleter )
  noexcept
  : m_storage(ptr, deleter)
{

}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T[],Deleter>
  ::scoped_ptr( pointer ptr, Deleter&& deleter )
  noexcept
  : m_storage(ptr, std::move(deleter))
{

}

//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline bit::stl::scoped_ptr<T[],Deleter>::~scoped_ptr()
{
  reset();
}

//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline bit::stl::scoped_ptr<T[],Deleter>&
  bit::stl::scoped_ptr<T[],Deleter>::operator=( std::nullptr_t )
{
  reset();

  return (*this);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------


template<typename T, typename Deleter>
inline void bit::stl::scoped_ptr<T[],Deleter>::reset( pointer ptr )
{
  if( m_storage.ptr ) {
    m_storage( m_storage.ptr );
  }
  m_storage.ptr = ptr;
}

template<typename T, typename Deleter>
inline void bit::stl::scoped_ptr<T[],Deleter>::reset( std::nullptr_t )
{
  if( m_storage.ptr ) {
    m_storage( m_storage.ptr );
  }
  m_storage.ptr = nullptr;
}

template<typename T, typename Deleter>
inline void bit::stl::scoped_ptr<T[],Deleter>::swap( scoped_ptr& other )
  noexcept
{
  using std::swap;

  swap(m_storage, other.m_storage);
}

template<typename T, typename Deleter>
inline typename bit::stl::scoped_ptr<T[],Deleter>::pointer
  bit::stl::scoped_ptr<T[],Deleter>::release()
  noexcept
{
  auto ptr = m_storage.ptr;
  m_storage.ptr = nullptr;
  return ptr;
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T, typename Deleter>
inline constexpr typename bit::stl::scoped_ptr<T[],Deleter>::pointer
  bit::stl::scoped_ptr<T[],Deleter>::get()
  const noexcept
{
  return m_storage.ptr;
}

template<typename T, typename Deleter>
inline constexpr bit::stl::scoped_ptr<T[],Deleter>::operator bool()
  const noexcept
{
  return m_storage.ptr;
}

template<typename T, typename Deleter>
inline constexpr typename bit::stl::scoped_ptr<T[],Deleter>::element_type&
  bit::stl::scoped_ptr<T[],Deleter>::operator[]( std::ptrdiff_t n )
  const noexcept
{
  return m_storage.ptr[n];
}

template<typename T, typename Deleter>
Deleter& bit::stl::scoped_ptr<T[],Deleter>::get_deleter()
  noexcept
{
  return m_storage;
}

template<typename T, typename Deleter>
const Deleter& bit::stl::scoped_ptr<T[],Deleter>::get_deleter()
  const noexcept
{
  return m_storage;
}

//----------------------------------------------------------------------------
// Utilities
//----------------------------------------------------------------------------

template<typename T, typename Deleter>
void bit::stl::swap( scoped_ptr<T,Deleter>& lhs, scoped_ptr<T,Deleter>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::stl::operator==( const scoped_ptr<T>& lhs,
                                            const scoped_ptr<U>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator!=( const scoped_ptr<T>& lhs,
                                            const scoped_ptr<U>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator<( const scoped_ptr<T>& lhs,
                                           const scoped_ptr<U>& rhs )
  noexcept
{
  return lhs.get() < rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator>( const scoped_ptr<T>& lhs,
                                           const scoped_ptr<U>& rhs )
  noexcept
{
  return lhs.get() > rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator<=( const scoped_ptr<T>& lhs,
                                            const scoped_ptr<U>& rhs )
  noexcept
{
  return lhs.get() <= rhs.get();
}

template<typename T, typename U>
inline constexpr bool bit::stl::operator>=( const scoped_ptr<T>& lhs,
                                            const scoped_ptr<U>& rhs )
  noexcept
{
  return lhs.get() >= rhs.get();
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator==( std::nullptr_t,
                                            const scoped_ptr<T>& rhs )
  noexcept
{
  return nullptr == rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator==( const scoped_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() == nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator!=( std::nullptr_t,
                                            const scoped_ptr<T>& rhs )
  noexcept
{
  return nullptr != rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator!=( const scoped_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator<( std::nullptr_t,
                                           const scoped_ptr<T>& rhs )
  noexcept
{
  return nullptr < rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator<( const scoped_ptr<T>& lhs,
                                           std::nullptr_t )
  noexcept
{
  return lhs.get() < nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator>( std::nullptr_t,
                                           const scoped_ptr<T>& rhs )
  noexcept
{
  return nullptr > rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator>( const scoped_ptr<T>& lhs,
                                           std::nullptr_t )
  noexcept
{
  return lhs.get() > nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator<=( std::nullptr_t,
                                            const scoped_ptr<T>& rhs )
  noexcept
{
  return nullptr <= rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator<=( const scoped_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() <= nullptr;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool bit::stl::operator>=( std::nullptr_t,
                                            const scoped_ptr<T>& rhs )
  noexcept
{
  return nullptr >= rhs.get();
}

template<typename T>
inline constexpr bool bit::stl::operator>=( const scoped_ptr<T>& lhs,
                                            std::nullptr_t )
  noexcept
{
  return lhs.get() >= nullptr;
}

#endif /* BIT_STL_MEMORY_DETAIL_SCOPED_PTR_INL */
