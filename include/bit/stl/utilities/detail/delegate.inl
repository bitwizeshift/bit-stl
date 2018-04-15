#ifndef BIT_STL_UTILITIES_DETAIL_DELEGATE_INL
#define BIT_STL_UTILITIES_DETAIL_DELEGATE_INL

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

template<typename R, typename ... Types>
constexpr bit::stl::delegate<R(Types...)>::delegate()
  noexcept
  : m_delegate_stub(nullptr,nullptr)
{

}

//-----------------------------------------------------------------------------
// Function Binding
//-----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<bit::stl::function_pointer<R(Types...)> Function>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind()
  noexcept
{
  const auto callback = [](void*, Types...args )
  {
    return invoke( Function, std::forward<Types>(args)... );
  };
  m_delegate_stub.first  = nullptr;
  m_delegate_stub.second = callback;
}

//-----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<typename C, bit::stl::member_function_pointer<C,R(Types...)> MemberFunction>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind( C& instance )
  noexcept
{
  const auto callback = [](void* ptr, Types...args )
  {
    return invoke( MemberFunction, static_cast<C*>(ptr), std::forward<Types>(args)... );
  };
  m_delegate_stub.first  = static_cast<void*>( std::addressof(instance) );
  m_delegate_stub.second = callback;
}

//-----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<typename C, bit::stl::member_function_pointer<const C,R(Types...)> MemberFunction>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind( const C& instance )
  noexcept
{
  cbind<C,MemberFunction>( instance );
}

template<typename R, typename ... Types>
template<typename C, bit::stl::member_function_pointer<const C,R(Types...)> MemberFunction>
inline constexpr void
  bit::stl::delegate<R(Types...)>::cbind( const C& instance )
  noexcept
{
  const auto callback = [](void* ptr, Types...args )
  {
    return invoke( MemberFunction, static_cast<const C*>(ptr), std::forward<Types>(args)... );
  };
  m_delegate_stub.first  = static_cast<void*>( const_cast<C*>( std::addressof(instance) ) ); // needed for const
  m_delegate_stub.second = callback;
}

//----------------------------------------------------------------------------
// Queries
//----------------------------------------------------------------------------

template<typename R, typename ... Types>
inline constexpr bool
  bit::stl::delegate<R(Types...)>::is_bound()
  const noexcept
{
  return m_delegate_stub.second != nullptr;
}

template<typename R, typename...Types>
inline constexpr bit::stl::delegate<R(Types...)>::operator bool()
  const noexcept
{
  return m_delegate_stub.second != nullptr;
}

//----------------------------------------------------------------------------
// Invocation
//----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<typename...Args,typename>
inline constexpr typename bit::stl::delegate<R(Types...)>::return_type
  bit::stl::delegate<R(Types...)>::operator()( Args&&... args )
  const
{
  BIT_ASSERT( m_delegate_stub.second != nullptr,
              "delegate::operator(): cannot invoke unbound delegate");

  return m_delegate_stub.second( m_delegate_stub.first, std::forward<Args>(args)... );
}

template<typename Fn>
inline bool bit::stl::operator==(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
  noexcept
{
  return lhs.m_delegate_stub == rhs.m_delegate_stub;
}

template<typename Fn>
inline bool bit::stl::operator!=(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
  noexcept
{
  return !(lhs==rhs);
}

template<typename Fn>
inline bool bit::stl::operator<(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
  noexcept
{
  return lhs.m_delegate_stub < rhs.m_delegate_stub;
}

template<typename Fn>
inline bool bit::stl::operator>(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
  noexcept
{
  return (rhs < lhs);
}

template<typename Fn>
inline bool bit::stl::operator<=(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
  noexcept
{
  return !(rhs < lhs);
}

template<typename Fn>
inline bool bit::stl::operator>=(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
  noexcept
{
  return !(lhs < rhs);
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename Fn>
inline bit::stl::hash_t bit::stl::hash_value( const delegate<Fn>& fn )
  noexcept
{
  return hash_values( fn.m_delegate_stub.first, fn.m_delegate_stub.second );
}


#endif /* BIT_STL_UTILITIES_DETAIL_DELEGATE_INL */
