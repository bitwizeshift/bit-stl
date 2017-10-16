#ifndef BIT_STL_UTILITIES_DETAIL_UTILITY_COMPRESSED_PAIR_INL
#define BIT_STL_UTILITIES_DETAIL_UTILITY_COMPRESSED_PAIR_INL

//============================================================================
// compressed_pair
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

// (2)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<U1,U2,const U1&,const U2&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const T1& x, const T2& y )
  : base_type( x, y )
{
}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<U1,U2,const U1&, const U2&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const T1& x, const T2& y )
  : base_type( x, y )
{
}

// (3)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<T1,T2,U1&&,U2&&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( U1&& x, U2&& y )
  : base_type( std::forward<U1>(x), std::forward<U2>(y) )
{

}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<T1,T2,U1&&,U2&&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( U1&& x, U2&& y )
  : base_type(std::forward<U1>(x), std::forward<U2>(y) )
{
}

// (4)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<T1,T2,const U1&,const U2&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const compressed_pair<U1,U2>& other )
  : base_type( other.first(), other.second() )
{
}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<T1,T2,const U1&,const U2&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( const compressed_pair<U1,U2>& other )
  : base_type( other.first(), other.second() )
{
}

// (5)

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_constructible<T1,T2,U1&&,U2&&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( compressed_pair<U1,U2>&& other )
  : base_type( std::forward<U1>(other.first()), std::forward<U2>(other.second()))
{
}

template<typename T1, typename T2>
template<typename U1, typename U2, std::enable_if_t<bit::stl::detail::is_explicit_constructible<T1,T2,U1&&,U2&&>::value>*>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( compressed_pair<U1,U2>&& other )
  : base_type( std::forward<U1>(other.first()), std::forward<U2>(other.second()))
{
}

// (6)

template<typename T1, typename T2>
template<typename...Args1, typename...Args2>
constexpr bit::stl::compressed_pair<T1,T2>
  ::compressed_pair( std::piecewise_construct_t,
                     std::tuple<Args1...> first_args,
                     std::tuple<Args2...> second_args )
  : base_type( std::move(first_args), std::move(second_args), std::make_index_sequence<sizeof...(Args1)>{}, std::make_index_sequence<sizeof...(Args2)>{})
{}

//----------------------------------------------------------------------------

template<typename T1, typename T2>
bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( const compressed_pair& other )
{
  base_type::first()  = other.first();
  base_type::second() = other.second();

  return (*this);
}

template<typename T1, typename T2>
template<typename U1, typename U2>
bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( const compressed_pair<U1,U2>& other )
{
  base_type::first()  = other.first();
  base_type::second() = other.second();

  return (*this);
}

template<typename T1, typename T2>
bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( compressed_pair&& other )
{
  base_type::first()  = std::move(other.first());
  base_type::second() = std::move(other.second());

  return (*this);
}

template<typename T1, typename T2>
template<typename U1, typename U2>
bit::stl::compressed_pair<T1,T2>&
  bit::stl::compressed_pair<T1,T2>::operator=( compressed_pair<U1,U2>&& other )
{
  base_type::first()  = std::move(other.first());
  base_type::second() = std::move(other.second());

  return (*this);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T1, typename T2>
void bit::stl::compressed_pair<T1,T2>::swap( compressed_pair& other )
{
  using std::swap;

  swap( base_type::first(), other.first() );
  swap( base_type::second(), other.second() );
}


//----------------------------------------------------------------------------
// Non-member Functions
//----------------------------------------------------------------------------

template<typename T1, typename T2>
void bit::stl::swap( compressed_pair<T1,T2>& lhs, compressed_pair<T1,T2>& rhs )
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------

template<typename T1, typename T2>
constexpr bool bit::stl::operator==( const compressed_pair<T1,T2>& lhs,
                                     const compressed_pair<T1,T2>& rhs )
{
  return lhs.first() == rhs.first() && lhs.second() == rhs.second();
}

template<typename T1, typename T2>
constexpr bool bit::stl::operator!=( const compressed_pair<T1,T2>& lhs,
                                     const compressed_pair<T1,T2>& rhs )
{
  return !(lhs==rhs);
}

template<typename T1, typename T2>
constexpr bool bit::stl::operator<( const compressed_pair<T1,T2>& lhs,
                                    const compressed_pair<T1,T2>& rhs )
{
  return (lhs.first()==rhs.first())
         ? lhs.second() < rhs.second()
         : lhs.first() < rhs.first();
}

template<typename T1, typename T2>
constexpr bool bit::stl::operator<=( const compressed_pair<T1,T2>& lhs,
                                     const compressed_pair<T1,T2>& rhs )
{
  return (rhs<lhs);
}

template<typename T1, typename T2>
constexpr bool bit::stl::operator>( const compressed_pair<T1,T2>& lhs,
                                    const compressed_pair<T1,T2>& rhs )
{
  return !(rhs<lhs);
}

template<typename T1, typename T2>
constexpr bool bit::stl::operator>=( const compressed_pair<T1,T2>& lhs,
                                     const compressed_pair<T1,T2>& rhs )
{
  return !(lhs<rhs);
}

//------------------------------------------------------------------------

template<typename T1, typename T2>
constexpr bit::stl::compressed_pair<std::decay_t<T1>,std::decay_t<T2>>
  bit::stl::make_compressed_pair( T1&& x, T2&& y )
{
  return {std::forward<T1>(x),std::forward<T2>(y)};
}

#endif /* BIT_STL_UTILITIES_DETAIL_UTILITY_COMPRESSED_PAIR_INL */
