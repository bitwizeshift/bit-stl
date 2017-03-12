#ifndef BIT_STL_DETAIL_MEMORY_OBSERVER_PTR_INL
#define BIT_STL_DETAIL_MEMORY_OBSERVER_PTR_INL

template<typename T>
inline constexpr bit::stl::observer_ptr<T>
  bit::stl::make_observer( T* ptr )
  noexcept
{
  return observer_ptr<T>(ptr);
}

template<typename T>
inline void bit::stl::swap( observer_ptr<T>& lhs, observer_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}


template<typename T>
inline std::size_t bit::stl::hash_value( const observer_ptr<T>& val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

#endif /* BIT_STL_DETAIL_MEMORY_OBSERVER_PTR_INL */
