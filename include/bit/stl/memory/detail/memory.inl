#ifndef BIT_STL_MEMORY_DETAIL_INL
#define BIT_STL_MEMORY_DETAIL_INL

template<typename InputIterator>
constexpr auto bit::stl::address_from( InputIterator& it ) noexcept
  -> typename std::iterator_traits<InputIterator>::value_type*
{
  return std::addressof( *it );
}

//------------------------------------------------------------------------
namespace bit { namespace stl { namespace detail {

template<typename T>
inline constexpr T& dereference(T& ref)
{
  return ref;
}

template<typename T>
inline constexpr decltype(auto) dereference(T* ptr)
{
  return dereference(*ptr);
}

} } } // namespace bit::stl::detail

template<typename T>
inline constexpr decltype(auto) bit::stl::dereference(T& ptr)
{
  return detail::dereference(ptr);
}

inline std::uintptr_t bit::stl::to_address( void* ptr )
  noexcept
{
  return reinterpret_cast<std::uintptr_t>(ptr);
}

inline void* bit::stl::from_address( std::uintptr_t address )
  noexcept
{
  return reinterpret_cast<void*>(address);
}

//------------------------------------------------------------------------
// Hashing
//------------------------------------------------------------------------

template<typename T, typename Deleter>
inline std::size_t
  bit::stl::hash_value( const std::unique_ptr<T,Deleter>& val )
  noexcept
{
  return reinterpret_cast<std::size_t>( val.get() );
}

template<typename T>
inline std::size_t
  bit::stl::hash_value( const std::shared_ptr<T>& val )
  noexcept
{
  return reinterpret_cast<std::size_t>( val.get() );
}

template<typename T, typename U>
inline constexpr bool bit::stl::deep_compare( const T& lhs, const U& rhs )
  noexcept
{
  return (lhs == rhs) || (lhs && rhs && (*lhs == *rhs));
}

template<typename T>
inline constexpr bool deep_compare( std::nullptr_t, const T& rhs )
  noexcept
{
  return nullptr == rhs;
}

template<typename T>
inline constexpr bool deep_compare( const T& lhs, std::nullptr_t )
  noexcept
{
  return lhs == nullptr;
}

inline constexpr bool deep_compare( std::nullptr_t, std::nullptr_t )
  noexcept
{
  return true;
}

#endif /* BIT_STL_MEMORY_DETAIL_INL */
