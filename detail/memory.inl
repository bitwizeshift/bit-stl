#ifndef BIT_DETAIL_MEMORY_INL
#define BIT_DETAIL_MEMORY_INL

namespace bit {

  inline namespace stl {

    namespace detail {

      template<typename T>
      inline constexpr T& dereference(T& ref)
      {
        return ref;
      }

      template<typename T>
      inline constexpr auto& dereference(T* ptr)
      {
        return dereference(*ptr);
      }

    } // namespace detail

    template<typename T>
    inline constexpr auto& dereference(T* ptr)
    {
      return detail::dereference(ptr);
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

    template<typename T>
    inline std::size_t align_forward( T** ptr,
                                      std::size_t align,
                                      std::size_t offset )
    {
      //BIT_ASSERT( is_power_of_two(align), "Align must be power of two.", align );

      const std::uintptr_t address     = reinterpret_cast<std::uintptr_t>(*ptr);
      const std::uintptr_t new_address = ((address + offset + static_cast<std::uintptr_t>(align-1)) & static_cast<std::uintptr_t>(~(align-1))) - offset;
      *ptr = reinterpret_cast<void*>(new_address);

      return static_cast<size_t>( new_address - address );
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
      new (ptr) T(other);
      return static_cast<T*>(ptr);
    }


    template<typename T, typename...Args>
    inline T* uninitialized_construct_at( void* ptr, Args&&...args )
    {
      new (ptr) T( std::forward<Args>(args)... );
      return static_cast<T*>(ptr);
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
    // C++17 features
    //------------------------------------------------------------------------

    inline namespace cpp17 {

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

    } // namespace cpp17

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

  } // inline namespace stl
} // namespace bit

#endif /* BIT_DETAIL_MEMORY_INL */
