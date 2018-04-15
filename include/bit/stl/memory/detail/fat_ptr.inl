#ifndef BIT_STL_MEMORY_DETAIL_FAT_PTR_INL
#define BIT_STL_MEMORY_DETAIL_FAT_PTR_INL

//============================================================================
// fat_ptr<T>
//============================================================================

//----------------------------------------------------------------------------
// Constructors / Assignment
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
constexpr bit::stl::fat_ptr<T>::fat_ptr( const fat_ptr<U>& other )
  noexcept
  : m_ptr( other.get() ),
    m_size( other.size() )
{

}

template<typename T>
template<typename U>
constexpr bit::stl::fat_ptr<T>::fat_ptr( fat_ptr<U>&& other )
  noexcept
  : m_ptr( other.get() ),
    m_size( other.size() )
{
  other.reset();
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::stl::fat_ptr<T>& bit::stl::fat_ptr<T>::operator=( const fat_ptr<U>& other )
  noexcept
{
  m_ptr  = other.get();
  m_size = other.size();
  return (*this);
}

template<typename T>
template<typename U>
bit::stl::fat_ptr<T>& bit::stl::fat_ptr<T>::operator=( fat_ptr<U>&& other )
  noexcept
{
  m_ptr  = other.get();
  m_size = other.size();
  other.reset();
  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
constexpr typename bit::stl::fat_ptr<T>::element_type*
  bit::stl::fat_ptr<T>::get()
  const noexcept
{
  return m_ptr;
}

template<typename T>
constexpr std::size_t bit::stl::fat_ptr<T>::size()
  const noexcept
{
  return m_size;
}

template<typename T>
constexpr typename bit::stl::fat_ptr<T>::element_type&
  bit::stl::fat_ptr<T>::operator*()
  const noexcept
{
  return *m_ptr;
}

template<typename T>
constexpr typename bit::stl::fat_ptr<T>::element_type*
  bit::stl::fat_ptr<T>::operator->()
  const noexcept
{
  return m_ptr;
}

template<typename T>
constexpr bit::stl::fat_ptr<T>::operator bool()
  const noexcept
{
  return m_ptr;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
constexpr void bit::stl::fat_ptr<T>::reset( )
  noexcept
{
  m_ptr  = nullptr;
  m_size = 0;
}

template<typename T>
template<typename U>
constexpr void bit::stl::fat_ptr<T>::reset( U* p, std::size_t n )
  noexcept
{
  m_ptr = p;
  m_size = n;
}

template<typename T>
void bit::stl::fat_ptr<T>::swap( fat_ptr& other )
  noexcept
{
  using std::swap;

  swap(m_ptr,other.m_ptr);
  swap(m_size,other.m_size);
}

//============================================================================
// fat_ptr<T[]>
//============================================================================

//----------------------------------------------------------------------------
// Constructors / Assignment
//----------------------------------------------------------------------------

template<typename T>
constexpr bit::stl::fat_ptr<T[]>::fat_ptr( T* p, std::size_t n )
  noexcept
  : m_ptr(p),
    m_size(n)
{

}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
constexpr void bit::stl::fat_ptr<T[]>::reset()
  noexcept
{
  reset(nullptr,0);
}

template<typename T>
constexpr void bit::stl::fat_ptr<T[]>::reset( T* p, std::size_t n )
  noexcept
{
  m_ptr = p;
  m_size = n;
}

template<typename T>
constexpr void bit::stl::fat_ptr<T[]>::swap( fat_ptr& other )
  noexcept
{
  using std::swap;

  swap(m_ptr,other.m_ptr);
  swap(m_size,other.m_size);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
constexpr typename bit::stl::fat_ptr<T[]>::element_type*
  bit::stl::fat_ptr<T[]>::get()
  const noexcept
{
  return m_ptr;
}

template<typename T>
constexpr std::size_t bit::stl::fat_ptr<T[]>::size()
  const noexcept
{
  return m_size;
}

template<typename T>
constexpr typename bit::stl::fat_ptr<T[]>::element_type&
  bit::stl::fat_ptr<T[]>::operator[]( std::ptrdiff_t n )
  const noexcept
{
  return m_ptr[n];
}

template<typename T>
constexpr bit::stl::fat_ptr<T[]>::operator bool()
  const noexcept
{
  return m_ptr;
}

//----------------------------------------------------------------------------
// Utilities
//----------------------------------------------------------------------------

template<typename T>
void bit::stl::swap( fat_ptr<T>& lhs, fat_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

template<typename T>
inline bit::stl::hash_t bit::stl::hash_value( const fat_ptr<T>& val )
  noexcept
{
  return hash_combine( hash_value( val.get() ), val.size() );
}

//----------------------------------------------------------------------------

template<typename To, typename From>
constexpr bit::stl::fat_ptr<To>
  bit::stl::casts::static_pointer_cast( const fat_ptr<From>& other )
  noexcept
{
  return fat_ptr<To>{ static_cast<To*>(other.get()), other.size() };
}

//----------------------------------------------------------------------------

template<typename To, typename From>
constexpr bit::stl::fat_ptr<To>
  bit::stl::casts::dynamic_pointer_cast( const fat_ptr<From>& other )
  noexcept
{
  auto p = dynamic_cast<To*>(other.get());
  return fat_ptr<To>{ p, p ? other.size() : 0 };
}

//----------------------------------------------------------------------------

template<typename To, typename From>
constexpr bit::stl::fat_ptr<To>
  bit::stl::casts::const_pointer_cast( const fat_ptr<From>& other )
  noexcept
{
  return fat_ptr<To>{ const_cast<To*>(other.get()), other.size() };
}

//----------------------------------------------------------------------------

template<typename To, typename From>
constexpr bit::stl::fat_ptr<To>
  bit::stl::casts::reinterpret_pointer_cast( const fat_ptr<From>& other )
  noexcept
{
  return fat_ptr<To>{ reinterpret_cast<To*>(other.get()), other.size() };
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
constexpr bool bit::stl::operator==( const fat_ptr<T>& lhs,
                                     const fat_ptr<U>& rhs )
  noexcept
{
  return lhs.get() == rhs.get() && lhs.size() == rhs.size();
}

template<typename T, typename U>
constexpr bool bit::stl::operator!=( const fat_ptr<T>& lhs,
                                     const fat_ptr<U>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename T, typename U>
constexpr bool bit::stl::operator<( const fat_ptr<T>& lhs,
                                    const fat_ptr<U>& rhs )
  noexcept
{
  return (lhs.get() == rhs.get() ? lhs.size() < rhs.size() : lhs.get() < rhs.get());
}

template<typename T, typename U>
constexpr bool bit::stl::operator>( const fat_ptr<T>& lhs,
                                    const fat_ptr<U>& rhs )
  noexcept
{
  return (rhs<lhs);
}

template<typename T, typename U>
constexpr bool bit::stl::operator<=( const fat_ptr<T>& lhs,
                                     const fat_ptr<U>& rhs )
  noexcept
{
  return !(rhs<lhs);
}

template<typename T, typename U>
constexpr bool bit::stl::operator>=( const fat_ptr<T>& lhs,
                                     const fat_ptr<U>& rhs )
  noexcept
{
  return !(lhs<rhs);
}

#endif // BIT_STL_MEMORY_DETAIL_FAT_PTR_INL
