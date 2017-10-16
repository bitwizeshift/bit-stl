#ifndef BIT_STL_MEMORY_DETAIL_INDIRECT_PTR_INL
#define BIT_STL_MEMORY_DETAIL_INDIRECT_PTR_INL

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>::indirect_ptr()
  noexcept
  : m_ptr(nullptr)
{

}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>::indirect_ptr( T* ptr )
  noexcept
  : m_ptr(ptr)
{

}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::indirect_ptr<T>::swap( indirect_ptr<T>& rhs )
  noexcept
{
  using std::swap;
  swap(m_ptr,rhs.m_ptr);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::indirect_ptr<T>::element_type*
  bit::stl::indirect_ptr<T>::get()
  const noexcept
{
  return m_ptr;
}

template<typename T>
inline constexpr typename bit::stl::indirect_ptr<T>::element_type&
  bit::stl::indirect_ptr<T>::operator*()
  const noexcept
{
  return dereference(m_ptr);
}

template<typename T>
inline constexpr typename bit::stl::indirect_ptr<T>::element_type*
  bit::stl::indirect_ptr<T>::operator->()
  const noexcept
{
  return std::addressof(dereference(m_ptr));
}

template<typename T>
inline constexpr typename bit::stl::indirect_ptr<T>::element_type&
  bit::stl::indirect_ptr<T>::operator[]( std::ptrdiff_t n )
  const noexcept
{
  return m_ptr[n];
}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>::operator bool()
  const noexcept
{
  return static_cast<bool>(m_ptr);
}

//----------------------------------------------------------------------------
// Mutators
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::stl::swap( indirect_ptr<T>& lhs,
                                      indirect_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>&
  bit::stl::indirect_ptr<T>::operator+=( std::ptrdiff_t n )
  noexcept
{
  m_ptr += n;
  return (*this);
}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>&
  bit::stl::indirect_ptr<T>::operator-=( std::ptrdiff_t n )
  noexcept
{
  m_ptr -= n;
  return (*this);
}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>&
  bit::stl::indirect_ptr<T>::operator++()
  noexcept
{
  ++m_ptr;
  return (*this);
}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>
  bit::stl::indirect_ptr<T>::operator++(int)
  noexcept
{
  return indirect_ptr<T>(m_ptr++);
}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>&
  bit::stl::indirect_ptr<T>::operator--()
  noexcept
{
  --m_ptr;
  return (*this);
}

template<typename T>
inline constexpr bit::stl::indirect_ptr<T>
  bit::stl::indirect_ptr<T>::operator--(int)
  noexcept
{
  return indirect_ptr<T>(m_ptr--);
}

//----------------------------------------------------------------------------
// Equality
//----------------------------------------------------------------------------

template<typename T>
inline bool bit::stl::operator==( const indirect_ptr<T>& lhs,
                                  const indirect_ptr<T>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}

template<typename T>
inline bool bit::stl::operator!=( const indirect_ptr<T>& lhs,
                                  const indirect_ptr<T>& rhs )
  noexcept
{
  return lhs.get() != rhs.get();
}

template<typename T>
inline bool bit::stl::operator< ( const indirect_ptr<T>& lhs,
                                  const indirect_ptr<T>& rhs )
  noexcept
{
  return lhs.get() < rhs.get();
}

template<typename T>
inline bool bit::stl::operator<=( const indirect_ptr<T>& lhs,
                                  const indirect_ptr<T>& rhs )
  noexcept
{
  return lhs.get() <= rhs.get();
}

template<typename T>
inline bool bit::stl::operator> ( const indirect_ptr<T>& lhs,
                                  const indirect_ptr<T>& rhs )
  noexcept
{
  return lhs.get() > rhs.get();
}

template<typename T>
inline bool bit::stl::operator>=( const indirect_ptr<T>& lhs,
                                  const indirect_ptr<T>& rhs )
  noexcept
{
  return lhs.get() >= rhs.get();
}

#endif /* BIT_STL_MEMORY_DETAIL_INDIRECT_PTR_INL */
