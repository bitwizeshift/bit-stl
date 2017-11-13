#ifndef BIT_STL_UTILITIES_DETAIL_EXPECTED_INL
#define BIT_STL_UTILITIES_DETAIL_EXPECTED_INL


//=============================================================================
// X.Z.7, class bad_expected_access
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<typename E>
bit::stl::bad_expected_access<E>::bad_expected_access( error_type e )
  : std::logic_error("Found an error instead of the expected value."),
    m_error_value(std::move(e))
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename E>
typename bit::stl::bad_expected_access<E>::error_type&
  bit::stl::bad_expected_access<E>::error()
  & noexcept
{
  return m_error_value;
}

template<typename E>
const typename bit::stl::bad_expected_access<E>::error_type&
  bit::stl::bad_expected_access<E>::error()
  const & noexcept
{
  return m_error_value;
}

//-----------------------------------------------------------------------------

template<typename E>
typename bit::stl::bad_expected_access<E>::error_type&&
  bit::stl::bad_expected_access<E>::error()
  && noexcept
{
  return std::move(m_error_value);
}

template<typename E>
const typename bit::stl::bad_expected_access<E>::error_type&&
  bit::stl::bad_expected_access<E>::error()
  const && noexcept
{
  return std::move(m_error_value);
}

//=============================================================================

inline bit::stl::bad_expected_access<void>::bad_expected_access()
  : std::logic_error("Bad access to expected type with no value.")
{

}

//=============================================================================
// X.Y.4, unexpected_type
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<typename E>
template<typename E2,typename>
inline constexpr bit::stl::unexpected_type<E>
  ::unexpected_type( const unexpected_type<E2>& other )
  : m_value(other.value())
{

}

template<typename E>
template<typename E2,typename>
inline constexpr bit::stl::unexpected_type<E>
  ::unexpected_type( unexpected_type<E2>&& other )
  : m_value(std::move(other.value()))
{

}

template<typename E>
inline constexpr bit::stl::unexpected_type<E>
  ::unexpected_type( const E& other )
  : m_value(other)
{

}

template<typename E>
inline constexpr bit::stl::unexpected_type<E>
  ::unexpected_type( E&& other )
  : m_value(std::move(other))
{

}

template<typename E>
template<typename...Args, typename>
inline constexpr bit::stl::unexpected_type<E>
  ::unexpected_type( in_place_t, Args&&...args )
  : m_value{ std::forward<Args>(args)... }
{

}

template<typename E>
template<typename U, typename...Args, typename>
inline constexpr bit::stl::unexpected_type<E>
  ::unexpected_type( in_place_t, std::initializer_list<U> ilist, Args&&...args )
  : m_value{ std::move(ilist), std::forward<Args>(args)... }
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename E>
inline constexpr E& bit::stl::unexpected_type<E>::value()
  &
{
  return m_value;
}

template<typename E>
inline constexpr const E& bit::stl::unexpected_type<E>::value()
  const &
{
  return m_value;
}

//-----------------------------------------------------------------------------

template<typename E>
inline constexpr E&& bit::stl::unexpected_type<E>::value()
  &&
{
  return std::move(m_value);
}

template<typename E>
inline constexpr const E&& bit::stl::unexpected_type<E>::value()
  const &&
{
  return std::move(m_value);
}

//=============================================================================
// X.Y.4, Unexpected factories
//=============================================================================

template<typename E, typename...Args>
inline constexpr bit::stl::unexpected_type<E>
  bit::stl::make_unexpected( Args&&...args )
{
  return unexpected_type<E>( in_place, std::forward<Args>(args)... );
}

//=============================================================================
// X.Y.5, unexpected_type relational operators
//=============================================================================

template<typename E>
inline constexpr bool bit::stl::operator==( const unexpected_type<E>& lhs,
                                            const unexpected_type<E>& rhs )
{
  return lhs.value() == rhs.value();
}

template<typename E>
inline constexpr bool bit::stl::operator!=( const unexpected_type<E>& lhs,
                                            const unexpected_type<E>& rhs )
{
  return lhs.value() != rhs.value();
}

template<typename E>
inline constexpr bool bit::stl::operator<( const unexpected_type<E>& lhs,
                                           const unexpected_type<E>& rhs )
{
  return lhs.value() < rhs.value();
}

template<typename E>
inline constexpr bool bit::stl::operator>( const unexpected_type<E>& lhs,
                                           const unexpected_type<E>& rhs )
{
  return lhs.value() > rhs.value();
}

template<typename E>
inline constexpr bool bit::stl::operator<=( const unexpected_type<E>& lhs,
                                            const unexpected_type<E>& rhs )
{
  return lhs.value() <= rhs.value();
}

template<typename E>
inline constexpr bool bit::stl::operator>=( const unexpected_type<E>& lhs,
                                            const unexpected_type<E>& rhs )
{
  return lhs.value() >= rhs.value();
}

//=============================================================================
// detail::expected_base<true,T,E>
//=============================================================================

//-----------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bit::stl::detail::expected_base<true,T,E>::expected_base()
  : m_storage(),
    m_has_value(indeterminate)
{

}

template<typename T, typename E>
template<typename...Args>
  inline constexpr bit::stl::detail::expected_base<true,T,E>
  ::expected_base( in_place_t, Args&&...args )
  : m_storage( in_place, std::forward<Args>(args)... ),
    m_has_value(true)
{

}

template<typename T, typename E>
template<typename...Args>
inline constexpr bit::stl::detail::expected_base<true,T,E>
  ::expected_base( unexpect_t, Args&&...args )
  : m_storage( unexpect, std::forward<Args>(args)... ),
    m_has_value(false)
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bool bit::stl::detail::expected_base<true,T,E>
  ::has_value()
  const noexcept
{
  return m_has_value == true;
}

template<typename T, typename E>
inline constexpr bool bit::stl::detail::expected_base<true,T,E>
  ::has_error()
  const noexcept
{
  return m_has_value == false;
}

template<typename T, typename E>
inline constexpr bool bit::stl::detail::expected_base<true,T,E>
  ::valueless_by_exception()
  const noexcept
{
  return m_has_value == indeterminate;
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr T&
  bit::stl::detail::expected_base<true,T,E>::get_value()
  & noexcept
{
  return m_storage.value;
}

template<typename T, typename E>
inline constexpr T&&
  bit::stl::detail::expected_base<true,T,E>::get_value()
  && noexcept
{
  return m_storage.value;
}

template<typename T, typename E>
inline constexpr const T&
  bit::stl::detail::expected_base<true,T,E>::get_value()
  const & noexcept
{
  return m_storage.value;
}

template<typename T, typename E>
inline constexpr const T&&
  bit::stl::detail::expected_base<true,T,E>::get_value()
  const && noexcept
{
  return m_storage.value;
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bit::stl::unexpected_type<E>&
  bit::stl::detail::expected_base<true,T,E>::get_unexpected()
  & noexcept
{
  return m_storage.error;
}

template<typename T, typename E>
inline constexpr  bit::stl::unexpected_type<E>&&
  bit::stl::detail::expected_base<true,T,E>::get_unexpected()
  && noexcept
{
  return m_storage.error;
}

template<typename T, typename E>
inline constexpr const  bit::stl::unexpected_type<E>&
  bit::stl::detail::expected_base<true,T,E>::get_unexpected()
  const & noexcept
{
  return m_storage.error;
}

template<typename T, typename E>
inline constexpr const  bit::stl::unexpected_type<E>&&
  bit::stl::detail::expected_base<true,T,E>::get_unexpected()
  const && noexcept
{
  return m_storage.error;
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename...Args>
inline void bit::stl::detail::expected_base<true,T,E>
  ::emplace_value( Args&&...args )
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  try {
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
    new (&m_storage.value) T( std::forward<Args>(args)... );
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  } catch( ... ) {
    m_has_value = indeterminate;
    throw;
  }
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
}

template<typename T, typename E>
template<typename...Args>
inline void bit::stl::detail::expected_base<true,T,E>
  ::emplace_error( Args&&...args )
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  try {
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
    new (&m_storage.value) unexpected_type<T>{ std::forward<Args>(args)... };
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  } catch( ... ) {
    m_has_value = indeterminate;
    throw;
  }
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U>
inline void bit::stl::detail::expected_base<true,T,E>::assign_value( U&& value )
{
  if( m_has_value ) {
    m_storage.value = std::forward<U>(value);
  } else {
    emplace( std::forward<U>(value) );
  }
}

template<typename T, typename E>
template<typename U>
inline void bit::stl::detail::expected_base<true,T,E>::assign_error( U&& error )
{
  if( !m_has_value ) {
    m_storage.error = std::forward<U>(error);
  } else {
    emplace_error( std::forward<U>(error) );
  }
}

//=============================================================================
// detail::expected_base<false,T,E>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bit::stl::detail::expected_base<false,T,E>::expected_base()
  : m_storage(),
    m_has_value(indeterminate)
{

}

template<typename T, typename E>
template<typename...Args>
inline constexpr bit::stl::detail::expected_base<false,T,E>
  ::expected_base( in_place_t, Args&&...args )
  : m_storage( in_place, std::forward<Args>(args)... ),
    m_has_value(true)
{

}

template<typename T, typename E>
template<typename...Args>
inline constexpr bit::stl::detail::expected_base<false,T,E>
  ::expected_base( unexpect_t, Args&&...args )
  : m_storage( unexpect, std::forward<Args>(args)... ),
    m_has_value(false)
{

}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline bit::stl::detail::expected_base<false,T,E>
  ::~expected_base()
{
  destruct();
}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bool bit::stl::detail::expected_base<false,T,E>::has_value()
  const noexcept
{
  return m_has_value == true;
}

template<typename T, typename E>
constexpr bool bit::stl::detail::expected_base<false,T,E>::has_error()
  const noexcept
{
  return m_has_value == false;
}

template<typename T, typename E>
constexpr bool bit::stl::detail::expected_base<false,T,E>
  ::valueless_by_exception()
  const noexcept
{
  return m_has_value == indeterminate;
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr T&
  bit::stl::detail::expected_base<false,T,E>::get_value()
  & noexcept
{
  return m_storage.value;
}

template<typename T, typename E>
inline constexpr T&&
  bit::stl::detail::expected_base<false,T,E>::get_value()
  && noexcept
{
  return m_storage.value;
}

template<typename T, typename E>
inline constexpr const T&
  bit::stl::detail::expected_base<false,T,E>::get_value()
  const & noexcept
{
  return m_storage.value;
}

template<typename T, typename E>
inline constexpr const T&&
  bit::stl::detail::expected_base<false,T,E>::get_value()
  const && noexcept
{
  return m_storage.value;
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bit::stl::unexpected_type<E>&
  bit::stl::detail::expected_base<false,T,E>::get_unexpected()
  & noexcept
{
  return m_storage.error;
}

template<typename T, typename E>
inline constexpr  bit::stl::unexpected_type<E>&&
  bit::stl::detail::expected_base<false,T,E>::get_unexpected()
  && noexcept
{
  return m_storage.error;
}

template<typename T, typename E>
inline constexpr const  bit::stl::unexpected_type<E>&
  bit::stl::detail::expected_base<false,T,E>::get_unexpected()
  const & noexcept
{
  return m_storage.error;
}

template<typename T, typename E>
inline constexpr const  bit::stl::unexpected_type<E>&&
  bit::stl::detail::expected_base<false,T,E>::get_unexpected()
  const && noexcept
{
  return m_storage.error;
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T, typename E>
inline void bit::stl::detail::expected_base<false,T,E>::destruct()
{
  if( m_has_value ) {
    m_storage.value.~T();
  } else if( !m_has_value ) {
    m_storage.error.~E();
  }
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename...Args>
inline void bit::stl::detail::expected_base<false,T,E>
  ::emplace_value( Args&&...args )
{
  destruct();
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  try {
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
    new (&m_storage.value) T{ std::forward<Args>(args)... };
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  } catch( ... ) {
    m_has_value = indeterminate;
    throw;
  }
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
}

template<typename T, typename E>
template<typename...Args>
void bit::stl::detail::expected_base<false,T,E>
  ::emplace_error( Args&&...args )
{
  destruct();
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  try {
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
    new (&m_storage.value) unexpected_type<T>{ std::forward<Args>(args)... };
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  } catch( ... ) {
    m_has_value = indeterminate;
    throw;
  }
#endif // BIT_COMPILER_EXCEPTIONS_ENABLED
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U>
inline void bit::stl::detail::expected_base<false,T,E>
::assign_value( U&& value )
{
  if( !m_has_value ) {
    m_storage.value = std::forward<U>(value);
  } else {
    emplace( std::forward<U>(value) );
  }
}

template<typename T, typename E>
template<typename U>
inline void bit::stl::detail::expected_base<false,T,E>
  ::assign_error( U&& error )
{
  if( m_has_value ) {
    m_storage.error = std::forward<U>(error);
  } else {
    emplace_error( std::forward<U>(error) );
  }
}

//=============================================================================
// expected<T,E>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U, typename>
inline constexpr bit::stl::expected<T,E>::expected()
  : base_type( in_place )
{

}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline bit::stl::expected<T,E>
  ::expected( enable_overload_if<std::is_copy_constructible<T>::value &&
                                 std::is_copy_constructible<E>::value,
                                 const expected&> other )
  : base_type()
{
  if( other.has_value() ) {
    base_type::emplace_value( other.get_value() );
  } else if ( other.has_error() ) {
    base_type::emplace_error( other.get_unexpected() );
  }
}

template<typename T, typename E>
inline bit::stl::expected<T,E>
  ::expected( enable_overload_if<std::is_move_constructible<T>::value &&
                                 std::is_move_constructible<E>::value,
                                 expected&&> other )
  : base_type()
{
  if( other.has_value() ) {
    base_type::emplace_value( std::move(other.get_value()) );
  } else if ( other.has_error() ) {
    base_type::emplace_error( std::move(other.get_unexpected()) );
  }
}

//-----------------------------------------------------------------------

template<typename T, typename E>
template<typename U, typename G, typename>
inline bit::stl::expected<T,E>::expected( const expected<U,G>& other )
  : base_type()
{
  if( other.has_value() ) {
    base_type::emplace_value( other.get_value() );
  } else if ( other.has_error() ) {
    base_type::emplace_error( other.get_unexpected() );
  }
}

template<typename T, typename E>
template<typename U, typename G, typename>
inline bit::stl::expected<T,E>::expected( expected<U,G>&& other )
  : base_type()
{
  if( other.has_value() ) {
    base_type::emplace_value( std::move(other.get_value()) );
  } else if ( other.has_error() ) {
    base_type::emplace_error( std::move(other.get_unexpected()) );
  }
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U, typename>
inline constexpr bit::stl::expected<T,E>::expected( const T& value )
  : base_type( in_place, value )
{

}

template<typename T, typename E>
template<typename U, typename>
constexpr bit::stl::expected<T,E>::expected( T&& value )
  : base_type( in_place, std::forward<T>(value) )
{

}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename...Args, typename>
inline constexpr bit::stl::expected<T,E>
  ::expected( in_place_t, Args&&...args )
  : base_type( in_place, std::forward<Args>(args)... )
{

}

template<typename T, typename E>
template<typename U, typename...Args, typename>
inline constexpr bit::stl::expected<T,E>
  ::expected( in_place_t, std::initializer_list<U> ilist, Args&&...args )
  : base_type( in_place, std::move(ilist), std::forward<Args>(args)... )
{

}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename UError, typename>
inline constexpr bit::stl::expected<T,E>
  ::expected( unexpected_type<E> const& unexpected )
  : base_type( unexpect, unexpected.value() )
{

}

template<typename T, typename E>
template<typename Err, typename>
inline constexpr bit::stl::expected<T,E>
  ::expected( unexpected_type<Err> const& unexpected )
  : base_type( unexpect, unexpected.value() )
{

}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename...Args, typename>
inline constexpr bit::stl::expected<T,E>
  ::expected( unexpect_t, Args&&...args )
  : base_type( unexpect, std::forward<Args>(args)... )
{

}

template<typename T, typename E>
template<typename U, typename...Args, typename>
inline constexpr bit::stl::expected<T,E>
  ::expected( unexpect_t, std::initializer_list<U> ilist, Args&&...args )
  : base_type( unexpect, std::move(ilist), std::forward<Args>(args)... )
{

}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U, typename F, typename>
inline bit::stl::expected<T,E>& bit::stl::expected<T,E>
  ::operator=( const expected& other )
{
  if( other.has_value() ) {
    base_type::assign_value(other.get_value());
  } else if( other.has_error() ) {
    base_type::assign_error(other.get_unexpected());
  }

  return (*this);
}

template<typename T, typename E>
template<typename U, typename F, typename>
inline bit::stl::expected<T,E>& bit::stl::expected<T,E>
  ::operator=( expected&& other )
{
  if( other.has_value() ) {
    base_type::assign_value( std::move(other.get_value()) );
  } else if( other.has_error() ) {
    base_type::assign_error( std::move(other.get_unexpected()) );
  }

  return (*this);
}

template<typename T, typename E>
template<typename U,typename>
inline bit::stl::expected<T,E>&
  bit::stl::expected<T,E>::operator=( U&& value )
{
  base_type::assign_value( std::forward<U>(value) );

  return (*this);
}

template<typename T, typename E>
inline bit::stl::expected<T,E>&
  bit::stl::expected<T,E>::operator=( const unexpected_type<E>& unexpected )
{
  base_type::assign_error( unexpected.value() );

  return (*this);
}

template<typename T, typename E>
inline bit::stl::expected<T,E>&
  bit::stl::expected<T,E>::operator=( unexpected_type<E>&& unexpected )
{
  base_type::assign_error( std::move(unexpected.value()) );

  return (*this);
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename...Args, typename>
inline void bit::stl::expected<T,E>::emplace( Args&&...args )
{
  base_type::emplace_value( std::forward<Args>(args)... );
}

template<typename T, typename E>
template<typename U, typename...Args, typename>
inline void bit::stl::expected<T,E>::emplace( std::initializer_list<U> ilist,
                                              Args&&...args )
{
  base_type::emplace_value( std::move(ilist), std::forward<Args>(args)... );
}

template<typename T, typename E>
inline void bit::stl::expected<T,E>::swap( expected& other )
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bool bit::stl::expected<T,E>::has_value()
  const noexcept
{
  return base_type::has_value();
}

template<typename T, typename E>
inline constexpr bool bit::stl::expected<T,E>::has_error()
  const noexcept
{
  return base_type::has_error();
}

template<typename T, typename E>
inline constexpr bool bit::stl::expected<T,E>::valueless_by_exception()
  const noexcept
{
  return base_type::valueless_by_exception();
}

template<typename T, typename E>
inline constexpr bit::stl::expected<T,E>::operator bool()
  const noexcept
{
  return has_value();
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr T* bit::stl::expected<T,E>::operator->()
{
  return &base_type::get_value();
}

template<typename T, typename E>
inline constexpr const T* bit::stl::expected<T,E>::operator->()
  const
{
  return &base_type::get_value();
}

template<typename T, typename E>
inline constexpr T& bit::stl::expected<T,E>::operator*()
  &
{
  return base_type::get_value();
}

template<typename T, typename E>
inline constexpr T&& bit::stl::expected<T,E>::operator*()
  &&
{
  return base_type::get_value();
}

template<typename T, typename E>
inline constexpr const T& bit::stl::expected<T,E>::operator*()
  const &
{
  return base_type::get_value();
}

template<typename T, typename E>
inline constexpr const T&& bit::stl::expected<T,E>::operator*()
  const &&
{
  return base_type::get_value();
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr T& bit::stl::expected<T,E>::value()
  &
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( has_error() ) {
    throw bad_expected_access<E>( base_type::get_unexpected().value() );
  } else if ( valueless_by_exception() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_value(), "expected must have value" );
#endif
  return base_type::get_value();
}

template<typename T, typename E>
inline constexpr T&& bit::stl::expected<T,E>::value()
  &&
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( has_error() ) {
    throw bad_expected_access<E>( base_type::get_unexpected().value() );
  } else if ( valueless_by_exception() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_value(), "expected must have value" );
#endif
  return std::move(base_type::get_value());
}

template<typename T, typename E>
inline constexpr const T& bit::stl::expected<T,E>::value()
  const &
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( has_error() ) {
    throw bad_expected_access<E>( base_type::get_unexpected().value() );
  } else if ( valueless_by_exception() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_value(), "expected must have value" );
#endif
  return base_type::get_value();
}

template<typename T, typename E>
inline constexpr const T&& bit::stl::expected<T,E>::value()
  const &&
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( has_error() ) {
    throw bad_expected_access<E>( base_type::get_unexpected().value() );
  } else if ( valueless_by_exception() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_value(), "expected must have value" );
#endif
  return std::move(base_type::get_value());
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U>
inline constexpr T bit::stl::expected<T,E>::value_or( U&& default_value )
  const &
{
  return bool(*this) ? base_type::get_value() : std::forward<U>(default_value);
}

template<typename T, typename E>
template<typename U>
inline constexpr T bit::stl::expected<T,E>::value_or( U&& default_value )
  &&
{
  return bool(*this) ? base_type::get_value() : std::forward<U>(default_value);
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
constexpr E& bit::stl::expected<T,E>::error()
  &
{
  return get_unexpected().value();
}

template<typename T, typename E>
constexpr E&& bit::stl::expected<T,E>::error()
  &&
{
  return std::move(get_unexpected().value());
}
template<typename T, typename E>
constexpr const E& bit::stl::expected<T,E>::error()
  const &
{
  return get_unexpected().value();
}
template<typename T, typename E>
constexpr const E&& bit::stl::expected<T,E>::error()
  const &&
{
  return std::move(get_unexpected().value());
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
template<typename U>
inline constexpr E bit::stl::expected<T,E>::error_or( U&& default_value )
  const &
{
  return !bool(*this) ? base_type::get_unexpected().value() : default_value;
}

template<typename T, typename E>
template<typename U>
inline constexpr E bit::stl::expected<T,E>::error_or( U&& default_value )
  &&
{
  return !bool(*this) ? base_type::get_unexpected().value() : default_value;
}

//-----------------------------------------------------------------------------

template<typename T, typename E>
inline constexpr bit::stl::unexpected_type<E>&
  bit::stl::expected<T,E>::get_unexpected()
  &
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( !has_error() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_error(), "expected must have error" );
#endif

  return base_type::get_unexpected();
}

template<typename T, typename E>
inline constexpr bit::stl::unexpected_type<E>&&
  bit::stl::expected<T,E>::get_unexpected()
  &&
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( !has_error() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_error(), "expected must have error" );
#endif

  return std::move(base_type::get_unexpected());
}

template<typename T, typename E>
inline constexpr const bit::stl::unexpected_type<E>&
  bit::stl::expected<T,E>::get_unexpected()
  const &
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( !has_error() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_error(), "expected must have error" );
#endif

  return base_type::get_unexpected();
}

template<typename T, typename E>
inline constexpr const bit::stl::unexpected_type<E>&&
  bit::stl::expected<T,E>::get_unexpected()
  const &&
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( !has_error() ) {
    throw bad_expected_access<void>();
  }
#else
  BIT_ALWAYS_ASSERT( has_error(), "expected must have error" );
#endif

  return std::move(base_type::get_unexpected());
}

#endif /* BIT_STL_UTILITIES_DETAIL_EXPECTED_INL */
