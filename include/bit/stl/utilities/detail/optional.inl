#ifndef BIT_STL_UTILITIES_DETAIL_OPTIONAL_INL
#define BIT_STL_UTILITIES_DETAIL_OPTIONAL_INL

//----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::optional<T>::optional()
  noexcept
  : m_has_value(false)
{

}

template<typename T>
inline constexpr bit::stl::optional<T>::optional( nullopt_t )
  : optional()
{

}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::optional<T>::optional( const optional& other )
  : m_has_value(other.m_has_value)
{
  if(m_has_value)
  {
    new (val()) value_type( *other.val() );
  }
}

template<typename T>
inline bit::stl::optional<T>::optional( optional&& other )
  : m_has_value(other.m_has_value)
{
  if(m_has_value)
  {
    new (val()) value_type( std::move(*other.val()) );
  }
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::optional<T>::optional( const value_type& value )
  : m_has_value(true)
{
  new (val()) value_type(value);
}


template<typename T>
inline constexpr bit::stl::optional<T>::optional( value_type&& value )
  : m_has_value(true)
{
  new (val()) value_type(std::move(value));
}

//------------------------------------------------------------------------

template<typename T>
template<typename...Args>
inline constexpr bit::stl::optional<T>::
  optional( in_place_t, Args&&... args )
  : m_has_value(true)
{
  new (val()) value_type( std::forward<Args>(args)... );
}


template<typename T>
template<typename U, typename...Args, typename>
inline constexpr bit::stl::optional<T>::
  optional( in_place_t, std::initializer_list<U> ilist, Args&&... args )
  : m_has_value(true)
{
  new (val()) value_type( ilist, std::forward<Args>(args)... );
}

//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::optional<T>::~optional()
{
  destruct();
}

//----------------------------------------------------------------------------
// Assignment
//----------------------------------------------------------------------------

template<typename T>
inline bit::stl::optional<T>& bit::stl::optional<T>::operator=( nullopt_t )
{
  destruct();
  return (*this);
}

template<typename T>
inline bit::stl::optional<T>&
  bit::stl::optional<T>::operator=( const optional& other )
{
  if(m_has_value && other.m_has_value) {
    *val() = *other.val();
  } else if( m_has_value ) {
    destruct();
  } else if( other.m_has_value ) {
    new (val()) value_type( *other.val() );
    m_has_value = true;
  }
  return (*this);
}

template<typename T>
inline bit::stl::optional<T>&
  bit::stl::optional<T>::operator=( optional&& other )
{
  if(m_has_value && other.m_has_value) {
    *val() = std::move( *other.val() );
  } else if( m_has_value ) {
    destruct();
  } else if( other.m_has_value ) {
    new (val()) value_type( std::move( *other.val() ) );
    m_has_value = true;
  }
  return (*this);
}

template<typename T>
template<typename U, typename>
inline bit::stl::optional<T>&
  bit::stl::optional<T>::operator=( U&& value )
{
  if(m_has_value) {
    *val() = std::forward<U>(value);
  } else {
    new (val()) value_type( std::forward<U>(value) );
    m_has_value = true;
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::optional<T>::operator bool()
  const noexcept
{
  return m_has_value;
}

template<typename T>
inline constexpr bool bit::stl::optional<T>::has_value()
  const noexcept
{
  return m_has_value;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::optional<T>::value_type*
  bit::stl::optional<T>::operator->()
  noexcept
{
  return val();
}

template<typename T>
inline constexpr const typename bit::stl::optional<T>::value_type*
  bit::stl::optional<T>::operator->()
  const noexcept
{
  return val();
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::optional<T>::value_type&
  bit::stl::optional<T>::operator*()
  & noexcept
{
  return *val();
}

template<typename T>
inline constexpr typename bit::stl::optional<T>::value_type&&
  bit::stl::optional<T>::operator*()
  && noexcept
{
  return std::move(*val());
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr const typename bit::stl::optional<T>::value_type&
  bit::stl::optional<T>::operator*()
  const & noexcept
{
  return *val();
}

template<typename T>
inline constexpr const typename bit::stl::optional<T>::value_type&&
  bit::stl::optional<T>::operator*()
  const && noexcept
{
  return std::move(*val());
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::optional<T>::value_type&
  bit::stl::optional<T>::value()
  &
{
  return bool(*this) ? *val() : throw bad_optional_access();
}

template<typename T>
inline constexpr const typename bit::stl::optional<T>::value_type&
  bit::stl::optional<T>::value()
  const &
{
  return bool(*this) ? *val() : throw bad_optional_access();
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::stl::optional<T>::value_type&&
  bit::stl::optional<T>::value()
  &&
{
  return bool(*this) ? std::move(*val()) : throw bad_optional_access();
}

template<typename T>
inline constexpr const typename bit::stl::optional<T>::value_type&&
  bit::stl::optional<T>::value()
  const &&
{
  return bool(*this) ? std::move(*val()) : throw bad_optional_access();
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr typename bit::stl::optional<T>::value_type
  bit::stl::optional<T>::value_or( U&& default_value )
  const&
{
  return bool(*this) ? *val() : std::forward<U>(default_value);
}

template<typename T>
template<typename U>
inline constexpr typename bit::stl::optional<T>::value_type
  bit::stl::optional<T>::value_or( U&& default_value )
  &&
{
  return bool(*this) ? *val() : std::forward<U>(default_value);
}

//----------------------------------------------------------------------------
// Monadic Functionality
//----------------------------------------------------------------------------


template<typename T>
template<typename Fn,typename>
bit::stl::invoke_result_t<Fn,const T&> bit::stl::optional<T>::flat_map( Fn&& fn )
  const
{
  if( has_value() ) return invoke( std::forward<Fn>(fn), **this );
  return nullopt;
}

template<typename T>
template<typename Fn,typename>
bit::stl::optional<bit::stl::invoke_result_t<Fn,const T&>>
  bit::stl::optional<T>::map( Fn&& fn )
  const
{
  if( has_value() ) return make_optional(invoke( std::forward<Fn>(fn), **this ));
  return nullopt;
}

//-----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::stl::optional<std::decay_t<U>> bit::stl::optional<T>::and_then( U&& u )
  const
{
  if( has_value() ) return make_optional( std::forward<U>(u) );
  return nullopt;
}

template<typename T>
template<typename U>
bit::stl::optional<std::decay_t<U>> bit::stl::optional<T>::or_else( U&& u )
  const
{
  if( has_value() ) return make_optional( std::forward<U>(u) );
  return nullopt;
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::optional<T>::swap( optional<T>& other )
{
  using std::swap;

  if( m_has_value && other.m_has_value ){
    swap(*val(),*other.val());
  } else if( m_has_value ) {
    other = std::move(*this);
  } else if( other.m_has_value ) {
    *this = std::move(other);
  }
}

template<typename T>
inline void bit::stl::optional<T>::reset()
  noexcept(std::is_nothrow_destructible<T>::value)
{
  destruct();
}

//----------------------------------------------------------------------------

template<typename T>
template<typename...Args>
inline void bit::stl::optional<T>::emplace( Args&&...args )
{
  destruct();
  new (val()) value_type( std::forward<Args>(args)... );
  m_has_value = true;
}

template<typename T>
template<typename U, typename...Args>
inline void bit::stl::optional<T>::emplace( std::initializer_list<U> ilist,
                                            Args&&...args )
{
  destruct();
  new (val()) value_type( std::forward<std::initializer_list<U>>(ilist), std::forward<Args>(args)... );
  m_has_value = true;
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr T* bit::stl::optional<T>::val()
  const noexcept
{
  return reinterpret_cast<T*>( const_cast<storage_type*>(&m_value) );
}

template<typename T>
inline void bit::stl::optional<T>::destruct()
  const
{
  if(!std::is_trivially_destructible<T>::value && m_has_value) {
    val()->~T();
    m_has_value = false;
  }
}

//============================================================================
// Equality Operators
//============================================================================

//----------------------------------------------------------------------------
// Compare two optional objects
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool
  bit::stl::operator==( const optional<T>& lhs, const optional<T>& rhs )
{
  if(static_cast<bool>(lhs) != static_cast<bool>(rhs)) return false;
  if(!static_cast<bool>(lhs)) return true;
  return *lhs == *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator!=( const optional<T>& lhs, const optional<T>& rhs )
{
  if(static_cast<bool>(lhs) != static_cast<bool>(rhs)) return true;
  if(!static_cast<bool>(lhs)) return false;
  return *lhs != *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<( const optional<T>& lhs, const optional<T>& rhs )
{
  if(!static_cast<bool>(rhs)) return false;
  if(!static_cast<bool>(lhs)) return true;
  return *lhs < *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>( const optional<T>& lhs, const optional<T>& rhs )
{
  if(!static_cast<bool>(lhs)) return false;
  if(!static_cast<bool>(rhs)) return true;
  return *lhs > *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<=( const optional<T>& lhs, const optional<T>& rhs )
{
  if(!static_cast<bool>(lhs)) return true;
  if(!static_cast<bool>(rhs)) return false;
  return *lhs <= *rhs;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>=( const optional<T>& lhs, const optional<T>& rhs )
{
  if(!static_cast<bool>(rhs)) return true;
  if(!static_cast<bool>(lhs)) return false;
  return *lhs >= *rhs;
}

//----------------------------------------------------------------------------
// Compare an optional object with a nullopt
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool
  bit::stl::operator==( const optional<T>& opt, nullopt_t )
  noexcept
{
  return !opt;
}

template<typename T>
inline constexpr bool
  bit::stl::operator==( nullopt_t, const optional<T>& opt )
  noexcept
{
  return !opt;
}

template<typename T>
inline constexpr bool
  bit::stl::operator!=( const optional<T>& opt, nullopt_t )
  noexcept
{
  return static_cast<bool>(opt);
}

template<typename T>
inline constexpr bool
  bit::stl::operator!=( nullopt_t, const optional<T>& opt )
  noexcept
{
  return static_cast<bool>(opt);
}

template<typename T>
inline constexpr bool
  bit::stl::operator<( const optional<T>&, nullopt_t )
  noexcept
{
  return false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<( nullopt_t, const optional<T>& opt )
  noexcept
{
  return static_cast<bool>(opt);
}

template<typename T>
inline constexpr bool
  bit::stl::operator>( const optional<T>& opt, nullopt_t )
  noexcept
{
  return static_cast<bool>(opt);
}

template<typename T>
inline constexpr bool
  bit::stl::operator>( nullopt_t, const optional<T>& )
  noexcept
{
  return false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<=( const optional<T>& opt, nullopt_t )
  noexcept
{
  return !opt;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<=( nullopt_t, const optional<T>& )
  noexcept
{
  return true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>=( const optional<T>&, nullopt_t )
  noexcept
{
  return true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>=( nullopt_t, const optional<T>& opt )
  noexcept
{
  return !opt;
}

//----------------------------------------------------------------------------
// Compare an optional object with a T
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bool
  bit::stl::operator==( const optional<T>& opt, const T& value )
{
  return static_cast<bool>(opt) ? *opt == value : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator==( const T& value, const optional<T>& opt )
{
  return static_cast<bool>(opt) ? value == *opt : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator!=( const optional<T>& opt, const T& value )
{
  return static_cast<bool>(opt) ? *opt != value : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator!=( const T& value, const optional<T>& opt )
{
  return static_cast<bool>(opt) ? value != *opt : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<( const optional<T>& opt, const T& value )
{
  return static_cast<bool>(opt) ? *opt < value  : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<( const T& value, const optional<T>& opt )
{
  return static_cast<bool>(opt) ? value < *opt  : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>( const optional<T>& opt, const T& value )
{
  return static_cast<bool>(opt) ? *opt > value  : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>( const T& value, const optional<T>& opt )
{
  return static_cast<bool>(opt) ? value > *opt  : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<=( const optional<T>& opt, const T& value )
{
  return static_cast<bool>(opt) ? *opt <= value : true;
}

template<typename T>
inline constexpr bool
  bit::stl::operator<=( const T& value, const optional<T>& opt )
{
  return static_cast<bool>(opt) ? value <= *opt : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>=( const optional<T>& opt, const T& value )
{
  return static_cast<bool>(opt) ? *opt >= value : false;
}

template<typename T>
inline constexpr bool
  bit::stl::operator>=( const T& value, const optional<T>& opt )
{
  return static_cast<bool>(opt) ? value >= *opt : true;
}

//----------------------------------------------------------------------------
// Non-member functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr
  bit::stl::optional<std::decay_t<T>> bit::stl::make_optional( T&& value )
{
  return optional<std::decay_t<T>>( std::forward<T>(value) );
}

template<typename T, typename... Args >
inline constexpr
  bit::stl::optional<T> bit::stl::make_optional( Args&&... args )
{
  return optional<T>( in_place, std::forward<Args>(args)... );
}

template<typename T, typename U, typename... Args >
inline constexpr
  bit::stl::optional<T> bit::stl::make_optional( std::initializer_list<U> il, Args&&... args )
{
  return optional<T>( in_place, std::forward<std::initializer_list<U>>(il), std::forward<Args>(args)... );
}

template<typename T>
inline void bit::stl::swap( optional<T>& lhs, optional<T>& rhs )
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Hashing
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::hash_t bit::stl::hash_value( const optional<T>& s )
  noexcept
{
  if( s ) {
    return hash_value( s.value() );
  }
  return static_cast<hash_t>(0);
}

#endif /* BIT_STL_UTILITIES_DETAIL_OPTIONAL_INL */
