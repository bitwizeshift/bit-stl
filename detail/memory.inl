#ifndef BIT_DETAIL_MEMORY_INL
#define BIT_DETAIL_MEMORY_INL

namespace bit {

  namespace stl {

    template<typename InputIterator>
    constexpr auto address_from( InputIterator& it ) noexcept
      -> typename std::iterator_traits<InputIterator>::value_type*
    {
      return std::addressof( *it );
    }

    //------------------------------------------------------------------------

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

    template<typename T>
    inline constexpr decltype(auto) dereference(T& ptr)
    {
      return detail::dereference(ptr);
    }

    inline std::uintptr_t to_address( const void* ptr )
      noexcept
    {
      return reinterpret_cast<std::uintptr_t>(ptr);
    }

    inline void* from_address( std::uintptr_t address )
      noexcept
    {
      return reinterpret_cast<void*>(address);
    }

    //------------------------------------------------------------------------
    // Pointer Manipulation
    //------------------------------------------------------------------------

    inline constexpr std::size_t pointer_distance( const void* lhs,
                                                   const void* rhs )
      noexcept
    {
      return (lhs > rhs)
             ? static_cast<std::size_t>(pointer_difference(lhs,rhs))
             : static_cast<std::size_t>(pointer_difference(rhs,lhs));
    }

    inline constexpr std::ptrdiff_t pointer_difference( const void* lhs,
                                                        const void* rhs )
      noexcept
    {
      return static_cast<const byte*>(lhs) - static_cast<const byte*>(rhs);
    }

    inline constexpr bool in_region( const void* ptr,
                                     const void* first,
                                     const void* last ) noexcept
    {
      return (ptr >= first && ptr < last);
    }

    //------------------------------------------------------------------------
    // Pointer Alignment
    //------------------------------------------------------------------------

    inline std::pair<void*,std::size_t>
      align_forward( void* ptr, std::size_t align, std::size_t offset )
      noexcept
    {
      auto old_ptr = static_cast<byte*>(ptr);
      auto address = to_address(old_ptr);
      auto new_ptr = from_address( ((address + offset + static_cast<std::uintptr_t>(align-1)) & static_cast<std::uintptr_t>(~(align-1))) - offset );

      return std::make_pair( new_ptr, (static_cast<byte*>(new_ptr) - old_ptr) );
    }

    inline std::pair<void*,std::size_t>
      align_backward( void* ptr, std::size_t align, std::size_t offset )
      noexcept
    {
      auto old_ptr = static_cast<byte*>(ptr);
      auto address = to_address(old_ptr);
      auto new_ptr = from_address( (address & (~static_cast<std::uintptr_t>(align-1))) + offset );

      return std::make_pair( new_ptr, (old_ptr - static_cast<byte*>(new_ptr)) );
    }

    //------------------------------------------------------------------------
    // Alignment Detection
    //------------------------------------------------------------------------

    inline bool is_aligned( const void* ptr, std::size_t align )
      noexcept
    {
      return ( (reinterpret_cast<std::uintptr_t>(ptr) & (align - 1)) == 0);
    }

    inline std::size_t align_of( const void* ptr )
      noexcept
    {
      if( !ptr ) return 0;

      auto align   = std::size_t{1};
      auto address = reinterpret_cast<std::uintptr_t>( ptr );

      while( !(address & align) )
      {
        align <<= 1;
      }
      return align;
    }

    //------------------------------------------------------------------------
    // Uninitialized Construction
    //------------------------------------------------------------------------

    template<typename T>
    inline T* uninitialized_default_construct_at( void* ptr )
    {
      new (ptr) T;
      return static_cast<T*>(ptr);
    }


    template<typename T>
    inline T* uninitialized_copy_at( void* ptr, const T& other )
    {
      new (ptr) T(other);
      return static_cast<T*>(ptr);
    }


    template<typename T>
    inline T* uninitialized_move_at( void* ptr, T&& other )
    {
      new (ptr) T(std::move(other));
      return static_cast<T*>(ptr);
    }


    template<typename T, typename...Args>
    inline T* uninitialized_construct_at( void* ptr, Args&&...args )
    {
      new (ptr) T( std::forward<Args>(args)... );
      return static_cast<T*>(ptr);
    }

    namespace detail {

      template <typename T, typename Tuple, std::size_t... I>
      inline T* uninitialized_tuple_construct_at_impl( void* ptr, Tuple&& t, std::index_sequence<I...> )
      {
        new (ptr) T(std::get<I>(std::forward<Tuple>(t))...);
        return static_cast<T*>(ptr);
      }

    } // namespace detail


    template<typename T, typename Tuple>
    inline T* uninitialized_tuple_construct_at( void* ptr, Tuple&& tuple )
    {
      return detail::uninitialized_tuple_construct_at_impl<T>(
        ptr,
        std::forward<Tuple>(tuple),
        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>()
      );
    }


    template<typename ForwardIterator, typename...Args>
    inline void uninitialized_construct( ForwardIterator first, ForwardIterator last, Args&&...args )
    {
      using type = typename std::iterator_traits<ForwardIterator>::value_type;

      ForwardIterator current = first;
      try {
        for (; current != last; ++current) {
          ::new (static_cast<void*>(std::addressof(*current))) type( std::forward<Args>(args)... );
        }
      } catch (...) {
        for (; first != current; ++first) {
          first->~Value();
        }
        throw;
      }

    }


    template<typename ForwardIterator, typename Size, typename...Args>
    inline ForwardIterator uninitialized_construct_n( ForwardIterator first, Size n, Args&&...args )
    {
      using type = typename std::iterator_traits<ForwardIterator>::value_type;

      ForwardIterator current = first;
      try {
        for(; n > 0; ++current, --n) {
          new (static_cast<void*>(std::addressof(*current))) type(std::forward<Args>(args)...);
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
    inline void destroy_at( T* p )
    {
      p->~T();
    }

    template<typename ForwardIterator>
    inline void destroy( ForwardIterator first, ForwardIterator last )
    {
      for(; first != last; ++first) {
        destroy_at( std::addressof(*first) );
      }
    }

    template<typename ForwardIterator>
    inline ForwardIterator destroy_n( ForwardIterator first, std::size_t n )
    {
      for (; n > 0; ++first, --n) {
        destroy_at( std::addressof(*first) );
      }
      return first;
    }

    template<typename T>
    inline void destroy_array_at( T* ptr )
    {
      std::size_t n = array_size(ptr);

      destroy_n( ptr, n );
    }

    //------------------------------------------------------------------------
    // Array Utilities
    //------------------------------------------------------------------------

    template<typename Size>
    inline constexpr void* uninitialized_create_array_at( void* ptr, Size count )
    {
      auto size_ptr = static_cast<std::size_t*>(ptr);
      (*size_ptr++) = static_cast<std::size_t>(count);

      return static_cast<void*>(size_ptr);
    }

    inline constexpr std::size_t array_size( const void* ptr )
      noexcept
    {
      return *(static_cast<const std::size_t*>(ptr)-1);
    }

    inline constexpr std::size_t array_max_size()
      noexcept
    {
      return std::numeric_limits<std::size_t>::max();
    }

    inline constexpr std::size_t array_offset()
      noexcept
    {
      return sizeof(std::size_t);
    }

    //------------------------------------------------------------------------
    // Hashing
    //------------------------------------------------------------------------

    template<typename T, typename Deleter>
    inline std::size_t hash_value( const std::unique_ptr<T,Deleter>& val )
      noexcept
    {
      return reinterpret_cast<std::size_t>( val.get() );
    }

    template<typename T>
    inline std::size_t hash_value( const std::shared_ptr<T>& val )
      noexcept
    {
      return reinterpret_cast<std::size_t>( val.get() );
    }

  } // namespace stl
} // namespace bit

#endif /* BIT_DETAIL_MEMORY_INL */
