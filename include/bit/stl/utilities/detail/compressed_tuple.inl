#ifndef BIT_STL_UTILITIES_DETAIL_COMPRESSED_TUPLE_INL
#define BIT_STL_UTILITIES_DETAIL_COMPRESSED_TUPLE_INL

//=============================================================================
// compressed_tuple_storage<Idx,T,true>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T>
template<typename Tuple, std::size_t...Idxs>
inline constexpr bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::compressed_tuple_storage( std::piecewise_construct_t,
                              Tuple&& tuple,
                              std::index_sequence<Idxs...> )
  : T( adl_get<Idxs>( std::forward<Tuple>(tuple) )... )
{

}

template<std::size_t Idx, typename T>
template<typename...Args>
inline constexpr bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::compressed_tuple_storage( in_place_t,
                              Args&&...args )
  : T( std::forward<Args>(args)... )
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T>
inline constexpr T& bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::do_get( size_constant<Idx> ) &
{
  return static_cast<T&>(*this);
}

template<std::size_t Idx, typename T>
inline constexpr const T& bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::do_get( size_constant<Idx> ) const &
{
  return static_cast<const T&>(*this);
}

template<std::size_t Idx, typename T>
inline constexpr T&& bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::do_get( size_constant<Idx> ) &&
{
  return static_cast<T&&>(*this);
}

template<std::size_t Idx, typename T>
inline constexpr const T&& bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::do_get( size_constant<Idx> ) const &&
{
  return static_cast<const T&&>(*this);
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T>
template<typename U>
inline void bit::stl::detail::compressed_tuple_storage<Idx,T,true>
  ::do_assign( size_constant<Idx>, U&& val )
{
  static_cast<T&>(*this) = std::forward<U>(val);
}

//=============================================================================
// compressed_tuple_storage<Idx,T,false>
//=============================================================================

template<std::size_t Idx, typename T>
template<typename Tuple, std::size_t...Idxs>
inline constexpr bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::compressed_tuple_storage( std::piecewise_construct_t,
                              Tuple&& tuple,
                              std::index_sequence<Idxs...> )
    : m_current( adl_get<Idxs>( std::forward<Tuple>(tuple) )... )
{

}

template<std::size_t Idx, typename T>
template<typename...Args>
inline constexpr bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::compressed_tuple_storage( in_place_t,
                              Args&&...args )
  : m_current( std::forward<Args>(args)... )
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T>
inline constexpr T& bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::do_get( size_constant<Idx> ) &
{
  return static_cast<T&>(m_current);
}

template<std::size_t Idx, typename T>
inline constexpr const T& bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::do_get( size_constant<Idx> ) const &
{
  return static_cast<const T&>(m_current);
}

template<std::size_t Idx, typename T>
inline constexpr T&& bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::do_get( size_constant<Idx> ) &&
{
  return static_cast<T&&>(m_current);
}

template<std::size_t Idx, typename T>
inline constexpr const T&& bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::do_get( size_constant<Idx> ) const &&
{
  return static_cast<const T&&>(m_current);
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T>
template<typename U>
inline void bit::stl::detail::compressed_tuple_storage<Idx,T,false>
  ::do_assign( size_constant<Idx>, U&& val )
{
  m_current = std::forward<U>(val);
}

//=============================================================================
// compressed_tuple_impl<Idx,T0,Ts...>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T0, typename...Ts>
template<typename Arg0, typename...Args>
inline constexpr bit::stl::detail::compressed_tuple_impl<Idx,T0,Ts...>
  ::compressed_tuple_impl( in_place_t,
                           Arg0&& arg0, Args&&...args )
  : storage_type( in_place, std::forward<Arg0>(arg0) ),
    base_type( in_place, std::forward<Args>(args)... )
{

}

template<std::size_t Idx, typename T0, typename...Ts>
template<typename Tuple0, typename...Tuples>
inline constexpr bit::stl::detail::compressed_tuple_impl<Idx,T0,Ts...>
  ::compressed_tuple_impl( std::piecewise_construct_t,
                           Tuple0&& tuple0, Tuples&&...tuples )
  : storage_type( std::piecewise_construct, std::forward<Tuple0>(tuple0), std::make_index_sequence<std::tuple_size<Tuple0>::value>{} ),
    base_type( std::piecewise_construct, std::forward<Tuples>(tuples)... )
{

}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<std::size_t Idx, typename T0, typename...Ts>
inline constexpr void bit::stl::detail::compressed_tuple_impl<Idx,T0,Ts...>
  ::swap( compressed_tuple_impl& other )
  noexcept
{
  using std::swap;

  auto& lhs = static_cast<storage_type&>(*this).get( size_constant<Idx>{} );
  auto& rhs = static_cast<storage_type&>(other).get( size_constant<Idx>{} );

  swap( lhs, rhs );

  static_cast<base_type&>(*this).swap( static_cast<base_type&>(other) );
}

template<std::size_t Idx, typename T0, typename...Ts>
template<typename Arg0, typename...Args>
inline void bit::stl::detail::compressed_tuple_impl<Idx,T0,Ts...>
  ::assign( Arg0&& arg0, Args&&...args )
{
  static_cast<storage_type&>(*this).do_assign( size_constant<Idx>{}, std::forward<Arg0>(arg0) );

  base_type::assign( std::forward<Args>(args)... );
}

//=============================================================================
// compressed_tuple_impl<Idx>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline constexpr bit::stl::detail::compressed_tuple_impl<Idx>
  ::compressed_tuple_impl( in_place_t )
{

}

template<std::size_t Idx>
inline constexpr bit::stl::detail::compressed_tuple_impl<Idx>
  ::compressed_tuple_impl( std::piecewise_construct_t )
{

}

//-----------------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline void bit::stl::detail::compressed_tuple_impl<Idx>
  ::do_get( size_constant<Idx> )
  noexcept
{
  // nothing to get
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<std::size_t Idx>
inline constexpr void bit::stl::detail::compressed_tuple_impl<Idx>
  ::swap( compressed_tuple_impl& )
  noexcept
{
  // nothing to swap
}

template<std::size_t Idx>
inline void bit::stl::detail::compressed_tuple_impl<Idx>
  ::assign()
  noexcept
{
  // nothing to assign
}

//=============================================================================
// compressed_tuple
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors / Assignment
//-----------------------------------------------------------------------------

// (2)
template<typename...Types>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( const Types&...args )
  : base_type( in_place, std::piecewise_construct, args... )
{

}

// (3)
template<typename...Types>
template<typename...UTypes>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( UTypes&&...args )
  : base_type( in_place, std::forward<UTypes>(args)... )
{

}

// (4)
template<typename...Types>
template<typename...UTypes>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( const compressed_tuple<UTypes...>& other )
  : compressed_tuple( std::make_index_sequence<sizeof...(UTypes)>{}, other )
{

}

// (5)
template<typename...Types>
template<typename...UTypes>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( compressed_tuple<UTypes...>&& other )
  : compressed_tuple( std::make_index_sequence<sizeof...(UTypes)>{}, std::move(other) )
{

}

// (6)
template<typename...Types>
template<typename U1, typename U2>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( const compressed_pair<U1,U2>& p )
  : base_type( in_place, p.fist(), p.second() )
{

}

// (7)
template<typename...Types>
template<typename U1, typename U2>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( compressed_pair<U1,U2>&& p )
  : base_type( in_place, p.first(), p.second()  )
{

}

// (10)
template<typename...Types>
template<typename...Tuples, typename>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( std::piecewise_construct_t, Tuples&&...tuples )
  : base_type( std::piecewise_construct, std::forward<Tuples>(tuples)... )
{

}

//-----------------------------------------------------------------------------

template<typename...Types>
template<typename... UTypes>
inline bit::stl::compressed_tuple<Types...>& bit::stl::compressed_tuple<Types...>
  ::operator=( const compressed_tuple<UTypes...>& other )
{

  assign_tuple(other, std::make_index_sequence<sizeof...(UTypes)>{} );

  return (*this);
}

template<typename...Types>
template<typename... UTypes>
inline bit::stl::compressed_tuple<Types...>& bit::stl::compressed_tuple<Types...>
  ::operator=( compressed_tuple<UTypes...>&& other )
{
  assign_tuple( std::move(other), std::make_index_sequence<sizeof...(UTypes)>{} );

  return (*this);
}

template<typename...Types>
template<typename U1, typename U2>
inline bit::stl::compressed_tuple<Types...>& bit::stl::compressed_tuple<Types...>
  ::operator=( const compressed_tuple<U1,U2>& p )
{
  assign_tuple( p, std::make_index_sequence<sizeof...(Types)>{} );

  return (*this);
}

template<typename...Types>
template<typename U1, typename U2>
inline bit::stl::compressed_tuple<Types...>& bit::stl::compressed_tuple<Types...>
  ::operator=( compressed_tuple<U1,U2>&& p )
{
  assign_tuple( std::move(p), std::make_index_sequence<sizeof...(Types)>{} );

  return (*this);
}


//-----------------------------------------------------------------------------
// Private Constructor
//-----------------------------------------------------------------------------

template<typename...Types>
template<typename Tuple, std::size_t...Idxs>
inline constexpr bit::stl::compressed_tuple<Types...>
  ::compressed_tuple( std::index_sequence<Idxs...>, Tuple&& tuple )
  : base_type( in_place, adl_get<Idxs>( std::forward<Tuple>(tuple) )... )
{

}

//-----------------------------------------------------------------------------
// Private Modifiers
//-----------------------------------------------------------------------------

template<typename...Types>
template<typename Tuple, std::size_t...Idxs>
inline void bit::stl::compressed_tuple<Types...>
  ::assign_tuple( std::index_sequence<Idxs...>, Tuple&& tuple )
{
  base_type::assign( adl_get<Idxs>( std::forward<Tuple>(tuple) )... );
}


//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

template<typename...Types>
inline constexpr void bit::stl::compressed_tuple<Types...>
  ::swap( compressed_tuple& other )
{
  base_type::swap( static_cast<base_type&>(other) );
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename...Types>
inline constexpr void bit::stl::swap( compressed_tuple<Types...>& lhs,
                                      compressed_tuple<Types...>& rhs )
{
  return lhs.swap(rhs);
}

//-----------------------------------------------------------------------------

template<typename...Args>
inline constexpr bit::stl::compressed_tuple<std::decay_t<Args>...>
  bit::stl::make_compressed_tuple( Args&&...args )
{
  using result_type = bit::stl::compressed_tuple<std::decay_t<Args>...>;
  return result_type{ std::forward<Args>(args)... };
}

//-----------------------------------------------------------------------------

template<std::size_t I, typename...UTypes>
inline constexpr bit::stl::tuple_element_t<I,bit::stl::compressed_tuple<UTypes...>>&
  bit::stl::get( compressed_tuple<UTypes...>& tuple )
  noexcept
{
  return tuple.do_get( size_constant<I>{} );
}

template<std::size_t I, typename...UTypes>
inline constexpr bit::stl::tuple_element_t<I,bit::stl::compressed_tuple<UTypes...>>&&
  bit::stl::get( compressed_tuple<UTypes...>&& tuple )
  noexcept
{
  return std::move(tuple).do_get( size_constant<I>{} );
}

template<std::size_t I, typename...UTypes>
inline constexpr const bit::stl::tuple_element_t<I,bit::stl::compressed_tuple<UTypes...>>&
  bit::stl::get( const compressed_tuple<UTypes...>& tuple )
  noexcept
{
  return tuple.do_get( size_constant<I>{} );
}

template<std::size_t I, typename...UTypes>
inline constexpr const bit::stl::tuple_element_t<I,bit::stl::compressed_tuple<UTypes...>>&&
  bit::stl::get( const compressed_tuple<UTypes...>&& tuple )
  noexcept
{
  return std::move(tuple).do_get( size_constant<I>{} );
}

//-----------------------------------------------------------------------------
// Comparison
//-----------------------------------------------------------------------------

template<typename...Types>
inline constexpr bool bit::stl::operator==( const compressed_tuple<Types...>& lhs,
                                            const compressed_tuple<Types...>& rhs )
  noexcept
{
//  lhs.compare(rhs,[](auto& l, auto& r)
//  {
//    return l == r;
//  });
  return true;
}

template<typename...Types>
inline constexpr bool bit::stl::operator!=( const compressed_tuple<Types...>& lhs,
                                            const compressed_tuple<Types...>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename...Types>
inline constexpr bool bit::stl::operator<( const compressed_tuple<Types...>& lhs,
                                           const compressed_tuple<Types...>& rhs )
  noexcept
{
//  lhs.compare(rhs,[](auto& l, auto& r)
//  {
//    return ((l < r) || !(r < l));
//  });
  return true;
}

template<typename...Types>
inline constexpr bool bit::stl::operator<=( const compressed_tuple<Types...>& lhs,
                                            const compressed_tuple<Types...>& rhs )
  noexcept
{
  return !(rhs < lhs);
}

template<typename...Types>
inline constexpr bool bit::stl::operator>( const compressed_tuple<Types...>& lhs,
                                           const compressed_tuple<Types...>& rhs )
  noexcept
{
  return (rhs<lhs);
}

template<typename...Types>
inline constexpr bool bit::stl::operator>=( const compressed_tuple<Types...>& lhs,
                                            const compressed_tuple<Types...>& rhs )
  noexcept
{
  return !(lhs<rhs);
}


//-----------------------------------------------------------------------------

//
//template<typename T, typename...Types>
//inline constexpr bit::stl::tuple_element<bit::stl::index_of_type<T,Types...>::value,bit::stl::compressed_tuple<Types...>>&
//  bit::stl::get( compressed_tuple<Types...>& tuple )
//  noexcept
//{
//  static constexpr auto index = index_of_type<T,Types...>::value;
//
//  return get<index>( tuple );
//}
//
//template<typename T, typename...Types>
//inline constexpr bit::stl::tuple_element<bit::stl::index_of_type<T,Types...>::value,bit::stl::compressed_tuple<Types...>>&&
//  bit::stl::get( compressed_tuple<Types...>&& tuple )
//  noexcept
//{
//  static constexpr auto index = index_of_type<T,Types...>::value;
//
//  return get<index>( std::move(tuple) );
//}
//
//template<typename T, typename...Types>
//inline constexpr const bit::stl::tuple_element<bit::stl::index_of_type<T,Types...>::value,bit::stl::compressed_tuple<Types...>>&
//  bit::stl::get( const compressed_tuple<Types...>& tuple )
//  noexcept
//{
//  static constexpr auto index = index_of_type<T,Types...>::value;
//
//  return get<index>( tuple );
//}
//
//template<typename T, typename...Types>
//inline constexpr const bit::stl::tuple_element<bit::stl::index_of_type<T,Types...>::value,bit::stl::compressed_tuple<Types...>>&&
//  bit::stl::get( const compressed_tuple<Types...>&& tuple )
//  noexcept
//{
//  static constexpr auto index = index_of_type<T,Types...>::value;
//
//  return get<index>( std::move(tuple) );
//}

#endif /* BIT_STL_UTILITIES_DETAIL_COMPRESSED_TUPLE_INL */
