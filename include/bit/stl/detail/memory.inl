#ifndef BIT_STL_DETAIL_MEMORY_INL
#define BIT_STL_DETAIL_MEMORY_INL

template<typename InputIterator>
constexpr auto bit::stl::address_from( InputIterator& it ) noexcept
  -> typename std::iterator_traits<InputIterator>::value_type*
{
  return std::addressof( *it );
}

//------------------------------------------------------------------------
namespace bit {
  namespace stl {
    namespace detail {

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

    } // namespace detail
  }
}

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
// Uninitialized Construction
//------------------------------------------------------------------------

template<typename T>
inline T* bit::stl::uninitialized_default_construct_at( void* ptr )
{
  new (ptr) T;
  return static_cast<T*>(ptr);
}

template<typename T>
inline T* bit::stl::uninitialized_copy_at( void* ptr, const T& other )
{
  new (ptr) T(other);
  return static_cast<T*>(ptr);
}

template<typename T>
inline T* bit::stl::uninitialized_move_at( void* ptr, T&& other )
{
  new (ptr) T(std::move(other));
  return static_cast<T*>(ptr);
}

template<typename T, typename...Args>
inline T* bit::stl::uninitialized_construct_at( void* ptr, Args&&...args )
{
  new (ptr) T( std::forward<Args>(args)... );
  return static_cast<T*>(ptr);
}

namespace bit {
  namespace stl {
    namespace detail {

      template <typename T, typename Tuple, std::size_t... I>
      inline T* uninitialized_tuple_construct_at_impl( void* ptr, Tuple&& t, std::index_sequence<I...> )
      {
        new (ptr) T(std::get<I>(std::forward<Tuple>(t))...);
        return static_cast<T*>(ptr);
      }

    } // namespace detail
  }
}

template<typename T, typename Tuple>
inline T* bit::stl::uninitialized_tuple_construct_at( void* ptr, Tuple&& tuple )
{
  return detail::uninitialized_tuple_construct_at_impl<T>(
    ptr,
    std::forward<Tuple>(tuple),
    std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>()
  );
}


template<typename ForwardIterator, typename...Args>
inline void bit::stl::uninitialized_construct( ForwardIterator first,
                                               ForwardIterator last,
                                               Args&&...args )
{
  using type = typename std::iterator_traits<ForwardIterator>::value_type;

  ForwardIterator current = first;
  try {
    for (; current != last; ++current) {
      new (static_cast<void*>(std::addressof(*current))) type( std::forward<Args>(args)... );
    }
  } catch (...) {
    for (; first != current; ++first) {
      first->~type();
    }
    throw;
  }

}

template<typename ForwardIterator, typename Size, typename...Args>
inline ForwardIterator
  bit::stl::uninitialized_construct_n( ForwardIterator first,
                                       Size n,
                                       Args&&...args )
{
  using type = typename std::iterator_traits<ForwardIterator>::value_type;

  ForwardIterator current = first;
  try {
    for(; n > 0; ++current, --n) {
      new (static_cast<void*>(std::addressof(*current))) type( std::forward<Args>(args)... );
    }
    return current;
  }  catch (...) {
    for (; first != current; ++first) {
      first->~type();
    }
    throw;
  }
}

//------------------------------------------------------------------------
// Destruction
//------------------------------------------------------------------------

template<typename T>
inline void bit::stl::destroy_at( T* p )
{
  p->~T();
}

template<typename ForwardIterator>
inline void
  bit::stl::destroy( ForwardIterator first, ForwardIterator last )
{
  for(; first != last; ++first) {
    destroy_at( std::addressof(*first) );
  }
}

template<typename ForwardIterator>
inline ForwardIterator
  bit::stl::destroy_n( ForwardIterator first, std::size_t n )
{
  for (; n > 0; ++first, --n) {
    destroy_at( std::addressof(*first) );
  }
  return first;
}

template<typename T>
inline void
  bit::stl::destroy_array_at( T* ptr )
{
  std::size_t n = array_size(ptr);

  destroy_n( ptr, n );
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

#endif /* BIT_STL_DETAIL_MEMORY_INL */
