#ifndef BIT_STL_MEMORY_DETAIL_UNINITIALIZED_STORAGE_INL
#define BIT_STL_MEMORY_DETAIL_UNINITIALIZED_STORAGE_INL

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

namespace bit { namespace stl { namespace detail {

template <typename T, typename Tuple, std::size_t... I>
inline T* uninitialized_tuple_construct_at_impl( void* ptr, Tuple&& t, std::index_sequence<I...> )
{
  new (ptr) T(std::get<I>(std::forward<Tuple>(t))...);
  return static_cast<T*>(ptr);
}

} } } // namespace bit::stl::detail

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

#endif /* BIT_STL_MEMORY_DETAIL_UNINITIALIZED_STORAGE_INL */
