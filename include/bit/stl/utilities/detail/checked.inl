#ifndef BIT_STL_UTILITIES_DETAIL_CHECKED_INL
#define BIT_STL_UTILITIES_DETAIL_CHECKED_INL

//============================================================================
// error
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::stl::error_code::error_code( error_code&& other )
  noexcept
  : m_error_code( std::move(other.m_error_code) ),
    m_category( std::move(other.m_category) )
{
  other.m_error_code = 0;
  other.m_category   = nullptr;
}

template<typename Enum, std::enable_if_t<std::is_enum<Enum>::value>*>
inline bit::stl::error_code::
  error_code( Enum value, const std::error_category& category )
  noexcept
  : error_code( static_cast<int>(value), category )
{

}

inline bit::stl::error_code::
  error_code( int value, const std::error_category& category )
  noexcept
  : m_error_code( value ),
    m_category(std::addressof(category))
{

}

//------------------------------------------------------------------------
// Public Static Functions
//------------------------------------------------------------------------

inline bit::stl::error_code bit::stl::error_code::success()
  noexcept
{
  return error_code();
}

//------------------------------------------------------------------------
// Observers
//------------------------------------------------------------------------

inline int bit::stl::error_code::value()
  const noexcept
{
  return m_error_code;
}

inline const std::error_category* bit::stl::error_code::category()
  const noexcept
{
  return m_category;
}

inline std::string bit::stl::error_code::message()
  const
{
  return m_category ? m_category->message(m_error_code) : "No error";
}

inline bool bit::stl::error_code::is_error()
  const noexcept
{
  return m_category;
}

inline bit::stl::error_code::operator bool()
  const noexcept
{
  return is_error();
}

//------------------------------------------------------------------------
// Private Constructors
//------------------------------------------------------------------------

inline bit::stl::error_code::error_code()
  noexcept
  : m_error_code(0),
    m_category(nullptr)
{

}

//------------------------------------------------------------------------
// Free Functions
//------------------------------------------------------------------------

template<typename Error, std::enable_if_t<std::is_enum<Error>::value>*>
inline bit::stl::error_code
  bit::stl::make_error( Error error, const std::error_category& category )
  noexcept
{
  return error_code(error,category);
}

inline bit::stl::error_code
  bit::stl::make_error( int error, const std::error_category& category )
  noexcept
{
  return error_code(error,category);
}

//========================================================================
// checked
//========================================================================

//------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------

template<typename T>
inline bit::stl::checked<T>::checked()
  noexcept( std::is_nothrow_default_constructible<T>::value )
  : m_storage( stl::in_place<T> ),
    m_is_checked( false ),
    m_has_value( true )
{

}

template<typename T>
inline bit::stl::checked<T>::checked( error_code err )
  noexcept
  : m_storage( std::move(err) ),
    m_is_checked( false ),
    m_has_value( false )
{

}

//------------------------------------------------------------------------

template<typename T>
inline bit::stl::checked<T>::checked( checked&& other )
  noexcept( std::is_nothrow_move_constructible<T>::value )
  : m_storage(),
    m_is_checked( other.m_is_checked ),
    m_has_value( other.m_has_value )
{
  if( m_has_value ) {
    new (&m_storage.value) value_type( std::move(other.m_storage.value) );
  } else {
    new (&m_storage.error) error_type( std::move(other.m_storage.error) );
  }
  other.m_is_checked = true;
}

//------------------------------------------------------------------------

template<typename T>
template<typename U, std::enable_if_t<bit::stl::detail::checked_is_enabled_move_ctor<T,U>::value && !std::is_convertible<U&&, T>::value>*>
inline bit::stl::checked<T>::checked( checked<U>&& other )
  noexcept( std::is_nothrow_constructible<T,U&&>::value )
  : m_storage(),
    m_is_checked( other.m_is_checked ),
    m_has_value( other.m_has_value )
{
  if( m_has_value ) {
    new (&m_storage.value) value_type( std::move(other.m_storage.value) );
  } else {
    new (&m_storage.error) error_type( std::move(other.m_storage.error) );
  }
  other.m_is_checked = true;
}

template<typename T>
template<typename U, std::enable_if_t<bit::stl::detail::checked_is_enabled_move_ctor<T,U>::value && std::is_convertible<U&&, T>::value>*>
inline bit::stl::checked<T>::checked( checked<U>&& other )
  noexcept( std::is_nothrow_constructible<T,U&&>::value )
  : m_storage(),
    m_is_checked( other.m_is_checked ),
    m_has_value( other.m_has_value )
{
  if( m_has_value ) {
    new (&m_storage.value) value_type( std::move(other.m_storage.value) );
  } else {
    new (&m_storage.error) error_type( std::move(other.m_storage.error) );
  }
  other.m_is_checked = true;
}

//------------------------------------------------------------------------

template<typename T>
template<typename...Args>
inline bit::stl::checked<T>::checked( in_place_t, Args&&...args )
  noexcept(std::is_nothrow_constructible<T,Args...>::value)
  : m_storage( in_place<T>, std::forward<Args>(args)... ),
    m_is_checked( false ),
    m_has_value( true )
{

}

template<typename T>
template<typename U, typename...Args>
inline bit::stl::checked<T>::
  checked( in_place_t, std::initializer_list<U> ilist, Args&&...args )
  noexcept(std::is_nothrow_constructible<T,std::initializer_list<U>,Args...>::value)
  : m_storage( in_place<T>, ilist, std::forward<Args>(args)... ),
    m_is_checked( false ),
    m_has_value( true )
{

}

//------------------------------------------------------------------------

template<typename T>
template<typename U, std::enable_if_t<bit::stl::detail::checked_is_direct_initializable<T,U>::value && !bit::stl::is_callable<U&>::value && std::is_convertible<U&&, T>::value>*>
inline bit::stl::checked<T>::checked( U&& value )
  noexcept(std::is_nothrow_constructible<T,U>::value)
  : m_storage( in_place<T>, std::forward<U>(value) ),
    m_is_checked( false ),
    m_has_value( true )
{

}

template<typename T>
template<typename U, std::enable_if_t<bit::stl::detail::checked_is_direct_initializable<T,U>::value && !bit::stl::is_callable<U&>::value && !std::is_convertible<U&&, T>::value>*>
inline bit::stl::checked<T>::checked( U&& value )
  noexcept(std::is_nothrow_constructible<T,U>::value)
  : m_storage( in_place<T>, std::forward<U>(value) ),
    m_is_checked( false ),
    m_has_value( true )
{

}

//------------------------------------------------------------------------

template<typename T>
inline bit::stl::checked<T>::~checked()
{
  destruct();

  abort_if_unchecked();
}

//------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------

template<typename T>
inline bit::stl::checked<T>&
  bit::stl::checked<T>::operator=( checked<T>&& other )
  noexcept
{
  if( m_has_value == other.m_has_value) {
    if( m_has_value ) {
      m_storage.value = std::move(other.m_storage.value);
    } else {
      m_storage.error = std::move(other.m_storage.error);
    }
  } else {
    destruct();
    if( other.m_has_value ) {
      new (std::addressof(m_storage.value)) value_type( std::move(other.m_storage.value) );
    } else {
      new (std::addressof(m_storage.error)) error_type( std::move(other.m_storage.error) );
    }
  }

  m_is_checked = other.m_is_checked;
  m_has_value = other.m_has_value;
  other.m_is_checked = true;

  return (*this);
}

//------------------------------------------------------------------------
// Observers
//------------------------------------------------------------------------

template<typename T>
inline bool bit::stl::checked<T>::check()
  const noexcept
{
  m_is_checked = true;

  return m_has_value ? false : bool(m_storage.error);
}

template<typename T>
inline bit::stl::error_code bit::stl::checked<T>::consume()
  const noexcept
{
  m_is_checked = true;

  return m_has_value ? error_code::success() : std::move(m_storage.error);
}

template<typename T>
inline bit::stl::checked<T>::operator bool()
  const noexcept
{
  return check();
}

template<typename T>
inline bool bit::stl::checked<T>::has_value()
  const noexcept
{
  return check();
}

template<typename T>
inline bool bit::stl::checked<T>::has_error()
  const noexcept
{
  return !check();
}

//----------------------------------------------------------------------

template<typename T>
inline T* bit::stl::checked<T>::operator->()
  noexcept
{
  return std::addressof(m_storage.value);
}

template<typename T>
inline const T* bit::stl::checked<T>::operator->()
  const noexcept
{
  return std::addressof(m_storage.value);
}

//----------------------------------------------------------------------

template<typename T>
inline T& bit::stl::checked<T>::operator*()
  & noexcept
{
  return m_storage.value;
}

template<typename T>
inline const T& bit::stl::checked<T>::operator*()
  const & noexcept
{
  return m_storage.value;
}

template<typename T>
inline T&& bit::stl::checked<T>::operator*()
  && noexcept
{
  return m_storage.value;
}

template<typename T>
inline const T&& bit::stl::checked<T>::operator*()
  const && noexcept
{
  return m_storage.value;
}
//------------------------------------------------------------------------

template<typename T>
inline T& bit::stl::checked<T>::value()
  &
{
  BIT_ASSERT(m_has_value, "checked::value: checked does not contain a value");
  abort_if_unchecked();

  return m_storage.value;
}

template<typename T>
inline const T& bit::stl::checked<T>::value()
  const &
{
  BIT_ASSERT(m_has_value, "checked::value: checked does not contain a value");
  abort_if_unchecked();

  return m_storage.value;
}

//------------------------------------------------------------------------

template<typename T>
inline T&& bit::stl::checked<T>::value()
  &&
{
  BIT_ASSERT(m_has_value, "checked::value: checked does not contain a value");
  abort_if_unchecked();

  return std::move(m_storage.value);
}

template<typename T>
inline const T&& bit::stl::checked<T>::value()
  const &&
{
  BIT_ASSERT(m_has_value, "checked::value: checked does not contain a value");
  abort_if_unchecked();

  return std::move(m_storage.value);
}

//------------------------------------------------------------------------

template<typename T>
template<typename U>
inline T bit::stl::checked<T>::value_or( U&& default_value )
  &&
{
  m_is_checked = true;

  return m_has_value ? std::move(m_storage.value) : static_cast<T>(std::forward<U>(default_value));
}

template<typename T>
template<typename U>
inline T bit::stl::checked<T>::value_or( U&& default_value )
  const &
{
  m_is_checked = true;

  return m_has_value ? m_storage.value : static_cast<T>(std::forward<U>(default_value));
}

//------------------------------------------------------------------------
// Private Member Functions
//------------------------------------------------------------------------

template<typename T>
inline void bit::stl::checked<T>::destruct()
{
  if( m_has_value ) {
    destroy_at( std::addressof(m_storage.value) );
  } else {
    destroy_at( std::addressof(m_storage.error) );
  }
}

template<typename T>
inline void bit::stl::checked<T>::abort_if_unchecked()
  const
{
  if( !(m_is_checked) ){
    std::abort();
  }
}

//------------------------------------------------------------------------
// Free Functions
//------------------------------------------------------------------------

template<typename T, typename...Args>
inline bit::stl::checked<T>
  bit::stl::make_checked( Args&&...args )
{
  return checked<T>( in_place<T>, std::forward<Args>(args)... );
}

template<typename T, typename U, typename...Args>
inline bit::stl::checked<T>
  bit::stl::make_checked( std::initializer_list<U> ilist, Args&&...args )
{
  return checked<T>( in_place<T>, std::move(ilist), std::forward<Args>(args)... );
}

#endif /* BIT_STL_UTILITIES_DETAIL_CHECKED_INL */
