#ifndef BIT_STL_UTILITIES_DETAIL_DELEGATE_INL
#define BIT_STL_UTILITIES_DETAIL_DELEGATE_INL

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename R, typename ... Types>
constexpr bit::stl::delegate<R(Types...)>::delegate()
  noexcept
  : m_delegate_stub(nullptr,nullptr)
{

}

//----------------------------------------------------------------------------
// Function Binding
//----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<R (*function)(Types...)>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind()
  noexcept
{
  const auto callback = [](void*, Types...args )
  {
    return function(std::forward<Types>(args)...);
  };
  m_delegate_stub.first  = nullptr;
  m_delegate_stub.second = +callback;
}

//----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<typename C, R (C::*member_function)(Types...)>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind( C* instance )
  noexcept
{
  const auto callback = [](void* ptr, Types...args )
  {
    return (static_cast<C*>(ptr)->*member_function)(std::forward<Types>(args)...);
  };
  m_delegate_stub.first  = instance;
  m_delegate_stub.second = +callback;
}

template<typename R, typename ... Types>
template<typename C, R (C::*member_function)(Types...)>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind( C& instance )
  noexcept
{
  bind<C,member_function>( std::addressof(instance) );
}

//----------------------------------------------------------------------------

template<typename R, typename ... Types>
template<typename C, R (C::*member_function)(Types...) const>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind( const C* instance )
  noexcept
{
  cbind<C,member_function>( instance );
}

template<typename R, typename ... Types>
template<typename C, R (C::*member_function)(Types...) const>
inline constexpr void
  bit::stl::delegate<R(Types...)>::bind( const C& instance )
  noexcept
{
  cbind<C,member_function>( std::addressof(instance) );
}

template<typename R, typename ... Types>
template<typename C, R (C::*member_function)(Types...) const>
inline constexpr void
  bit::stl::delegate<R(Types...)>::cbind( const C* instance )
  noexcept
{
  const auto callback = [](void* ptr, Types...args )
  {
    return (static_cast<const C*>(ptr)->*member_function)(std::forward<Types>(args)...);
  };
  m_delegate_stub.first  = const_cast<C*>(instance); // needed for const
  m_delegate_stub.second = +callback;
}

template<typename R, typename ... Types>
template<typename C, R (C::*member_function)(Types...) const>
inline constexpr void
  bit::stl::delegate<R(Types...)>::cbind( const C& instance )
  noexcept
{
  cbind<C,member_function>( std::addressof(instance) );
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
  bit::stl::delegate<R(Types...)>::invoke( Args&&... args )
  const
{
  BIT_ASSERT( m_delegate_stub.second != nullptr, "delegate::invoke: cannot invoke unbound delegate");

  return m_delegate_stub.second( m_delegate_stub.first, std::forward<Args>(args)... );
}

template<typename R, typename ... Types>
template<typename...Args,typename>
inline constexpr typename bit::stl::delegate<R(Types...)>::return_type
  bit::stl::delegate<R(Types...)>::operator()( Args&&... args )
  const
{
  BIT_ASSERT( m_delegate_stub.second != nullptr, "delegate::operator(): cannot invoke unbound delegate");

  return m_delegate_stub.second( m_delegate_stub.first, std::forward<Args>(args)... );
}

template<typename Fn>
inline bool bit::stl::operator==(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
{
  return lhs.m_delegate_stub == rhs.m_delegate_stub;
}

template<typename Fn>
inline bool bit::stl::operator!=(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
{
  return !(lhs==rhs);
}

template<typename Fn>
inline bool bit::stl::operator<(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
{
  return lhs.m_delegate_stub < rhs.m_delegate_stub;
}

template<typename Fn>
inline bool bit::stl::operator>(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
{
  return (rhs < lhs);
}

template<typename Fn>
inline bool bit::stl::operator<=(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
{
  return !(rhs < lhs);
}

template<typename Fn>
inline bool bit::stl::operator>=(const delegate<Fn>& lhs, const delegate<Fn>& rhs)
{
  return !(lhs < rhs);
}

//----------------------------------------------------------------------------
// Make Utilities
//----------------------------------------------------------------------------

//template<typename Sig, bit::stl::function_t<Sig> function>
//bit::stl::delegate<Sig> bit::stl::make_delegate()
//  noexcept
//{
//  auto result = delegate<Sig>();
//  return result.bind<function>();
//}
//
//template<typename T, typename Sig, bit::stl::member_function_t<T,Sig> member_function>
//bit::stl::delegate<Sig> bit::stl::make_delegate( T& instance )
//  noexcept
//{
//  auto result = delegate<Sig>();
//  return result.bind<member_function>( instance );
//}
//
//template<typename T, typename Sig, bit::stl::member_function_t<T,Sig> member_function>
//bit::stl::delegate<Sig> bit::stl::make_delegate( T* instance )
//  noexcept
//{
//  auto result = delegate<Sig>();
//  return result.bind<member_function>( instance );
//}

#endif /* BIT_STL_UTILITIES_DETAIL_DELEGATE_INL */
