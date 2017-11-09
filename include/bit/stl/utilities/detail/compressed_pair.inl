#ifndef BIT_STL_UTILITIES_DETAIL_UTILITY_COMPRESSED_PAIR_INL
#define BIT_STL_UTILITIES_DETAIL_UTILITY_COMPRESSED_PAIR_INL

//=============================================================================
// compressed_pair
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

// (2)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<U1,U2,const U1&,const U2&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const T1& x, const T2& y )
  : base_type( x, y )
{
}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<U1,U2,const U1&, const U2&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const T1& x, const T2& y )
  : base_type( x, y )
{
}

// (3)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<T1,T2,U1&&,U2&&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( U1&& x, U2&& y )
  : base_type( std::forward<U1>(x), std::forward<U2>(y) )
{

}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<T1,T2,U1&&,U2&&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( U1&& x, U2&& y )
  : base_type(std::forward<U1>(x), std::forward<U2>(y) )
{
}

// (4)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<T1,T2,const U1&,const U2&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const compressed_pair<U1,U2>& other )
  : base_type( other.first(), other.second() )
{
}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<T1,T2,const U1&,const U2&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const compressed_pair<U1,U2>& other )
  : base_type( other.first(), other.second() )
{
}

// (5)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<T1,T2,U1&&,U2&&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( compressed_pair<U1,U2>&& other )
  : base_type( std::forward<U1>(other.first()), std::forward<U2>(other.second()))
{
}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<T1,T2,U1&&,U2&&>::value>*>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( compressed_pair<U1,U2>&& other )
  : base_type( std::forward<U1>(other.first()), std::forward<U2>(other.second()))
{
}

// (6)

template<typename T1, typename T2>
template<typename Tuple1, typename Tuple2>
inline constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( std::piecewise_construct_t,
                     Tuple1&& first_args,
                     Tuple2&& second_args )
  : base_type( std::forward<Tuple1>(first_args),
               std::forward<Tuple2>(second_args),
               std::make_index_sequence<std::tuple_size<std::decay_t<Tuple1>>::value>{},
               std::make_index_sequence<std::tuple_size<std::decay_t<Tuple2>>::value>{} )
{}

//----------------------------------------------------------------------------

template<typename T1, typename T2>
inline bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( const compressed_pair& other )
{
  base_type::first()  = other.first();
  base_type::second() = other.second();

  return (*this);
}

template<typename T1, typename T2>
template<typename U1, typename U2>
inline bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( const compressed_pair<U1,U2>& other )
{
  base_type::first()  = other.first();
  base_type::second() = other.second();

  return (*this);
}

template<typename T1, typename T2>
inline bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( compressed_pair&& other )
{
  base_type::first()  = std::move(other.first());
  base_type::second() = std::move(other.second());

  return (*this);
}

template<typename T1, typename T2>
template<typename U1, typename U2>
inline bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( compressed_pair<U1,U2>&& other )
{
  base_type::first()  = std::move(other.first());
  base_type::second() = std::move(other.second());

  return (*this);
}

//-----------------------------------------------------------------------------
// Member Access
//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline constexpr typename bit::stl::compressed_pair<T1,T2>::first_type&
  bit::stl::compressed_pair<T1,T2>::first()
  noexcept
{
  return base_type::first();
}

template<typename T1, typename T2>
inline constexpr const typename bit::stl::compressed_pair<T1,T2>::first_type&
  bit::stl::compressed_pair<T1,T2>::first()
  const noexcept
{
  return base_type::first();
}

//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline constexpr typename bit::stl::compressed_pair<T1,T2>::second_type&
  bit::stl::compressed_pair<T1,T2>::second()
  noexcept
{
  return base_type::second();
}

template<typename T1, typename T2>
inline constexpr const typename bit::stl::compressed_pair<T1,T2>::second_type&
  bit::stl::compressed_pair<T1,T2>::second()
  const noexcept
{
  return base_type::second();
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline void bit::stl::compressed_pair<T1,T2>::swap( compressed_pair& other )
{
  using std::swap;

  swap( base_type::first(), other.first() );
  swap( base_type::second(), other.second() );
}

//-----------------------------------------------------------------------------
// Private Observers
//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline T1& bit::stl::compressed_pair<T1,T2>::get( size_constant<0> )
  &
{
  return first();
}

template<typename T1, typename T2>
inline const T1& bit::stl::compressed_pair<T1,T2>::get( size_constant<0> )
  const &
{
  return first();
}

template<typename T1, typename T2>
inline T1&& bit::stl::compressed_pair<T1,T2>::get( size_constant<0> )
  &&
{
  return std::move(first());
}

template<typename T1, typename T2>
inline const T1&& bit::stl::compressed_pair<T1,T2>::get( size_constant<0> )
  const &&
{
  return std::move(first());
}

//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline T1& bit::stl::compressed_pair<T1,T2>::get( size_constant<1> )
  &
{
  return second();
}

template<typename T1, typename T2>
inline const T1& bit::stl::compressed_pair<T1,T2>::get( size_constant<1> )
  const &
{
  return second();
}

template<typename T1, typename T2>
inline T1&& bit::stl::compressed_pair<T1,T2>::get( size_constant<1> )
  &&
{
  return std::move(second());
}

template<typename T1, typename T2>
inline const T1&& bit::stl::compressed_pair<T1,T2>::get( size_constant<1> )
  const &&
{
  return std::move(second());
}

//-----------------------------------------------------------------------------
// Free Functions
//-----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr std::size_t
  bit::stl::hash_value( const compressed_pair<T,U>& pair )
{
  auto seed = hash_value( pair.first );
  hash_combine( seed, pair.second );

  return seed;
}

template<typename T1, typename T2>
inline void bit::stl::swap( compressed_pair<T1,T2>& lhs,
                            compressed_pair<T1,T2>& rhs )
{
  lhs.swap(rhs);
}

//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline constexpr bit::stl::compressed_pair<std::decay_t<T1>,std::decay_t<T2>>
  bit::stl::make_compressed_pair( T1&& x, T2&& y )
{
  return {std::forward<T1>(x),std::forward<T2>(y)};
}

//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T1, typename T2>
inline constexpr bit::stl::tuple_element_t<Idx,bit::stl::compressed_pair<T1,T2>>&
  bit::stl::get( compressed_pair<T1,T2>& p )
  noexcept
{
  return p.get( size_constant<Idx>{} );
}

template<std::size_t Idx, typename T1, typename T2>
inline constexpr const bit::stl::tuple_element_t<Idx,bit::stl::compressed_pair<T1,T2>>&
  bit::stl::get( const compressed_pair<T1,T2>& p )
  noexcept
{
  return p.get( size_constant<Idx>{} );
}

template<std::size_t Idx, typename T1, typename T2>
inline constexpr bit::stl::tuple_element_t<Idx,bit::stl::compressed_pair<T1,T2>>&&
  bit::stl::get( compressed_pair<T1,T2>&& p )
  noexcept
{
  return std::move(p).get( size_constant<Idx>{} );
}

template<std::size_t Idx, typename T1, typename T2>
inline constexpr const bit::stl::tuple_element_t<Idx,bit::stl::compressed_pair<T1,T2>>&&
  bit::stl::get( const compressed_pair<T1,T2>&& p )
  noexcept
{
  return std::move(p).get( size_constant<Idx>{} );
}

//-----------------------------------------------------------------------------
// Comparison
//-----------------------------------------------------------------------------

template<typename T1, typename T2>
inline constexpr bool bit::stl::operator==( const compressed_pair<T1,T2>& lhs,
                                            const compressed_pair<T1,T2>& rhs )
{
  return lhs.first() == rhs.first() && lhs.second() == rhs.second();
}

template<typename T1, typename T2>
inline constexpr bool bit::stl::operator!=( const compressed_pair<T1,T2>& lhs,
                                            const compressed_pair<T1,T2>& rhs )
{
  return !(lhs==rhs);
}

template<typename T1, typename T2>
inline constexpr bool bit::stl::operator<( const compressed_pair<T1,T2>& lhs,
                                           const compressed_pair<T1,T2>& rhs )
{
  return (lhs.first()==rhs.first())
         ? lhs.second() < rhs.second()
         : lhs.first() < rhs.first();
}

template<typename T1, typename T2>
inline constexpr bool bit::stl::operator<=( const compressed_pair<T1,T2>& lhs,
                                            const compressed_pair<T1,T2>& rhs )
{
  return (rhs<lhs);
}

template<typename T1, typename T2>
inline constexpr bool bit::stl::operator>( const compressed_pair<T1,T2>& lhs,
                                           const compressed_pair<T1,T2>& rhs )
{
  return !(rhs<lhs);
}

template<typename T1, typename T2>
inline constexpr bool bit::stl::operator>=( const compressed_pair<T1,T2>& lhs,
                                            const compressed_pair<T1,T2>& rhs )
{
  return !(lhs<rhs);
}

#endif /* BIT_STL_UTILITIES_DETAIL_UTILITY_COMPRESSED_PAIR_INL */
