#ifndef BIT_STL_UTILITIES_DETAIL_LAZY_INL
#define BIT_STL_UTILITIES_DETAIL_LAZY_INL

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------

    template<typename T>
    inline lazy<T>::lazy()
      noexcept
      : m_ctor_function(+[](void* ptr){ uninitialized_tuple_construct_at<T>(ptr, std::forward_as_tuple() ); }),
        m_storage(),
        m_is_initialized(false)
    {

    }

    //------------------------------------------------------------------------

    template<typename T>
    inline lazy<T>::lazy( const lazy& other )
      : m_ctor_function(other.m_ctor_function),
        m_is_initialized(other.m_is_initialized)
    {
      if(m_is_initialized) {
        uninitialized_tuple_construct_at<T>( std::addressof(m_storage), std::forward_as_tuple(*other) );
      }
    }


    template<typename T>
    inline lazy<T>::lazy( lazy&& other )
      : m_ctor_function(std::move(other.m_ctor_function)),
        m_is_initialized(std::move(other.m_is_initialized))
    {
      if( m_is_initialized ) {
        uninitialized_tuple_construct_at<T>( std::addressof(m_storage), std::forward_as_tuple( *std::move(other) ) );
      }
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_enabled_copy_ctor<T,U>::value && !std::is_convertible<const U&, T>::value>*>
    inline lazy<T>::lazy( const lazy<U>& other )
      : m_ctor_function(nullptr),
        m_is_initialized(other.m_is_initialized)
    {
      if( m_is_initialized ) {
        uninitialized_tuple_construct_at<T>( std::addressof(m_storage), std::forward_as_tuple( *other ) );
      } else {
        auto  copy = other;
        auto& ref  = other.value();

        m_ctor_function = [ref]( void* ptr )
          mutable
        {
          uninitialized_tuple_construct_at<T>( ptr, std::forward_as_tuple( std::move(ref) ) );
        };
      }
    }


    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_enabled_copy_ctor<T,U>::value && std::is_convertible<const U&, T>::value>*>
    inline lazy<T>::lazy( const lazy<U>& other )
      : m_ctor_function(nullptr),
        m_is_initialized(other.m_is_initialized)
    {
      if( m_is_initialized ) {
        uninitialized_tuple_construct_at<T>( std::addressof(m_storage), std::forward_as_tuple( *other ) );
      } else {
        auto  copy = other;
        auto& ref  = other.value();

        m_ctor_function = [ref]( void* ptr )
          mutable
        {
          uninitialized_tuple_construct_at<T>( ptr, std::forward_as_tuple( std::move(ref) ) );
        };
      }
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_enabled_move_ctor<T,U>::value && !std::is_convertible<U&&, T>::value>*>
    inline lazy<T>::lazy( lazy<U>&& other )
      : m_ctor_function(nullptr),
        m_is_initialized(std::move(other.m_is_initialized))
    {
      if( m_is_initialized ) {
        uninitialized_tuple_construct_at<T>( std::addressof(m_storage), std::forward_as_tuple( *std::move(other) ) );
      } else {
        auto&& ref  = std::move(other).value();

        m_ctor_function = [ref]( void* ptr )
          mutable
        {
          uninitialized_tuple_construct_at<T>( ptr, std::forward_as_tuple( std::move(ref) ) );
        };
      }
    }


    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_enabled_move_ctor<T,U>::value && std::is_convertible<U&&, T>::value>*>
    inline lazy<T>::lazy( lazy<U>&& other )
      : m_ctor_function(nullptr),
        m_is_initialized(std::move(other.m_is_initialized))
    {
      if( m_is_initialized ) {
        uninitialized_tuple_construct_at<T>( std::addressof(m_storage), std::forward_as_tuple( *std::move(other) ) );
      } else {
        auto&& ref  = std::move(other).value();

        m_ctor_function = [ref]( void* ptr )
          mutable
        {
          uninitialized_tuple_construct_at<T>( ptr, std::forward_as_tuple( std::move(ref) ) );
        };
      }
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename...Args, typename>
    inline lazy<T>::lazy( in_place_t, Args&&... args )
      : m_ctor_function(nullptr),
        m_is_initialized(false)
    {
      auto arg_tuple = std::make_tuple( std::forward<Args>(args)... );

      m_ctor_function = [arg_tuple]( void* ptr )
        mutable
      {
        uninitialized_tuple_construct_at<T>( ptr, std::move(arg_tuple) );
      };
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, typename...Args, typename>
    inline lazy<T>::lazy( in_place_t, std::initializer_list<U> ilist, Args&&... args )
      : m_ctor_function(nullptr),
        m_is_initialized(false)
    {
      auto arg_tuple = std::make_tuple( std::move(ilist), std::forward<Args>(args)... );

      m_ctor_function = [arg_tuple]( void* ptr )
        mutable
      {
        uninitialized_tuple_construct_at<T>( ptr, std::move(arg_tuple) );
      };
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_direct_initializable<T,U>::value && std::is_convertible<U&&, T>::value>*>
    inline lazy<T>::lazy( U&& other )
      : m_ctor_function([other](void* ptr) mutable { uninitialized_tuple_construct_at<T>(ptr, std::forward_as_tuple( std::move(other) ) );} ),
        m_is_initialized(false)
    {

    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_direct_initializable<T,U>::value && !std::is_convertible<U&&, T>::value>*>
    inline lazy<T>::lazy( U&& other )
      : m_ctor_function([other](void* ptr) mutable { uninitialized_tuple_construct_at<T>(ptr, std::forward_as_tuple( std::move(other) ) );} ),
        m_is_initialized(false)
    {

    }

    //------------------------------------------------------------------------

    template<typename T>
    inline lazy<T>::~lazy()
    {
      destruct();
    }

    //------------------------------------------------------------------------
    // Assignment
    //------------------------------------------------------------------------

    template<typename T>
    inline lazy<T>& lazy<T>::operator=( const lazy& other )
    {
      if( m_is_initialized && other.m_is_initialized ) {
        (*ptr()) = (*other);
      } else if( m_is_initialized ) {
        (*ptr()) = other.value();
      } else if( other.m_is_initialized ) {
        value() = (*other);
      } else {
        m_ctor_function = other.m_ctor_function;
      }
      return (*this);
    }


    template<typename T>
    inline lazy<T>& lazy<T>::operator=( lazy&& other )
    {
      if( m_is_initialized && other.m_is_initialized ) {
        (*ptr()) = *std::move(other);
      } else if( m_is_initialized ) {
        (*ptr()) = std::move(other).value();
      } else if( other.m_is_initialized ) {
        value() = *std::move(other);
      } else {
        m_ctor_function = std::move(other.m_ctor_function);
      }
      return (*this);
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_enabled_copy_assignment<T,U>::value>*>
    inline lazy<T>& lazy<T>::operator=( const lazy<U>& other )
    {
      if( m_is_initialized && other.m_is_initialized ) {
        (*ptr()) = (*other);
      } else if( m_is_initialized ) {
        (*ptr()) = other.value();
      } else if( other.m_is_initialized ) {
        value() = *other;
      } else {
        auto  copy = other;
        auto& ref  = other.value();

        m_ctor_function = [ref](void* ptr)
        {
          uninitialized_tuple_construct_at<T>( ptr, std::forward_as_tuple( std::move(ref) ) );
        };
      }
      return (*this);
    }


    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_enabled_move_assignment<T,U>::value>*>
    inline lazy<T>& lazy<T>::operator=( lazy<U>&& other )
    {
      if( m_is_initialized && other.m_is_initialized ) {
        (*ptr()) = *std::move(other);
      } else if( m_is_initialized ) {
        (*ptr()) = std::move(other).value();
      } else if( other.m_is_initialized ) {
        value() = *std::move(other);
      } else {
        auto&& ref  = std::move(other).value();

        m_ctor_function = [ref](void* ptr)
        {
          uninitialized_tuple_construct_at<T>( ptr, std::forward_as_tuple( std::move(ref) ) );
        };
      }
      return (*this);
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U, std::enable_if_t<detail::lazy_is_direct_init_assignable<T,U>::value>*>
    inline lazy<T>& lazy<T>::operator=( U&& value )
    {
      this->value() = std::forward<U>(value);
      return (*this);
    }

    //------------------------------------------------------------------------
    // Modifiers
    //------------------------------------------------------------------------

    template<typename T>
    inline void lazy<T>::initialize()
      const
    {
      lazy_construct();
    }

    template<typename T>
    inline void lazy<T>::reset()
    {
      destruct();
    }

    template<typename T>
    inline void lazy<T>::swap( lazy& other )
    {
      using std::swap;

      if( m_is_initialized && other.m_is_initialized ) {
        swap(*ptr(),*other);
      } else if( m_is_initialized ) {
        swap(*ptr(),other.value());
      } else if( other.m_is_initialized ) {
        swap(value(),*other);
      } else {
        swap(m_ctor_function, other.m_ctor_function);
      }
    }

    //------------------------------------------------------------------------
    // Observers
    //------------------------------------------------------------------------

    template<typename T>
    inline lazy<T>::operator bool()
      const noexcept
    {
      return m_is_initialized;
    }


    template<typename T>
    inline bool lazy<T>::has_value()
      const noexcept
    {
      return m_is_initialized;
    }

    //------------------------------------------------------------------------

    template<typename T>
    inline typename lazy<T>::value_type* lazy<T>::operator->()
    {
      return ptr();
    }


    template<typename T>
    inline const typename lazy<T>::value_type* lazy<T>::operator->()
      const
    {
      return ptr();
    }


    template<typename T>
    inline typename lazy<T>::value_type& lazy<T>::operator*()
      &
    {
      return *ptr();
    }


    template<typename T>
    inline const typename lazy<T>::value_type& lazy<T>::operator*()
      const &
    {
      return *ptr();
    }


    template<typename T>
    inline typename lazy<T>::value_type&& lazy<T>::operator*()
      &&
    {
      return std::move(*ptr());
    }


    template<typename T>
    inline const typename lazy<T>::value_type&& lazy<T>::operator*()
      const &&
    {
      return std::move(*ptr());
    }

    //------------------------------------------------------------------------

    template<typename T>
    inline typename lazy<T>::value_type& lazy<T>::value()
      &
    {
      lazy_construct();
      return *ptr();
    }


    template<typename T>
    inline const typename lazy<T>::value_type& lazy<T>::value()
      const &
    {
      lazy_construct();
      return *ptr();
    }


    template<typename T>
    inline typename lazy<T>::value_type&& lazy<T>::value()
      &&
    {
      lazy_construct();
      return std::move(*ptr());
    }


    template<typename T>
    inline const typename lazy<T>::value_type&& lazy<T>::value()
      const &&
    {
      lazy_construct();
      return std::move(*ptr());
    }

    //------------------------------------------------------------------------

    template<typename T>
    template<typename U>
    inline typename lazy<T>::value_type lazy<T>::value_or( U&& default_value )
      const &
    {
      return has_value() ? (*ptr()) : std::forward<U>(default_value);
    }


    template<typename T>
    template<typename U>
    inline typename lazy<T>::value_type lazy<T>::value_or( U&& default_value )
      &&
    {
      return has_value() ? (*ptr()) : std::forward<U>(default_value);
    }


    //------------------------------------------------------------------------
    // Private Constructor
    //------------------------------------------------------------------------

    template<typename T>
    template<typename Ctor>
    inline lazy<T>::lazy( ctor_tag, Ctor&& ctor )
      : m_ctor_function([ctor](void* ptr){ uninitialized_tuple_construct_at<T>(ptr, ctor()); }),
        m_is_initialized(false)
    {

    }

    //------------------------------------------------------------------------
    // Private Member Functions
    //------------------------------------------------------------------------

    template<typename T>
    inline typename lazy<T>::value_type* lazy<T>::ptr()
      const
    {
      return static_cast<value_type*>( static_cast<void*>( std::addressof(m_storage) ) );
    }


    template<typename T>
    inline void lazy<T>::lazy_construct() const
    {
      if(!m_is_initialized) {
        m_ctor_function( std::addressof(m_storage) );
        m_is_initialized = true;
      }
    }


    template<typename T>
    inline void lazy<T>::destruct()
    {
      if(m_is_initialized) {
        destroy_at<T>( static_cast<T*>(static_cast<void*>(std::addressof(m_storage))) );
        m_is_initialized = false;
      }
    }

    //------------------------------------------------------------------------
    // Utilities
    //------------------------------------------------------------------------

    template<typename T>
    inline std::size_t hash_value( const lazy<T>& val )
    {
      return hash_value( val.value() );
    }

    //------------------------------------------------------------------------

    template<typename T, typename...Args>
    inline lazy<T> make_lazy( Args&&...args )
    {
      return lazy<T>( in_place, std::forward<Args>(args)... );
    }

    template<typename T, typename U, typename...Args>
    inline lazy<T> make_lazy( std::initializer_list<U> ilist, Args&&...args )
    {
      return lazy<T>( in_place, std::move(ilist), std::forward<Args>(args)... );
    }

    template<typename T, typename Ctor>
    lazy<T> make_lazy_generator( Ctor&& ctor )
    {
      return lazy<T>( typename lazy<T>::ctor_tag{}, std::forward<Ctor>(ctor) );
    }


    //------------------------------------------------------------------------

    template<typename T>
    inline void swap( lazy<T>& lhs, lazy<T>& rhs )
    {
      lhs.swap(rhs);
    }

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    template<typename T>
    inline bool operator==( const lazy<T>& lhs, const lazy<T>& rhs )
    {
      return lhs.value() == rhs.value();
    }

    template<typename T>
    inline bool operator==( const lazy<T>& lhs, const T& rhs )
    {
      return lhs.value() == rhs;
    }

    template<typename T>
    inline bool operator==( const T& lhs, const lazy<T>& rhs )
    {
      return lhs == rhs.value();
    }

    //------------------------------------------------------------------------

    template<typename T>
    inline bool operator!=( const lazy<T>& lhs, const lazy<T>& rhs )
    {
      return lhs.value() != rhs.value();
    }

    template<typename T>
    inline bool operator!=( const lazy<T>& lhs, const T& rhs )
    {
      return lhs.value() != rhs;
    }

    template<typename T>
    inline bool operator!=( const T& lhs, const lazy<T>& rhs )
    {
      return lhs != rhs.value();
    }

    //------------------------------------------------------------------------

    template<typename T>
    inline bool operator<( const lazy<T>& lhs, const lazy<T>& rhs )
    {
      return lhs.value() < rhs.value();
    }

    template<typename T>
    inline bool operator<( const lazy<T>& lhs, const T& rhs )
    {
      return lhs.value() < rhs;
    }

    template<typename T>
    inline bool operator<( const T& lhs, const lazy<T>& rhs )
    {
      return lhs < rhs.value();
    }

    //------------------------------------------------------------------------

    template<typename T>
    inline bool operator<=( const lazy<T>& lhs, const lazy<T>& rhs )
    {
      return lhs.value() <= rhs.value();
    }

    template<typename T>
    inline bool operator<=( const lazy<T>& lhs, const T& rhs )
    {
      return lhs.value() <= rhs;
    }

    template<typename T>
    inline bool operator<=( const T& lhs, const lazy<T>& rhs )
    {
      return lhs <= rhs.value();
    }

    //------------------------------------------------------------------------
    template<typename T>
    inline bool operator>( const lazy<T>& lhs, const lazy<T>& rhs )
    {
      return lhs.value() > rhs.value();
    }

    template<typename T>
    inline bool operator>( const lazy<T>& lhs, const T& rhs )
    {
      return lhs.value() > rhs;
    }

    template<typename T>
    inline bool operator>( const T& lhs, const lazy<T>& rhs )
    {
      return lhs > rhs.value();
    }

    //------------------------------------------------------------------------

    template<typename T>
    inline bool operator>=( const lazy<T>& lhs, const lazy<T>& rhs )
    {
      return lhs.value() >= rhs.value();
    }

    template<typename T>
    inline bool operator>=( const lazy<T>& lhs, const T& rhs )
    {
      return lhs.value() >= rhs;
    }

    template<typename T>
    inline bool operator>=( const T& lhs, const lazy<T>& rhs )
    {
      return lhs >= rhs.value();
    }


  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_LAZY_INL */
