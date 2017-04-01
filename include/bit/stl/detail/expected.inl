#ifndef BIT_STL_DETAIL_EXPECTED_INL
#define BIT_STL_DETAIL_EXPECTED_INL

//----------------------------------------------------------------------------
// Constructors / Assignment / Destructor
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::expected<T>::expected()
  noexcept( std::is_nothrow_default_constructible<T>::value )
  : m_storage( in_place<T> ),
    m_is_exception(false)
{

}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::expected<T>::expected( in_place_type_t<std::exception_ptr> )
  : expected( in_place<std::exception_ptr>, std::current_exception() )
{

}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::expected<T>::
  expected( in_place_type_t<std::exception_ptr>, std::exception_ptr ptr )
  : m_storage( in_place<std::exception_ptr>,
               ptr ? std::move(ptr) :
                     std::make_exception_ptr(bad_expected_access()) ),
    m_is_exception(true)
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename Exception, typename...Args>
inline bit::stl::expected<T>::
  expected( in_place_type_t<Exception>, Args&&...args )
  noexcept( std::is_nothrow_constructible<Exception,Args...>::value )
  : expected( in_place<std::exception_ptr>,
              std::make_exception_ptr(Exception(std::forward<Args>(args)...)))
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename Exception, typename U, typename...Args>
inline bit::stl::expected<T>::
  expected( in_place_type_t<Exception>,
            std::initializer_list<U> ilist, Args&&...args )
  noexcept( std::is_nothrow_constructible<Exception,std::initializer_list<U>,Args...>::value )
  : expected( in_place<std::exception_ptr>,
              std::make_exception_ptr( Exception( ilist, std::forward<Args>(args)... ) ) )
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename...Args>
inline constexpr bit::stl::expected<T>::
  expected( in_place_t, Args&&...args )
  noexcept( std::is_nothrow_constructible<Args...>::value )
  : m_storage( in_place<T>, std::forward<Args>(args)... ),
    m_is_exception(false)
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U, typename...Args>
inline constexpr bit::stl::expected<T>::
  expected( in_place_t, std::initializer_list<U> ilist, Args&&...args )
  noexcept( std::is_nothrow_constructible<std::initializer_list<U>,Args...>::value )
  : m_storage( in_place<T>, ilist, std::forward<Args>(args)... ),
    m_is_exception(false)
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::expected<T>::expected( const T& value )
  noexcept( std::is_nothrow_copy_constructible<T>::value )
  : m_storage( in_place<T>, value ),
    m_is_exception(false)
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::expected<T>::expected( T&& value )
  noexcept( std::is_nothrow_move_constructible<T>::value )
  : m_storage( in_place<T>, std::move(value) ),
    m_is_exception(false)
{

}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::expected<T>::expected( const expected<T>& other )
  : m_storage(),
    m_is_exception(other.m_is_exception)
{
  if(other.m_is_exception) {
    new (&m_storage.exception) std::exception_ptr(other.m_storage.exception);
  } else {
    new (&m_storage.value) value_type(other.m_storage.value);
  }
}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::expected<T>::expected( expected<T>&& other )
  : m_storage(),
    m_is_exception(other.m_is_exception)
{
  if(other.m_is_exception) {
    new (&m_storage.exception) std::exception_ptr( std::move(other.m_storage.exception) );
  } else {
    new (&m_storage.value) value_type( std::move(other.m_storage.value) );
  }
}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::expected<T>&
  bit::stl::expected<T>::operator=( const expected<T>& other )
{
  if( m_is_exception == other.m_is_exception ) {
    if( other.m_is_exception ) {
      m_storage.exception = other.m_storage.exception;
    } else {
      m_storage.value = other.m_storage.value;
    }
  } else {
    if( other.m_is_exception ) {
      reconstruct_exception(*this, other.m_storage.exception );
    } else {
      reconstruct_value(*this, other.m_storage.value);
    }
  }
}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::expected<T>&
  bit::stl::expected<T>::operator=( expected<T>&& other )
{
  if( m_is_exception == other.m_is_exception )
  {
    if( other.m_is_exception )
    {
      m_storage.exception = std::move(other.m_storage.exception);
    }
    else
    {
      m_storage.value = std::move(other.m_storage.value);
    }
  }
  else
  {
    if( other.m_is_exception )
    {
      reconstruct_exception(*this, std::move(other.m_storage.exception) );
    }
    else
    {
      reconstruct_value(*this, std::move(other.m_storage.value) );
    }
  }
}

template<typename T>
inline bit::stl::expected<T>::~expected()
{
  destruct();
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::expected<T>::operator bool()
  const noexcept
{
  return !m_is_exception;
}

template<typename T>
inline constexpr bool bit::stl::expected<T>::valueless_by_exception()
  const noexcept
{
  return m_is_exception && m_storage.exception == nullptr;
}

template<typename T>
inline constexpr bool bit::stl::expected<T>::has_value()
  const noexcept
{
  return !m_is_exception;
}

template<typename T>
template<typename Exception>
inline bool bit::stl::expected<T>::has_exception()
  const noexcept
{
  if( !m_is_exception ) return false;
  if( !m_storage.exception ) return false;

  try
  {
    std::rethrow_exception( m_storage.exception );
  }
  catch ( const Exception& )
  {
    return true;
  }
  catch ( ... )
  {
    return false;
  }
  return false; // this case shouldn't be hit
}

template<typename T>
inline bool bit::stl::expected<T>::has_exception()
  const noexcept
{
  return m_is_exception;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::expected<T>::value_type*
  bit::stl::expected<T>::operator->()
  noexcept
{
  return std::addressof(m_storage.value);
}

template<typename T>
inline constexpr const typename bit::stl::expected<T>::value_type*
  bit::stl::expected<T>::operator->()
  const noexcept
{
  return std::addressof(m_storage.value);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::expected<T>::value_type&
  bit::stl::expected<T>::operator*()
  & noexcept
{
  return m_storage.value;
}

template<typename T>
inline constexpr typename bit::stl::expected<T>::value_type&&
  bit::stl::expected<T>::operator*()
  && noexcept
{
  return std::move(m_storage.value);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr const typename bit::stl::expected<T>::value_type&
  bit::stl::expected<T>::operator*()
  const & noexcept
{
  return m_storage.value;
}

template<typename T>
inline constexpr const typename bit::stl::expected<T>::value_type&&
  bit::stl::expected<T>::operator*()
  const && noexcept
{
  return std::move(m_storage.value);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::expected<T>::value_type&
  bit::stl::expected<T>::value()
  &
{
  throw_if_exception();
  return m_storage.value;
}

template<typename T>
inline constexpr const typename bit::stl::expected<T>::value_type&
  bit::stl::expected<T>::value()
  const &
{
  throw_if_exception();
  return m_storage.value;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::expected<T>::value_type&&
  bit::stl::expected<T>::value()
  &&
{
  throw_if_exception();
  return std::move(m_storage.value);
}

template<typename T>
inline constexpr const typename bit::stl::expected<T>::value_type&&
  bit::stl::expected<T>::value()
  const &&
{
  throw_if_exception();
  return std::move(m_storage.value);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr typename bit::stl::expected<T>::value_type
  bit::stl::expected<T>::value_or( U&& default_value )
  const &
{
  return !m_is_exception ? m_storage.value : static_cast<T>(std::forward<U>(default_value));
}

template<typename T>
template<typename U>
inline constexpr typename bit::stl::expected<T>::value_type
bit::stl::expected<T>::value_or( U&& default_value )
  &&
{
  return !m_is_exception ? std::move(m_storage.value) : static_cast<T>(std::forward<U>(default_value));
}

//----------------------------------------------------------------------------
// Mutators
//----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::expected<T>::swap( expected<T>& rhs )
  noexcept
{
  using std::swap;

  if( m_is_exception == rhs.m_is_exception )
  {
    if( m_is_exception )
    {
      swap( m_storage.exception, rhs.m_storage.exception );
    }
    else
    {
      swap( m_storage.value, rhs.m_storage.value );
    }
  }
  else
  {
    if( m_is_exception )
    {
      auto exception = std::move(m_storage.exception);

      reconstruct_value( *this, std::move(rhs.m_storage.value) );
      reconstruct_exception( rhs, std::move(exception) );
    }
    else
    {
      auto value = std::move(m_storage.value);

      reconstruct_exception( *this, std::move(rhs.m_storage.exception) );
      reconstruct_value( rhs, std::move(value) );
    }
  }
}

template<typename T>
template<typename...Args>
inline void bit::stl::expected<T>::emplace( Args&&...args )
  noexcept( std::is_nothrow_constructible<T,Args...>::value )
{
  reconstruct_value( *this, std::forward<Args>(args)... );
}

template<typename T>
template<typename U, typename...Args>
inline void
  bit::stl::expected<T>::emplace( std::initializer_list<U> ilist,
                                  Args&&...args )
  noexcept( std::is_nothrow_constructible<T,std::initializer_list<U>,Args...>::value )
{
  reconstruct_value( *this, ilist, std::forward<Args>(args)... );
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::expected<T>::throw_if_exception()
  const
{
  if( m_is_exception )
  {
    if( m_storage.exception )
    {
      std::rethrow_exception( m_storage.exception );
    }
    else
    {
      throw bad_expected_access();
    }
  }
}

template<typename T>
inline void bit::stl::expected<T>::destruct()
{
  if( m_is_exception )
  {
    m_storage.exception.~exception_ptr();
  }
  else
  {
    m_storage.value.~T();
  }
}

template<typename T>
template<typename...Args>
inline void
  bit::stl::expected<T>::reconstruct_value( expected<T>& expected,
                                            Args&&...args )
{

  try {
    expected.destruct();
    new (&expected.m_storage.value) value_type( std::forward<Args>(args)... );
    expected.m_is_exception = false;
  } catch (...) {
    new (&expected.m_storage.exception) std::exception_ptr( nullptr );
    expected.m_is_exception = true;
    throw;
  }
}

template<typename T>
template<typename...Args>
inline void
  bit::stl::expected<T>::reconstruct_exception( expected<T>& expected,
                                                Args&&...args )
{
  try {
    expected.destruct();
    new (&expected.m_storage.exception) std::exception_ptr( std::forward<Args>(args)... );
    expected.m_is_exception = true;
  } catch (...) {
    new (&expected.m_storage.exception) std::exception_ptr( nullptr );
    expected.m_is_exception = true;
    throw;
  }
}

//----------------------------------------------------------------------------
// Comparison Operators
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool
  bit::stl::operator == ( const expected<T>& lhs, const expected<T>& rhs )
  noexcept
{
  if( bool(lhs)!=bool(rhs) ) return false;
  if( bool(lhs)==false ) return true;
  return *lhs == *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator != ( const expected<T>& lhs, const expected<T>& rhs )
  noexcept
{
  if( bool(lhs)!=bool(rhs) ) return true;
  if( bool(lhs)==false ) return false;
  return *lhs != *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator < ( const expected<T>& lhs, const expected<T>& rhs )
  noexcept
{
  if( bool(rhs)==false ) return false;
  if( bool(lhs)==false ) return true;
  return *lhs < *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator <= ( const expected<T>& lhs, const expected<T>& rhs )
  noexcept
{
  if( bool(lhs) == false ) return true;
  if( bool(rhs) == false ) return false;
  return *lhs <= *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator > ( const expected<T>& lhs, const expected<T>& rhs )
  noexcept
{
  if( bool(lhs) == false ) return false;
  if( bool(rhs) == false ) return true;
  return *lhs > *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator >= ( const expected<T>& lhs, const expected<T>& rhs )
  noexcept
{
  if( bool(rhs)==false ) return true;
  if( bool(lhs)==false ) return false;
  return *lhs >= *rhs;
}

//----------------------------------------------------------------------------
// Compare an optional object with a T
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool
  bit::stl::operator == ( const T& lhs, const expected<T>& rhs )
  noexcept
{
  return bool(rhs) ? lhs == *rhs : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator == ( const expected<T>& lhs, const T& rhs )
  noexcept
{
  return rhs == lhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator != ( const T& lhs, const expected<T>& rhs )
  noexcept
{
  return bool(rhs) ? lhs != *rhs : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator != ( const expected<T>& lhs, const T& rhs )
  noexcept
{
  return rhs != lhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator < ( const T& lhs, const expected<T>& rhs )
  noexcept
{
  return bool(rhs) ? lhs < *rhs : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator < ( const expected<T>& lhs, const T& rhs )
  noexcept
{
  return rhs >= lhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator <= ( const T& lhs, const expected<T>& rhs )
  noexcept
{
  return bool(rhs) ? lhs <= *rhs : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator <= ( const expected<T>& lhs, const T& rhs )
  noexcept
{
  return rhs > lhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator > ( const T& lhs, const expected<T>& rhs )
  noexcept
{
  return bool(rhs) ? lhs > *rhs : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator > ( const expected<T>& lhs, const T& rhs )
  noexcept
{
  return rhs <= lhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator >= ( const T& lhs, const expected<T>& rhs )
  noexcept
{
  return bool(rhs) ? lhs >= *rhs : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator >= ( const expected<T>& lhs, const T& rhs )
  noexcept
{
  return rhs < lhs;
}

//----------------------------------------------------------------------------
// Inline Definitions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::expected<std::decay_t<T>>
  bit::stl::make_expected( T&& value )
  noexcept( noexcept( expected<std::decay_t<T>>( std::forward<T>(value) ) ) )
{
  return expected<std::decay_t<T>>( std::forward<T>(value) );
}


template<typename T, typename...Args>
inline constexpr bit::stl::expected<T>
  bit::stl::make_expected( Args&&...args )
  noexcept( noexcept( expected<T>( std::forward<Args>(args)... ) ) )
{
  return expected<T>( in_place<T>, std::forward<Args>(args)... );
}


template<typename T, typename U, typename... Args >
constexpr bit::stl::expected<T>
  bit::stl::make_expected( std::initializer_list<U> il, Args&&... args )
  noexcept( noexcept( expected<T>( il, std::forward<Args>(args)... ) ) )
{
  return expected<T>( in_place<T>, il, std::forward<Args>(args)... );
}


template<typename T>
inline constexpr std::size_t bit::stl::hash_value( const expected<T>& val )
  noexcept
{
  if( val ) {
    return hash_value( val.value() );
  }
  return 0;
}

#endif /* BIT_STL_DETAIL_EXPECTED_INL */
