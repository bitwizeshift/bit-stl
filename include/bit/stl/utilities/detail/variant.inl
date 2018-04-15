#ifndef BIT_STL_UTILITIES_DETAIL_VARIANT_INL
#define BIT_STL_UTILITIES_DETAIL_VARIANT_INL

//----------------------------------------------------------------------------
// Constructors / Assignment
//----------------------------------------------------------------------------

template<typename...Types>
inline constexpr bit::stl::variant<Types...>
  ::variant( enable_overload_if_t<is_default_constructible,variant_ctor> )
  noexcept(std::is_nothrow_default_constructible<T0>::value)
  : base_type( in_place_index<0> )
{

}

template<typename...Types>
inline bit::stl::variant<Types...>
  ::variant( enable_overload_if_t<is_copy_constructible,const variant&> other )
  noexcept( bit::stl::conjunction<std::is_nothrow_copy_constructible<Types>...>::value )
{
  runtime_emplace( other.index(), other.m_union );
}

template<typename...Types>
inline bit::stl::variant<Types...>
  ::variant( enable_overload_if_t<is_move_constructible,variant&&> other )
  noexcept( bit::stl::conjunction<std::is_nothrow_move_constructible<Types>...>::value )
{
  runtime_emplace( other.index(), std::move(other.m_union) );
}

template<typename...Types>
template<typename T, typename>
inline constexpr bit::stl::variant<Types...>::variant( T&& t )
  noexcept( std::is_nothrow_constructible<typename bit::stl::variant<Types...>::template T_j<T>,T>::value )
  : base_type( in_place_index<detail::conversion_index_v<T,variant>>, std::forward<T>(t) )
{

}

template<typename...Types>
template<typename T, typename...Args, typename>
inline constexpr bit::stl::variant<Types...>
  ::variant( in_place_type_t<T>, Args&&... args )
  : base_type( in_place_index<detail::index_from<T,Types...>::value>, std::forward<Args>(args)... )
{

}

template<typename...Types>
template<typename T, typename U, typename...Args, typename>
inline constexpr bit::stl::variant<Types...>
  ::variant( in_place_type_t<T>, std::initializer_list<U> il, Args&&... args )
  : base_type( in_place_index<detail::index_from<T,Types...>::value>, il, std::forward<Args>(args)... )
{

}

template<typename...Types>
template<std::size_t I, typename...Args, typename>
inline constexpr bit::stl::variant<Types...>
  ::variant( in_place_index_t<I>, Args&&...args )
  : base_type( in_place_index<I>, std::forward<Args>(args)... )
{

}

template<typename...Types>
template<std::size_t I, typename U, typename... Args, typename>
inline constexpr bit::stl::variant<Types...>
  ::variant( in_place_index_t<I>, std::initializer_list<U> il, Args&&...args )
  : base_type( in_place_index<I>, il, std::forward<Args>(args)... )
{

}

//----------------------------------------------------------------------------

template<typename...Types>
inline bit::stl::variant<Types...>&
  bit::stl::variant<Types...>::operator=( enable_overload_if_t<is_copy_assignable,const variant&> other )
{
  if( other.valueless_by_exception() ) {
    base_type::destruct();
  } else if( index() == other.index() ) {
    runtime_assign( other.index(),other.m_union );
  } else {
    this->operator=(variant(other));
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename...Types>
inline bit::stl::variant<Types...>&
  bit::stl::variant<Types...>::operator=( enable_overload_if_t<is_move_assignable,variant&&> other )
    noexcept( bit::stl::conjunction<std::is_nothrow_move_constructible<Types>...,
                                    std::is_nothrow_move_assignable<Types>...>::value)
{
  if( other.valueless_by_exception() ) {
    base_type::destruct();
  } else if( index() == other.index() ) {
    runtime_assign( other.index(), std::move(other.m_union) );
  } else {
    runtime_emplace( other.index(), std::move(other.m_union) );
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename...Types>
template<typename T, typename>
inline bit::stl::variant<Types...>&
  bit::stl::variant<Types...>::operator=(T&& t)
  noexcept( std::is_nothrow_assignable<typename bit::stl::variant<Types...>::template T_j<T>,T>::value &&
            std::is_nothrow_constructible<typename bit::stl::variant<Types...>::template T_j<T>,T>::value )
{
  static constexpr auto index = detail::conversion_index<T,variant>::value;

  using T_j = variant_alternative_t<index,variant>;

  if( index == this->index() ) {
    static_assign<index>( std::forward<T>(t) );
  } else if (std::is_nothrow_constructible<T_j, T>::value ||
             !std::is_nothrow_move_constructible<T_j>::value ) {
    emplace<index>( std::forward<T>(t) );
  } else {
    this->operator=(variant(std::forward<T>(t)));
  }

  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename...Types>
inline constexpr std::size_t bit::stl::variant<Types...>::index()
  const noexcept
{
  return base_type::m_index;
}

template<typename...Types>
inline constexpr bool bit::stl::variant<Types...>::valueless_by_exception()
  const noexcept
{
  return base_type::m_index == variant_npos;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename...Types>
template<typename T, typename...Args, typename>
inline T& bit::stl::variant<Types...>::emplace( Args&&...args )
{
  using index = detail::index_from<T,Types...>;

  return emplace<index::value>( std::forward<Args>(args)... );
}

template<typename...Types>
template<typename T, typename U, typename...Args, typename>
inline T& bit::stl::variant<Types...>::emplace( std::initializer_list<U> il,
                                                Args&&...args )
{
  using index = detail::index_from<T,Types...>;

  return emplace<index::value>( il, std::forward<Args>(args)... );
}

template<typename...Types>
template<std::size_t I, typename... Args, typename>
inline bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::emplace( Args&&... args )
{
  static_assert(I<sizeof...(Types), "");

  base_type::destruct();
  auto& result = static_emplace<I>( in_place_index<I>, base_type::m_union, std::forward<Args>(args)... );
  base_type::m_index = I;

  return result;
}

template<typename...Types>
template<std::size_t I, typename U, typename... Args, typename>
inline bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::emplace( std::initializer_list<U> il,
                                        Args&&... args )
{
  static_assert(I<sizeof...(Types), "");

  base_type::destruct();
  auto& result = static_emplace<I>( in_place_index<I>, base_type::m_union, il, std::forward<Args>(args)... );
  base_type::m_index = I;

  return result;
}

template<typename...Types>
inline void bit::stl::variant<Types...>::swap( variant& rhs )
{
  // Do nothing if both types are valueless by exception
  if( valueless_by_exception() && rhs.valueless_by_exception() ) {
    return;
  }

  // If indices match, call swap
  if( index() == rhs.index() ) {
    base_type::swap( static_cast<base_type&>(rhs) );
  } else {
    variant tmp = std::move(*this);
    *this = std::move(rhs);
    rhs = std::move(tmp);
  }
}


template<typename...Types>
template<std::size_t I>
inline constexpr bit::stl::variant_alternative_t<I,bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::get( in_place_index_t<I> )
  noexcept
{
  return base_type::get( in_place_index<I> );
}

template<typename...Types>
template<std::size_t I>
inline constexpr const bit::stl::variant_alternative_t<I,bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::get( in_place_index_t<I> )
  const noexcept
{
  return base_type::get( in_place_index<I> );
}
//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_assign( std::size_t index,
                    VariantUnion&& source )
{
  runtime_assign_impl( index, base_type::m_union, std::forward<VariantUnion>(source) );
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_assign_impl( std::size_t current,
                         VariantUnion& dest,
                         VariantUnion&& source,
                         std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  if( current == 0 ) {
    dest.current = std::move(source.current);
    return;
  }
  runtime_assign_impl( current-1, dest.next, std::move(source.next) );
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_assign_impl( std::size_t current,
                         VariantUnion& dest,
                         VariantUnion&& source,
                         std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  dest.current = std::move(source.current);
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_assign_impl( std::size_t current,
                         VariantUnion& dest,
                         const VariantUnion& source,
                         std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  if( current == 0 ) {
    dest.current = source.current;
    return;
  }
  runtime_assign_impl( current-1, dest.next, source.next );
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_assign_impl( std::size_t current,
                         VariantUnion& dest,
                         const VariantUnion& source,
                         std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  dest.current = source.current;
}

//----------------------------------------------------------------------------

template<typename...Types>
template<std::size_t I, typename T>
inline void bit::stl::variant<Types...>::static_assign( T&& value )
{
  static_assign( in_place_index<I>, base_type::m_union, std::forward<T>(value) );
}

template<typename...Types>
template<typename VariantUnion, typename T>
inline void bit::stl::variant<Types...>
  ::static_assign( in_place_index_t<std::size_t(-1)>, VariantUnion&, T&& )
{
  // avoid instantiation issues
}

template<typename...Types>
template<std::size_t I, typename VariantUnion, typename T>
inline void bit::stl::variant<Types...>
  ::static_assign( in_place_index_t<I>, VariantUnion& dest, T&& value )
{
  static_assign( in_place_index<I-1>, dest.next, std::forward<T>(value) );
}

template<typename...Types>
template<typename VariantUnion, typename T>
inline void bit::stl::variant<Types...>
  ::static_assign( in_place_index_t<0>, VariantUnion& dest, T&& value )
{
  dest.current = std::forward<T>(value);
}

//----------------------------------------------------------------------------

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_emplace( std::size_t index, VariantUnion&& source )
{
  base_type::destruct();
  runtime_emplace_impl( index, base_type::m_union, std::forward<VariantUnion>(source) );
  base_type::m_index = index;
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_emplace_impl( std::size_t current,
                          VariantUnion& dest,
                          VariantUnion&& source,
                          std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  using type = decltype(dest.current);

  if( current == 0 ) {
    new (&dest.current) type( std::move(source.current) );
    return;
  }
  runtime_emplace_impl( current-1, dest.next, std::move(source.next) );
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_emplace_impl( std::size_t current,
                          VariantUnion& dest,
                          VariantUnion&& source,
                          std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  using type = decltype(dest.current);

  new (&dest.current) type( std::move(source.current) );
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_emplace_impl( std::size_t current,
                          VariantUnion& dest,
                          const VariantUnion& source,
                          std::enable_if_t<detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  using type = decltype(dest.current);

  if( current == 0 ) {
    new (&dest.current) type( source.current );
    return;
  }
  runtime_emplace_impl( current-1, dest.next, source.next );
}

template<typename...Types>
template<typename VariantUnion>
inline void bit::stl::variant<Types...>
  ::runtime_emplace_impl( std::size_t current,
                          VariantUnion& dest,
                          const VariantUnion& source,
                          std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  using type = decltype(dest.current);

  new (&dest.current) type( source.current );
}

//----------------------------------------------------------------------------

template<typename...Types>
template<std::size_t I, std::size_t N, typename...Ts, typename...Args>
inline bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::static_emplace( in_place_index_t<N>,
                                               union_type<Ts...>& storage,
                                               Args&&...args )
{
  return static_emplace<I>( in_place_index<N-1>,
                            storage.next, std::forward<Args>(args)... );
}

template<typename...Types>
template<std::size_t I, typename...Ts, typename...Args>
inline bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::static_emplace( in_place_index_t<0>,
                                               union_type<Ts...>& storage,
                                               Args&&...args )
{
  using type = variant_alternative_t<I, variant>;

  new (&storage.current) type( std::forward<Args>(args)... );
  return storage.current;
}

//-----------------------------------------------------------------------------
// Comparisons
//-----------------------------------------------------------------------------

namespace bit { namespace stl { namespace detail {

  template<std::size_t N, typename...Types, typename Compare>
  inline constexpr bool variant_compare( in_place_index_t<N>,
                                         const variant<Types...>& lhs,
                                         const variant<Types...>& rhs,
                                         Compare&& compare )
    noexcept
  {
    if( N == lhs.index() ) {
      return std::forward<Compare>(compare)( get<N>(lhs), get<N>(rhs) );
    }
    return variant_compare( in_place_index<(N-1)>, lhs, rhs, std::forward<Compare>(compare) );
  }

  template<typename...Types, typename Compare>
  inline constexpr bool variant_compare( in_place_index_t<0>,
                                         const variant<Types...>& lhs,
                                         const variant<Types...>& rhs,
                                         Compare&& compare )
    noexcept
  {
    return std::forward<Compare>(compare)( get<0>(lhs), get<0>(rhs) );
  }

} } } // namespace bit::stl::detail

template<typename...Types>
inline constexpr bool bit::stl::operator==( const variant<Types...>& lhs,
                                            const variant<Types...>& rhs )
  noexcept
{
  if( lhs.index() != rhs.index() ) return false;
  if( lhs.valueless_by_exception() ) return true;

  auto tag = in_place_index<(sizeof...(Types)-1)>;
  return detail::variant_compare( tag, lhs, rhs, std::equal_to<>{});
}

template<typename...Types>
inline constexpr bool bit::stl::operator!=( const variant<Types...>& lhs,
                                            const variant<Types...>& rhs )
  noexcept
{
  if( lhs.index() != rhs.index() ) return true;
  if( lhs.valueless_by_exception() ) return false;

  auto tag = in_place_index<(sizeof...(Types)-1)>;
  return detail::variant_compare( tag, lhs, rhs, std::not_equal_to<>{});
}

template<typename...Types>
inline constexpr bool bit::stl::operator<( const variant<Types...>& lhs,
                                           const variant<Types...>& rhs )
  noexcept
{
  if( rhs.valueless_by_exception() ) return false;
  if( lhs.valueless_by_exception() ) return true;
  if( lhs.index() < rhs.index() ) return true;
  if( lhs.index() > rhs.index() ) return false;

  auto tag = in_place_index<(sizeof...(Types)-1)>;
  return detail::variant_compare( tag, lhs, rhs, std::less<>{});
}

template<typename...Types>
inline constexpr bool bit::stl::operator>( const variant<Types...>& lhs,
                                           const variant<Types...>& rhs )
  noexcept
{
  if( lhs.valueless_by_exception() ) return false;
  if( rhs.valueless_by_exception() ) return true;
  if( lhs.index() > rhs.index() ) return true;
  if( lhs.index() < rhs.index() ) return false;

  auto tag = in_place_index<(sizeof...(Types)-1)>;
  return detail::variant_compare( tag, lhs, rhs, std::greater<>{});
}

template<typename...Types>
inline constexpr bool bit::stl::operator<=( const variant<Types...>& lhs,
                                            const variant<Types...>& rhs )
  noexcept
{
  if( lhs.valueless_by_exception() ) return true;
  if( rhs.valueless_by_exception() ) return false;
  if( lhs.index() < rhs.index() ) return true;
  if( lhs.index() > rhs.index() ) return false;

  auto tag = in_place_index<(sizeof...(Types)-1)>;
  return detail::variant_compare( tag, lhs, rhs, std::less_equal<>{});
}

template<typename...Types>
inline constexpr bool bit::stl::operator>=( const variant<Types...>& lhs,
                                            const variant<Types...>& rhs )
  noexcept
{
  if( rhs.valueless_by_exception() ) return true;
  if( lhs.valueless_by_exception() ) return false;
  if( lhs.index() > rhs.index() ) return true;
  if( lhs.index() < rhs.index() ) return false;

  auto tag = in_place_index<(sizeof...(Types)-1)>;
  return detail::variant_compare( tag, lhs, rhs, std::greater_equal<>{});
}

//=============================================================================
// 23.7.5 : value access
//=============================================================================

template<typename T, typename...Types>
constexpr bool bit::stl::holds_alternative( const variant<Types...>& v )
  noexcept
{
  return detail::index_from<T,Types...>::value == v.index();
}

//----------------------------------------------------------------------------

template<std::size_t I, typename...Types>
constexpr bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::get( variant<Types...>& v )
{
  static_assert( (I < sizeof...(Types)), "I is not a valid index into the variant" );

  if( v.index() != I ) throw bad_variant_access{};
  return v.get( in_place_index<I> );
}

template<std::size_t I, typename...Types>
constexpr bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&&
  bit::stl::get( variant<Types...>&& v )
{
  static_assert( (I < sizeof...(Types)), "I is not a valid index into the variant" );

  return std::move( get<I>( v ) );
}

template<std::size_t I, typename...Types>
constexpr const bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::get( const variant<Types...>& v )
{
  static_assert( (I < sizeof...(Types)), "I is not a valid index into the variant" );

  if( v.index() != I ) throw bad_variant_access{};
  return v.get( in_place_index<I> );
}

template<std::size_t I, typename...Types>
constexpr const bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&&
  bit::stl::get( const variant<Types...>&& v )
{
  static_assert( (I < sizeof...(Types)), "I is not a valid index into the variant" );

  return std::move( get<I>( v ) );
}

//----------------------------------------------------------------------------

template<typename T, typename...Types>
constexpr T& bit::stl::get( variant<Types...>& v )
{
  return get<detail::index_from<T,Types...>::value>(v);
}

template<typename T, typename...Types>
constexpr T&& bit::stl::get( variant<Types...>&& v )
{
  return get<detail::index_from<T,Types...>::value>(v);
}

template<typename T, typename...Types>
constexpr const T& bit::stl::get( const variant<Types...>& v )
{
  return get<detail::index_from<T,Types...>::value>(v);
}

template<typename T, typename...Types>
constexpr const T&& bit::stl::get( const variant<Types...>&& v )
{
  return get<detail::index_from<T,Types...>::value>(v);
}

//----------------------------------------------------------------------------

template<std::size_t I, typename...Types>
constexpr std::add_pointer_t<bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>>
  bit::stl::get_if( variant<Types...>* pv )
  noexcept
{
  static_assert( (I < sizeof...(Types)), "I is not a valid index into the variant" );

  if( !pv ) return nullptr;
  if( I != pv->index() ) return nullptr;

  return &get<I>(*pv);
}

template<std::size_t I, typename...Types>
constexpr std::add_pointer_t<const bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>>
  bit::stl::get_if( const variant<Types...>* pv )
  noexcept
{
  static_assert( (I < sizeof...(Types)), "I is not a valid index into the variant" );

  if( !pv ) return nullptr;
  if( I != pv->index() ) return nullptr;

  return &get<I>(*pv);
}

template<typename T, typename...Types>
constexpr std::add_pointer_t<T> bit::stl::get_if( variant<Types...>* pv )
  noexcept
{
  return get_if<detail::index_from<T,Types...>::value>( pv );
}

template<typename T, typename...Types>
constexpr std::add_pointer_t<const T> bit::stl::get_if( const variant<Types...>* pv )
  noexcept
{
  return get_if<detail::index_from<T,Types...>::value>( pv );
}

//-----------------------------------------------------------------------------

namespace bit { namespace stl { namespace detail {

  template<std::size_t N, typename...Types>
  inline constexpr hash_t hash_variant_impl( in_place_index_t<N>,
                                             const variant<Types...>& val )
  {
    if( val.index() == N ) {
      return hash_value( get<N>( val ) );
    }
    return hash_variant_impl( in_place_index<(N-1)>, val );
  }

  template<typename...Types>
  inline constexpr hash_t hash_variant_impl( in_place_index_t<0>,
                                             const variant<Types...>& val )
  {
    // Must be 0 by here; what else can it be?
    assert( val.index() == 0 );

    return hash_value( get<0>( val ) );
  }

} } } // namespace bit::stl::detail

template<typename...Types>
inline constexpr bit::stl::hash_t bit::stl::hash_value( const variant<Types...>& val )
  noexcept
{
  if( val.valueless_by_exception() ) return static_cast<hash_t>(0xDEADBEEF);

  // hash from last value to first value
  return detail::hash_variant_impl( in_place_index<(sizeof...(Types)-1)>, val );
}

#endif /* BIT_STL_UTILITIES_DETAIL_VARIANT_INL */
