#ifndef BIT_STL_DETAIL_VARIANT_INL
#define BIT_STL_DETAIL_VARIANT_INL

//----------------------------------------------------------------------------
// Constructors / Assignment
//----------------------------------------------------------------------------

template<typename...Types>
constexpr bit::stl::variant<Types...>
  ::variant( block_unless_t<is_default_constructible,variant_ctor> )
  : base_type( in_place<0> )
{

}

template<typename...Types>
bit::stl::variant<Types...>::variant( block_unless_t<is_copy_constructible,const variant&> other )
{
  runtime_emplace( other.index(), other.m_union );
}

template<typename...Types>
bit::stl::variant<Types...>::variant( block_unless_t<is_move_constructible,variant&&> other )
{
  runtime_emplace( other.index(), std::move(other.m_union) );
}

template<typename...Types>
template<typename T>
constexpr bit::stl::variant<Types...>::variant( T&& t, std::enable_if_t<is_convertible<T>>* )
  : base_type( in_place<detail::conversion_index_v<T,variant>>, std::forward<T>(t) )
{

}

template<typename...Types>
template<typename T, typename...Args, std::enable_if_t<std::is_constructible<T,Args...>::value>*>
constexpr bit::stl::variant<Types...>::variant( in_place_type_t<T>, Args&&... args )
  : base_type( in_place<detail::index_from<T>::value>, std::forward<Args>(args)... )
{

}

template<typename...Types>
template<typename T, typename U, typename...Args, std::enable_if_t<std::is_constructible<T,std::initializer_list<U>,Args...>::value>*>
constexpr bit::stl::variant<Types...>::variant( in_place_type_t<T>,
                                                std::initializer_list<U> il, Args&&... args )
  : base_type( in_place<detail::index_from<T>::value>, il, std::forward<Args>(args)... )
{

}

template<typename...Types>
template<std::size_t I, typename...Args, std::enable_if_t<(I<sizeof...(Types)) && std::is_constructible<bit::stl::variant_alternative_t<I,bit::stl::variant<Types...>>,Args...>::value>*>
constexpr bit::stl::variant<Types...>::variant( in_place_index_t<I>, Args&&... args )
  : base_type( in_place<I>, std::forward<Args>(args)... )
{

}

template<typename...Types>
template<std::size_t I, typename U, typename... Args, std::enable_if_t<(I<sizeof...(Types)) && std::is_constructible<bit::stl::variant_alternative_t<I,bit::stl::variant<Types...>>,std::initializer_list<U>,Args...>::value>*>
constexpr bit::stl::variant<Types...>::variant( in_place_index_t<I>,
                                                std::initializer_list<U> il,
                                                Args&&... args )
  : base_type( in_place<I>, il, std::forward<Args>(args)... )
{

}

//----------------------------------------------------------------------------

template<typename...Types>
bit::stl::variant<Types...>&
  bit::stl::variant<Types...>::operator=( block_unless_t<is_copy_assignable,const variant&> rhs)
{
  if( rhs.index() == variant_npos ) {
    base_type::destruct();
  } else if( index() == rhs.index() ) {
    runtime_assign(rhs.index(),rhs.m_union);
  } else { // TODO: This should call operator=( variant(rhs) )
    runtime_emplace( rhs.index(), rhs.m_union );
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename...Types>
bit::stl::variant<Types...>&
  bit::stl::variant<Types...>::operator=( block_unless_t<is_move_assignable,variant&&> rhs)
{
  if( rhs.index() == variant_npos ) {
    base_type::destruct();
  } else if( index() == rhs.index() ) {
    runtime_assign( rhs.index(), std::move(rhs.m_union) );
  } else {
    runtime_emplace( rhs.index(), std::move(rhs.m_union) );
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename...Types>
template<typename T, typename>
bit::stl::variant<Types...>& bit::stl::variant<Types...>::operator=(T&& t)
{
  static constexpr auto index = detail::conversion_index<T,variant>::value;

  using T_j = variant_alternative_t<index,variant>;

  if( index == index() ) {
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
constexpr std::size_t bit::stl::variant<Types...>::index()
  const noexcept
{
  return base_type::m_index;
}

template<typename...Types>
constexpr bool bit::stl::variant<Types...>::valueless_by_exception()
  const noexcept
{
  return base_type::m_index == variant_npos;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename...Types>
template<typename T, typename...Args>
T& bit::stl::variant<Types...>::emplace( Args&&... args )
{
  using index = detail::index_from<T,Types...>;

  return emplace<index::value>( std::forward<Args>(args)... );
}

template<typename...Types>
template<typename T, typename U, typename...Args>
T& bit::stl::variant<Types...>::emplace( std::initializer_list<U> il,
                                         Args&&... args )
{
  using index = detail::index_from<T,Types...>;

  return emplace<index::value>( il, std::forward<Args>(args)... );
}

template<typename...Types>
template<std::size_t I, typename... Args>
bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::emplace( Args&&... args )
{
  static_assert(I<sizeof...(Types), "");

  base_type::destruct();
  auto& result = static_emplace<I>( in_place<I>, base_type::m_union, std::forward<Args>(args)... );
  base_type::m_index = I;

  return result;
}

template<typename...Types>
template<std::size_t I, typename U, typename... Args>
bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::emplace( std::initializer_list<U> il,
                                        Args&&... args )
{
  static_assert(I<sizeof...(Types), "");

  base_type::destruct();
  auto& result = static_emplace<I>( in_place<I>, base_type::m_union, std::forward<Args>(args)... );
  base_type::m_index = I;

  return result;
}

template<typename...Types>
void bit::stl::variant<Types...>::swap( variant& rhs )
{

}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename...Types>
template<typename VariantUnion>
void bit::stl::variant<Types...>::runtime_assign( std::size_t index,
                                                  VariantUnion&& source )
{
  runtime_assign_impl( index, base_type::m_union, std::forward<VariantUnion>(source) );
}

template<typename...Types>
template<typename VariantUnion>
void bit::stl::variant<Types...>
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
void bit::stl::variant<Types...>
  ::runtime_assign_impl( std::size_t current,
                         VariantUnion& dest,
                         VariantUnion&& source,
                         std::enable_if_t<!detail::variant_union_has_next<std::decay_t<VariantUnion>>::value>* )
{
  dest.current = std::move(source.current);
}

template<typename...Types>
template<typename VariantUnion>
void bit::stl::variant<Types...>
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
void bit::stl::variant<Types...>
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
void bit::stl::variant<Types...>::static_assign( T&& value )
{
  static_assign( in_place<I>, base_type::m_union, std::forward<T>(value) );
}

template<typename...Types>
template<typename VariantUnion, typename T>
void bit::stl::variant<Types...>
  ::static_assign( in_place_index_t<std::size_t(-1)>, VariantUnion&, T&& )
{
  // avoid instantiation issues
}

template<typename...Types>
template<std::size_t I, typename VariantUnion, typename T>
void bit::stl::variant<Types...>::static_assign( in_place_index_t<I>,
                                                 VariantUnion& dest,
                                                 T&& value )
{
  static_assign( in_place<I-1>, dest.next, std::forward<T>(value) );
}

template<typename...Types>
template<typename VariantUnion, typename T>
void bit::stl::variant<Types...>
  ::static_assign( in_place_index_t<0>, VariantUnion& dest, T&& value )
{
  dest.current = std::forward<T>(value);
}

//----------------------------------------------------------------------------

template<typename...Types>
template<typename VariantUnion>
void bit::stl::variant<Types...>::runtime_emplace( std::size_t index,
                                                   VariantUnion&& source )
{
  base_type::destruct();
  runtime_emplace_impl( index, base_type::m_union, std::forward<VariantUnion>(source) );
  base_type::m_index = index;
}

template<typename...Types>
template<typename VariantUnion>
void bit::stl::variant<Types...>
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
void bit::stl::variant<Types...>
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
void bit::stl::variant<Types...>
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
void bit::stl::variant<Types...>
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
bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::static_emplace( in_place_index_t<N>,
                                               union_type<Ts...>& storage,
                                               Args&&...args )
{
  return static_emplace( in_place<N-1>,
                         storage.next, std::forward<Args>(args)... );
}

template<typename...Types>
template<std::size_t I, typename...Ts, typename...Args>
bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::variant<Types...>::static_emplace( in_place_index_t<0>,
                                               union_type<Ts...>& storage,
                                               Args&&...args )
{
  using type = variant_alternative_t<I, variant>;

  new (&storage.current) type( std::forward<Args>(args)... );
  return storage.current;
}

//----------------------------------------------------------------------------
// 23.7.5, value access
//----------------------------------------------------------------------------

template<typename T, typename...Types>
constexpr bool bit::stl::holds_alternative( const variant<Types...>& v )
  noexcept
{
  return detail::index_from<T,Types...>::value == v.index();
}

//----------------------------------------------------------------------------

template<std::size_t I, typename...Types>
constexpr bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::get( variant<Types...>& )
{
  // TODO: implement
}

template<std::size_t I, typename...Types>
constexpr bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&&
  bit::stl::get( variant<Types...>&& )
{
  // TODO: implement
}

template<std::size_t I, typename...Types>
constexpr const bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&
  bit::stl::get( const variant<Types...>& )
{
  // TODO: implement
}

template<std::size_t I, typename...Types>
constexpr const bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>&&
  bit::stl::get( const variant<Types...>&& )
{
  // TODO: implement
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
  if( !pv ) return nullptr;
  if( I != pv->index() ) return nullptr;

  return &get<I>(*pv);
}

template<std::size_t I, typename...Types>
constexpr std::add_pointer_t<const bit::stl::variant_alternative_t<I, bit::stl::variant<Types...>>>
  bit::stl::get_if( const variant<Types...>* pv )
  noexcept
{
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

#endif /* BIT_STL_DETAIL_VARIANT_INL */
