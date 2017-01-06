#ifndef BIT_STL_INTERNAL_MEMORY_SMART_PTR_HPP
#define BIT_STL_INTERNAL_MEMORY_SMART_PTR_HPP

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Deleters
    //------------------------------------------------------------------------

    /// \brief
    ///
    template<typename T>
    struct dtor_deleter
    {
      void operator()( T* instance )
      {
        instance->~T();
      }
    };

    /// \brief
    ///
    struct free_deleter
    {
      void operator()( void* instance )
      {
        std::free( instance );
      }
    };

    //------------------------------------------------------------------------
    // Unique Pointer Types
    //------------------------------------------------------------------------

    template<typename T>
    using unique_dtor_ptr = std::unique_ptr<T,dtor_deleter<T>>;

    template<typename T>
    using unique_free_ptr = std::unique_ptr<T,free_deleter>;

    template<typename T>
    constexpr unique_free_ptr<T> make_unique_free( T* ptr )
    {
      return unique_free_ptr<T>( ptr );
    }

    template<typename T>
    constexpr unique_dtor_ptr<T> make_unique_dtor( T* ptr )
    {
      return unique_dtor_ptr<T>( ptr );
    }


    template<typename Allocator, typename T, typename...Args>
    std::shared_ptr<T> allocate_shared( const Allocator& allocator, Args&&...args )
    {
      return std::allocate_shared<T>( allocator, args... );
    }


  } // namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_MEMORY_SMART_PTR_HPP */
